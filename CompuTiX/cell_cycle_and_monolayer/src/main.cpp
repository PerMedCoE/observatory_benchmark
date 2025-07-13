// CompuTiX - computational library for tissue simulations.
// Source: https://gitlab.inria.fr/computix/computix
// Copyright (C) 2025 INRIA
//
// This file is part of CompuTiX.
//
// CompuTiX is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CompuTiX is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

//! \example CellGrowth/Monolayer/main.cpp
//! \section monolayer_growth Monolayer growth
//!
//! This simulation represents an example of a monolayer growth starting from a single cell.
//! Each cell is represented by a sphere of a given radius, which during the growth increases.
//! Furthermore at a given size, cell undergoes mitosis in the randomly generated direction.
//! And then goes dormant for a certain period of time before the growth is resumed for each daughter cell.
//!
//! \subsection monolayer_growth_cycle Cell cycle
//! The basic cell cycle is formed by three states:
//! * Quiescent state - here cell just passively rest
//! * Proliferating state - where cell metabolizes and can increase its radius
//!   * Growing sub-state - where the cell are not crowded and can grow.
//!                         Further bellow cells, which are Proliferating and not Growing are denoted *Dormant*.
//! * Dividing state - where a dumbbell is formed by cell and its daughter cell
//!                    and they are gradually being separated and shrunk,
//!                    while the total volume of the dumbbell is being preserved.
//!
//! \startuml "State diagram"
//!
//! state Dividing {
//!   Divide --> Mitosis
//!   Divide : instantaneous
//!   Mitosis --> Mitosis : Gradually separate
//!   Mitosis : duration: 2 hours
//! }
//!
//! Mitosis --> Quiescent
//! Quiescent --> Proliferating
//! Quiescent : duration: 7 hours
//! Proliferating --> Proliferating : Increase cell radius
//! Proliferating --> Divide : Create daughter cell
//! Proliferating --> Quiescent : when maximal overlap is more than 10%
//! Proliferating : duration: 9 hours
//!
//! Proliferating --> Dormant : when crowded
//! Dormant --> Proliferating : when density decreased
//! \enduml
//!
//! \subsection monolayer_growth_data_layout Data layout
//! The need to represent cells in various states leads to non-trivial design,
//! which will allow us effectively track the state of each individual cell.
//! This is achieved by following hierarchy
//! * Universes - stores global parameters
//!   * Cells - contains \link CompuTiX::Components::DegreesOfFreedom DegreesOfFreedom\endlink representing the state of cells
//!     * Quiescent - subset of Cells, for which `is_quiescent` is set true.
//!       * Done - subset of Quiescent Cells, which are due to change the state, i.e. `t > dt_quiescent`.
//!                For these cells the state is updated to Proliferating and internal clock `t` is reset.
//!     * Proliferating - subset of Cells, for which `is_proliferating` is set to true.
//!                       They reprense cells which can grow if they are not crowded.
//!       * Growing - Cells which are actually growing.
//!                   At every timestep their radius is updated to represent their growth.
//!                   Transition between `Growing` and `Proliferating` is based upon a threshold over a relative overlapping volume.
//!                   When cell is not `Growing` it's internal clock is not updated.
//!       * Done - subset of Proliferating Cells, which are due to change the state, i.e. `t > dt_grow`.
//!                For these cells the state is update to Dividing, internal clock `t` is reset,
//!                and a new daughter cell is generated with slightly offset position.
//!     * Dividing - subsets of Cells, for which `is_dividing` is set true.
//!                  This collection represents cells undergoing mitosis.
//!                  At every timestep the cell's radius is shrunk in such a way that the total volume of the dumbbell is preserved.
//!       * Done - subset of Dividing Cells, which are due to change the state, i.e. `t > dt_division`.
//!                For these cells the state is update to Quiescent and internal clock `t` is reset.
//!       * New - subset of Dividing Cells, containing freshly generated daughters.
//!               For these cells new contacts inside `Dividing cells contacts` is generated.
//!   * Dividing cells contacts - represents contacts between Cells undergoing mitoses and their respective daughter cells.
//!                               Note, that each contact represent one dividing pair of mother-daughter cells.
//!     * New - subset of `Dividing cells contacts` which were just generated.
//!             It is used to initialize the contact, e.g. by establishing the volume of the dumbbell.
//!   * Contacts - represents collisions between cells.
//!                All contacts from `Dividing cells contacts` are excluded from this collection,
//!                in order to avoid duplicate contacts between daughter and corresponding mother cells, which are currently undergoing mitosis.
//!
//! in unison \link CompuTiX::Actions::OnParticles::Copy Copy\endlink and \link CompuTiX::Actions::OnParticles::Prune Prune\endlink idiom,
//! which allow us to sort particles to individual sub-collections.
//!
//! \subsection monolayer_growth_mechanics Mechanics
//! There are two basic mechanical interactions:
//! * \link CompuTiX::Actions::Contact::Models::Collisions::JKR::Damped::SphereSphere::Implicit JKR \endlink force, applied to contacts from `Contacts`,
//!   representing volume exclusion between individual cells.
//! * \link CompuTiX::Actions::Contact::Models::Division::Dumbbell::Implicit Dumbbell \endlink force, applied to contacts from `Dividing cells contacts`,
//!   ensuring gradual separation of daughter cells while preserving the total volume of the dumbbell:
//!   \image html Example_Growth_Monolayer_division.png The detail of single cell division.
//!
//! The resulting forces are then integrated via implicit scheme with the help of \link CompuTiX::Actions::Solvers::ConjugateGradient ConjugateGradient\endlink solver
//! and \link CompuTiX::Actions::Integration::ForwardEuler ForwardEuler\endlink integration scheme.
//!
//! \remark The main difference from \link spheroid_growth Spheroid example \endlink is that the division axis is generated in plane via \link CompuTiX::Actions::Elementary::Random::OrientationInPlane OrientationInPlane\endlink
//!         and in additional projection of the acceleration to the plane.
//!         These two conditions are enough to ensure that the proliferating cell collony will remain in plane.

#include <CompuTiX/Components/Actions/ExecutableBase.h>
#include <CompuTiX/Components/Collections/ParticleCollection.h>
#include <CompuTiX/Components/DegreesOfFreedom/DegreeOfFreedom.h>
#include <CompuTiX/Components/Parameters/Values/ComponentList.h>
#include <CompuTiX/Components/Parameters/Values/Root.h>
#include <CompuTiX/Components/Parameters/Values/absolute_path.h>
#include <CompuTiX/Components/Random/MersenneTwister.h>
#include <CompuTiX/Components/tree_to_yaml.h>
#include <CompuTiX/Math/constants.h>
#include <CompuTiX/Math/pow.h>
#include <CompuTiX/Particles/Particle.h>
#include <CompuTiX/Particles/ParticlesView.h>
#include <CompuTiX/SIUnits/UnitDeclarations.h>
#include <CompuTiX/Types/Public/Count.h>
#include <CompuTiX/Types/Public/Logical.h>
#include <CompuTiX/Types/Public/ParticleIndex.h>
#include <CompuTiX/Types/Public/Position.h>
#include <CompuTiX/Types/Public/Scalar.h>
#include <CompuTiX/Types/Public/Vector.h>

#include <cxxopts.hpp>

