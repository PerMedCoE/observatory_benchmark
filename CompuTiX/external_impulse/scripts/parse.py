__copyright__ = "Copyright (C) 2025 INRIA"
__license__ = """
    CompuTiX - computational library for tissue simulations.
    Source: https://gitlab.inria.fr/computix/computix
    Copyright (C) 2025 INRIA
    
    This file is part of CompuTiX.
    
    CompuTiX is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, version 3 of the License.
    
    CompuTiX is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.
    
    You should have received a copy of the GNU Affero General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
    """

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

    #Prepare empty lists to fill over time points saved
    t = [] #time in min
    x_exp = [] #positions in m
    v_exp = [] #velocities in m/s
    x_imp = [] #positions in m
    v_imp = [] #velocities in m/s
    for f in files:
        print( f'File: {f}' )
        #Load tree
        tree = etree.parse( f )

        #Get root
        root = tree.getroot()

        #Parse tree and skip "CompuTiX" root
        universe = parse_tree( root )[0]
        
        #Time
        t.append(float(universe["t"].values[0])) #[s]
 
        #Get first component of the relevant data
        spheres = universe["Spheres"]
        x_exp.append(float(spheres["x_explicit"].values[0][0])) #[m]
        v_exp.append(float(spheres["v_explicit"].values[0][0])) #[m/s]
        x_imp.append(float(spheres["x_implicit"].values[0][0])) #[m]
        v_imp.append(float(spheres["v_implicit"].values[0][0])) #[m/s]

    return {
        "F_loc": {
            "description": "External force applied to the sphere",
            "unit": spheres["F_loc"].unit,
            "value": float(spheres["F_loc"].values[0][0])
        },
        "gamma": {
            "description": "Friction coefficient between sphere and medium",
            "unit": spheres["gamma"].unit,
            "value": float(spheres["gamma"].values[0])
        },
        "t": {
            "description": "Times t",
            "unit": universe["t"].unit,
            "values": t
        },
        "x_explicit": {
            "description": "Positions of a first cell over time x(t), for explicit scheme",
            "unit": spheres["x_explicit"].unit,
            "values": x_exp
        },
        "v_explicit": {
            "description": "Velocities of a first cell over time v(t), for explicit scheme",
            "unit": spheres["v_explicit"].unit,
            "values": v_exp
        },
        "x_implicit": {
            "description": "Positions of a first cell over time x(t), for implicit scheme",
            "unit": spheres["x_implicit"].unit,
            "values": x_imp
        },
        "v_implicit": {
            "description": "Velocities of a first cell over time v(t), for implicit scheme",
            "unit": spheres["v_implicit"].unit,
            "values": v_imp
        },
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
        with open( d.with_suffix(".yaml" ), "w") as f:
            yaml.dump( data, f )

if __name__ == '__main__':
    main()

