//! \section overlap_relaxation Two cells overlap relaxation
//!
//! \subsection overlap_relaxation_problem_statement Problem statement
//! This simulation illustrates the relaxation dynamics of two cells, identical in radius and properties, detaching from an initial configuration where the overlap exceeds the equilibrium one.
//!
//! \subsubsection collisions_pushing_cells_problem_statement_equation_motion Equation of motion
//! The system to solve for the two spheres is then composed of the two equation of motion for velocity and position:
//! \f{align*}
//! \gamma \vec{ v }(t) &= \vec{F}_\text{ext_Hertz}
//! \\ \frac{\mathrm{d}\vec{x}}{\mathrm{d}t}(t) &= \vec{v}(t)
//! \f}
//! with \f$\vec{ x }\f$ the position, \f$\vec{ v }\f$ the velocity, \f$\vec{F}_\text{ext_Hertz}\f$ a
//! collision adhesive force force and \f$\gamma\f$ the friction coefficient with the external medium.
//!
//! \subsubsection collisions_pushing_cells_problem_statement_stokes Stokes drag force
//! Stokes drag force is used to model the viscous firction, assuming a homogeneous isotropic friction coefficient that mimics friction of a cell with the extracellular matrix in an idealised way.
//! \f[
//! \vec{F}^{\text{Stokes}} = - \gamma \vec{v}^{\text{rel}}
//! \f]
//! where \f$\gamma\f$ is the friction coefficient or friction matrix for a given particle and \f$\vec{v}^{rel}\f$ is a relative velocity of the particle with respect to the fluid.
//! Implementation relies on the action \link CompuTiX::Actions::Forces::StokesDrag StokesDrag\endlink, which apply directly the Stokes drag on the particle with negative force sign.
//!
//! \subsubsection overlap_relaxation_problem_statement_derjaguin Derjaguin Model
//! \link CompuTiX::ContactModelComponents::Forces::Derjaguin Derjaguin\endlink force is extended with an adhesive contribution to model the collision of two spheres.
//! The extended Derjaguin force applied here is:
//! \f[
//! \vec{F}_\text{ext_Derjaguin} = \vec{F}_\text{Hertz} + \pi \gamma \tilde{R},
//! \f]
//! where \f$\gamma\f$ is the adhesion energy and \f$\tilde{R}\f$ the effective radius.
//! Implementation relies on the \link CompuTiX::ContactModelComponents::Forces::Derjaguin Derjaguin\endlink force.
//!
//! \subsubsection overlap_relaxation_problem_statement_equilibrium_overlap Expected equilibrium overlap
//! The equilibrium overlap for the two spheres is obtained by balancing the repulsive Hertz contribution with the constant adhesive term of the extended Hertz model.
//!
//! \subsection overlap_relaxation_integration_scheme Integration scheme
//! The implicit integration scheme is used and set of equations we are going to integrate is the following:
//! \f{align*}
//! \left( \vec{ v }(t +\Delta t) - \vec{ v }(t) \right) \cdot \left[ m \mathbb{I}  - \Delta t \; \nabla_{\vec{v}} \vec { F }( \vec{ x }(t), \vec{ v }(t) ) \right] &= \Delta t \; \vec { F }\left( \vec{ x }(t), \vec{ v }(t) \right)
//! \\ \vec{x}(t+\Delta t)-\vec{x}(t) &= \Delta t \cdot \vec{v}(t+\Delta t),
//! \f}
//! where the combined mass tensor matrix contains a (negative) friction matrix term \f$\nabla_{\vec{v}} \vec{F}\f$
//! \f[
//! M = m \mathbb{I} - \Delta t \; \nabla_{\vec{v}} \vec{F}( \vec{x}(t), \vec{v}(t) ),
//! \f]
//! and all the contributions to the total force can be written shorthand as
//! \f[
//! \vec{F} = \vec{F}^\text{Stokes} + \vec{F}_\text{Hertz} + \vec{F}_\text{adhesive}.
//! \f]
//! Allowing for approximation of the acceleration \f$\vec{a}\f$ at time \f$t\f$ in the first equation as
//! \f[
//! \vec{a}(t) = \frac{\vec{v}( t +\Delta t ) - \vec{v}(t) }{\Delta t},
//! \f]
//! one can rewrite obtaining the implicit system
//! \f[
//! \vec{a}(t) M = \vec{F}(\vec{x}(t), \vec{v}(t)),
//! \f]
//! which can be solved by using \link CompuTiX::Actions::Solvers::ConjugateGradient Conjugate Gradient\endlink for computing the accelerations, followed by \link CompuTiX::Actions::Integration::ForwardEuler Forward Euler\endlink for updating velocities and positions from
//! \f{align*}
//! \vec{v}(t+\Delta t)-\vec{v}(t) &= \Delta t \cdot \vec{a}(t+\Delta t)
//! \\ \vec{x}(t+\Delta t)-\vec{x}(t) &= \Delta t \cdot \vec{v}(t+\Delta t).
//! \f}
//!
//! \subsection overlap_relaxation_simulation_pipeline Simulation pipeline
//! The simulation consists of the following steps executed in a \link CompuTiX::Actions::OnActions::Loop Loop\endlink:
//! * Check simulation time (`OnActions::Triggers::ExecuteWhileLess`)
//! * Geometric pipeline (`OnActions::And`)
//!     * Zero overlap (`Elementary::Reset`)
//!     * Get Sphere-Sphere contact overlap (`Contact::Models::Geometry::Overlap::SphereSphere`)
//! * Forces (`OnActions::And`)
//!     * Zero total force (`Elementary::Reset`)
//!     * Zero mass matrix (`Elementary::Reset`)
//!     * Set mass matrix (`Elementary::Algebraic::Multiply`)
//!     * Sphere-Sphere Hertz contact model (`Contact::Models::Collisions::Hertz::Damped::SphereSphere::Overdamped`)
//!     * Add adhesive force (`Elementary::Algebraic::Add`)
//!     * Compute Stokes drag force (`Forces::StokesDrag`)
//! * Write out data:
//!      * Write out spheres' DoFs (`IO::SimpleVTKWriter`).
//!      * Write out whole data to XML (`IO::Save`).
//!      * Increment frame counter (`Elementary::Algebraic::Increment`).
//! * Integration pipeline (`OnActions::And`)
//!     * Compute acceleration (`Solvers::ConjugateGradient`)
//!     * Integrate position (`Integration::ForwardEuler`)
//!     * Integrate velocity (`Integration::ForwardEuler`)
//! * Increment time (`Elementary::Algebraic::Add`)
//! * Store elapsed time (`OnActions::StoreElapsedTime`).
//!
//! \subsection Flowchart diagram
//! Flowchart diagram with all the states of the simulation pipeline.
//!
//! \startuml "Simulation flowchart" !pragma useVerticalIf on
//! skinparam DefaultTextAlignment center
//! skinparam ConditionEndStyle hline
//! start
//! partition "Simulation\nOnActions::And" {
//!     partition "Loop\nOnActions::Loop" {
//!         while( true )
//!             if( Check simulation time\nOnActions::Triggers::ExecuteWhileLess ) then( false )
//!                 break
//!             else( true )
//!                 partition "Geometric pipeline\nOnActions::Queue" {
//!                     :Zero overlap\nElementary::Reset;
//!                     :Get Sphere-Sphere contact overlap\nContact::Models::Geometry::Overlap::SphereSphere;
//!                     (E)
//!                 }
//!                 partition "Forces\nOnActions::And" {
//!                     :Zero total Sphere force\nElementary::Reset;
//!                     :Reset mass tensor\nElementary::Reset;
//!                     :Set mass tensor\nElementary::Algebraic::Multiply;
//!                     (E)
//!                     }
//!                     :Apply local force\nElementary::Algebraic::Add;
//!                     :Sphere-Sphere Hertz contact model\nContact::Models::Collisions::Hertz::Damped::SphereSphere::Overdamped;
//!                     :Add adhesive force\nElementary::Algebraic::Add;
//!                     :Compute Stokes drag force\nForces::StokesDrag;
//!                     (E)
//!                 }
//!                 partition "IO\nOnActions::Queue" {
//!                     :Write VTK files for cells\nIO::SimpleVTKWriter;
//!                     :Write VTK files for faces\nIO::Save;
//!                     :Increment frame counter\nElementary::Algebraic::Increment;
//!                     (E)
//!                 }
//!                 partition "Integration pipeline\nOnActions::And" {
//!                     :Compute acceleration\nSolvers::ConjugateGradient;
//!                     :Integrate velocity\nIntegration::ForwardEuler;
//!                     :Integrate position\nIntegration::ForwardEuler;
//!                     (E)
//!                 }
//!                 :Advance time\nElementary::Algebraic::Add;
//!                 :Store simulation runtime\nOnActions::StoreElapsedTime;
//!             endif
//!         endwhile( false )
//!     }
//!     (E)
//! }
//! stop
//!
//! \enduml
//!
//! \subsection overlap_relaxation_data_layout Data layout
//! The data hierarchy is set up as first thing, including the following collections and degrees of freedom:
//! - Universes - \link CompuTiX::Components::Collections::ParticleCollection ParticleCollection\endlink
//!   representing the universe which is parent of the particle collection or DoF in the data structure.
//!     - t - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!     \link CompuTiX::Types::Scalar Scalar\endlink type representing the elapsed time of the simulation.
//!     Physical dimension: \link CompuTiX::SIUnits::second \f$\unit{\second}\f$\endlink.
//!     - dt - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!     \link CompuTiX::Types::Scalar Scalar\endlink type representing the time-step of the simulation.
//!     Physical dimension: \link CompuTiX::SIUnits::second \f$\unit{\second}\f$\endlink.
//!     - t_end - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!     \link CompuTiX::Types::Scalar Scalar\endlink type representing the final time of the simulation.
//!     Physical dimension: \link CompuTiX::SIUnits::second \f$\unit{\second}\f$\endlink.
//!     - t_elapsed - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!     \link CompuTiX::Types::Scalar Scalar\endlink type representing the current run time.
//!     Physical dimension: \link CompuTiX::SIUnits::second \f$\unit{\second}\f$\endlink.
//!     - current_frame - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Count> DegreeOfFreedom\endlink of
//!     \link CompuTiX::Types::Scalar Scalar\endlink type representing the current iteration number of the simulation.
//!     Physical dimension: \link CompuTiX::SIUnits::second \f$\unit{\second}\f$\endlink.
//!     - r - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the radius of the two spheres.
//!     Physical dimension: \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink.
//!     - M - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Matrix> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Matrix Matrix\endlink type representing the spheres' mass tensors.
//!       Physical dimension: \link CompuTiX::SIUnits::kilogram \f$\unit{\kilogram}\f$\endlink.
//!     - tension - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the interfacial tension of the contact.
//!     Physical dimension: \link CompuTiX::SIUnits::newton / CompuTiX::SIUnits::meter \f$\unit{\newton\per\meter}\f$\endlink.
//!     - gamma_tangential - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the tangential friction coefficient.
//!     Physical dimension: \link CompuTiX::SIUnits::pascal * CompuTiX::SIUnits::second \ CompuTiX::SIUnits::meter \f$\unit{\pascal \second\per\meter}\f$\endlink.
//!     - gamma_normal - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the normal friction coefficient.
//!     Physical dimension: \link CompuTiX::SIUnits::pascal * CompuTiX::SIUnits::second \ CompuTiX::SIUnits::meter \f$\unit{\pascal \second\per\meter}\f$\endlink.
//!     - overlap - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the overlap between the two spheres.
//!     Physical dimension: \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink.
//! - Spheres - \link CompuTiX::Components::Collections::ParticleCollection ParticleCollection\endlink representing the spheres.
//!     - x - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Position> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Position Position\endlink type representing the spheres' centers.
//!       Physical dimension: \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink.
//!     - v - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Vector> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Vector Vector\endlink type representing the spheres' velocities.
//!       Physical dimension: \link CompuTiX::SIUnits::meter \ CompuTiX::SIUnits::second \f$\unit{\meter\per\second}\f$\endlink.
//!     - a - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Vector> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Vector Vector\endlink type representing the spheres' accelerations.
//!       Physical dimension: \link CompuTiX::SIUnits::meter \ CompuTiX::SIUnits::second^2 \f$\unit{\meter\per\second\tothe{2}}\f$\endlink.
//!     - r - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Scalar Scalar\endlink type representing the spheres' radii.
//!       Physical dimension: \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink.
//!     - m - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Scalar Scalar\endlink type representing the spheres' masses.
//!       Physical dimension: \link CompuTiX::SIUnits::kilogram \f$\unit{\kilogram}\f$\endlink.
//!     - M - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Matrix> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Matrix Matrix\endlink type representing the spheres' mass tensors.
//!       Physical dimension: \link CompuTiX::SIUnits::kilogram \f$\unit{\kilogram}\f$\endlink.
//!     - id - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Matrix> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Matrix Matrix\endlink type representing the identity matrix.
//!       Physical dimension: \link CompuTiX::SIUnits::dimensionless \f$1\f$\endlink.
//!     - gamma - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Scalar Scalar\endlink type representing the friction coefficient of the spheres with the external medium.
//!       Physical dimension: \link CompuTiX::SIUnits::newton * CompuTiX::SIUnits::second / CompuTiX::SIUnits::meter \f$\unit{\newton\second\per\meter}\f$\endlink.
//!     - E - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Scalar Scalar\endlink type representing the spheres' Young's modulus.
//!       Physical dimension: \link CompuTiX::SIUnits::pascal \f$\unit{\pascal}\f$\endlink.
//!     - nu - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Scalar Scalar\endlink type representing the spheres' Poisson's ratio.
//!       Physical dimension: \link CompuTiX::SIUnits::dimensionless \f$1\f$\endlink.
//!     - e_adh - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Scalar Scalar\endlink type representing the spheres' adhesion energy density.
//!       Physical dimension: \link CompuTiX::SIUnits::joule / CompuTiX::SIUnits::meter^2 \f$\unit{\joule\per\meter\tothe{2}}\f$\endlink.
//!     - F - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Vector> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Vector Vector\endlink type representing the total force applied on the spheres.
//!       Physical dimension: \link CompuTiX::SIUnits::newton \f$\unit{\newton}\f$\endlink.
//! - Contacts - \link CompuTiX::Components::Collections::ParticleCollection ParticleCollection\endlink representing the spheres.
//!     - M - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Matrix> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Matrix Matrix\endlink type representing the spheres' mass tensors.
//!       Physical dimension: \link CompuTiX::SIUnits::kilogram \f$\unit{\kilogram}\f$\endlink.
//!
//! \subsection overlap_relaxation_parameters_values Parameters' values
//! The following table summarizes the parameters' values used and how the constants relate to each other.
//!
//! | Parameter | Symbol | Value | Unit | Derivation |
//! |-----------|--------|-------|------|------------|
//! | Cell radius (Ri and Rj) | \f$R_i, R_j\f$ | \f$5\times10^{-6}\f$ | \f$\unit{\meter}\f$ | prescribed |
//! | Initial center-to-center distance (d0) | \f$d_0\f$ | \f$9\times10^{-6}\f$ | \f$\unit{\meter}\f$ | prescribed |
//! | Initial overlap (\f$\delta_0\f$) | \f$\delta_0\f$ | \f$1\times10^{-6}\f$ | \f$\unit{\meter}\f$ | prescribed |
//! | Poisson ratio (\f$\nu_i\f$ and \f$\nu_j\f$) | \f$\nu_i, \nu_j\f$ | \f$0.4\f$ | \f$1\f$ | prescribed |
//! | Adhesion density | \f$\rho_\text{adh}\f$ | \f$1\times10^{5}\f$ | \f$\unit{\meter^{-2}}\f$ | prescribed |
//! | Temperature (for the single-bond work) | \f$T\f$ | \f$310\f$ | \f$\unit{\kelvin}\f$ | prescribed |
//! | Adhesion parameter | \f$\gamma\f$ | \f$8.56\times10^{-15}\f$ | \f$\unit{\joule\per\meter^2}\f$ | prescribed |
//! | Cell's Young Modulus (\f$E_i\f$ and \f$E_j\f$) | \f$E_i, E_j\f$ | \f$450\f$ | \f$\unit{\pascal}\f$ | prescribed |
//! | Composite Young Modulus | \f$E^*\f$ | \f$268\f$ | \f$\unit{\pascal}\f$ | derived |

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
#include <CompuTiX/Math/constants.h>
#include <CompuTiX/Math/pow.h>
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
                                     "Collision of two spheres pushing each other." };

    //Add options
    {
        using std::to_string;

        auto option_adder = options.add_options();
        option_adder( "h,help", "Print usage." );
        option_adder( "v,verbose", "Verbose print." );
        option_adder( "without-io", "Disable IO. Disables generation of VTP and save files." );
        option_adder( "t,run-time", "Maximal run time [s].", cxxopts::value< Types::Scalar >()->default_value( to_string( std::numeric_limits< Types::Scalar >::max() ) ) );
        option_adder( "T,sim-time", "Target simulation time [s].", cxxopts::value< Types::Scalar >()->default_value( "10." ) );
        option_adder( "dt", "Time step [s].", cxxopts::value< Types::Scalar >()->default_value( "0.6" ) );
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

    //Prepare cell collection
    auto spheres = universes->add( Collections::ParticleCollection::create( "Spheres" ) );
    auto contacts = universes->add( Collections::PairCollection::create( "Contacts", spheres, spheres ) );

    //Prepare DoFs for Universes
    // - time management: current time (t), time step (dt), final time (t_end), current run time (t_elapsed)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dt", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_end", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_elapsed", SIUnits::second ) );

    // - VTK printing parameters: current frame index (current_frame)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Count >::create( "current_frame", SIUnits::dimensionless ) );

    // - contact model DoFs: interfacial tension (tension), tangential friction coefficient (gamma_tangential), normal friction coefficient (gamma_normal), mass tensor (M), overlap, spheres' radius (r)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "tension", SIUnits::newton / SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma_tangential", SIUnits::pascal * SIUnits::second / SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma_normal", SIUnits::pascal * SIUnits::second / SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "overlap", SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "r", SIUnits::meter ) );

    //Prepare DoFs for Spheres
    // - kinematic DoFs: position (x), velocity (v), acceleration (a)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "x", SIUnits::meter ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "v", SIUnits::meter / SIUnits::second ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "a", SIUnits::meter / ( SIUnits::second ^ 2 ) ) );

    // - geometric DoFs: radius (r)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "r", SIUnits::meter ) );

    // - dynamic DoFs: mass (m), mass tensor (M), identity matrix (id), force (F), friction coefficient (gamma)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "m", SIUnits::kilogram ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "M", SIUnits::kilogram ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "id", SIUnits::dimensionless ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "F", SIUnits::newton ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "gamma", SIUnits::newton * SIUnits::second / ( SIUnits::meter ) ) );

    // - material DoFs: sphere material Young's modulus (E), sphere Poisson's ratio (nu), adhesion energy (e_adh)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "E", SIUnits::pascal ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "nu", SIUnits::dimensionless ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "e_adh", SIUnits::joule / ( SIUnits::meter ^ 2 ) ) );

    //Prepare DoFs for Contacts
    // - mass tensor
    contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "M", SIUnits::kilogram ) );

    // ---------------------------------------
    // Set particles' data
    // ---------------------------------------
    // - verbosity, without_io
    const auto verbose = result["v"].as< bool >();
    const auto without_io = result["without-io"].as< bool >();

    // - Global parameters:
    //Simulation duration time
    constexpr Types::Scalar t_end = 60. * 100.; // [ s ]
    //Time-step size
    constexpr Types::Scalar dt = 60.; // [ s ]

    // - Physical and geometrical parameters:
    //Hepatocyte mass
    constexpr Types::Scalar mass = 0.; // [ kg ]
    //Initial positions
    const Types::Position x_init_1 = Types::Position::Zero(); // [ m ]
    const Types::Position x_init_2 = 9e-6 * Types::Position::UnitX(); // [ m ]
    //Spheres radius
    constexpr Types::Scalar r = 5e-6; // [ m ]
    //Young's modulus
    constexpr Types::Scalar E = 450.; // [ Pa ]
    //Poisson's ratio
    constexpr Types::Scalar nu = 0.4; // [ 1 ]
    //Friction coefficient
    const Types::Matrix gamma = 1. * Types::Matrix::Identity(); // [ kg / s ]
    //Specific adhesion energy
    constexpr Types::Scalar adhesion_energy_density = 8.56e-15 / 2; // [ J / m^2 ]
    //Contact interfacial tension
    constexpr Types::Scalar tau = 0.; // [ N / m ]

    // - Collision parameters:
    //Tangential friction coefficient
    constexpr Types::Scalar gamma_tang = 1e8; // [ Pa s / m ]
    //Normal friction coefficient
    constexpr Types::Scalar gamma_norm = 1e8; // [ Pa s / m ]

    // - IO
    const std::string output_dir = result["output-dir"].as< std::string >();

    //Create unverse and sphere
    auto universe = [&]() {
        // View for universe
        auto u_view = Particles::make_particles_view( Access::Modes::read_write, universes );
        auto u = u_view.add();

        // Set values for universe
        u.set< Types::Scalar >( Access::Modes::read_write, "dt", SIUnits::second, dt );
        u.set< Types::Scalar >( Access::Modes::read_write, "t_end", SIUnits::second, t_end );
        u.set< Types::Scalar >( Access::Modes::read_write, "tension", SIUnits::newton / SIUnits::meter, tau );
        u.set< Types::Scalar >( Access::Modes::read_write, "gamma_tangential", SIUnits::pascal * SIUnits::second / SIUnits::meter, gamma_tang );
        u.set< Types::Scalar >( Access::Modes::read_write, "gamma_normal", SIUnits::pascal * SIUnits::second / SIUnits::meter, gamma_norm );
        u.set< Types::Scalar >( Access::Modes::read_write, "r", SIUnits::meter, r );

        // View for spheres
        auto s_view = Particles::make_particles_view( Access::Modes::read_write, spheres );
        auto s1 = s_view.add( u );
        auto s2 = s_view.add( u );

        // Set values for first sphere
        s1.set< Types::Scalar >( Access::Modes::read_write, "m", SIUnits::kilogram, mass );
        s1.set< Types::Position >( Access::Modes::read_write, "x", SIUnits::meter, x_init_1 );
        s1.set< Types::Scalar >( Access::Modes::read_write, "r", SIUnits::meter, r );
        s1.set< Types::Matrix >( Access::Modes::read_write, "gamma", SIUnits::kilogram / SIUnits::second, gamma );
        s1.set< Types::Scalar >( Access::Modes::read_write, "E", SIUnits::pascal, E );
        s1.set< Types::Scalar >( Access::Modes::read_write, "nu", SIUnits::dimensionless, nu );
        s1.set< Types::Scalar >( Access::Modes::read_write, "e_adh", SIUnits::joule / ( SIUnits::meter ^ 2 ), adhesion_energy_density );
        s1.set< Types::Matrix >( Access::Modes::read_write, "id", SIUnits::dimensionless, Types::Matrix::Identity() );

        // Set values for second sphere
        s2.set< Types::Scalar >( Access::Modes::read_write, "m", SIUnits::kilogram, mass );
        s2.set< Types::Position >( Access::Modes::read_write, "x", SIUnits::meter, x_init_2 );
        s2.set< Types::Scalar >( Access::Modes::read_write, "r", SIUnits::meter, r );
        s2.set< Types::Matrix >( Access::Modes::read_write, "gamma", SIUnits::kilogram / SIUnits::second, gamma );
        s2.set< Types::Scalar >( Access::Modes::read_write, "E", SIUnits::pascal, E );
        s2.set< Types::Scalar >( Access::Modes::read_write, "nu", SIUnits::dimensionless, nu );
        s2.set< Types::Scalar >( Access::Modes::read_write, "e_adh", SIUnits::joule / ( SIUnits::meter ^ 2 ), adhesion_energy_density );
        s2.set< Types::Matrix >( Access::Modes::read_write, "id", SIUnits::dimensionless, Types::Matrix::Identity() );

        // View for the contact
        auto c_view = Particles::make_particles_view( Access::Modes::read_write, contacts );
        auto c = c_view.add( Types::PairIndex{ 0, 1 }, u );

        return u;
    }();

    // ---------------------------------------
    // Generate simulation
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

    // prepare main loop
    {
        auto loop = simulation->add( create_executable( "OnActions::Loop", "Loop" ) );

        // - condition for termination (simulation time)
        {
            auto action = loop->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "Check simulation time" ) );
            action->set_parameter_value( "a", absolute_path( "Universes/t" ) );
            action->set_parameter_value( "b", absolute_path( "Universes/t_end" ) );
        }

        // - geometry pipeline
        {
            auto geom_pipeline = loop->add( create_executable( "OnActions::Queue", "Geometric pipeline" ) );

            // -- reset overlap
            {
                auto action = geom_pipeline->add( create_executable( "Elementary::Reset", "Zero overlap" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/overlap" ) );
            }
            // -- get the overlap
            {
                auto action = geom_pipeline->add( create_executable( "Contact::Models::Geometry::Overlap::SphereSphere", "Get Sphere-Sphere contact overlap" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
                action->set_parameter_value( "overlap", absolute_path( "Universes/overlap" ) );
            }
        }

        // - forces pipeline
        {
            auto forces = loop->add( create_executable( "OnActions::And", "Forces" ) );

            // -- reset total force
            {
                auto action = forces->add( create_executable( "Elementary::Reset", "Zero total Sphere force" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Spheres/F" ) );
            }

            // -- reset the mass tensor in spheres
            {
                auto action = forces->add( create_executable( "Elementary::Reset", "Reset spheres mass tensor" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Spheres" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Spheres/M" ) );
            }

            // -- reset the mass tensor in contacts
            {
                auto action = forces->add( create_executable( "Elementary::Reset", "Reset contacts mass tensor" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Contacts/M" ) );
            }

            // -- compute extended Hertz interaction force and set mass matrix
            {
                auto action = forces->add( create_executable( "Contact::Models::Collisions::Derjaguin::Damped::SphereSphere::Overdamped", "Sphere-Sphere Derjaguin contact model" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
                action->set_parameter_value( "gamma_tangential", absolute_path( "Universes/gamma_tangential" ) );
                action->set_parameter_value( "gamma_normal", absolute_path( "Universes/gamma_normal" ) );
                action->set_parameter_value( "M", absolute_path( "Universes/Contacts/M" ) );
                action->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }

            // -- compute Stokes drag force and set mass matrix
            {
                auto stokes = forces->add( create_executable( "Forces::StokesDrag", "Compute Stokes drag force" ) );
                stokes->set_parameter_value( "F", absolute_path( "Universes/Spheres/F" ) );
                stokes->set_parameter_value( "gamma", absolute_path( "Universes/Spheres/gamma" ) );
                stokes->set_parameter_value( "v_rel", absolute_path( "Universes/Spheres/v" ) );
                stokes->set_parameter_value( "M", absolute_path( "Universes/Spheres/M" ) );
                stokes->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }
        }

        // - IO
        if( !without_io ) {
            auto io_pipeline = loop->add( create_executable( "OnActions::Queue", "IO" ) );

            // -- write cells data
            {
                auto action = io_pipeline->add( create_executable( "IO::SimpleVTKWriter", "Write VTK files for cells" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Spheres" ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/current_frame" ) );
                action->set_parameter_value( "filename", std::make_unique< String >( output_dir + "/Cells_{:03}.vtp" ) );
            }

            // -- write the whole data to XML file
            {
                auto action = io_pipeline->add( create_executable( "IO::Save", "Write VTK files for universes" ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/current_frame" ) );
                action->set_parameter_value( "filename", std::make_unique< String >( output_dir + "/Universes_{:03}.xml" ) );
            }

            // -- increment frame counter
            {
                auto action = io_pipeline->add( create_executable( "Elementary::Algebraic::Increment", "Increment frame counter" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/current_frame" ) );
            }
        }

        // - integration pipeline
        auto integration_pipeline = loop->add( create_executable( "OnActions::And", "Integration pipeline" ) );
        {
            // -- compute acceleration
            {
                auto action = integration_pipeline->add( create_executable( "Solvers::ConjugateGradient", "Compute acceleration" ) );
                action->set_parameter_value( "x", std::make_unique< ComponentList >( absolute_path( "Universes/Spheres/a" ) ) );
                action->set_parameter_value( "y", std::make_unique< ComponentList >( absolute_path( "Universes/Spheres/F" ) ) );
                action->set_parameter_value( "D", std::make_unique< ComponentList >( absolute_path( "Universes/Spheres/M" ) ) );
                action->set_parameter_value( "S", std::make_unique< ComponentList >( absolute_path( "Universes/Contacts/M" ) ) );
            }

            // -- velocity integration
            {
                auto action = integration_pipeline->add( create_executable( "Integration::ForwardEuler", "Integrate velocity" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Spheres/v" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Spheres/a" ) );
                action->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }

            // -- position integration
            {
                auto action = integration_pipeline->add( create_executable( "Integration::ForwardEuler", "Integrate position" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Spheres/x" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Spheres/v" ) );
                action->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }
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
    std::cout << "- Final tree:\n"
              << "    " << tree_to_yaml( simulation, verbose, "    " ) << "\n";

    auto t_elapsed = universe.get< Types::Scalar >( Access::Modes::read_only, "t_elapsed", SIUnits::second );
    auto t = universe.get< Types::Scalar >( Access::Modes::read_only, "t", SIUnits::second );
    std::cout << "  Timings:\n"
              << "    Target simulation time: " << t_end << "\n"
              << "    Final simulation time: " << t << "\n"
              << "    Elapsed time: " << t_elapsed << "\n";

    return 0;
}
