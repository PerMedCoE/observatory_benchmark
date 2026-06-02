// CompuTiX - computational library for tissue simulations.
// Source: https://gitlab.inria.fr/computix/computix
// Copyright (C) 2025 INRIA
//
// This file is part of CompuTiX.
//
// CompuTiX is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, version 3 of the License.
//
// CompuTiX is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

//! \example CBM/Impulse/src/main.cpp
//! \section impulse Movement of a cell considering an initial external force and a friction force
//!
//! \subsection impulse_problem_statement Problem statement
//!
//! This simulation illustrates the movement of a cell given a homogeneous isotropic friction coefficient,
//! that mimics friction of a cell with the extracellular matrix in an idealised way,
//! after the instantaneous application of a fixed and constant force.
//!
//! \subsubsection impulse_problem_statement_equation_motion Equation of motion
//! The system to solve is then composed of the two equation of motion for velocity and position:
//! \f{align*}
//! \gamma \vec{v}(t) &= \vec{F}_\text{loc}(t)
//! \\ \frac{\mathrm{d}\vec{x}}{\mathrm{d}t}(t) &= \vec{v}(t)
//! \f}
//! with \f$\vec{ x }\f$ the position, \f$\vec{ v }\f$ the velocity, \f$\vec{F}_\text{loc}\f$ the external force and
//! \f$\gamma\f$ the friction coefficient with the external medium.
//!
//! \subsubsection impulse_problem_statement_force External force
//! The initial constant force is applied to an initially motionless sphere at time instant \f$t_0\f$, and then kept active for a time interval \f$\Delta t\f$:
//! \f[
//! F_{\text{loc}}(t) = F_0 \Theta(t-t_0) \Theta(\Delta t + t_0 - t)
//! \f]
//! with \f$\Theta(t)\f$ is Heaviside function.
//!
//! \subsubsection impulse_problem_statement_stokes Stokes drag force
//! Stokes drag force is used to model the viscous firction, assuming a homogeneous isotropic friction coefficient that mimics friction of a cell with the extracellular matrix in an idealised way.
//! \f[
//! \vec{F}^{\text{Stokes}} = - \gamma \vec{v}^{\text{rel}}
//! \f]
//! where \f$\gamma\f$ is the friction coefficient or friction matrix for a given particle and \f$\vec{v}^{rel}\f$ is a relative velocity of the particle with respect to the fluid.
//! Implementation relies on the action \link CompuTiX::Actions::Forces::StokesDrag StokesDrag\endlink, which apply directly the Stokes drag on the particle with negative force sign.
//!
//! \subsubsection impulse_theoretical_prediction Theoretical predictions
//! Given the system follows overdamped dynamics we expect the sphere to stop right after the second time-step, based on the prescribed ratio of force and friction coefficient. Positions and velocities expected at meaningful time-steps hold the following expected values:
//! \f{align*}
//!   \vec{v}(\Delta t) &= \frac{\vec{F}_\text{loc}(t=0)}{\gamma} = \begin{pmatrix} 10 & 0 & 0 \end{pmatrix} \, \unit{\micro\meter\per\minute}
//!   \\ \vec{x}(\Delta t) &= \vec{v}(\Delta t) \Delta t = \begin{pmatrix} 1 & 0 & 0 \end{pmatrix} \, \unit{\micro\meter}
//!   \\ \vec{v}(2\Delta t) &= \frac{\vec{F}_\text{loc}(t=\Delta t)}{\gamma} = \begin{pmatrix} 0 & 0 & 0 \end{pmatrix}\,
//!      \unit{\micro\meter\per\minute}
//!   \\ \vec{x}(2\Delta t) &= \vec{x}(\Delta t) + \vec{v}(2\Delta t) \Delta t = \begin{pmatrix} 1 & 0 & 0 \end{pmatrix} \, \unit{\micro\meter}.
//! \f}
//! At \f$t=0.2\, \unit{\minute}\f$ system reaches equilibrium and the sphere is not moving any more.
//!
//! \subsection impulse_integration_scheme Integration schemes
//! Purpose of this example is to compare implicit and explicit integration schemes, showing their differences implementation-wise
//! and subsequently in terms of relaxation time for the sphere velocity.
//!
//! \subsubsection impulse_integration_scheme_explicit Explicit underdamped
//! Set of equations we are going to integrate for the explicit underdamped case is the following:
//! \f{align*}
//! m \frac{ \mathrm{d}\vec{v} }{ \mathrm{d}t } &= \vec{F}_{\text{loc}} - \gamma \vec{v}
//! \\ \vec{v} &= \frac{ \mathrm{d}\vec{x} }{ \mathrm{d}t }
//! \f}
//! where substituting the second into the first gives underdamped dynamics
//! \f[
//! m \frac{ \mathrm{d}^2\vec{x} }{ \mathrm{d}t^2 } = - \mu \frac{ \mathrm{d}\vec{x} }{ \mathrm{d}t } + \vec{F}_{\text{loc}}
//! /f]
//! using respectively \link CompuTiX::Actions::Integration::WeightedForwardEuler Weighted Forward Euler\endlink and \link CompuTiX::Actions::Integration::ForwardEuler Forward Euler\endlink.
//! The discretization by explicit Euler method gives:
//! \f{align*}
//! \vec{v}_{t+\mathrm{d}t} &= \vec{v}_t + \mathrm{d}t \cdot \frac{1}{m} \left( F_{\text{loc}}(t) - \gamma \vec{v}_t \right)
//! \\ \vec{x}_{t+\mathrm{d}t} &= \vec{x}_t + \mathrm{d}t \cdot \vec{v}_t
//! \f}

