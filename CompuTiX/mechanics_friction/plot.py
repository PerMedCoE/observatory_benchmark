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
        x = np.array( data['x']['values'] ) #[m]
        v = np.array( data['v']['values'] ) #[m/s]

        #Plot position over time
        plt.figure( 10 )
        plt.plot( t / 60., x / 1e-6, linestyle='None', marker='x', color='red' )

        #Plot velocity over time
        plt.figure( 20 )
        plt.plot( t / 60., v * 60 / 1e-6, linestyle='None', marker='x', color='green' )
        
    #Finalize figures
    plt.figure( 10 )
    plt.xlabel( 't [min]' )
    plt.ylabel( 'x [µm]' )
    ax = plt.gca()
    ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    fig = plt.gcf()
    fig.tight_layout()
    fig.set_size_inches(8, 6)
    plt.savefig( f'{prefix}x_vs_t.png', bbox_inches='tight', dpi = 600 )
    plt.close()

    plt.figure( 20 )
    plt.xlabel( 't [min]' )
    plt.ylabel( 'v [µm / min]' )
    ax = plt.gca()
    ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
    fig = plt.gcf()
    fig.tight_layout()
    fig.set_size_inches(8, 6)
    plt.savefig( f'{prefix}v_vs_t.png', bbox_inches='tight', dpi = 600 )
    plt.close()

if __name__ == '__main__':
    main()
