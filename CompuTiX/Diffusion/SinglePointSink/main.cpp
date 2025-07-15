//! \example Diffusion/BoxInitiallyEmpty/SingleCellPointSink/main.cpp
//! \section diffusion_box_initially_full_single_cell_point_sink Diffusion on a box initially full with single point sink
//!
//! \subsection diffusion_box_initially_full_single_cell_point_sink_problem_statement Problem statement
//!
//! This simulation illustrates diffusion of a species in a box with a single point sink
//! representing a cell with a constant uptake rate. The box is initially empty.
//! The equation to solve is then a reaction-diffusion equation with a homogeneous source term
//! \f{align*}
//! \partial_t c(\vec{x},t) - \nabla \cdot \left( D \nabla c(\vec{x},t) \right) &=
//! - \lambda_\text{cell} \delta_{\vec{x}_\text{cell}}( \vec{x} )  &\text{if}& \; \vec{x} \in \left(-\frac{L}{2}, \frac{L}{2} \right)^3
//! \\ c(\vec{x}) &= c_\text{BC} \;
//! &\text{if}& \; x,y,z = \pm \frac{L}{2}
//! \\ c(\vec{x},0) &= c_\text{BC}
//! \f}
//! with \f$c\f$ the concentration, \f$c_\text{BC}\f$ the concentration at the boundary,
//! \f$D\f$ the diffusion coefficient and \f$\lambda_\text{cell}\f$ the uptake rate of the single cell,
//! \f$\delta_{\vec{x}_\text{cell}}\f$ the Dirac's function at the cell's position \f$\vec{x}_\text{cell}\f$
//! and \f$L\f$ the length of the box.
//!
//! \image html Example_Diffusion_BoxInitiallyFull_CellsAtCenter_setup.png Figure: 2D slice of box with cells' at final time step. width=50%
//!
//! \subsection diffusion_box_initially_full_single_cell_point_sink_analytical solution Analytical solution
//!
//! The analytical solution is given as
//! \f{align*}
//!     c(\vec{x},t) &= c_\text{BC} - \lambda_\text{cell} \sum \limits _{ijk}^\infty \phi_{ijk}(\vec{x}) \phi_{ijk}(\vec{x}_\text{cell}) \frac{1 - \mathrm{e}^{-\lambda_{ijk}t}}{\lambda_{ijk}}
//! \\  \phi_{ijk}(x,y,z) &=  \left( \frac{2}{L} \right)^{\frac{3}{2}}\cos{\left( \frac{(2i+1) \pi x}{L} \right)} \cos{\left( \frac{(2j+1) \pi y}{L} \right)} \cos{\left(\frac{(2k+1) \pi z}{L} \right)}
//! \\  \lambda_{ijk} &= \left( (2i+1)^2+(2j+1)^2+(2k+1)^2 \right) \frac{\pi^2 D}{L^2}.
//! \f}
//!
//! \subsection diffusion_box_initially_full_single_cell_point_sink_finite_volume Finite volume scheme
//!
//! The physical domain is a cube of length \f$L\f$ and volume \f$V = L\times L \times L\f$.
//! The domain is then discretized regularly with cubes of length \f$a\f$.
//!
//! The equation is solved numerically using a finite volume approach which is described here after.
//! For a voxel \f$\alpha\f$, integrating on its volume \f$V_\alpha\f$,
//! \f[
//! \partial_t \int \limits_{V_\alpha} \mathrm{d}V \; c = \int \limits_{V_\alpha} \mathrm{d}V \; D \nabla^2 c
//!- \int \limits_{V_\alpha}\mathrm{d}V \lambda_\text{cell} \delta_{\vec{x}_\text{cell}}( \vec{x} ),
//! \f]
//! with \f$\mathbf{1}_{\alpha}(\vec{x}_\text{cell})\f$ is the indicator function
//! whose value is 0 if \f$\vec{x}_\text{cell}\f$ is not in \f$\alpha\f$ voxel and 1 otherwise.
//! This gives, considering \f$c_\alpha = \frac{n_\alpha}{V_\alpha}\f$, Gauss's theorem and integration of dirac functions,
//! \f[
//! \partial_t n_\alpha  = \oint \limits_{\partial V_\alpha} \mathrm{d}\vec{A} \cdot D \nabla c - \mathbf{1}_{\alpha}(\vec{x}_\text{cell}) \lambda_\text{cell}.
//! \f]
//! Then,
//! \f{align*}
//!    \partial_t n_\alpha &= \sum \limits_{\beta \in \text{Neigh}(\alpha)} A_{\alpha\beta}D
//!    \frac{ c_\beta - c_\alpha }{d_{\alpha\beta}} - \mathbf{1}_{\alpha}(\vec{x}_\text{cell}) \lambda_\text{cell}
//! \\ &= \frac{D}{a^2} \sum \limits_{\beta \in \text{Neigh}(\alpha)}
//!    \left( n_\beta - n_\alpha\right) - \mathbf{1}_{\alpha}(\vec{x}_\text{cell}) \lambda_\text{cell}
//! \f}
//! where the first sum is over the neighbouring voxels of \f$\alpha\f$
//! and with \f$d_{\alpha\beta} = a\f$ the distance between the centers of voxels \f$\alpha\f$ and \f$\beta\f$.
//!
//! Implicit scheme is given as
//! \f[
//! n_\alpha^{t+\Delta t}
//! -C_\text{Courant} \sum \limits_{\beta \in \text{Neigh}(\alpha)} \left( n_\beta^{t+\Delta t} - n_\alpha^{t+\Delta t} \right)
//! = n_\alpha^t - \Delta t \; \sum \limits _{l:\vec{x}_\text{cell} \in V_\alpha} \lambda_\text{cell}
//! \f]
//! with \f$C_\text{Courant} = \frac{ D \, \Delta t }{ a^2 }\f$ the Courant number.
//! This linear system can then be solved with conjugate gradient solver.
//!
//! Dirichlet boundary conditions are set by introducing ghost voxels (see figure below) with same volumes than internal ones and surrounding the box.
//! Those ghost voxels have constant concentration \f$c_\text{BC}\f$.
//!
//! \image html Example_Diffusion_BoxInitiallyFull_ghost_voxels.png Figure: 2D slice with ghost voxels representation. width=50%
//!
//! \subsection diffusion_box_initially_full_single_cell_point_sink_results Results
//!
//! The figures below display the concentration over time over the whole box or at its center.
//! As expected, the concentration decreases until it reaches a stationary state.
//! The minimum value is reached for the voxel at the center of the domain.
//! Different time steps and number of voxels are in the plot to verify numerical converge with
//! decreasing time step and voxel size.
//!
//! \image html Example_Diffusion_BoxInitiallyFull_Decay_center_of_box_over_time.png Figure: average concentration over the whole box over time. width=50%
//! \image html Example_Diffusion_BoxInitiallyFull_Decay_average_over_time.png Figure: concentration at center of the box over time. width=50%