//! \subsubsection impulse_integration_scheme_implicit Implicit overdamped
//! Set of equations we are going to integrate are defining the implicit numerical scheme
//! \f{align*}
//! M \cdot (\vec{v}(t+\Delta t)-\vec{v}(t)) &= \Delta t \cdot \left[ \vec{F}_{\text{loc}}(t) - \gamma \vec{v}(t) \right]
//! \\ \vec{x}(t+\Delta t)-\vec{x}(t) &= \Delta t \cdot \vec{v}(t+\Delta t).
//! \f}
//! where the mass tensor is defined as \f$M = m\mathbb{I}-\gamma\Delta t\f$. In our case we neglect the intertial constribution, \f$ m\mathbb{I}\f$, resulting in an overdamped regime.
//! One can also prove the solution for velocity is the same one would have obtained for the explicit overdamped scheme:
//! \f{align*}
//! &M = \gamma \Delta t
//! \\ &\Rightarrow \gamma \Delta t (\vec{v}_{t+\Delta t}-\vec{v}_t) = \Delta t(\vec{F} - \gamma \vec{v}_t)
//! \\ &\Rightarrow \gamma (\vec{v}_{t+\Delta t}-\vec{v}_t) = \vec{F} - \gamma \vec{v}_t
//! \\ &\Rightarrow \vec{v}_{t+\Delta t} = \frac{\vec{F}}{\gamma}.
//! \f}
//!
//! \subsection impulse_simulation_pipeline Simulation pipeline
//! The simulation consists of the following steps executed in a \link CompuTiX::Actions::OnActions::Loop Loop\endlink:
//! * Condition for termination (`OnActions::Triggers::ExecuteWhileLess`).
//! * Compute forces (`OnActions::And`):
//!      * Reset forces sum (`Elementary::Reset`).
//!      * Reset mass matrix \f$M\f$ (`Elementary::Reset`).
//!      * Add initial force \f$\vec{F}_\text{loc}\f$ (`Elementary::Algebraic::Add`).
//!      * Compute Stokes drag (`Forces::StokesDrag`).
//!      * Reset the initial force (`Elementary::Reset`).
//! * Write out data:
//!      * Write out spheres' DoFs (`IO::SimpleVTKWriter`).
//!      * Write out whole data to XML (`IO::Save`).
//!      * Increment frame counter (`Elementary::Algebraic::Increment`).
//! * Integration pipeline (`OnActions::And`):
//!      * Velocity integration (`Integration::WeightedForwardEuler`)
//!      * Position integration (`Integration::ForwardEuler`)
//! * Update time \f$t += dt\f$ (`Elementary::Algebraic::Add`).
//! * Store elapsed time (`OnActions::StoreElapsedTime`).
//!
//! \subsection impulse_flowchart Flowchart diagram
//! Flowchart diagram with all the states of the simulation pipeline.
//!
//! \startuml "Simulation flowchart, relative to the implicit scheme"
//! !pragma useVerticalIf on
//! skinparam DefaultTextAlignment center
//! skinparam ConditionEndStyle hline
//! start
//! partition "Simulation\nOnActions::And" {
//!     partition "Loop\nOnActions::Loop" {
//!         while( true )
//!             if( Check simulation time\nOnActions::Triggers::ExecuteWhileLess ) then( false )
//!                 break
//!             else( true )
//!                 partition "Forces pipeline\nOnActions::And" {
//!                     :Reset total force\nElementary::Reset;
//!                     :Reset mass matrix\nElementary::Reset;
//!                     :Apply local force\nElementary::Algebraic::Add;
//!                     :Compute Stokes drag force\nForces::StokesDrag;
//!                     :Zero local force\nElementary::Reset;
//!                     (E)
//!                 }
//!                 partition "IO\nOnActions::Queue" {
//!                     :Write VTK files for cells\nIO::SimpleVTKWriter;
//!                     :Write VTK files for faces\nIO::Save;
//!                     :Increment frame counter\nElementary::Algebraic::Increment;
//!                     (E)
//!                 }
//!                 partition "Integration pipeline\nOnActions::And" {
//!                     :Integrate velocity\nIntegration::WeightedForwardEuler;
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
//! \enduml
//!
//! \subsection impulse_data_layout Data layout
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
//! - Spheres - \link CompuTiX::Components::Collections::ParticleCollection ParticleCollection\endlink
//!     representing the spheres.
//!     - x - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Position> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Position Position\endlink type representing the spheres' centers.
//!       Physical dimension: \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink.
//!     - v - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Vector> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Vector Vector\endlink type representing the spheres' velocities.
//!       Physical dimension: \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink / \link CompuTiX::SIUnits::second \f$\unit{\second}\f$\endlink.
//!     - F - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Vector> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Vector Vector\endlink type representing the force applied on the spheres.
//!       Physical dimension: \link CompuTiX::SIUnits::newton \f$\unit{\newton}\f$\endlink.
//!     - F_loc - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Vector> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Vector Vector\endlink type representing the force applied initially on the sphere.
//!       Physical dimension: \link CompuTiX::SIUnits::newton \f$\unit{\newton}\f$\endlink.
//!     - m - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!     \link CompuTiX::Types::Scalar Scalar\endlink type representing the mass of the sphere.
//!     Physical dimension: \link CompuTiX::SIUnits::kilogram \f$\unit{\kilogram}\f$\endlink.
//!     - M - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Matrix> DegreeOfFreedom\endlink of
//!     \link CompuTiX::Types::Matrix Matrix\endlink type representing the mass matrix of the sphere, used in the implicit overdamped case.
//!     Physical dimension: \link CompuTiX::SIUnits::kilogram \f$\unit{\kilogram}\f$\endlink.
//!     - gamma - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of
//!     \link CompuTiX::Types::Scalar Scalar\endlink type representing the triangles' and spheres' Young's modulus.
//!     Physical dimension: \link CompuTiX::SIUnits::newton \f$\unit{\newton}\f$\endlink * \link CompuTiX::SIUnits::second \f$\unit{\second}\f$\endlink / \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink.
//!
//! \subsection impulse_parameters_values Parameters' values
//! The following table summarizes the parameters' values used and how the constants relate to each other.
//!
//! | Parameter                | Symbol               | Value      	          | Unit         	 | Derivation          	   |
//! |--------------------------|----------------------|-----------------------|------------------|-------------------------|
//! | Target time 	           | \f$t_\text{end}\f$   | \f$10\f$	          | \f$\unit{second}\f$        | \f$\text{prescribed}\f$ |
//! | Time step 	           | \f$\Delta t\f$       | \f$10^{-4}\f$	          | \f$\unit{second}\f$        | \f$\text{prescribed}\f$ |
//! | Cell's radius            | \f$r\f$		      | \f$5\f$               | \f$\unit{\micro\meter}\f$      | \f$\text{prescribed}\f$ |
//! | Initial force            | \f$F_\text{loc}\f$   | \f$\begin{pmatrix} 20 & 0 & 0 \end{pmatrix}\f$   | \f$\unit{\pico\newton}\f$   | \f$\text{free}\f$  |
//! | Friction coefficient     | \f$\gamma\f$		  | \f$7.2\f$               | \f$\unit{\kilogram\per\minute}\f$     | \f$\gamma = 0.1 F_{\text{loc}}\f$ |
//!

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
#include <stdexcept>

