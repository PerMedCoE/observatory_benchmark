import argparse
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
from pathlib import Path

from AnalyticalSolution import AnalyticalSolution

def main() -> None:
    """
    Plot the analytical solution:
    - Over time: concentration at center of the box
    - Over time: concentration over the whole box
    - At stationnary state, 2D plot in plane (x,y,0)
    """
    parser = argparse.ArgumentParser(description="Plot analytical solution. Note: the 2D stationary state case can run for quite some time due to the high number of concentration computations to perform.")
    parser.add_argument("-p", "--prefix", type=str, default="", help="Filename prefix.")
    parser.add_argument("-D", "--diffusion", type=float, default=2000., help="Diffusion coefficient [um^2/min].")
    parser.add_argument("--rate", type=float, default=2., help="Uptake rate [1/min].")
    parser.add_argument("-T", "--tend", type=float, default=3., help="End time [min].")
    parser.add_argument("--count-modes", type=int, default=25, help="Number of modes to consider per dimension [1].")
    parser.add_argument("--sample-dt", type=float, default=0.1, help="Sampling time step for exported values [min].")
    parser.add_argument("--sample-tend", type=float, default=10.0, help="End time for exported values [min].")
    parser.add_argument("--output-data", type=Path, default=None, help="Optional output file for sampled analytical values.")
    parser.add_argument("--without-center", action='store_true', help="Option to disable plot of concentration at center of domain (0,0,0) over time.")
    parser.add_argument("--without-average",action='store_true', help="Option to disable plot of average concentration over time.")
    parser.add_argument("--without-stationary-2D", action='store_true', help="Option to disable plot 2D stationary state on (x,y) plane at z=0.")

    #Get arguments
    args = parser.parse_args()

    #Get prefix for figures' names
    prefix = args.prefix

    #Parameters
    D = args.diffusion * 1e-12 / 60. #[m^2/s]
    c_0 = 10. * 1e-3 #[mol/m^3]
    L = 240. * 1e-6 #[m]
    rate = args.rate / 60. #[1/s]
    x_central = np.array( ( 0.,0.,0. ) ) #[m]

    #Number of modes to consider
    count_modes=args.count_modes

    #Initialize class with analytical solution helper methods
    sol = AnalyticalSolution( c_0=c_0, D=D, L=L, rate=rate, count_modes=count_modes )

    #Sample analytical values on a regular time grid and optionally export them.
    sample_times_min = np.arange(0.0, args.sample_tend + 0.5 * args.sample_dt, args.sample_dt)
    sample_times_s = sample_times_min * 60.0
    c_expected_central_sampled = sol.concentration( x=x_central, t=sample_times_s )
    U_expected_domain_sampled = sol.amount( x=x_central,
                                            t=sample_times_s,
                                            x_first=-0.5 * L,
                                            x_second=0.5 * L,
                                            y_first=-0.5 * L,
                                            y_second=0.5 * L,
                                            z_first=-0.5 * L,
                                            z_second=0.5 * L )
    c_expected_domain_sampled = U_expected_domain_sampled / L**3

    if args.output_data is not None:
        output_path = args.output_data
        np.savetxt(
            output_path,
            np.column_stack((sample_times_min, 1e3 * c_expected_central_sampled, 1e3 * c_expected_domain_sampled)),
            delimiter=",",
            header="time_min,center_concentration_uM,average_concentration_uM",
            comments="",
        )

    #Plot concentration at central position over time
    if(not args.without_center):
        #Compute analytical solution for central voxel
        time_steps = np.linspace(0., args.tend * 60., 100) #Convert to seconds to have everything in SI
        c_expected_central = sol.concentration( x=x_central, t=time_steps )

        #Plot concentration over central voxel
        plt.figure( 10 )
        plt.plot( time_steps / 60., 1e3 * c_expected_central, color='black' )
        plt.xlabel( 't [min]' )
        plt.ylabel( 'c [uM]' )
        ax = plt.gca()
        ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        fig = plt.gcf()
        fig.tight_layout()
        fig.set_size_inches(2, 1.5)
        plt.savefig( f'{prefix}center_of_box.png', bbox_inches='tight', dpi = 600 )
        plt.close()

    #Plot concentration over domain over time
    if(not args.without_average):
        #Compute total amount on the whole domain
        time_steps = np.linspace(0., args.tend * 60., 100) #Convert to seconds to have everything in SI
        U_expected_domain = sol.amount( x=x_central,\
                                        t=time_steps,\
                                        x_first=-0.5 * L,\
                                        x_second=0.5 * L,\
                                        y_first=-0.5 * L,\
                                        y_second=0.5 * L,\
                                        z_first=-0.5 * L,\
                                        z_second=0.5 * L )

        c_expected_domain = U_expected_domain / L**3

        #Plot concentration over whole domain
        plt.figure( 20 )
        plt.plot( time_steps / 60., 1e3 * c_expected_domain, color='black' )
        plt.xlabel( 't [min]' )
        plt.ylabel( r'$\\bar{c}$ [uM]' )
        ax = plt.gca()
        ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        fig = plt.gcf()
        fig.tight_layout()
        fig.set_size_inches(2, 1.5)
        plt.savefig( f'{prefix}whole_box.png', bbox_inches='tight', dpi = 600 )
        plt.close()

    #Plot stationnary state in plane (x,y) at z=0
    if(not args.without_stationary_2D):
        #Analytical solution 2D profile
        x = np.linspace( -0.5 * L, 0.5*L, num=50 )
        y = np.linspace( -0.5 * L, 0.5*L, num=50 )
        z= 0.
        c_2D_expected = np.zeros( [ len(x), len(y) ] )
        for i, x_i in enumerate( x ):
            for j, y_i in enumerate( y ):
                c_2D_expected[i,j] = sol.concentration( x=[x_i,y_i,z],\
                                                        t=60000. )

        #Plot expected - 2D profile at stationnary state
        plt.figure( 30 )
        plt.pcolormesh(1e6 * x, 1e6 * y, 1e3 * c_2D_expected, shading='auto', cmap='viridis')
        plt.xlabel( 'x [um]' )
        plt.ylabel( 'y [um]' )
        ax = plt.gca()
        ax.xaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        ax.yaxis.set_major_formatter(ticker.ScalarFormatter(useOffset=False))
        plt.colorbar(label='c [uM]')
        fig = plt.gcf()
        fig.tight_layout()
        fig.set_size_inches(2, 1.5)
        plt.savefig( f'{prefix}2D_stationnary_state.png', bbox_inches='tight', dpi = 600 )
        plt.close()

if __name__ == '__main__':
    main()