#include <CompuTiX/Access/Modes.h>
#include <CompuTiX/Components/Actions/ExecutableBase.h>
#include <CompuTiX/Components/Collections/PairCollection.h>
#include <CompuTiX/Components/Collections/ParticleCollection.h>
#include <CompuTiX/Components/DegreesOfFreedom/DegreeOfFreedom.h>
#include <CompuTiX/Components/Parameters/Values/ComponentList.h>
#include <CompuTiX/Components/Parameters/Values/String.h>
#include <CompuTiX/Components/Parameters/Values/absolute_path.h>
#include <CompuTiX/Components/Random/MersenneTwister.h>
#include <CompuTiX/Components/tree_to_yaml.h>
#include <CompuTiX/Math/pow.h>
#include <CompuTiX/Math/relative_tolerance.h>
#include <CompuTiX/Particles/Particle.h>
#include <CompuTiX/Particles/ParticlesView.h>
#include <CompuTiX/Types/Public/Count.h>
#include <CompuTiX/Types/Public/Logical.h>
#include <CompuTiX/Types/Public/ParticleIndex.h>
#include <CompuTiX/Types/Public/Position.h>
#include <CompuTiX/Types/Public/Scalar.h>
#include <CompuTiX/Types/Public/Vector.h>

#include <cmath>
#include <cxxopts.hpp>
#include <random>
#include <stdexcept>

