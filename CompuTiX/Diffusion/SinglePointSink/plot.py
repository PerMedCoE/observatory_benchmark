import argparse
import itertools
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
from pathlib import Path
import yaml

from AnalyticalSolution import AnalyticalSolution

def float_to_latex(x: float, precision: int = 2) -> str:
    """
    Convert float to its string representation in latex format with scientific precision
    
    Parameters:
        x - the float to convert
        precision - the number of digits to consider

    Returns:
        The string representation in latex format of the given float
    """
    if x == 0:
        return '0'

    x = np.float64(x)  # ensure consistent type
    exponent = int(np.floor(np.log10(np.abs(x))))
    mantissa = x / (10 ** exponent)

    #Round and format mantissa
    mantissa = np.round(mantissa, decimals=precision)
    mantissa_str = f"{mantissa:.{precision}f}".rstrip('0').rstrip('.')

    return f"{mantissa_str} \\times 10^{{{exponent}}}"

def main() -> None:
    """
    Plot the data contained in the given `yaml` files:
    - Over time: total concentration vs analytical solution
    - At last time step (stationnary state), 2D plot in plane (x,y,0)
    """
    parser = argparse.ArgumentParser(description="Parse XML files.")
    parser.add_argument( "-p", "--prefix", default="", help="Filename prefix.")
    parser.add_argument( "-f", "--files", nargs="+", type=Path, required=True, help="List of YAML files that contain the data to plot.")
    parser.add_argument("--count-modes", type=int, default=25, help="Number of modes to consider per dimension [1].")
    parser.add_argument("--without-average",action='store_true', help="Option to disable plot of average concentration over time.")
    parser.add_argument("--without-stationary-2D", action='store_true', help="Option to disable plot 2D stationary state on (x,y) plane at z=0.")

    #Get arguments
    args = parser.parse_args()

    #Get yaml files
    files = args.files

    #Get prefix
    prefix = args.prefix

    #For plots
    colors = { 0.6 : 'orange',\
               0.06 : 'green',\
               0.006: 'red',\
               0.0006  : 'blue' }

    markers = { 3 : '<',\
                7 : 'x',\
                15 : 'v',\
                31 : 'o',\
                63 : '^',\
                127 : 'X'}

    #Get global DoFs
    with open( files[0], "r" ) as f:
        data = yaml.safe_load( f )


    D = data["D"]["values"] #[m^2/s]
    c_0 = data["c_0"]["values"] #[mol/m^3]
    L = data["L"]["values"] #[m]
    rate = data["lambda"]["values"] #[1/s]
    x_central = data["x_central"]["values"] #[m]
    x_cell = data["x_cell"]["values"] #[m]

    #Number of modes to consider
    count_modes=args.count_modes

    #Initialize class with analytical solution helper methods
    sol = AnalyticalSolution( c_0=c_0, D=D, L=L, rate=rate, x_cell=x_cell, count_modes=count_modes )
    time_steps = np.linspace(0., 600, 200)

    #Compute analytical solution - over domain over time
    if(not args.without_average):
        #Compute total amount on the whole domain
        U_expected_domain = sol.amount( x=x_central,\
                                        t=time_steps,\
                                        x_first=-0.5 * L,\
                                        x_second=0.5 * L,\
                                        y_first=-0.5 * L,\
                                        y_second=0.5 * L,\
                                        z_first=-0.5 * L,\
                                        z_second=0.5 * L )

        c_expected_domain = U_expected_domain / L**3

    #Compute analytical solution - stationnary state in plane (x,y) at z=0
    if(not args.without_stationary_2D):
        #Analytical solution 2D profile
        x_analytical = np.linspace( -0.5 * L, 0.5*L, num=50 )
        y_analytical = np.linspace( -0.5 * L, 0.5*L, num=50 )
        z= 0.
        c_2D_expected = np.zeros( [ len(x_analytical), len(y_analytical) ] )
        for i, x_i in enumerate( x_analytical ):
            for j, y_i in enumerate( y_analytical ):
                c_2D_expected[i,j] = sol.concentration( x=[x_i,y_i,z],\
                                                        t=60000. )

    #Parse all files
    processed_dt = set()
    for fname in files:
        print( f'Current file: {fname}' )
        with open( fname, "r" ) as f:
            data = yaml.safe_load( f )

        #Get relevant data
        dt = data["dt"]["values"] #[s]
        N = data["N"]["values"] #[1]
        t = np.array( data["time_series"]["values"]["t"]["values"] ) #[s]
        c_domain = np.array( data["time_series"]["values"]["c_domain"]["values"] ) #[mol/m^3]
        c_central = np.array( data["time_series"]["values"]["c_central"]["values"] ) #[mol/m^3]

        #Get current color
        color = colors[dt]

        #Get current marker
        marker = markers[N]

        #Plot concentration over domain over time
        if(not args.without_average):
            print(f'concentration whole box stationary [µM]: {1e3 * c_domain[-1]}')

            #Over time
            plt.figure( 20 )
            plt.plot( t / 60., 1e3 * c_domain, linestyle='None', marker=marker, color=color, label=r'$\Delta t = ' + float_to_latex( dt / 60. ) + '$ min' + f', N={N}')

            #Error at stationary state
            rel_error = abs( c_domain[-1] - c_expected_domain[-1] ) / abs( c_expected_domain[-1] )
            plt.figure( 200 )
            if( dt not in processed_dt ):
                plt.plot( N, 100. * rel_error, linestyle='None', marker='x', color=color, label=r'$\Delta t = ' + float_to_latex( dt / 60. ) + '$ min' )
            else:
                plt.plot( N, 100. * rel_error, linestyle='None', marker='x', color=color )

        #Plot stationnary state in plane (x,y) at z=0
        if(not args.without_stationary_2D):
            #Plot 2D concentration at last time step - stationary state
            x_all = data["last_snapshot"]["values"]["x"]["values"] #[m]
            c_stationary = data["last_snapshot"]["values"]["c"]["values"] #[mol/m^3]
            N_squared = N**2
            c_2D = np.zeros([N,N])
            x = np.zeros(N)
            y = np.zeros(N)
            for idx, x_i in enumerate(x_all) :
                i = int( idx / N_squared )
                r = idx % N_squared
                j = int( r / N )
                if( abs(x_i[2] ) <= 1e-6 ) :
                    c_2D[i,j] = c_stationary[idx]
                    x[i] = x_i[0]
                    y[j] = x_i[1]

            plt.figure( 30 )
            plt.pcolormesh(1e6 * x, 1e6 * y, 1e3 * c_2D, shading='auto', cmap='viridis' )
            plt.xlabel( 'x [µm]' )
            plt.ylabel( 'y [µm]' )
            ax = plt.gca()
            ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
            ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
            plt.colorbar(label='c [µM]')
            fig = plt.gcf()
            fig.tight_layout()
            fig.set_size_inches(8, 6)
            plt.savefig( f'{prefix}stationnary_state_dt-min-{dt/60.:.2e}_N-{N}.png', bbox_inches='tight', dpi = 600 )
            plt.close()

        #Add time step to set of processed time steps
        processed_dt.add( dt )

    #Add analytical solution to the plots and finalize plots
    #Plot concentration over domain over time
    if(not args.without_average):
        #Plot expected - concentration over the entire domain
        plt.figure( 20 )
        plt.plot( time_steps / 60., 1e3 * c_expected_domain, label='Expected', color='black' )
        plt.xlabel( 't [min]' )
        plt.ylabel( r'$\bar{c}$ [µM]' )
        ax = plt.gca()
        ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
        fig = plt.gcf()
        fig.tight_layout()
        fig.set_size_inches(8, 6)
        plt.savefig( f'{prefix}whole_box.png', bbox_inches='tight', dpi = 600 )
        plt.close()
        
        #Plot at stationary state - relative error over the entire domain
        plt.figure( 200 )
        plt.xlabel( 'N [1]' )
        plt.ylabel( r'$\delta \bar{c}$ [%]' )
        plt.xscale('log')
        ax = plt.gca()
        ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))
        fig = plt.gcf()
        fig.tight_layout()
        fig.set_size_inches(8, 6)
        plt.savefig( f'{prefix}whole_box_error_stationary_state.png', bbox_inches='tight', dpi = 600 )
        plt.close()

if __name__ == '__main__':
    main()
