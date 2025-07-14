import argparse
from pathlib import Path
import numpy as np
import xml.etree.ElementTree as etree
import yaml

from computix.utils.parse import parse_tree

def parse_data( input_dir: Path ) -> dict :
    """
    Parse the XML files in the given `input_dir`
    
    Parameters:
        input_dir - the path to the directory to process

    Returns:
        A dictionnary with the data extracted from the list of XML files in the given directory
    """
    print( f'Current_dir: {input_dir}' )

    #The files with the time series
    files = sorted( input_dir.glob( 'Universes_*.xml' ) )

    #The topology and positions should not change over the different file
    #Parse the initial one to get indexes corresponding to internal voxels
    #diffusion coefficient, length of domain, initial concentration,
    #uptake rate
    #Load tree using first file in list
    tree = etree.parse( files[0] )

    #Get root
    root = tree.getroot()

    #Parse tree and skip "CompuTiX" root
    universe = parse_tree( root )[0]

    #Get relevant data
    voxels = universe["Voxels"]

    #Get all voxel volumes in m^3 (in principle all voxels have the same one)
    V_voxel = voxels["V"].values[0]

    #Get internal voxels particle indices
    is_internal = np.logical_not( voxels["is_ghost"].values )
    internal_voxels = np.where( is_internal )

    #Get position of central voxel
    x_central = universe["x"].values[0] #[m]
    
    #Get space step
    dx = universe["dx"].values[0]
    
    #Find central voxel idx by looking through all voxels' positions
    x = voxels["x"].values

    #Find index which corresponds to central voxel
    for i, x_i in enumerate( x ):
        if np.all( np.isclose( x_i, x_central, atol=dx*1e-6) ):
            idx_central = i
            break;

    #Only keep the positions of internal voxels
    x = x[internal_voxels] #[m]

    #Get number of voxels
    count_voxels = len( x )

    #Total volume
    V = V_voxel * count_voxels

    #Prepare arrays to fill over time points saved
    count_outputs = len( files )
    t = np.zeros( count_outputs ) #time in s
    c = np.zeros( [ count_outputs, count_voxels ] ) #concentration in mol / m^3
    c_central = np.zeros( count_outputs ) #concentration in mol / m^3
    U = np.zeros( [ count_outputs, count_voxels ] ) #amount in mol
    U_central = np.zeros( count_outputs ) #amount in mol
    for n, f in enumerate( files ):
        print( f'File: {f}' )
        #Load tree
        tree = etree.parse( f )

        #Get root
        root = tree.getroot()

        #Parse tree and skip "CompuTiX" root
        universe = parse_tree( root )[0]

        #Time
        t[n] = universe["t"].values[0] #[s]

        #Get relevant data
        voxels = universe["Voxels"]
        c[n] = voxels["c"].values[internal_voxels]
        c_central[n] = voxels["c"].values[idx_central]
        U[n] = voxels["n"].values[internal_voxels]
        U_central[n] = voxels["n"].values[idx_central]

        if( U[n] < 0 ).any() :
            print( f'Warning: negative value at time {t_n} [s]: U = {U[n]} [mol] in file {f}' )

    U_domain = np.array( [ np.sum( U[n,:] ) for n,_ in enumerate( t ) ] )
    c_domain = U_domain / V

    return { "D" : { "description" : "Diffusion coefficient", "unit" : universe["D"].unit, "values" : universe["D"].values[0].tolist() },\
             "c_0" : { "description" : "Initial concentration","unit" : universe["c_0"].unit, "values" : universe["c_0"].values[0].tolist() },\
             "lambda" : { "description" : "Reaction rate","unit" : universe["lambda"].unit, "values" : universe["lambda"].values[0].tolist() },\
             "dt" : { "description" : "Time step", "unit" : universe["dt"].unit, "values" : universe["dt"].values[0].tolist() },\
             "L" : { "description" : "Box's length","unit" : universe["L"].unit, "values" : universe["L"].values[0].tolist() },\
             "V" : { "description" : "Box's volume", "unit": voxels["V"].unit , "values" : V.tolist() },\
             "dx" : { "description" : "Voxel's length", "unit" : universe["dx"].unit, "values" : dx.tolist() },\
             "V_voxel" : { "description" : "Voxel's volume", "unit" : voxels["V"].unit, "values" : V_voxel.tolist() },\
             "x_central" : { "description" : "Central Voxel's position", "unit" : universe["x"].unit, "values" : x_central.tolist() },\
             "N" : { "description" : "Number of voxel on one axis", "unit": "1", "values" : round( np.cbrt( count_voxels ) ) },\
             "time_series" : { "description" : "Time series of the system",\
                               "values" : { "t" : { "description" : "Time", "unit": universe["dt"].unit, "values" : t.tolist() },\
                                            "c_domain" : { "description" : "Concentration over full domain", "unit": voxels["c"].unit, "values" : c_domain.tolist() },\
                                            "n_domain" : { "description" : "Amount over full domain", "unit": voxels["n"].unit, "values" : U_domain.tolist() },\
                                            "c_central" : { "description" : "Concentration in central voxel", "unit": voxels["c"].unit, "values" : c_central.tolist() },\
                                            "n_central" : { "description" : "Amount in central voxel", "unit": voxels["n"].unit, "values" : U_central.tolist() } } },\
             "last_snapshot" : { "description" : "Last snapshot of the system",\
                          "values" : { "x" : { "description" : "Voxels' positions", "unit" : voxels["x"].unit, "values": x.tolist() },\
                                       "c" : { "description" : "Voxels' concentrations", "unit" : voxels["c"].unit, "values": c[-1].tolist() },\
                                       "n" : { "description" : "Voxels' amounts", "unit" : voxels["n"].unit, "values": U[-1].tolist() } } } }

def main() -> None:
    """
    Parse the list of directories given as argument and extract relevant data contained in the xml files as a dictionnary.
    The dictionnary is then saved as a `yaml` files (one per directory)
    The filenames are generated from the directory's name: if the directory is "/path/to/dir"
    then the corresponding `yaml` file will be `path/to/dir.yaml`.
    """
    parser = argparse.ArgumentParser(description="Parse series of XML files in a list of directories.")
    parser.add_argument( "-d", "--dirs", nargs="+", type=Path, required=True, help="List of directories that contain series of XML files to process.")

    #Get arguments
    args = parser.parse_args()

    #Parse all directories whith contain series of XML files
    for d in args.dirs:
        #Check directory given as argument is really a directory
        if not d.is_dir():
            raise argparse.ArgumentTypeError(f"{d} is not a valid directory.")

        #Parse the data
        data = parse_data( d )

        #Save it as yaml.
        with open( d.with_suffix(".yaml" ), "w") as f:
            yaml.dump( data, f )

if __name__ == '__main__':
    main()