int main( int argc, char** argv )
{
    using namespace CompuTiX;
    using namespace Components;

    //Prepare description
    auto options = cxxopts::Options{ "simulation",
                                     "Diffusion in a 3D grid with a single cell representing a sink." };

    //Add options
    {
        using std::to_string;

        auto option_adder = options.add_options();
        option_adder( "h,help", "Print usage." );
        option_adder( "v,verbose", "Verbose print." );
        option_adder( "without-io", "Disable IO. Disables generation of VTP and save files." );
        option_adder( "t,run-time", "Maximal run time [s].", cxxopts::value< Types::Scalar >()->default_value( to_string( std::numeric_limits< Types::Scalar >::max() ) ) );
        option_adder( "T,sim-time", "Target simulation time [s].", cxxopts::value< Types::Scalar >()->default_value( "600." ) );
        option_adder( "dt", "Time step [s].", cxxopts::value< Types::Scalar >()->default_value( "0.6" ) );
        option_adder( "N,num-voxels", "Number of voxels in one dimension [1]."
                                      "Must be an odd value to guarantee that there is one voxel at the center of the domain.",
                      cxxopts::value< Types::Count >()->default_value( "9" ) );
        option_adder( "lambda", "Individual cell's uptake rate [mol/s].", cxxopts::value< Types::Scalar >()->default_value( "2.6666666666666673e-18" ) );
        option_adder( "output-dir", "Output directory.", cxxopts::value< std::string >()->default_value( "./" ) );
    }

    //Parse arguments
    const auto result = options.parse( argc, argv );

    if( result["h"].as< bool >() ) {
        std::cout << options.help();

        return 0;
    }

    // ---------------------------------------
    // Generate data layout
    // ---------------------------------------
    //Create top level collection
    auto universes = Collections::ParticleCollection::create( "Universes" );
    if( !universes ) {
        throw std::runtime_error( "Failed to initialize 'Universes'." );
    }

    //Prepare particle collection in universe
    auto cells = universes->add( Collections::ParticleCollection::create( "Cells" ) );
    auto voxels = universes->add( Collections::ParticleCollection::create( "Voxels" ) );
    voxels->add( Collections::ParticleCollection::create( "Ghost" ) );

    //contacts between voxels
    auto faces = universes->add( Collections::PairCollection::create( "Faces", voxels, voxels ) );
    //contacts between voxels and cells
    auto sinks = universes->add( Collections::PairCollection::create( "Voxels-Cells contacts", voxels, cells ) );

    //Prepare DoFs for Universes
    // - time management: current time (t), time step (dt), final time (t_end), current run time (t_elapsed), maximal run time (t_elapsed_max)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dt", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_end", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_elapsed", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_elapsed_max", SIUnits::second ) );

    // - for VTK writer: writer interval (output_interval), time of next output (next_output), current frame index (current_frame)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "output_interval", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "next_output", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Count >::create( "current_frame", SIUnits::dimensionless ) );

    // - CG iterations counter
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Count >::create( "CG_iterations", SIUnits::dimensionless ) );

    // - for float comparison: relative tolerance
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "relative_tolerance", SIUnits::dimensionless ) );

    // - for voxels-cells contacts: epsilon buffer (epsilon)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "epsilon", SIUnits::meter ) );

    // - physical properties: diffusion coefficient (D), cell uptake (lambda),
    //                        concentration at boundary voxel (c_0), amount at boundary voxel (n_0)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "D", ( SIUnits::meter ^ 2 ) / SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "lambda", SIUnits::mole / SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "c_0", SIUnits::mole / ( SIUnits::meter ^ 3 ) ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "n_0", SIUnits::mole ) );

    // - Geometry: domain's length (L),
    //             number of voxels in one coodinate (N),
    //             voxel's length (dx),
    //             voxel's length plus extra buffer (dx_plus_epsilon),
    //             voxel's length squared (dx_squared),
    //             center of domain (x)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "L", SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dx", SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dx_plus_epsilon", SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dx_squared", SIUnits::meter ^ 2 ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Count >::create( "N", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "x", SIUnits::meter ) );

    // - For flux computation: D / dx^2 (diffusion_rate)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "diffusion_rate", SIUnits::second ^ ( -1 ) ) );

    // - For diagonal part of matrix: 1 (one)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "one", SIUnits::dimensionless ) );

    // - Courant number and -Courant
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "Courant", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "minus_Courant", SIUnits::dimensionless ) );

    //Prepare DoFs for Cells
    // - Geometry: center (x)
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "x", SIUnits::meter ) );

    // - Contacts detection: bounding box (AABB_min and AABB_max)
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "AABB_min", SIUnits::meter ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "AABB_max", SIUnits::meter ) );

    //Prepare DoFs for Voxels
    // - Geometry: position (x), edge length (dx), volume (V)
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "x", SIUnits::meter ) );
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V", SIUnits::meter ^ 3 ) );

    // - Contacts detection: bounding box for voxels-cells contacts (AABB_min and AABB_max)
    //                       and voxels-voxels contact (AABB_min_faces and AABB_max_faces)
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "AABB_min", SIUnits::meter ) );
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "AABB_max", SIUnits::meter ) );
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "AABB_min_faces", SIUnits::meter ) );
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "AABB_max_faces", SIUnits::meter ) );

    // - Chemokinetics - concentration (c), amount (n), right hand side of reaction-diffusion equation (rhs)
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "c", SIUnits::mole / ( SIUnits::meter ^ 3 ) ) );
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "n", SIUnits::mole ) );
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "rhs", SIUnits::mole ) );

    // - Uptake from cells (uptake), uptake rate (uptake_rate)
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "uptake", SIUnits::mole ) );
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "uptake_rate", SIUnits::mole / SIUnits::second ) );

    // - For boundary conditions: is_ghost
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_ghost", SIUnits::no_unit ) );

    // - For diagonal part of matrix
    voxels->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "diagonal", SIUnits::dimensionless ) );

    //Prepare DoFs for Faces
    // - To build matrix system:
    faces->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "minus_Courant", SIUnits::dimensionless ) );
    // - For voxels-voxels contact detection: if the contact is for two voxels in corners (is_corner)
    //                                        distance between two voxels' centers (l)
    //                                        unit vector between two voxels' centers (t)
    faces->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_corner", SIUnits::no_unit ) );
    faces->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "l", SIUnits::meter ) );
    faces->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "t", SIUnits::dimensionless ) );

    // ---------------------------------------
    // Set particles' data
    // ---------------------------------------
    // - verbosity, without_io and maximal runtime
    const auto verbose = result["v"].as< bool >();
    const auto without_io = result["without-io"].as< bool >();
    const auto maximal_run_time = result["t"].as< Types::Scalar >(); //[s]

    // - Global parameters:
    //Final simulation time
    const auto t_end = result["T"].as< Types::Scalar >(); //[s]
    //Time step
    const auto dt = result["dt"].as< Types::Scalar >(); //[s]
    //Diffusion coefficient (2000µm^2/min)
    constexpr auto D = 2000. * 1e-12 / 60.; //[m^2/s]

    // - Geometry
    //Position of domain center
    const Types::Position x_center = Types::Position::Zero();
    //Length of domain in x direction (same for all three dimensions)
    constexpr auto L = 60e-6; //[m]
    //Total volume
    constexpr Types::Scalar V = Math::pow< 3 >( L ); //[m]
    //Number of voxels in one dimension (same for all three dimensions)
    const Types::Count N = result["N"].as< Types::Count >(); //[1]
    //Expect that N is odd so that there is one voxel located exactly at the center of the domain
    if( N % 2 != 1 ) {
        throw std::invalid_argument( "Number of voxels in one dimension should be an odd number. Got N = " + Types::to_string( N ) );
    }

    //Distance between two voxels' centers (equal to voxel's edge length)
    const Types::Scalar dx = L / static_cast< Types::Scalar >( N ); //[m]
    //Volume of a single voxel
    const Types::Scalar V_voxel = Math::pow< 3 >( dx ); //[m^3]

    // - Cell uptake - set as dirac
    const auto lambda = result["lambda"].as< Types::Scalar >(); //[mol/s]

    // - Cell boundary condition
    //Concentration on boundary voxel
    constexpr auto c_0 = 1e-2; //[10µM = 1e-2 mol/m^3]
    //Amoount on boundary voxel
    const auto n_0 = c_0 * V_voxel; //[mol]

    // - Math
    //Relative tolerance
    constexpr auto relative_tolerance = 1e-6; //[1]

    // - IO
    constexpr auto output_interval = 1.; //[1]
    const std::string output_dir = result["output-dir"].as< std::string >();

    // - Numerics
    //Courant condition
    const auto dx_squared = Math::pow< 2 >( dx );
    const auto D_over_dx_squared = D / dx_squared;
    const auto Courant = dt * D_over_dx_squared;
    const auto implicit_stability = std::abs( 1. - 6. * Courant );

    // - Cell-Voxels buffer
    const auto epsilon = 1e-6 * dx;

    //Print-out parameters
    std::cout << "- Parameters:\n"
              << "    Verbosity: " << verbose << "\n"
              << "    Global:\n"
              << "      Maximal run time [s]: " << maximal_run_time << "\n"
              << "      Final simulation time [s]: " << t_end << "\n"
              << "      Time step [s]: " << dt << "\n"
              << "      Diffusion coefficient [m^2/s]: " << D << "\n"
              << "    Geometry:\n"
              << "      Voxel's edge length [m]: " << dx << "\n"
              << "      Voxel's volume [m]: " << V_voxel << "\n"
              << "      Domain's edge length [m]: " << L << "\n"
              << "      Domain's volume [m]: " << V << "\n"
              << "    Chemokinetics:\n"
              << "      c_0 [mol / m^3]: " << c_0 << "\n"
              << "      n_0 = c_0 * V_voxel [mol]: " << n_0 << "\n"
              << "      Cell uptake over one time step [mol]: " << lambda * dt << "\n"
              << "      Cell uptake [mol/s]: " << lambda << "\n"
              << "      D / a^2 * n_0 [mol/s]: " << D_over_dx_squared * n_0 << "\n"
              << "    Stability condition:\n"
              << "      Courant number [1]: " << Courant << "\n"
              << "      6 * Courant [1]: " << 6. * Courant << "\n"
              << "      |1. - 6 * Courant|[1]: " << implicit_stability << "\n";

    //Create universe
    auto universe = [&]() {
        //Create one instance
        auto view = Particles::make_particles_view( Access::Modes::read_write, universes );
        auto u = view.add();

        //Set basic values
        // - time step
        u.set< Types::Scalar >( Access::Modes::read_write, "dt", SIUnits::second, dt );

        // - final time
        u.set< Types::Scalar >( Access::Modes::read_write, "t_end", SIUnits::second, t_end );

        // - maximal run time
        u.set< Types::Scalar >( Access::Modes::read_write, "t_elapsed_max", SIUnits::second, maximal_run_time );

        // - write out interval
        u.set< Types::Scalar >( Access::Modes::read_write, "output_interval", SIUnits::second, output_interval );

        // - set relative tolerance for float comparison
        u.set< Types::Scalar >( Access::Modes::read_write, "relative_tolerance", SIUnits::dimensionless, relative_tolerance );

        // - diffusion coefficient
        u.set< Types::Scalar >( Access::Modes::read_write, "D", ( SIUnits::meter ^ 2 ) / SIUnits::second, D );

        // - cell uptake
        u.set< Types::Scalar >( Access::Modes::read_write, "lambda", SIUnits::mole / SIUnits::second, lambda );

        // - Boundary condition - concentration
        u.set< Types::Scalar >( Access::Modes::read_write, "c_0", SIUnits::mole / ( SIUnits::meter ^ 3 ), c_0 );

        // - Boundary condition - amount per voxel
        u.set< Types::Scalar >( Access::Modes::read_write, "n_0", SIUnits::mole, n_0 );

        // - Domain's length
        u.set< Types::Scalar >( Access::Modes::read_write, "L", SIUnits::meter, L );

        // - Voxel's length
        u.set< Types::Scalar >( Access::Modes::read_write, "dx", SIUnits::meter, dx );

        // - Center of domain
        u.set< Types::Position >( Access::Modes::read_write, "x", SIUnits::meter, x_center );

        // - Number of voxels in one coordintae
        u.set< Types::Count >( Access::Modes::read_write, "N", SIUnits::dimensionless, N );

        // - Voxel's length squared
        u.set< Types::Scalar >( Access::Modes::read_write, "dx_squared", SIUnits::meter ^ 2, dx_squared );

        // - Diffusion rate
        u.set< Types::Scalar >( Access::Modes::read_write, "diffusion_rate", SIUnits::second ^ ( -1 ), D_over_dx_squared );

        // - One
        u.set< Types::Scalar >( Access::Modes::read_write, "one", SIUnits::dimensionless, 1. );

        // - Courant
        u.set< Types::Scalar >( Access::Modes::read_write, "Courant", SIUnits::dimensionless, Courant );
        u.set< Types::Scalar >( Access::Modes::read_write, "minus_Courant", SIUnits::dimensionless, -Courant );

        // - Buffer for cells-voxels contacts
        u.set< Types::Scalar >( Access::Modes::read_write, "epsilon", SIUnits::meter, epsilon );
        u.set< Types::Scalar >( Access::Modes::read_write, "dx_plus_epsilon", SIUnits::meter, dx + epsilon );

        return u;
    }();

    //Create voxels
    {
        //Prepare view
        auto view = Particles::make_particles_view( Access::Modes::read_write, voxels );

        //Set up regular grid around center
        //Position of bottom-down-left corner - first voxel
        //Note: N is the number of voxels in one dimension but there is actually 2 more ghost voxels
        const Types::Position x_first = x_center + ( -0.5 * ( N + 1. ) * dx ) * Types::Vector::Ones();

        //Create all voxels and set ghosts
        for( Types::Count i = 0; i < N + 2; ++i ) {
            for( Types::Count j = 0; j < N + 2; ++j ) {
                for( Types::Count k = 0; k < N + 2; ++k ) {
                    //Add voxel and set up dofs
                    auto v = view.add( universe );

                    //Position
                    const Types::Position x = x_first + dx * Types::Vector{ static_cast< Types::Scalar >( i ), static_cast< Types::Scalar >( j ), static_cast< Types::Scalar >( k ) };

                    //Bounding boxes
                    const Types::Position AABB_min = x + ( -0.5 * dx ) * Types::Vector::Ones();
                    const Types::Position AABB_max = x + 0.5 * dx * Types::Vector::Ones();
                    const Types::Position AABB_min_faces = x + ( -( 0.5 * dx + epsilon ) ) * Types::Vector::Ones();
                    const Types::Position AABB_max_faces = x + ( 0.5 * dx + epsilon ) * Types::Vector::Ones();

                    //Set up dofs
                    v.set< Types::Position >( Access::Modes::read_write, "AABB_min", SIUnits::meter, AABB_min );
                    v.set< Types::Position >( Access::Modes::read_write, "AABB_max", SIUnits::meter, AABB_max );
                    v.set< Types::Position >( Access::Modes::read_write, "AABB_min_faces", SIUnits::meter, AABB_min_faces );
                    v.set< Types::Position >( Access::Modes::read_write, "AABB_max_faces", SIUnits::meter, AABB_max_faces );
                    v.set< Types::Position >( Access::Modes::read_write, "x", SIUnits::meter, x );
                    v.set< Types::Scalar >( Access::Modes::read_write, "V", SIUnits::meter ^ 3, V_voxel );
                    v.set< Types::Scalar >( Access::Modes::read_write, "c", SIUnits::mole / ( SIUnits::meter ^ 3 ), 0. );
                    v.set< Types::Scalar >( Access::Modes::read_write, "n", SIUnits::mole, 0. );

                    //Set ghost voxels
                    const bool condition = ( i == 0 ) || ( i == N + 1 ) || ( j == 0 ) || ( j == N + 1 ) || ( k == 0 ) || ( k == N + 1 );
                    v.set< Types::Logical >( Access::Modes::read_write, "is_ghost", SIUnits::no_unit, condition );
                }
            }
        }
    }

    //Create cells
    {
        //Add cell
        auto view = Particles::make_particles_view( Access::Modes::read_write, cells );
        auto cell = view.add( universe );

        //Set position and bounding boxes
        cell.set< Types::Position >( Access::Modes::read_write, "x", SIUnits::meter, x_center );
        cell.set< Types::Position >( Access::Modes::read_write, "AABB_min", SIUnits::meter, x_center + ( -epsilon * Types::Vector::Ones() ) );
        cell.set< Types::Position >( Access::Modes::read_write, "AABB_max", SIUnits::meter, x_center + epsilon * Types::Vector::Ones() );
    }

    // ---------------------------------------
    // Simulation.
    // ---------------------------------------
    //Prepare simulation
    using Actions::create_executable;
    using namespace Parameters::Values;

    // - create simulation itself
    auto simulation = create_executable( "OnActions::And", "Simulation" );
    if( !simulation ) {
        throw std::runtime_error( "Failed to initialize 'Simulation'." );
    }

    // - add data structure
    simulation->add( universes );

    // ---------------------------------------
    // Phase 1: Initialization
    // ---------------------------------------
    // - contact detection - voxels-cells
    {
        auto action = simulation->add( create_executable( "Contact::Detectors::AABBTree", "Generate contacts between voxels and cells" ) );
        action->set_parameter_value( "contacts", absolute_path( "Universes/Voxels-Cells contacts" ) );
    }

    // - contact detection - faces
    {
        auto contact_detection = simulation->add( create_executable( "OnActions::And", "Generate faces" ) );

        // - AABBTree
        {
            auto action = contact_detection->add( create_executable( "Contact::Detectors::AABBTree", "Generate contacts between voxels" ) );
            action->set_parameter_value( "contacts", absolute_path( "Universes/Faces" ) );
            action->set_parameter_value( "AABB_min_1", absolute_path( "Universes/Voxels/AABB_min_faces" ) );
            action->set_parameter_value( "AABB_max_1", absolute_path( "Universes/Voxels/AABB_max_faces" ) );
        }

        // - Prune contacts between corners
        {
            auto prune = contact_detection->add( create_executable( "OnActions::And", "Prune contacts between corners" ) );

            // - Compute distance between centers of voxels
            {
                auto action = prune->add( create_executable( "Contact::Models::Geometry::EdgeLengthAndTangent", "Distances between centers" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Faces" ) );
                action->set_parameter_value( "l", absolute_path( "Universes/Faces/l" ) );
            }

            // - Mark corners
            {
                auto action = prune->add( create_executable( "Elementary::Comparisons::Less", "Mark contacts at boundary" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Faces" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Faces/is_corner" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/dx_plus_epsilon" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/Faces/l" ) );
            }

            // - Prune
            {
                auto action = prune->add( create_executable( "OnParticles::Prune", "Prune corners" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Faces" ) );
                action->set_parameter_value( "to_prune", absolute_path( "Universes/Faces/is_corner" ) );
            }
        }
    }

    // - set minus Courant number
    {
        auto action = simulation->add( create_executable( "Elementary::Set", "Set minus Courant" ) );
        action->set_parameter_value( "collection", absolute_path( "Universes/Faces" ) );
        action->set_parameter_value( "original", absolute_path( "Universes/minus_Courant" ) );
        action->set_parameter_value( "result", absolute_path( "Universes/Faces/minus_Courant" ) );
    }

    // - copy ghost voxels
    {
        auto action = simulation->add( create_executable( "OnParticles::Copy", "Copy ghost voxels" ) );
        action->set_parameter_value( "from", absolute_path( "Universes/Voxels" ) );
        action->set_parameter_value( "to", absolute_path( "Universes/Voxels/Ghost" ) );
        action->set_parameter_value( "to_copy", absolute_path( "Universes/Voxels/is_ghost" ) );
    }

    // - Diagonal part
    {
        auto diagonal = simulation->add( create_executable( "OnActions::And", "Set up matrix" ) );

        // - Set identity matrix
        {
            auto action = diagonal->add( create_executable( "Elementary::Set", "Set identity matrix part" ) );
            action->set_parameter_value( "result", absolute_path( "Universes/Voxels/diagonal" ) );
            action->set_parameter_value( "original", absolute_path( "Universes/one" ) );
        }

        // - Subtract from both
        {
            auto action = diagonal->add( create_executable( "Contact::Models::Elementary::SubtractFromBoth::Scalar", "Subtract from both" ) );
            action->set_parameter_value( "collection", absolute_path( "Universes/Faces" ) );
            action->set_parameter_value( "value_1", absolute_path( "Universes/Voxels/diagonal" ) );
            action->set_parameter_value( "value_2", absolute_path( "Universes/Voxels/diagonal" ) );
            action->set_parameter_value( "value", absolute_path( "Universes/Faces/minus_Courant" ) );
        }
    }

    // ---------------------------------------
    // Phase 2: Main loop
    // ---------------------------------------
    // - prepare loop
    {
        auto loop = simulation->add( create_executable( "OnActions::Loop", "Loop" ) );

        // - condition for termination (runtime)
        {
            auto action = loop->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "Check runtime" ) );
            action->set_parameter_value( "a", absolute_path( "Universes/t_elapsed" ) );
            action->set_parameter_value( "b", absolute_path( "Universes/t_elapsed_max" ) );
        }

        // - condition for termination (simulation time)
        {
            auto action = loop->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "Check simulation time" ) );
            action->set_parameter_value( "a", absolute_path( "Universes/t" ) );
            action->set_parameter_value( "b", absolute_path( "Universes/t_end" ) );
        }

        // - Assemble right hand side
        {
            auto rhs = loop->add( create_executable( "OnActions::And", "Assemble rhs" ) );

            // - Set rhs to current voxel value
            {
                auto action = rhs->add( create_executable( "Elementary::Set", "Set rhs" ) );
                action->set_parameter_value( "original", absolute_path( "Universes/Voxels/n" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Voxels/rhs" ) );
            }

            // - Cells uptake
            {
                auto uptake = rhs->add( create_executable( "OnActions::Queue", "Cell's uptake" ) );

                // - reset uptake_rate
                {
                    auto action = uptake->add( create_executable( "Elementary::Reset", "Reset uptake rate" ) );
                    action->set_parameter_value( "dof", absolute_path( "Universes/Voxels/uptake_rate" ) );
                }

                // - reset uptake
                {
                    auto action = uptake->add( create_executable( "Elementary::Reset", "Reset uptake" ) );
                    action->set_parameter_value( "dof", absolute_path( "Universes/Voxels/uptake" ) );
                }

                // - Compute cell's uptake rate
                {
                    auto action = uptake->add( create_executable( "Contact::Models::Elementary::SubtractFromFirst::Scalar", "Compute cells' uptake rate" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Voxels-Cells contacts" ) );
                    action->set_parameter_value( "value_1", absolute_path( "Universes/Voxels/uptake_rate" ) );
                    action->set_parameter_value( "value", absolute_path( "Universes/lambda" ) );
                }

                // - Compute cell's uptake
                {
                    auto action = uptake->add( create_executable( "Elementary::Algebraic::Multiply", "Compute cells' uptake" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Voxels/uptake" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/Voxels/uptake_rate" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/dt" ) );
                }

                // - Remove it to rhs
                {
                    auto action = uptake->add( create_executable( "Elementary::Algebraic::Add", "Add uptake from rhs" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Voxels/rhs" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/Voxels/uptake" ) );
                }
            }
        }

        // - print data
        if( !without_io ) {
            auto io_pipeline = loop->add( create_executable( "OnActions::Queue", "IO" ) );

            // - condition for execution
            {
                auto action = io_pipeline->add( create_executable( "OnActions::Triggers::ExecuteUntilLess", "Check time" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/t" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/next_output" ) );
            }

            // - time advance
            {
                auto action = io_pipeline->add( create_executable( "Elementary::Algebraic::Add", "Update next output time" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/next_output" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/output_interval" ) );
            }

            // - write voxels data
            {
                auto action = io_pipeline->add( create_executable( "IO::SimpleVTKWriter", "Write VTK files for voxels" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Voxels" ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/current_frame" ) );
                action->set_parameter_value( "filename", std::make_unique< String >( output_dir + "/Voxels_{:04}.vtp" ) );
            }

            // - write cells data
            {
                auto action = io_pipeline->add( create_executable( "IO::SimpleVTKWriter", "Write VTK files for cells" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Cells" ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/current_frame" ) );
                action->set_parameter_value( "filename", std::make_unique< String >( output_dir + "/Cells_{:04}.vtp" ) );
            }

            // - write the whole data to XML file
            {
                auto action = io_pipeline->add( create_executable( "IO::Save", "Write VTK files for faces" ) );
                action->set_parameter_value( "root", absolute_path( "Universes" ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/current_frame" ) );
                action->set_parameter_value( "filename", std::make_unique< String >( output_dir + "/Universes_{:04}.xml" ) );
            }

            // - increment frame counter
            {
                auto action = io_pipeline->add( create_executable( "Elementary::Algebraic::Increment", "Increment frame counter" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/current_frame" ) );
            }
        }

        // - Solver pipeline
        {
            auto integration = loop->add( create_executable( "OnActions::And", "Solver" ) );

            // - reset iteration counter
            {
                auto action = integration->add( create_executable( "Elementary::Reset", "Zero iteration counter" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/CG_iterations" ) );
            }

            // - CG solver
            {
                auto action = integration->add( create_executable( "Solvers::ConjugateGradient", "CG" ) );
                action->set_parameter_value( "x", std::make_unique< ComponentList >( absolute_path( "Universes/Voxels/n" ) ) );
                action->set_parameter_value( "y", std::make_unique< ComponentList >( absolute_path( "Universes/Voxels/rhs" ) ) );
                action->set_parameter_value( "D", std::make_unique< ComponentList >( absolute_path( "Universes/Voxels/diagonal" ) ) );
                action->set_parameter_value( "S", std::make_unique< ComponentList >( absolute_path( "Universes/Faces/minus_Courant" ) ) );
                action->set_parameter_value( "iterations", absolute_path( "Universes/CG_iterations" ) );
                action->set_parameter_value( "relative_tolerance", absolute_path( "Universes/CG_tolerance" ) );
            }

            // - Restore ghost cell to their initial value
            {
                auto action = integration->add( create_executable( "Elementary::Set", "Reset ghost cells" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Voxels/Ghost" ) );
                action->set_parameter_value( "original", absolute_path( "Universes/n_0" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Voxels/n" ) );
            }
        }

        // - compute concentration
        {
            auto action = loop->add( create_executable( "Elementary::Algebraic::Divide", "Compute c" ) );
            action->set_parameter_value( "result", absolute_path( "Universes/Voxels/c" ) );
            action->set_parameter_value( "a", absolute_path( "Universes/Voxels/n" ) );
            action->set_parameter_value( "b", absolute_path( "Universes/Voxels/V" ) );
        }

        // - time advance
        {
            auto action = loop->add( create_executable( "Elementary::Algebraic::Add", "Advance time" ) );
            action->set_parameter_value( "result", absolute_path( "Universes/t" ) );
            action->set_parameter_value( "b", absolute_path( "Universes/dt" ) );
        }

        // - store elapsed time of simulation
        {
            auto action = loop->add( create_executable( "OnActions::StoreElapsedTime", "Store simulation runtime" ) );
            action->set_parameter_value( "elapsed_time", absolute_path( "Universes/t_elapsed" ) );
            action->set_parameter_value( "executable", absolute_path( "Loop" ) );
        }
    }

    //If we are verbose print the initial tree
    if( verbose ) {
        std::cout << "  Initial tree:\n"
                  << "    " << tree_to_yaml( simulation, verbose, "    " ) << "\n";
    }

    //Execute simulation:
    if( !simulation->execute() ) {
        throw std::runtime_error( "Simulation failed." );
    }

    //Print the tree after execution
    std::cout << "  Final tree:\n"
              << "    " << tree_to_yaml( simulation, verbose, "    " ) << "\n";

    auto t_elapsed = universe.get< Types::Scalar >( Access::Modes::read_only, "t_elapsed", SIUnits::second );
    auto t = universe.get< Types::Scalar >( Access::Modes::read_only, "t", SIUnits::second );
    std::cout << "  Timings:\n"
              << "    Target simulation time: " << t_end << "\n"
              << "    Final simulation time: " << t << "\n"
              << "    Target elapsed time: " << maximal_run_time << "\n"
              << "    Actual elapsed time: " << t_elapsed << "\n";

    return 0;
}