int main( int argc, char** argv )
{
    using namespace CompuTiX;
    using namespace Components;

    //Prepare description
    auto options = cxxopts::Options{ "simulation",
                                     "Example of monolayer growth. Showcase for center based model." };

    //Add options
    {
        using std::to_string;

        auto option_adder = options.add_options();
        option_adder( "h,help", "Print usage." );
        option_adder( "v,verbose", "Verbose print." );
        option_adder( "without-io", "Disable IO. Disables generation of VTP and save files." );
        option_adder( "t,run-time", "Maximal run time [s]. (Default: no limit)", cxxopts::value< Types::Scalar >()->default_value( to_string( std::numeric_limits< Types::Scalar >::max() ) ) );
        option_adder( "T,sim-time", "Target simulation time [s]. (Default: 27 days)", cxxopts::value< Types::Scalar >()->default_value( to_string( 27. * 24. * 60. * 60. ) ) );
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

    //Create cells
    auto cells = universes->add( Collections::ParticleCollection::create( "Cells" ) );

    // ... and collections for individual states every cell should bellong to one of them
    auto proliferating = cells->add( Collections::ParticleCollection::create( "Proliferating" ) );
    auto dividing = cells->add( Collections::ParticleCollection::create( "Dividing" ) );
    auto quiescent = cells->add( Collections::ParticleCollection::create( "Quiescent" ) );

    // ... and subcollection for those who are done
    auto growing = proliferating->add( Collections::ParticleCollection::create( "Growing" ) );
    proliferating->add( Collections::ParticleCollection::create( "Done" ) );
    dividing->add( Collections::ParticleCollection::create( "Done" ) );
    quiescent->add( Collections::ParticleCollection::create( "Done" ) );

    // ... and collection for filtering our new cells
    dividing->add( Collections::ParticleCollection::create( "New" ) );

    // ... prepare contacts for division and relevant subdivision
    auto dividing_contacts = universes->add( Collections::PairCollection::create( "Dividing cells contacts", cells, cells ) );
    dividing_contacts->add( Collections::PairCollection::create( "New", cells, cells ) );

    // ... contacts for collisions
    auto contacts = universes->add( Collections::PairCollection::create( "Contacts", cells, cells ) );

    // Add DoFs
    // ---------------------
    // Universes
    // ---------------------
    // - identity matrix, 1, 4 pi / 3, relative tolerance, plane normal and projection to the plane
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "identity", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "one", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "four_pi_thirds", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "relative_tolerance", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "n", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "projection", SIUnits::dimensionless ) );

    // - time management: current time (t), timestep (dt), final time (t_end), current run time (t_elapsed), maximal run time (t_elapsed_max)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dt", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_end", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_elapsed", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_elapsed_max", SIUnits::second ) );

    // - IO: output interval (dt_out), next print (t_out), current frame (frame)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dt_out", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t_out", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Count >::create( "frame", SIUnits::dimensionless ) );

    // - cell cycle: growth time (dt_grow), division time (dt_division), quiescent time (dt_quiescent),
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dt_grow", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dt_division", SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dt_quiescent", SIUnits::second ) );

    // - growth: growth rate (1/tau), limiting volume (V_infty)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "inv_tau", SIUnits::dimensionless / SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_infty", SIUnits::meter ^ 3 ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_crowded_relative", SIUnits::dimensionless ) );

    // - division: shift, division rate (rates are per time-step)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "shift", SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "division_rate", ( SIUnits::meter ^ 3 ) / SIUnits::second ) );

    // - global material properties: dynamic viscosity (mu), cells density (rho)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "mu", SIUnits::pascal * SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "rho", SIUnits::kilogram / ( SIUnits::meter ^ 3 ) ) );

    // - cell interactions: Young's modulus (E), Poisson's ration (nu), adhesion energy density (e_adh), interfacial tension (tension) and normal and tangential friction (gamma_tangential and gamma_normal)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "E", SIUnits::pascal ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "nu", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "e_adh", SIUnits::joule / ( SIUnits::meter ^ 2 ) ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "tension", SIUnits::joule / ( SIUnits::meter ^ 2 ) ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma_tangential", SIUnits::pascal / SIUnits::meter * SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma_normal", SIUnits::pascal / SIUnits::meter * SIUnits::second ) );

    // - mechanical parameters of division: stiffness and frictions
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "k_div", SIUnits::newton ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma_tangential_div", SIUnits::newton / SIUnits::meter * SIUnits::second ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma_normal_div", SIUnits::newton / SIUnits::meter * SIUnits::second ) );

    // - CG counter and tolerance
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Count >::create( "CG_iterations", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "CG_tolerance", SIUnits::dimensionless ) );

    // ---------------------
    // Cells
    // ---------------------
    // - geometry: center position (x), radiues (r), volumes (V), growth rate (dV_dt), bounding box (AABB_min, AABB_max)
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "x", SIUnits::meter ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "r", SIUnits::meter ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "r^3", SIUnits::meter ^ 3 ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V", SIUnits::meter ^ 3 ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "dV_dt", ( SIUnits::meter ^ 3 ) / SIUnits::second ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "AABB_min", SIUnits::meter ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "AABB_max", SIUnits::meter ) );

    // - kinematics: velocity (v) and acceleration (a)
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "v", SIUnits::meter / SIUnits::second ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "a", SIUnits::meter / ( SIUnits::second ^ 2 ) ) );

    // - dynamics: friction matrix (gamma), mass (m), mass matrix (M), force (F)
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "gamma", SIUnits::newton / SIUnits::meter * SIUnits::second ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "m", SIUnits::kilogram ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "M", SIUnits::kilogram ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "F", SIUnits::newton ) );

    // - cell state:
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_dividing", SIUnits::no_unit ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_proliferating", SIUnits::no_unit ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_quiescent", SIUnits::no_unit ) );

    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_new", SIUnits::no_unit ) );

    // - interactions: overlapping volume
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_overlap", SIUnits::meter ^ 3 ) );
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_overlap_rel", SIUnits::dimensionless ) );

    // - internal clock
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "t", SIUnits::second ) );

    // - lineage
    cells->add( DegreesOfFreedom::DegreeOfFreedom< Types::ParticleIndex >::create( "parent", cells ) );

    // ---------------------
    // Cell cycle
    // ---------------------
    // - store time per stage
    proliferating->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_done", SIUnits::no_unit ) );
    dividing->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_done", SIUnits::no_unit ) );
    quiescent->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_done", SIUnits::no_unit ) );

    // - are we crowded
    proliferating->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_growing", SIUnits::no_unit ) );

    // - quantities for computing the growth rate (dV_dt),
    //   Logistic growth: dV_dt = V / tau * ( 1 - V / V_infty )
    growing->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V ÷ V_infty", SIUnits::dimensionless ) );
    growing->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "1 - V ÷ V_infty", SIUnits::dimensionless ) );
    growing->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V * ( 1 - V ÷ V_infty )", SIUnits::meter ^ 3 ) );

    // ---------------------
    // Contacts
    // ---------------------
    // - to be able to filter out new contacts and to check which contact are still relevant
    dividing_contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "is_new", SIUnits::no_unit ) );
    dividing_contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Logical >::create( "are_both_dividing", SIUnits::no_unit ) );

    // - division axis, actual shift, target volume (V_eq)
    dividing_contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "axis", SIUnits::dimensionless ) );
    dividing_contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "shift", SIUnits::meter ) );
    dividing_contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_eq", SIUnits::meter ^ 3 ) );
    dividing_contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_cells", SIUnits::meter ^ 3 ) );
    dividing_contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_overlap", SIUnits::meter ^ 3 ) );

    // - add mass matrices
    dividing_contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "M", SIUnits::kilogram ) );
    contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "M", SIUnits::kilogram ) );

    // - add contact radius for JKR
    contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "r_contact", SIUnits::meter ) );

    // - add overlap and overlapping volume
    contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "overlap", SIUnits::meter ) );
    contacts->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_overlap", SIUnits::meter ^ 3 ) );

    // ---------------------
    // Add PRNG
    // ---------------------
    universes->add( Random::MersenneTwister::create( "PRNG" ) );

    // ---------------------------------------
    // Generate particles
    // ---------------------------------------
    // - verbosity, without_io and maximal runtime
    const auto verbose = result["v"].as< bool >();
    const auto without_io = result["without-io"].as< bool >();
    const auto maximal_run_time = result["t"].as< Types::Scalar >(); //[s]

    // - set parameters
    // Simulation:
    const auto t_end = result["T"].as< Types::Scalar >(); //[s]
    constexpr Types::Scalar dt = 10.; // [s]
    constexpr Types::Scalar dt_out = 6. * 60.; // [s]

    // Environment: water viscosity
    //constexpr Types::Scalar mu = 1e-3; // [Pa s]
    constexpr Types::Scalar mu = 10000.; // [Pa s]

    // Shift during division:
    constexpr Types::Scalar shift_rel = 0.01; // [1]

    // Relative tolerance for CG:
    constexpr auto relative_tolerance = 1e-5; //[1]
    constexpr auto CG_tolerance = 1e-10; //[1]

    // Cell:
    // - initial radius, density, Young's modulus, Poission ratio, adhesion energy density, frictions:
    //constexpr Types::Scalar V_0 = 2494e-18; // [m^3]
    constexpr Types::Scalar V_0 = 4188.79e-18; // [m^3]
    constexpr Types::Scalar r_0 = std::cbrt( V_0 / ( 4. / 3. * Math::pi ) ); // [m]
    constexpr Types::Scalar rho = 1000.; // [m^3]
    constexpr Types::Scalar E = 450.; // [Pa]
    constexpr Types::Scalar nu = 0.4; // [1]
    constexpr Types::Scalar e_adh = 1e-19 * 1e15; // [J/m^2] : 1e-19 J / bond * 1e15 bonds / m^2
    constexpr Types::Scalar gamma = 1e8; // [Pa s / m ]

    // - cell cycle:
    constexpr Types::Scalar dt_grow = 9. * 60. * 60.; // [s]
    constexpr Types::Scalar dt_division = 2. * 60. * 60.; // [s]
    constexpr Types::Scalar dt_quiescent = 7. * 60. * 60.; // [s]

    // - growth: Limiting value, characteristic growth time and crowding
    //constexpr Types::Scalar V_infty = 5065.66e-18; // [m^3]
    constexpr Types::Scalar V_infty = 5065.66e-18 * 4188.79 / 2494.; // [m^3]
    constexpr Types::Scalar tau = 7727.02; // [s]
    //constexpr Types::Scalar V_crowded_relative = 0.11; // [1]
    constexpr Types::Scalar V_crowded_relative = 0.07; // [1]

    // - division: Stiffness and friction
    constexpr Types::Scalar k_div = 1e-5; // [N]
    constexpr Types::Scalar gamma_div = 1e-2; // [N s / m ] //Has to be bigger than bulk

    std::cout << "- Parameters:\n"
              << "    Execution:\n"
              << "      Verbosity: " << verbose << "\n"
              << "      Maximal run time [s]: " << maximal_run_time << "\n"
              << "    Simulation:\n"
              << "      t_end: " << t_end << "\n"
              << "      dt: " << dt << "\n"
              << "      dt_out: " << dt_out << "\n"
              << "      CG relative tolerance: " << relative_tolerance << "\n"
              << "    Environment:\n"
              << "      mu: " << mu << "\n"
              << "    Cells:\n"
              << "      r_0: " << r_0 << "\n"
              << "      V_0: " << V_0 << "\n"
              << "      rho: " << rho << "\n"
              << "      dt_grow: " << dt_grow << "\n"
              << "      dt_division: " << dt_division << "\n"
              << "      dt_quiescent: " << dt_quiescent << "\n"
              << "      tau: " << tau << "\n"
              << "      V_infty: " << V_infty << "\n"
              << "    Forces:\n"
              << "      k_div: " << k_div << "\n"
              << "      max_JKR: " << 2. / 3. * E / ( 1. - Math::pow< 2 >( nu ) ) * Math::pow< 2 >( r_0 ) << "\n"
              << "    Mass matrix:\n"
              << "      min_mass: " << 4. / 3. * Math::pi * Math::pow< 3 >( r_0 ) * rho << "\n"
              << "      max_mass: " << 8. / 3. * Math::pi * Math::pow< 3 >( r_0 ) * rho << "\n"
              << "      min_gamma_liquid * dt: " << 6. * Math::pi * mu * r_0 * dt << "\n"
              << "      max_gamma_liquid * dt: " << 6. * Math::pi * mu * std::cbrt( 2. ) * r_0 * dt << "\n"
              << "      gamma_division * dt: " << gamma_div * dt << "\n"
              << "      max_gamma_contact * dt: " << gamma * Math::pi * Math::pow< 2 >( std::cbrt( 2. ) * r_0 ) * dt << "\n"
              << "      k_div / r_0 * dt^2: " << k_div / r_0 * Math::pow< 2 >( dt ) << "\n"
              << "      k_JKR * dt^2: " << 0.5 * E / ( 1. - Math::pow< 2 >( nu ) ) * r_0 * Math::pow< 2 >( dt ) << "\n"
              << "    Relaxation times:\n"
              << "      tau_division: " << gamma_div / k_div * r_0 << "\n";

    // ---------------------------------------
    // Create universe
    // ---------------------------------------
    // - create universe
    auto universe = [&]() {
        //Create universe
        auto universes_view = Particles::make_particles_view( Access::Modes::read_write, universes );
        auto p = universes_view.add();

        //Set global parameters
        // - set identity, plane normal and projection to the plane
        p.set< Types::Matrix >( Access::Modes::read_write, "identity", SIUnits::dimensionless, Types::Matrix::Identity() );
        p.set< Types::Scalar >( Access::Modes::read_write, "one", SIUnits::dimensionless, 1. );
        p.set< Types::Scalar >( Access::Modes::read_write, "four_pi_thirds", SIUnits::dimensionless, 4. / 3. * Math::pi );
        p.set< Types::Scalar >( Access::Modes::read_write, "relative_tolerance", SIUnits::dimensionless, relative_tolerance );
        p.set< Types::Vector >( Access::Modes::read_write, "n", SIUnits::dimensionless, Types::Vector::UnitX() );

        // - simulation time
        p.set< Types::Scalar >( Access::Modes::read_write, "t_end", SIUnits::second, t_end );
        p.set< Types::Scalar >( Access::Modes::read_write, "dt", SIUnits::second, dt );
        p.set< Types::Scalar >( Access::Modes::read_write, "dt_out", SIUnits::second, dt_out );
        p.set< Types::Scalar >( Access::Modes::read_write, "t_elapsed_max", SIUnits::second, maximal_run_time );

        // - set cell cycle
        p.set< Types::Scalar >( Access::Modes::read_write, "dt_grow", SIUnits::second, dt_grow );
        p.set< Types::Scalar >( Access::Modes::read_write, "dt_division", SIUnits::second, dt_division );
        p.set< Types::Scalar >( Access::Modes::read_write, "dt_quiescent", SIUnits::second, dt_quiescent );

        // - set growth
        //   Based on the fit from the provided data
        p.set< Types::Scalar >( Access::Modes::read_write, "V_infty", SIUnits::meter ^ 3, V_infty );
        p.set< Types::Scalar >( Access::Modes::read_write, "inv_tau", SIUnits::dimensionless / SIUnits::second, 1. / tau );
        p.set< Types::Scalar >( Access::Modes::read_write, "V_crowded_relative", SIUnits::dimensionless, V_crowded_relative );

        // - set shift and division rate
        //   Rate are chosen in such a way that cell halves the volume during division so the total volume of the dumbell is the original cell.
        p.set< Types::Scalar >( Access::Modes::read_write, "shift", SIUnits::meter, 2. * shift_rel * r_0 );
        p.set< Types::Scalar >( Access::Modes::read_write, "division_rate", ( SIUnits::meter ^ 3 ) / SIUnits::second, -V_0 / dt_division );

        // - set mechanical properties
        p.set< Types::Scalar >( Access::Modes::read_write, "mu", SIUnits::pascal * SIUnits::second, mu );
        p.set< Types::Scalar >( Access::Modes::read_write, "rho", SIUnits::kilogram / ( SIUnits::meter ^ 3 ), rho );
        p.set< Types::Scalar >( Access::Modes::read_write, "E", SIUnits::pascal, E );
        p.set< Types::Scalar >( Access::Modes::read_write, "nu", SIUnits::dimensionless, nu );
        p.set< Types::Scalar >( Access::Modes::read_write, "e_adh", SIUnits::joule / ( SIUnits::meter ^ 2 ), 0.5 * e_adh ); //Per particle
        p.set< Types::Scalar >( Access::Modes::read_write, "gamma_normal", SIUnits::pascal / SIUnits::meter * SIUnits::second, gamma );
        p.set< Types::Scalar >( Access::Modes::read_write, "gamma_tangential", SIUnits::pascal / SIUnits::meter * SIUnits::second, gamma );
        p.set< Types::Scalar >( Access::Modes::read_write, "k_div", SIUnits::newton, k_div );
        p.set< Types::Scalar >( Access::Modes::read_write, "gamma_normal_div", SIUnits::newton / SIUnits::meter * SIUnits::second, gamma_div );
        p.set< Types::Scalar >( Access::Modes::read_write, "gamma_tangential_div", SIUnits::newton / SIUnits::meter * SIUnits::second, gamma_div );

        // - set relative tolerance
        p.set< Types::Scalar >( Access::Modes::read_write, "CG_tolerance", SIUnits::dimensionless, CG_tolerance );

        return p;
    }();

    // ---------------------------------------
    // Seed cell
    // ---------------------------------------
    // - create cell
    auto cell = [&]() {
        //Create cell
        auto cells_view = Particles::make_particles_view( Access::Modes::read_write, cells );
        auto p = cells_view.add( universe );

        //Set her initial radius and volume
        p.set< Types::Scalar >( Access::Modes::read_write, "r", SIUnits::meter, r_0 );
        p.set< Types::Scalar >( Access::Modes::read_write, "V", SIUnits::meter ^ 3, V_0 );

        //Set her initial state
        p.set< Types::Logical >( Access::Modes::read_write, "is_quiescent", SIUnits::no_unit, true );

        return p;
    }();

    // ---------------------------------------
    // Simulation
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

    // ----------------------------------------
    // Intialization
    // ----------------------------------------
    // - compute projection to the plane
    {
        auto pipeline = simulation->add( create_executable( "OnActions::And", "Compute projection to the plane" ) );

        // Compute dyadic product
        {
            auto action = pipeline->add( create_executable( "Elementary::Algebraic::Dyadic", "P = n n" ) );
            action->set_parameter_value( "result", absolute_path( "Universes/projection" ) );
            action->set_parameter_value( "a", absolute_path( "Universes/n" ) );
        }

        //Determine projection to the plane
        {
            auto action = pipeline->add( create_executable( "Elementary::Algebraic::Subtract", "P = 1 - P" ) );
            action->set_parameter_value( "result", absolute_path( "Universes/projection" ) );
            action->set_parameter_value( "a", absolute_path( "Universes/identity" ) );
            action->set_parameter_value( "b", absolute_path( "Universes/projection" ) );
        }
    }

    // - copy cells marked as proliferating to the corresponding collection
    {
        auto action = simulation->add( create_executable( "OnParticles::Copy", "Copy is_proliferating to Proliferating" ) );
        action->set_parameter_value( "from", absolute_path( "Universes/Cells" ) );
        action->set_parameter_value( "to", absolute_path( "Universes/Cells/Proliferating" ) );
        action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/is_proliferating" ) );
    }

    // - copy cells marked as dividing to the corresponding collection
    {
        auto action = simulation->add( create_executable( "OnParticles::Copy", "Copy is_dividing to Dividng" ) );
        action->set_parameter_value( "from", absolute_path( "Universes/Cells" ) );
        action->set_parameter_value( "to", absolute_path( "Universes/Cells/Dividing" ) );
        action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/is_dividing" ) );
    }

    // - copy cells marked as quiescent to the corresponding collection
    {
        auto action = simulation->add( create_executable( "OnParticles::Copy", "Copy is_quiescent to Quiescent" ) );
        action->set_parameter_value( "from", absolute_path( "Universes/Cells" ) );
        action->set_parameter_value( "to", absolute_path( "Universes/Cells/Quiescent" ) );
        action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/is_quiescent" ) );
    }

    // ----------------------------------------
    // Main loop
    // ----------------------------------------
    {
        auto loop = simulation->add( create_executable( "OnActions::Loop", "Loop" ) );

        // - condition for termination (runtime)
        {
            auto action = loop->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "t_elapsed < t_elapsed_max ?" ) );
            action->set_parameter_value( "a", absolute_path( "Universes/t_elapsed" ) );
            action->set_parameter_value( "b", absolute_path( "Universes/t_elapsed_max" ) );
        }

        // - condition for termination (simulation time)
        {
            auto action = loop->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "t < t_end ?" ) );
            action->set_parameter_value( "a", absolute_path( "Universes/t" ) );
            action->set_parameter_value( "b", absolute_path( "Universes/t_end" ) );
        }

        // - cell cycle pipeline
        {
            auto state_machine = loop->add( create_executable( "OnActions::And", "Cell state machine" ) );

            // - reset is_new for cells
            {
                auto action = state_machine->add( create_executable( "Elementary::Reset", "is_new = false" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Cells/is_new" ) );
            }

            // - initiate cell division
            {
                auto division_onset = state_machine->add( create_executable( "OnActions::And", "Initialize division" ) );

                // - set particles ÷ which we will work
                {
                    auto filter = division_onset->add( create_executable( "OnActions::And", "Filter out proliferating particles which are done" ) );

                    // - clear done
                    {
                        auto action = filter->add( create_executable( "OnParticles::Clear", "Clear Done" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating/Done" ) );
                    }

                    // - mark proliferating
                    {
                        auto action = filter->add( create_executable( "Elementary::Comparisons::Less", "is_done = dt_grow < t" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/Proliferating/is_done" ) );
                        action->set_parameter_value( "a", absolute_path( "Universes/dt_grow" ) );
                        action->set_parameter_value( "b", absolute_path( "Universes/Cells/t" ) );
                    }

                    // - copy done
                    {
                        auto action = filter->add( create_executable( "OnParticles::Copy", "Copy is_done to Done" ) );
                        action->set_parameter_value( "from", absolute_path( "Universes/Cells/Proliferating" ) );
                        action->set_parameter_value( "to", absolute_path( "Universes/Cells/Proliferating/Done" ) );
                        action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/Proliferating/is_done" ) );
                    }
                }

                // - change the internal state
                {
                    auto change_state = division_onset->add( create_executable( "OnActions::And", "Change the internal state" ) );

                    // - reset is_proliferating
                    {
                        auto action = change_state->add( create_executable( "Elementary::Logical::Not", "is_proliferating[Proliferating & Done] = false" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating/Done" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/is_proliferating" ) );
                    }

                    // - set is_dividing
                    {
                        auto action = change_state->add( create_executable( "Elementary::Logical::Not", "is_dividing[Proliferating & Done] = true" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating/Done" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/is_dividing" ) );
                    }
                }

                // - reset the cell time
                {
                    auto action = division_onset->add( create_executable( "Elementary::Reset", "t[Proliferating & Done] = 0" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating/Done" ) );
                    action->set_parameter_value( "dof", absolute_path( "Universes/Cells/t" ) );
                }

                // - clone the particles
                {
                    auto action = division_onset->add( create_executable( "OnParticles::Clone", "Clone dividing" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating/Done" ) );
                    action->set_parameter_value( "to_clone", absolute_path( "Universes/Cells" ) );
                    action->set_parameter_value( "is_new", absolute_path( "Universes/Cells/is_new" ) );
                    action->set_parameter_value( "original", absolute_path( "Universes/Cells/parent" ) );
                }
            }

            // - initiate quiescence
            {
                auto quiescence_onset = state_machine->add( create_executable( "OnActions::And", "Initialize quiescence" ) );

                // - set particles ÷ which we will work
                {
                    auto filter = quiescence_onset->add( create_executable( "OnActions::And", "Filter out dividing particles which are done" ) );

                    // - clear done
                    {
                        auto action = filter->add( create_executable( "OnParticles::Clear", "Clear Done" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Dividing/Done" ) );
                    }

                    // - mark dividing
                    {
                        auto action = filter->add( create_executable( "Elementary::Comparisons::Less", "is_done = dt_division < t" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/Dividing/is_done" ) );
                        action->set_parameter_value( "a", absolute_path( "Universes/dt_division" ) );
                        action->set_parameter_value( "b", absolute_path( "Universes/Cells/t" ) );
                    }

                    // - copy done
                    {
                        auto action = filter->add( create_executable( "OnParticles::Copy", "Copy is_done to Done" ) );
                        action->set_parameter_value( "from", absolute_path( "Universes/Cells/Dividing" ) );
                        action->set_parameter_value( "to", absolute_path( "Universes/Cells/Dividing/Done" ) );
                        action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/Dividing/is_done" ) );
                    }
                }

                // - change the internal state
                {
                    auto change_state = quiescence_onset->add( create_executable( "OnActions::And", "Change the internal state" ) );

                    // - reset is_dividing
                    {
                        auto action = change_state->add( create_executable( "Elementary::Logical::Not", "is_dividing[Dividing & Done] = false" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Dividing/Done" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/is_dividing" ) );
                    }

                    // - set is_dividing
                    {
                        auto action = change_state->add( create_executable( "Elementary::Logical::Not", "is_quiescent[Dividing & Done] = true" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Dividing/Done" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/is_quiescent" ) );
                    }
                }

                // - reset the cell time
                {
                    auto action = quiescence_onset->add( create_executable( "Elementary::Reset", "t[Dividing & Done] = 0" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Dividing/Done" ) );
                    action->set_parameter_value( "dof", absolute_path( "Universes/Cells/t" ) );
                }
            }

            // - initiate growth
            {
                auto growth_onset = state_machine->add( create_executable( "OnActions::And", "Initialize growth" ) );

                // - set particles ÷ which we will work
                {
                    auto filter = growth_onset->add( create_executable( "OnActions::And", "Filter out quiescent particles which are done" ) );

                    // - clear done
                    {
                        auto action = filter->add( create_executable( "OnParticles::Clear", "Clear Done" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Quiescent/Done" ) );
                    }

                    // - mark quiescent
                    {
                        auto action = filter->add( create_executable( "Elementary::Comparisons::Less", "is_done = dt_quiescent < t" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/Quiescent/is_done" ) );
                        action->set_parameter_value( "a", absolute_path( "Universes/dt_quiescent" ) );
                        action->set_parameter_value( "b", absolute_path( "Universes/Cells/t" ) );
                    }

                    // - copy done
                    {
                        auto action = filter->add( create_executable( "OnParticles::Copy", "Copy is_done to Done" ) );
                        action->set_parameter_value( "from", absolute_path( "Universes/Cells/Quiescent" ) );
                        action->set_parameter_value( "to", absolute_path( "Universes/Cells/Quiescent/Done" ) );
                        action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/Quiescent/is_done" ) );
                    }
                }

                // - change the internal state
                {
                    auto change_state = growth_onset->add( create_executable( "OnActions::And", "Change the internal state" ) );

                    // - reset is_quiescent
                    {
                        auto action = change_state->add( create_executable( "Elementary::Logical::Not", "is_quiescent[Quiescent & Done] = false" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Quiescent/Done" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/is_quiescent" ) );
                    }

                    // - set is_dividing
                    {
                        auto action = change_state->add( create_executable( "Elementary::Logical::Not", "is_proliferating[Quiescent & Done] = true" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Quiescent/Done" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/is_proliferating" ) );
                    }
                }

                // - reset the cell time
                {
                    auto action = growth_onset->add( create_executable( "Elementary::Reset", "t[Proliferating & Done] = 0" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Quiescent/Done" ) );
                    action->set_parameter_value( "dof", absolute_path( "Universes/Cells/t" ) );
                }
            }
        }

        // - re-sort particles
        {
            auto resort = loop->add( create_executable( "OnActions::And", "Re-sort particles to corresponding collections" ) );

            // - copy cells marked as proliferating to the corresponding collection
            //   and remove those who are not longer marked
            {
                auto pipeline = resort->add( create_executable( "OnActions::And", "Update Proliferating" ) );

                // - keep marked
                {
                    auto action = pipeline->add( create_executable( "OnParticles::Keep", "Keep marked" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating" ) );
                    action->set_parameter_value( "to_keep", absolute_path( "Universes/Cells/is_proliferating" ) );
                }

                // - copy new
                {
                    auto action = pipeline->add( create_executable( "OnParticles::Copy", "Copy new" ) );
                    action->set_parameter_value( "from", absolute_path( "Universes/Cells" ) );
                    action->set_parameter_value( "to", absolute_path( "Universes/Cells/Proliferating" ) );
                    action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/is_proliferating" ) );
                }
            }

            // - copy cells marked as dividing to the corresponding collection
            //   and remove those who are not longer marked
            {
                auto pipeline = resort->add( create_executable( "OnActions::And", "Update Dividing" ) );

                // - keep marked
                {
                    auto action = pipeline->add( create_executable( "OnParticles::Keep", "Keep marked" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Dividing" ) );
                    action->set_parameter_value( "to_keep", absolute_path( "Universes/Cells/is_dividing" ) );
                }

                // - copy new
                {
                    auto action = pipeline->add( create_executable( "OnParticles::Copy", "Copy new" ) );
                    action->set_parameter_value( "from", absolute_path( "Universes/Cells" ) );
                    action->set_parameter_value( "to", absolute_path( "Universes/Cells/Dividing" ) );
                    action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/is_dividing" ) );
                }
            }

            // - copy cells marked as quiescent to the corresponding collection
            //   and remove those who are not longer marked
            {
                auto pipeline = resort->add( create_executable( "OnActions::And", "Update Quiescent" ) );

                // - keep marked
                {
                    auto action = pipeline->add( create_executable( "OnParticles::Keep", "Keep marked" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Quiescent" ) );
                    action->set_parameter_value( "to_keep", absolute_path( "Universes/Cells/is_quiescent" ) );
                }

                // - copy new
                {
                    auto action = pipeline->add( create_executable( "OnParticles::Copy", "Copy new" ) );
                    action->set_parameter_value( "from", absolute_path( "Universes/Cells" ) );
                    action->set_parameter_value( "to", absolute_path( "Universes/Cells/Quiescent" ) );
                    action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/is_quiescent" ) );
                }
            }

            // - filter the new particles
            {
                auto filter = resort->add( create_executable( "OnActions::And", "Filter new particles" ) );

                // - clear new
                {
                    auto action = filter->add( create_executable( "OnParticles::Clear", "Clear New" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Dividing/New" ) );
                }

                // - copy new cells
                {
                    auto action = filter->add( create_executable( "OnParticles::Copy", "Copy is_new to New" ) );
                    action->set_parameter_value( "from", absolute_path( "Universes/Cells/Dividing" ) );
                    action->set_parameter_value( "to", absolute_path( "Universes/Cells/Dividing/New" ) );
                    action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/is_new" ) );
                }
            }
        }

        // - update the dividing contact model with new particles
        {
            auto update_dividing_contacts = loop->add( create_executable( "OnActions::And", "Update pair collection for interactions of Dividing cells." ) );

            // - check whether both particles are still dividing
            {
                auto action = update_dividing_contacts->add( create_executable( "Contact::Models::Logical::And", "are_both_dividing = is_dividing[i] & is_dividing[j]" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Dividing cells contacts/are_both_dividing" ) );
                action->set_parameter_value( "value_1", absolute_path( "Universes/Cells/is_dividing" ) );
                action->set_parameter_value( "value_2", absolute_path( "Universes/Cells/is_dividing" ) );
            }

            // - prune contacts between non-dividing cells
            {
                auto action = update_dividing_contacts->add( create_executable( "OnParticles::Keep", "Remove contacts between non-existing particles" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts" ) );
                action->set_parameter_value( "to_keep", absolute_path( "Universes/Dividing cells contacts/are_both_dividing" ) );
            }

            // - reset is_new for contacts
            {
                auto action = update_dividing_contacts->add( create_executable( "Elementary::Reset", "is_new = false" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Dividing cells contacts/is_new" ) );
            }

            // - generate new contacts
            {
                auto action = update_dividing_contacts->add( create_executable( "Contact::Generators::OrderedFromDegreeOfFreedom", "Generate contacts for newly dividing particles" ) );
                action->set_parameter_value( "contacts", absolute_path( "Universes/Dividing cells contacts" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Dividing/New" ) );
                action->set_parameter_value( "indices", absolute_path( "Universes/Cells/parent" ) );
                action->set_parameter_value( "is_new", absolute_path( "Universes/Dividing cells contacts/is_new" ) );
            }

            // - filter the new contacts
            {
                auto filter = update_dividing_contacts->add( create_executable( "OnActions::And", "Filter new contacts" ) );

                // - clear new
                {
                    auto action = filter->add( create_executable( "OnParticles::Clear", "Keep new" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts/New" ) );
                }

                // - copy new contacts
                {
                    auto action = filter->add( create_executable( "OnParticles::Copy", "Copy new contacts" ) );
                    action->set_parameter_value( "from", absolute_path( "Universes/Dividing cells contacts" ) );
                    action->set_parameter_value( "to", absolute_path( "Universes/Dividing cells contacts/New" ) );
                    action->set_parameter_value( "to_copy", absolute_path( "Universes/Dividing cells contacts/is_new" ) );
                }
            }

            // - generate polarization for new contacts
            {
                auto action = update_dividing_contacts->add( create_executable( "Elementary::Random::OrientationInPlane", "Generate division axis for New" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts/New" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Dividing cells contacts/axis" ) );
                action->set_parameter_value( "random_number_generator", absolute_path( "Universes/PRNG" ) );
            }

            // - update shift
            {
                auto action = update_dividing_contacts->add( create_executable( "Elementary::Algebraic::Multiply", "shift[New] = axis * shift[Universes]" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts/New" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Dividing cells contacts/shift" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/Dividing cells contacts/axis" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/shift" ) );
            }

            // - shift the particles
            {
                auto action = update_dividing_contacts->add( create_executable( "Contact::Models::Elementary::Transfer::Position", "x[New & i] += shift & x[New & j] -= shift" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts/New" ) );
                action->set_parameter_value( "value", absolute_path( "Universes/Dividing cells contacts/shift" ) );
                action->set_parameter_value( "value_1", absolute_path( "Universes/Cells/x" ) );
                action->set_parameter_value( "value_2", absolute_path( "Universes/Cells/x" ) );
            }

            // - assemble the target volume
            {
                auto action = update_dividing_contacts->add( create_executable( "Contact::Models::Elementary::Average::ScalarScalar", "V_eq[New] = V[i] + V[j]" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts/New" ) );
                action->set_parameter_value( "value_1", absolute_path( "Universes/Cells/V" ) );
                action->set_parameter_value( "value_2", absolute_path( "Universes/Cells/V" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Dividing cells contacts/V_eq" ) );
            }
        }

        // - Set geometry dependent properties
        {
            auto geometry = loop->add( create_executable( "OnActions::And", "Geometry" ) );

            // - compute radius per particle
            {
                auto radius = geometry->add( create_executable( "OnActions::And", "Compute cell radius" ) );

                // - get radius cubed
                {
                    auto action = radius->add( create_executable( "Elementary::Algebraic::Divide", "r^3 = V ÷ four_pi_thirds" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Cells/r^3" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/Cells/V" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/four_pi_thirds" ) );
                }

                // - get radius
                {
                    auto action = radius->add( create_executable( "Elementary::Functions::Cbrt", "r = cbrt(r^3)" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Cells/r" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/Cells/r^3" ) );
                }
            }

            // - set mass
            {
                auto action = geometry->add( create_executable( "Elementary::Algebraic::Multiply", "m = V * rho" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Cells/m" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/Cells/V" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/rho" ) );
            }

            // - update cells volume
            {
                auto action = geometry->add( create_executable( "Contact::Models::Elementary::Add::ScalarScalar", "V_cells = V[i] + V[j]" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Dividing cells contacts/V_cells" ) );
                action->set_parameter_value( "value_1", absolute_path( "Universes/Cells/V" ) );
                action->set_parameter_value( "value_2", absolute_path( "Universes/Cells/V" ) );
            }
        }

        // - Establish contacts
        {
            auto contact_detection = loop->add( create_executable( "OnActions::And", "Contact detection" ) );

            // - determine bounding boxes
            {
                auto action = contact_detection->add( create_executable( "Contact::AABBs::Sphere", "Bounding box" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Cells" ) );
            }

            // - Generate contacts
            {
                auto action = contact_detection->add( create_executable( "Contact::Detectors::AABBTree", "Contact detector" ) );
                action->set_parameter_value( "contacts", absolute_path( "Universes/Contacts" ) );
            }

            // - Prune contacts on both dividing
            {
                auto action = contact_detection->add( create_executable( "OnParticles::PruneExistingContacts", "Prune contacts between currently dividing particles" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts" ) );
                action->set_parameter_value( "to_prune", absolute_path( "Universes/Contacts" ) );
            }
        }

        // - cell metabolism
        {
            auto cell_metabolism = loop->add( create_executable( "OnActions::And", "Cell metabolism" ) );

            // - Reset growth rate
            {
                auto action = cell_metabolism->add( create_executable( "Elementary::Reset", "dV_dt = 0" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Cells/dV_dt" ) );
            }

            // - Shrink ALL dividing particles
            {
                auto action = cell_metabolism->add( create_executable( "Contact::Models::Elementary::AddToBoth::Scalar", "dV_dt[i] += division_rate & dV_dt[j] += division_rate" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts" ) );
                action->set_parameter_value( "value", absolute_path( "Universes/division_rate" ) );
                action->set_parameter_value( "value_1", absolute_path( "Universes/Cells/dV_dt" ) );
                action->set_parameter_value( "value_2", absolute_path( "Universes/Cells/dV_dt" ) );
            }

            // - Cell growth
            {
                auto cell_growth = cell_metabolism->add( create_executable( "OnActions::And", "Cell growth" ) );

                // - update overlap volumes
                {
                    auto compute_overlap_volume = cell_growth->add( create_executable( "OnActions::And", "Compute V_overlap for Cells" ) );

                    // - update overlap volume
                    {
                        auto action = compute_overlap_volume->add( create_executable( "Contact::Models::Geometry::OverlapVolume::SphereSphere", "Compute V_overlap for 'Dividing cells contacts'" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts" ) );
                        action->set_parameter_value( "overlap_volume", absolute_path( "Universes/Dividing cells contacts/V_overlap" ) );
                    }

                    // - update overlap volume
                    {
                        auto action = compute_overlap_volume->add( create_executable( "Contact::Models::Geometry::OverlapVolume::SphereSphere", "Compute V_overlap for Cells" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
                        action->set_parameter_value( "overlap_volume", absolute_path( "Universes/Contacts/V_overlap" ) );
                    }

                    // - reset the V_overlap
                    {
                        auto action = compute_overlap_volume->add( create_executable( "Elementary::Reset", "V_overlap = 0" ) );
                        action->set_parameter_value( "dof", absolute_path( "Universes/Cells/V_overlap" ) );
                    }

                    // - distribute them
                    {
                        auto action = compute_overlap_volume->add( create_executable( "Contact::Models::Elementary::Distribute::Scalar", "V_overlap[i] += 0.5 * V_overlap & V_overlap[j] += 0.5 * V_overlap for 'Dividing cells contacts'" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts" ) );
                        action->set_parameter_value( "value", absolute_path( "Universes/Dividing cells contacts/V_overlap" ) );
                        action->set_parameter_value( "value_1", absolute_path( "Universes/Cells/V_overlap" ) );
                        action->set_parameter_value( "value_2", absolute_path( "Universes/Cells/V_overlap" ) );
                    }

                    {
                        auto action = compute_overlap_volume->add( create_executable( "Contact::Models::Elementary::Distribute::Scalar", "V_overlap[i] += 0.5 * V_overlap & V_overlap[j] += 0.5 * V_overlap for Contacts" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
                        action->set_parameter_value( "value", absolute_path( "Universes/Contacts/V_overlap" ) );
                        action->set_parameter_value( "value_1", absolute_path( "Universes/Cells/V_overlap" ) );
                        action->set_parameter_value( "value_2", absolute_path( "Universes/Cells/V_overlap" ) );
                    }

                    // - compute relative volume
                    {
                        auto action = compute_overlap_volume->add( create_executable( "Elementary::Algebraic::Divide", "V_overlap_rel = V_overlap ÷ V" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/V_overlap_rel" ) );
                        action->set_parameter_value( "a", absolute_path( "Universes/Cells/V_overlap" ) );
                        action->set_parameter_value( "b", absolute_path( "Universes/Cells/V" ) );
                    }
                }

                // - select cells which can grow
                {
                    auto filter_growing = cell_growth->add( create_executable( "OnActions::And", "Filter growing cells" ) );

                    // - select growing
                    {
                        auto action = filter_growing->add( create_executable( "Elementary::Comparisons::Less", "is_growing = V_overlap < V_crowded_relative" ) );
                        action->set_parameter_value( "result", absolute_path( "Universes/Cells/Proliferating/is_growing" ) );
                        action->set_parameter_value( "a", absolute_path( "Universes/Cells/V_overlap_rel" ) );
                        action->set_parameter_value( "b", absolute_path( "Universes/V_crowded_relative" ) );
                    }

                    // - clear growing
                    {
                        auto action = filter_growing->add( create_executable( "OnParticles::Clear", "Clear Growing" ) );
                        action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating/Growing" ) );
                    }

                    // - copy growing
                    {
                        auto action = filter_growing->add( create_executable( "OnParticles::Copy", "Copy is_growing to Growing" ) );
                        action->set_parameter_value( "from", absolute_path( "Universes/Cells/Proliferating" ) );
                        action->set_parameter_value( "to", absolute_path( "Universes/Cells/Proliferating/Growing" ) );
                        action->set_parameter_value( "to_copy", absolute_path( "Universes/Cells/Proliferating/is_growing" ) );
                    }
                }

                // - Compute V / V_infty
                {
                    auto action = cell_growth->add( create_executable( "Elementary::Algebraic::Divide", "'V ÷ V_infty' = V ÷ V_infty" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Cells/Proliferating/Growing/V ÷ V_infty" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/Cells/V" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/V_infty" ) );
                }

                // - Compute 1 - V / V_infty
                {
                    auto action = cell_growth->add( create_executable( "Elementary::Algebraic::Subtract", "'1 - V ÷ V_infty' = 1 - 'V ÷ V_infty'" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Cells/Proliferating/Growing/1 - V ÷ V_infty" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/one" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/Cells/Proliferating/Growing/V ÷ V_infty" ) );
                }

                // - Compute V * ( 1 - V / V_infty )
                {
                    auto action = cell_growth->add( create_executable( "Elementary::Algebraic::Multiply", "'V (1 - V ÷ V_infty)' = V * '1 - V ÷ V_infty'" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Cells/Proliferating/Growing/V * ( 1 - V ÷ V_infty )" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/Cells/V" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/Cells/Proliferating/Growing/1 - V ÷ V_infty" ) );
                }

                // - Compute dV_dt
                {
                    auto action = cell_growth->add( create_executable( "Elementary::Algebraic::Multiply", "dV_dt = inv_tau * 'V * ( 1 - V ÷ V_infty )'" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating/Growing" ) );
                    action->set_parameter_value( "result", absolute_path( "Universes/Cells/dV_dt" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/inv_tau" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/Cells/Proliferating/Growing/V * ( 1 - V ÷ V_infty )" ) );
                }
            }
        }

        // - Set frictions
        {
            auto frictions = loop->add( create_executable( "OnActions::And", "Frictions" ) );

            // - reset friction matrix
            {
                auto action = frictions->add( create_executable( "Elementary::Reset", "gamma = 0" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Cells/gamma" ) );
            }

            // - compute friction matrix
            {
                auto action = frictions->add( create_executable( "Frictions::Stokes", "gamma += 6 * pi * eta * r" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Cells" ) );
            }
        }

        // - Mass matrix
        {
            auto mass_matrix = loop->add( create_executable( "OnActions::And", "Mass matrix preparation" ) );

            // - reset contact friction matrix
            {
                auto action = mass_matrix->add( create_executable( "Elementary::Reset", "Reset Contacts mass matrix" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Contacts/M" ) );
            }

            // - reset contact friction matrix for dividing cells
            {
                auto action = mass_matrix->add( create_executable( "Elementary::Reset", "Reset Dividing cells contacts mass matrix" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Dividing cells contacts/M" ) );
            }

            // - set mass matrix
            {
                auto action = mass_matrix->add( create_executable( "Elementary::Algebraic::Multiply", "Set mass matrix" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Cells/M" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/identity" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/Cells/m" ) );
            }
        }

        // - Compute forces
        {
            auto forces = loop->add( create_executable( "OnActions::And", "Forces" ) );

            // - reset forces
            {
                auto action = forces->add( create_executable( "Elementary::Reset", "Reset forces" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Cells/F" ) );
            }

            // - friction force
            {
                auto action = forces->add( create_executable( "Forces::StokesDrag", "Apply Stokes drag" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Cells" ) );
            }

            // - compute separation force
            {
                auto action = forces->add( create_executable( "Contact::Models::Division::Dumbbell::Implicit", "Division force" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Dividing cells contacts" ) );
                action->set_parameter_value( "k", absolute_path( "Universes/k_div" ) );
                action->set_parameter_value( "gamma_tangential", absolute_path( "Universes/gamma_tangential_div" ) );
                action->set_parameter_value( "gamma_normal", absolute_path( "Universes/gamma_normal_div" ) );
                action->set_parameter_value( "x_1", absolute_path( "Universes/Cells/x" ) );
                action->set_parameter_value( "v_1", absolute_path( "Universes/Cells/v" ) );
                action->set_parameter_value( "F_1", absolute_path( "Universes/Cells/F" ) );
            }

            // - add repulsion
            {
                auto action = forces->add( create_executable( "Contact::Models::Collisions::JKR::Damped::SphereSphere::Implicit", "Cells repulsion" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
            }
        }

        // - IO
        if( !without_io ) {
            auto io = loop->add( create_executable( "OnActions::Queue", "IO" ) );

            // - check whether we should print out
            {
                auto action = io->add( create_executable( "OnActions::Triggers::ExecuteWhileLessOrEqual", "Check time" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/t_out" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/t" ) );
            }

            // - save the cells
            {
                auto action = io->add( create_executable( "IO::SimpleVTKWriter", "VTK writer for Cells" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Cells" ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/frame" ) );
            }

            // - print whole simulation to .xml.gz
            {
                auto action = io->add( create_executable( "IO::Save", "Write whole simulation data" ) );
                action->set_parameter_value( "root", absolute_path( "Universes" ) );
                action->set_parameter_value( "file_index", absolute_path( "Universes/frame" ) );
            }

            // - increase frame
            {
                auto action = io->add( create_executable( "Elementary::Algebraic::Increment", "Increment frame counter" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/frame" ) );
            }

            // - update next output time
            {
                auto action = io->add( create_executable( "Elementary::Algebraic::Add", "Advance output time" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/t_out" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/dt_out" ) );
            }
        }

        // - integration pipeline
        {
            auto integration = loop->add( create_executable( "OnActions::And", "Integration" ) );

            // - integrate volume
            {
                auto action = integration->add( create_executable( "Integration::ForwardEuler", "Volume integration" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Cells/V" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Cells/dV_dt" ) );
            }

            // - reset iteration counter
            {
                auto action = integration->add( create_executable( "Elementary::Reset", "Zero iteration counter" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/CG_iterations" ) );
            }

            // - CG solver
            {
                auto action = integration->add( create_executable( "Solvers::ConjugateGradient", "CG solver of sparse system" ) );
                action->set_parameter_value( "x", std::make_unique< ComponentList >( absolute_path( "Universes/Cells/a" ) ) );
                action->set_parameter_value( "y", std::make_unique< ComponentList >( absolute_path( "Universes/Cells/F" ) ) );
                action->set_parameter_value( "D", std::make_unique< ComponentList >( absolute_path( "Universes/Cells/M" ) ) );
                action->set_parameter_value( "S",
                                             std::make_unique< ComponentList >( absolute_path( "Universes/Dividing cells contacts/M" ),
                                                                                absolute_path( "Universes/Contacts/M" ) ) );
                action->set_parameter_value( "iterations", absolute_path( "Universes/CG_iterations" ) );
                action->set_parameter_value( "relative_tolerance", absolute_path( "Universes/CG_tolerance" ) );
            }

            // - Project acceleration
            //   Note: practically not needed we are quite stable even without it
            {
                auto action = integration->add( create_executable( "Elementary::Algebraic::Dot", "Project acceleration to the plane" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Cells/a" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/projection" ) );
            }

            // - integrate velocities
            {
                auto action = integration->add( create_executable( "Integration::ForwardEuler", "Velocity integration" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Cells/v" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Cells/a" ) );
            }

            // - integrate positions
            {
                auto action = integration->add( create_executable( "Integration::ForwardEuler", "Integrate positions" ) );
                action->set_parameter_value( "y", absolute_path( "Universes/Cells/x" ) );
                action->set_parameter_value( "dy_dt", absolute_path( "Universes/Cells/v" ) );
                action->set_parameter_value( "dt", absolute_path( "Universes/dt" ) );
            }
        }

        // - advance time
        {
            auto advance_time = loop->add( create_executable( "OnActions::And", "Advance time" ) );

            // - advance cell clock
            {
                auto action = advance_time->add( create_executable( "OnActions::And", "Advance cell clock" ) );
                {
                    auto action = advance_time->add( create_executable( "Elementary::Algebraic::Add", "Of Quiescent" ) );
                    action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Quiescent" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/Cells/t" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/dt" ) );
                }
            {
                auto action = advance_time->add( create_executable( "Elementary::Algebraic::Add", "Of Dividing" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Dividing" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/Cells/t" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/dt" ) );
            }
            {
                auto action = advance_time->add( create_executable( "Elementary::Algebraic::Add", "Of Growing" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Cells/Proliferating/Growing" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/Cells/t" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/dt" ) );
            }
            }

            // - advance simulation time
            {
                auto action = advance_time->add( create_executable( "Elementary::Algebraic::Add", "Advance simulation time" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/t" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/dt" ) );
            }
        }

        // - store elapsed time of simulation
        {
            auto action = loop->add( create_executable( "OnActions::StoreElapsedTime", "Store simulation runtime" ) );
            action->set_parameter_value( "elapsed_time", absolute_path( "Universes/t_elapsed" ) );
            action->set_parameter_value( "executable", absolute_path( "Loop" ) );
        }
    }

    // ----------------------------------------
    // Execution
    // ----------------------------------------
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
