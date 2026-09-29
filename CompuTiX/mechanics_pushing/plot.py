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

    #Get global DoFs
    with open( files[0], "r" ) as f:
        data = yaml.safe_load( f )
    t = data["t"]["values"] #[s]
    x = data['Cells']['values']['x']['values'] #[m]

    #Parse all files
    for fname in files:
        print( f'Current file: {fname}' )
        with open( fname, "r" ) as f:
            data = yaml.safe_load( f )

        #Get relevant data
        t = np.array( data["t"]["values"] ) #[s]
        x = np.array( data['Cells']['values']['x']['values'] ) #[m]

        #Compute absolute distance between spheres' centers
        d = np.abs(x[:, 0] - x[:, 1])

        #Plot distance over time
        plt.plot( t / 60., d / 1e-6, linestyle='None', marker='x', color='red' )
        
    #Finalize figures
    plt.xlabel( 't [min]' )
    plt.ylabel( 'distance [µm]' )
    ax = plt.gca()
    ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    fig = plt.gcf()
    fig.tight_layout()
    fig.set_size_inches(8, 6)
    plt.savefig( f'{prefix}abs_distance.png', bbox_inches='tight', dpi = 600 )
    plt.close()

if __name__ == '__main__':
    main()