int main( int argc, char** argv )
{
    using namespace CompuTiX;
    using namespace Components;

    //Prepare description
    auto options = cxxopts::Options{ "simulation",
                                     "Movement of a single cell with homogeneous friction." };

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

    //Prepare DoFs for Universes
    // - time management: current time (t), time step (dt), final time (t_end), current run time (t_elapsed), impulse start and end time (impulse_start, impulse_end)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dt", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_end", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_elapsed", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "impulse_start", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "impulse_end", SIUnits::second ) );

    // - VTK writer parameters: writer interval (output_interval), time of next output (next_output), current frame index (frame)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "output_interval", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "next_output", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Count >::create( "current_frame", SIUnits::dimensionless ) );

    //Prepare DoFs for Spheres
    // - kinematic DoFs: position for explicit and implicit scheme (x_explicit, x_implicit), velocity for explicit and implicit scheme (v_explicit, v_implicit)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "x_explicit", SIUnits::meter ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "v_explicit", SIUnits::meter / SIUnits::second ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "x_implicit", SIUnits::meter ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "v_implicit", SIUnits::meter / SIUnits::second ) );
    // - dynamic DoFs: mass (m), mass matrix (M), local initial force (F_loc), total force for explicit and implicit scheme (F_explicit, F_implicit), friction coefficient (gamma)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "m", SIUnits::kilogram ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "M", SIUnits::kilogram ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "F_loc", SIUnits::newton ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "F_explicit", SIUnits::newton ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "F_implicit", SIUnits::newton ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma", SIUnits::kilogram / SIUnits::second ) );

    // ---------------------------------------
    // Set particles' data
    // ---------------------------------------
    // - verbosity, without_io
    const auto verbose = result["v"].as< bool >();
    const auto without_io = result["without-io"].as< bool >();

    // - Global parameters:
    //Simulation duration time
    constexpr Types::Scalar t_end = 12.; // [ s ]
    //Time-step size
    constexpr Types::Scalar dt = 0.1; // [ s ]
    //Start of impulse
    constexpr Types::Scalar t0 = 3.; // [ s ]
    //Duration of impulse
    constexpr Types::Scalar impulse_duration = 3.; // [ s ]
    //Output interval
    constexpr auto output_interval = 0.1; // [ s ]

    // - Physical and geometrical parameters:
    //Sphere radius
    constexpr Types::Scalar sphere_radius = 5e-6; // [ m ]
    //Sphere volume
    constexpr Types::Scalar sphere_volume = 4. * Math::pi * Math::pow< 3 >( sphere_radius ) / 3.; // [ m^3 ]
    //Sphere density
    constexpr Types::Scalar sphere_density = 1000.; // [ kg / m^3 ]
    //Initial external local force
    const Types::Vector F_loc = 20e-12 * Types::Vector::UnitX(); // [ N ]
    //Friction coefficient
    constexpr Types::Scalar gamma = 7.2; // [ kg / min ]

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
        u.set< Types::Scalar >( Access::Modes::read_write, "impulse_start", SIUnits::second, t0 );
        u.set< Types::Scalar >( Access::Modes::read_write, "impulse_end", SIUnits::second, t0 + impulse_duration );
        u.set< Types::Scalar >( Access::Modes::read_write, "output_interval", SIUnits::second, output_interval );

        // View for spheres
        auto s_view = Particles::make_particles_view( Access::Modes::read_write, spheres );
        auto s = s_view.add( u );

        // Set values for spheres
        s.set< Types::Scalar >( Access::Modes::read_write, "m", SIUnits::kilogram, 0.01 );
        //s.set< Types::Scalar >( Access::Modes::read_write, "m", SIUnits::kilogram, sphere_density * sphere_volume );
        s.set< Types::Matrix >( Access::Modes::read_write, "M", SIUnits::kilogram, 1. * Types::Matrix::Identity() );
        s.set< Types::Scalar >( Access::Modes::read_write, "gamma", SIUnits::kilogram / SIUnits::minute, gamma );
        s.set< Types::Vector >( Access::Modes::read_write, "F_loc", SIUnits::newton, F_loc );

        return u;
    }();

    // ---------------------------------------
    // Generate simulation
    // ---------------------------------------
    //Prepare simulation
    using Actions::create_executable;
    using namespace Parameters::Values;

    // create simulation itself
    auto simulation = create_executable( "OnActions::And", "Simulation" );
    if( !simulation ) {
        throw std::runtime_error( "Failed to initialize 'Simulation'." );
    }

    // add data structure
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

        // - explicit forces pipeline
        {
            auto forces_explicit = loop->add( create_executable( "OnActions::And", "Explicit: forces pipeline" ) );

            // -- reset the sum of forces
            {
                auto action = forces_explicit->add( create_executable( "Elementary::Reset", "Explicit: reset total force" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Spheres" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Spheres/F_explicit" ) );
            }

            // -- apply the Heaviside impulse
            {
                auto impulse = forces_explicit->add( create_executable( "OnActions::Queue", "Explicit: Heaviside impulse" ) );

                // --- start condition
                {
                    auto action = impulse->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "Explicit: Heaviside start" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/impulse_start" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/t" ) );
                }
                // --- end condition
                {
                    auto action = impulse->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "Explicit: Heaviside end" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/t" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/impulse_end" ) );
                }
                // --- add the initial force
                {
                    auto action = impulse->add( create_executable( "Elementary::Algebraic::Add", "Explicit: apply explicit local force" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Spheres/F_explicit" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/Spheres/F_loc" ) );
                }
            }

            // -- compute Stokes drag force and sets mass matrix
            {
                auto stokes = forces_explicit->add( create_executable( "Forces::StokesDrag", "Explicit: compute Stokes drag force" ) );
                stokes->set_parameter_value( "F", absolute_path( "Universes/Spheres/F_explicit" ) );
                stokes->set_parameter_value( "gamma", absolute_path( "Universes/Spheres/gamma" ) );
                stokes->set_parameter_value( "v_rel", absolute_path( "Universes/Spheres/v_explicit" ) );
            }
        }

        // - implicit forces pipeline
        {
            auto forces_implicit = loop->add( create_executable( "OnActions::And", "Implicit: forces pipeline" ) );

            // -- reset the sum of forces
            {
                auto action = forces_implicit->add( create_executable( "Elementary::Reset", "Implicit: reset total force" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Spheres" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Spheres/F_implicit" ) );
            }

            // -- reset the mass matrix
            {
                auto action = forces_implicit->add( create_executable( "Elementary::Reset", "Implicit: reset mass matrix" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Spheres" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Spheres/M" ) );
            }

            // -- apply the Heaviside impulse
            {
                auto impulse = forces_implicit->add( create_executable( "OnActions::Queue", "Implicit: Heaviside impulse" ) );

                // --- start condition
                {
                    auto action = impulse->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "Implicit: Heaviside start" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/impulse_start" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/t" ) );
                }
                // --- end condition
                {
                    auto action = impulse->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "Implicit: Heaviside end" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/t" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/impulse_end" ) );
                }
                // --- add the initial force
                {
                    auto action = impulse->add( create_executable( "Elementary::Algebraic::Add", "Implicit: apply explicit local force" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Spheres/F_implicit" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/Spheres/F_loc" ) );
                }
            }

            // -- compute Stokes drag force and sets mass matrix
            {
                auto stokes = forces_implicit->add( create_executable( "Forces::StokesDrag", "Implicit: compute Stokes drag force" ) );
                stokes->set_parameter_value( "F", absolute_path( "Universes/Spheres/F_implicit" ) );
                stokes->set_parameter_value( "gamma", absolute_path( "Universes/Spheres/gamma" ) );
                stokes->set_parameter_value( "v_rel", absolute_path( "Universes/Spheres/v_implicit" ) );
                stokes->set_parameter_value( "M", absolute_path( "Universes/Spheres/M" ) );
                stokes->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }
        }

        // - IO pipeline
        if( !without_io ) {
            auto io_pipeline = loop->add( create_executable( "OnActions::Queue", "IO" ) );

            // - check simulation time
            {
                auto action = io_pipeline->add( create_executable( "OnActions::Triggers::ExecuteUntilLess", "Check simulation time" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/t" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/next_output" ) );
            }

            // -- write cells data
            {
                auto action = io_pipeline->add( create_executable( "IO::SimpleVTKWriter", "Write VTK files for cells" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Spheres" ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/current_frame" ) );
                action->set_parameter_value( "filename", std::make_unique< String >( output_dir + "/Cells_{:03}.vtp" ) );
            }

            // -- write the whole data to XML file
            {
                auto action = io_pipeline->add( create_executable( "IO::Save", "Write VTK files for faces" ) );
                action->set_parameter_value( "root", std::make_unique< ComponentList >( absolute_path( "Universes" ) ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/current_frame" ) );
                action->set_parameter_value( "filename", std::make_unique< String >( output_dir + "/Universes_{:03}.xml" ) );
            }

            // -- increment frame counter
            {
                auto action = io_pipeline->add( create_executable( "Elementary::Algebraic::Increment", "Increment frame counter" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/current_frame" ) );
            }

            // -- advance time checkpoint
            {
                auto action = io_pipeline->add( create_executable( "Elementary::Algebraic::Add", "Advance time checkpoint" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/next_output" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/output_interval" ) );
            }
        }

        // - explicit integration pipeline
        auto explicit_integration_pipeline = loop->add( create_executable( "OnActions::And", "Explicit: integration pipeline" ) );
        {
            // -- position integration
            {
                auto action = explicit_integration_pipeline->add( create_executable( "Integration::ForwardEuler", "Explicit: integrate position" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Spheres/x_explicit" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Spheres/v_explicit" ) );
                action->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }

            // -- velocity integration
            {
                auto action = explicit_integration_pipeline->add( create_executable( "Integration::WeightedForwardEuler", "Explicit: integrate velocity" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Spheres/v_explicit" ) );
                action->set_parameter_value( "w", absolute_path( "Universes/Spheres/m" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Spheres/F_explicit" ) );
                action->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }
        }

        // - implicit integration pipeline
        auto implicit_integration_pipeline = loop->add( create_executable( "OnActions::And", "Implicit: integration pipeline" ) );
        {
            // -- velocity integration
            {
                auto action = implicit_integration_pipeline->add( create_executable( "Integration::WeightedForwardEuler", "Implicit: integrate velocity" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Spheres/v_implicit" ) );
                action->set_parameter_value( "w", absolute_path( "Universes/Spheres/M" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Spheres/F_implicit" ) );
                action->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }

            // -- position integration
            {
                auto action = implicit_integration_pipeline->add( create_executable( "Integration::ForwardEuler", "Implicit: integrate position" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Spheres/x_implicit" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Spheres/v_implicit" ) );
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
