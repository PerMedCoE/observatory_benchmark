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

    #Parse the initial one to get indexes corresponding to the cell
    #Load tree using first file in list
    tree = etree.parse( files[0] )

    #Get root
    root = tree.getroot()

    #Parse tree
    simulation = parse_tree( root )[0]

    #Get universe
    universe = simulation["Universes"]

    #Get relevant data
    spheres = universe["Spheres"]

    #Get spheres indices
    spheres_idx = spheres.indices

    #Count number of spheres
    count_cells = len(spheres_idx)

    #Prepare arrays to fill over time points saved
    count_outputs = len( files )
    t = np.zeros( count_outputs ) #time in min
    x = np.zeros( [ count_outputs, count_cells] ) #positions in m
    for n, f in enumerate( files ):
        print( f'File: {f}' )
        #Load tree
        tree = etree.parse( f )

        #Get root
        root = tree.getroot()

        #Parse tree
        simulation = parse_tree( root )[0]

        #Get universe
        universe = simulation["Universes"]

        #Time
        t[n] = universe["t"].values[0] #[s]

        #Get first component of the positions
        spheres = universe["Spheres"]
        x[n] = spheres["x"].values[spheres_idx][:,0] #[m]
 
    return {    
        "t" : { "description" : "Time", "unit": universe["t"].unit, "values" : t.tolist() },
        "Cells" : { "description" : "Data related to cells", "values" : 
                   { "x" : { "description" : "Cells' positions", "unit" : spheres["x"].unit, "values": x.tolist() }, } }
         }

def main() -> None:
    """
    Parse the list of directories given as argument and extract relevant data contained in the xml files as a dictionary.
    The dictionary is then saved as a `yaml` files (one per directory)
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
        
        #Save it as yaml
        fname = d.name + ".yaml"
        with open( d.with_suffix(".yaml" ), "w") as f:
          yaml.dump( data, f )

if __name__ == '__main__':
    main()
