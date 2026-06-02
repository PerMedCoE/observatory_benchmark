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
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
from pathlib import Path
import yaml

def main() -> None:
    """
    Plot the data contained in the given `yaml` files:
    - Over time: position of the cell
    - Over time: velocity of the cell
    """
    parser = argparse.ArgumentParser(description="Parse XML files.")
    parser.add_argument( "-p", "--prefix", help="Filename prefix.", default="")
    parser.add_argument( "-f", "--files", nargs="+", type=Path, required=True, help="List of YAML files that contain the data to plot.")
    
    #Get arguments
    args = parser.parse_args()

    #Get yaml files
    files = args.files

    #Get prefix
    prefix = args.prefix

    #Parse all files
    for fname in files:
        print( f'Current file: {fname}' )
        with open( fname, "r" ) as f:
            data = yaml.safe_load( f )

        #Get relevant data
        t = np.array( data["t"]["values"] ) #[s]
        x_exp = np.array( data['x_explicit']['values'] ) #[m]
        v_exp = np.array( data['v_explicit']['values'] ) #[m/s]
        x_imp = np.array( data['x_implicit']['values'] ) #[m]
        v_imp = np.array( data['v_implicit']['values'] ) #[m/s]

        #Plot position over time
        plt.figure( 10 )
        #plt.plot( t, x_exp/1e-6, linestyle='None', marker='x', color='red', label='Underdampep' )
        plt.plot( t, x_imp/1e-6, linestyle='None', marker='x', color='green', label='Overdamped' )

        #Plot velocity over time
        plt.figure( 20 )
        #plt.plot( t, v_exp*60/1e-6, linestyle='None', marker='x', color='red', label='Underdampep' )
        plt.plot( t, v_imp/1e-6, linestyle='None', marker='x', color='green', label='Overdamped' )
        
    #Finalize figures
    plt.figure( 10 )
    plt.xlabel( 't [s]' )
    plt.ylabel( 'x [µm]' )
    ax = plt.gca()
    ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    fig = plt.gcf()
    fig.tight_layout()
    fig.set_size_inches(8, 6)
    #plt.legend(loc='lower right', frameon=False)
    plt.savefig( f'{prefix}x_vs_t.png', bbox_inches='tight', dpi = 600 )
    plt.close()

    plt.figure( 20 )
    plt.xlabel( 't [s]' )
    plt.ylabel( 'v [µm / s]' )
    ax = plt.gca()
    ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    fig = plt.gcf()
    fig.tight_layout()
    fig.set_size_inches(8, 6)
    #plt.legend(loc='upper right', frameon=False)
    plt.savefig( f'{prefix}v_vs_t.png', bbox_inches='tight', dpi = 600 )
    plt.close()

if __name__ == '__main__':
    main()
