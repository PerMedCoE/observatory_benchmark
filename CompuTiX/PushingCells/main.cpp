//! \example Collisions/PushingCells/main.cpp
//! \section collisions_pushing_cells Two cells pusing each other
//!
//! \subsection collisions_pushing_cells_problem_statement Problem statement
//! This simulation illustrates the dynamics of two cells, identical in radius and properties, pushed towards each other with an external force
//! which is removed when their overlap reaches a critical value equal to \f$10\%\f$ the volume of the spheres. JKR model is tested in this
//! example rather than the Hertz one and friction with the external medium is modeled as a viscous friction.
//!
//! \subsubsection collisions_pushing_cells_problem_statement_equation_motion Equation of motion
//! The system to solve for the two spheres is then composed of the two equation of motion for velocity and position:
//! \f{align*}
//! \gamma \vec{ v }(t) &= \vec{F}_\text{loc} + \vec{F}_\text{Hertz} + \vec{F}_\text{JKR}
//! \\ \frac{\mathrm{d}\vec{x}}{\mathrm{d}t}(t) &= \vec{v}(t)
//! \f}
//! with \f$\vec{ x }\f$ the position, \f$\vec{ v }\f$ the velocity, \f$\vec{F}_\text{loc}\f$ the external force, \f$\vec{F}_\text{JKR}\f$ a
//! collision adhesive force force and \f$\gamma\f$ the friction coefficient with the external medium.
//!
//! \subsubsection collisions_pushing_cells_problem_statement_force External force
//! Two forces, equal and opposite in direction, are applied to the two spheres until the value of the intersection volume reaches 10% their volume value:
//! \f[
//! F_{\text{loc}}(\delta) =
//! \begin{cases}
//! F_{\text{loc}}, & \text{if} \; V_{\text{overlap}} \leq \theta \cdot \frac{4}{3} \pi r^3
//! \\ 0, & \text{if} \; V_{\text{overlap}} > \theta \cdot \frac{4}{3} \pi r^3
//! \end{cases}
//! \f]
//! where \f$\delta\f$ is the spheres' overlap, \f$r\f$ the radius of the two spheres and \f$\theta\f$ the threshold value, set equal to \f$0.1\f$ in this case to capture the \f$10\%\f$ volume overlap.
//!
//! \subsubsection collisions_pushing_cells_problem_statement_stokes Stokes drag force
//! Stokes drag force is used to model the viscous firction, assuming a homogeneous isotropic friction coefficient that mimics friction of a cell with the extracellular matrix in an idealised way.
//! \f[
//! \vec{F}^{\text{Stokes}} = - \gamma \vec{v}^{\text{rel}}
//! \f]
//! where \f$\gamma\f$ is the friction coefficient or friction matrix for a given particle and \f$\vec{v}^{rel}\f$ is a relative velocity of the particle with respect to the fluid.
//! Implementation relies on the action \link CompuTiX::Actions::Forces::StokesDrag StokesDrag\endlink, which apply directly the Stokes drag on the particle with negative force sign.
//!
//! \subsubsection collisions_pushing_cells_problem_statement_jkr JKR Model
//! \link CompuTiX::Actions::Contact::Models::Collisions::JKR JKR\endlink (Johnson-Kendall-Roberts) model, with damping proportional to contact area, can be used to model the collision of two spheres.
//! The \link CompuTiX::ContactModelComponents::Forces::JKR JKR force\endlink together with \link CompuTiX::ContactModelComponents::Forces::Hertz Hertz force\endlink are applied here:
//! \f[
//! \vec{F} = \vec{F}_\text{Hertz} + \vec{F}_\text{JKR} = - \frac{4}{3} E^* \frac{a^3}{R} \hat{n} + \sqrt{8 \pi \gamma^* E^* a^3}\hat{n},
//! \f]
//! where \f$a\f$ is the contact radius, \f$1/R\f$ is the curvature, \f$\hat{n}\f$ the normal direction, \f$E^*\f$ the effective Young's modulus and \f$\gamma^*\f$ the contact adhesion energy density.
//! Implementation relies on the \link CompuTiX::Actions::Contact::Models::Collisions::JKR::Damped::SphereSphere JKR\endlink namespace actions for \link CompuTiX::ContactModelComponents::IntegrationSchemes::Explicit explicit\endlink and \link CompuTiX::ContactModelComponents::IntegrationSchemes::Overdamped overdamped\endlink integration schemes, which apply directly Hertz repulsive force and JKR adhesive force on the spheres.
//!
//! \subsubsection collisions_pushing_cells_problem_stamement_equilibrium_overlap Expected equilibrium overlap
//! The equilibrium overlap for the two spheres, when the JKR model is used, can be computed by equaling the repulsive component (Hertz) with the adhesive one (JKR), resulting in the following expression when solving for the contact radius \f$a\f$:
//! \f[
//! a_{eq} = \sqrt[3]{\frac{9 \pi \gamma^* R^2}{2 E^*}}.
//! \f]
//! The eqilibrium overlap value, \f$\delta_{eq}\f$, is then obtained as:
//! \f[
//! \delta_{eq} = \frac{a_{eq}^2}{R} - \sqrt{\frac{2 \pi \gamma^* a_{eq}}{E^*}},
//! \f]
//! where \f$\gamma^*\f$ and \f$E^*\f$ are respectively the contact adhesion energy and the effective Young's modulus from the JKR model.
//!
//! \subsection collisions_pushing_cells_integration_scheme Integration scheme
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
//! \vec{F} = F_\text{loc} + \vec{F}^\text{Stokes} + \vec{F}_\text{Hertz} + \vec{F}_\text{JKR}.
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
//! \subsection collisions_pushing_cells_simulation_pipeline Simulation pipeline
//! The simulation consists of the following steps executed in a \link CompuTiX::Actions::OnActions::Loop Loop\endlink:
//! * Check simulation time (`OnActions::Triggers::ExecuteWhileLess`)
//! * Geometric pipeline (`OnActions::And`)
//!     * Zero overlap (`Elementary::Reset`)
//!     * Zero volume overlap (`Elementary::Reset`)
//!     * Get Sphere-Sphere contact overlap (`Contact::Models::Geometry::Overlap::SphereSphere`)
//!     * Get Sphere-Sphere contact volume overlap (`Contact::Models::Geometry::OverlapVolume::SphereSphere`)
//! * Forces (`OnActions::And`)
//!     * Zero total force (`Elementary::Reset`)
//!     * Zero mass matrix (`Elementary::Reset`)
//!     * Set mass matrix (`Elementary::Algebraic::Multiply`)
//!     * Reset external force (`OnActions::Queue`)
//!         * Trigger point based on overlap volume (`OnActions::Triggers::ExecuteWhileLess`)
//!         * Zero local force (`Elementary::Reset`)
//!     * Add initial local force (`Elementary::Algebraic::Add`)
//!     * Sphere-Sphere JKR contact model (`Contact::Models::Collisions::JKR::Damped::SphereSphere::Overdamped`)
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
//!                     :Zero volume overlap\nElementary::Reset;
//!                     :Get Sphere-Sphere contact overlap\nContact::Models::Geometry::Overlap::SphereSphere;
//!                     :Get Sphere-Sphere contact volume overlap\nContact::Models::Geometry::OverlapVolume::SphereSphere;
//!                     (E)
//!                 }
//!                 partition "Forces\nOnActions::And" {
//!                     :Zero total Sphere force\nElementary::Reset;
//!                     :Reset mass tensor\nElementary::Reset;
//!                     :Set mass tensor\nElementary::Algebraic::Multiply;
//!                     partition "Reset external force at trigger point\nOnActions::Queue" {
//!                         if( Execute when overlap volume is higher than 10 % of sphere volume\nOnActions::Triggers::ExecuteWhileLess ) then( false )
//!                         else( true )
//!                             :Clear local force\nElementary::Reset;
//!                         endif
//!                     (E)
//!                     }
//!                     :Apply local force\nElementary::Algebraic::Add;
//!                     :Sphere-Sphere JKR contact model\nContact::Models::Collisions::JKR::Damped::SphereSphere::Overdamped;
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
//! \subsection collisions_pushing_cells_data_layout Data layout
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
//!     - r_contact - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the contact radius.
//!     Physical dimension: \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink.
//!     - tension - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the interfacial tension of the contact.
//!     Physical dimension: \link CompuTiX::SIUnits::newton / CompuTiX::SIUnits::meter \f$\unit{\newton\per\meter}\f$\endlink.
//!     - gamma_tangential - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the tangential friction coefficient.
//!     Physical dimension: \link CompuTiX::SIUnits::pascal * CompuTiX::SIUnits::second \ CompuTiX::SIUnits::meter \f$\unit{\pascal \second\per\meter}\f$\endlink.
//!     - gamma_normal - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the normal friction coefficient.
//!     Physical dimension: \link CompuTiX::SIUnits::pascal * CompuTiX::SIUnits::second \ CompuTiX::SIUnits::meter \f$\unit{\pascal \second\per\meter}\f$\endlink.
//!     - relative_tolerance - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the JKR model relative tolerance.
//!     Physical dimension: \link CompuTiX::SIUnits::dimensionless \f$1\f$\endlink.
//!     - overlap - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the overlap between the two spheres.
//!     Physical dimension: \link CompuTiX::SIUnits::meter \f$\unit{\meter}\f$\endlink.
//!     - V_overlap - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the volume of the overlap between the two spheres.
//!     Physical dimension: \link CompuTiX::SIUnits::meter ^ 3 \f$\unit{\meter^3}\f$\endlink.
//!     - V_limit - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Scalar> DegreeOfFreedom\endlink of \link CompuTiX::Types::Scalar Scalar\endlink type representing the threshold volume for the overlap to trigger removal of the external force.
//!     Physical dimension: \link CompuTiX::SIUnits::meter ^ 3 \f$\unit{\meter^3}\f$\endlink.
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
//!     - F_loc - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Vector> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Vector Vector\endlink type representing the external force initially applied on the spheres.
//!       Physical dimension: \link CompuTiX::SIUnits::newton \f$\unit{\newton}\f$\endlink.
//! - Contacts - \link CompuTiX::Components::Collections::ParticleCollection ParticleCollection\endlink representing the spheres.
//!     - M - \link CompuTiX::Components::DegreesOfFreedom::DegreeOfFreedom<CompuTiX::Types::Matrix> DegreeOfFreedom\endlink of
//!       \link CompuTiX::Types::Matrix Matrix\endlink type representing the spheres' mass tensors.
//!       Physical dimension: \link CompuTiX::SIUnits::kilogram \f$\unit{\kilogram}\f$\endlink.
//!
//! \subsection collisions_pushing_cells_parameters_values Parameters' values
//! The following table summarizes the parameters' values used and how the constants relate to each other.
//!
//! | Parameter                | Symbol                 | Value      	      | Unit         	            | Derivation      |
//! |--------------------------|------------------------|---------------------|-----------------------------|-----------------|
//! | Target time 	           | \f$t_\text{end}\f$     | \f$10\f$	          | \f$\unit{\minute}\f$        | prescribed	  |
//! | Time step 	           | \f$\Delta t\f$         | \f$0.1\f$	          | \f$\unit{\minute}\f$        | prescribed	  |
//! | Cell's radius            | \f$r\f$		        | \f$5\f$             | \f$\unit{\micro\meter}\f$   | prescribed      |
//! | Initial force            | \f$F_\text{loc}\f$     | \f$\begin{pmatrix} 100 & 0 & 0 \end{pmatrix}\f$   | \f$\unit{\kilogram\micro\meter\per\minute\tothe{2}}\f$   | free  |
//! | Medium friction coefficient  | \f$\gamma\f$  | \f$10\f$   | \f$\unit{\kilogram\per\minute}\f$ | \f$\gamma = 0.1 F_\text{loc}\f$ |
//! | Young's modulus              | \f$E\f$	   | \f$750\f$  | \f$\unit{\pascal}\f$              | free |
//! | Poisson's ratio              | \f$\nu\f$	   | \f$0.5\f$  | \f$1\f$                           | free |
//! | Adhesion energy density      | \f$E_\text{adh}\f$	| \f$10^{-4}\f$  | \f$\unit{\joule\per\meter\tothe{2}}\f$  | free |
//! | Tangential friction coefficient  | \f$\gamma_\text{tang}\f$	     | \f$10^{8}\f$   | \f$\unit{\newton\per\meter}\f$  | free |
//! | Normal friction coefficient    | \f$\gamma_\text{norm}\f$	  | \f$10^{8}\f$          | \f$\unit{\newton\per\meter}\f$  | free |

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

    // - contact model DoFs: interfacial tension (tension), tangential friction coefficient (gamma_tangential), normal friction coefficient (gamma_normal), mass tensor (M), relative tolerance, ten percent of the cell volume (V_limit), contact radius (r_contact), overlap, volume of the intersection (volume_overlap), spheres' radius (r)
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "tension", SIUnits::newton / SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma_tangential", SIUnits::pascal * SIUnits::second / SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "gamma_normal", SIUnits::pascal * SIUnits::second / SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "relative_tolerance", SIUnits::dimensionless ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "M", SIUnits::kilogram ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "r_contact", SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_limit", SIUnits::meter ^ 3 ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "overlap", SIUnits::meter ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "V_overlap", SIUnits::meter ^ 3 ) );
    universes->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "r", SIUnits::meter ) );

    //Prepare DoFs for Spheres
    // - kinematic DoFs: position (x), velocity (v), acceleration (a)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Position >::create( "x", SIUnits::meter ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "v", SIUnits::meter / SIUnits::second ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "a", SIUnits::meter / ( SIUnits::second ^ 2 ) ) );

    // - geometric DoFs: radius (r)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "r", SIUnits::meter ) );

    // - dynamic DoFs: mass (m), mass tensor (M), identity matrix (id), local initial force (F_loc), force (F), friction coefficient (gamma)
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Scalar >::create( "m", SIUnits::kilogram ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "M", SIUnits::kilogram ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Matrix >::create( "id", SIUnits::dimensionless ) );
    spheres->add( DegreesOfFreedom::DegreeOfFreedom< Types::Vector >::create( "F_loc", SIUnits::newton ) );
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
    constexpr Types::Scalar t_end = 10.; // [ min ]
    //Time-step size
    constexpr Types::Scalar dt = 0.1; // [ min ]

    // - Physical and geometrical parameters:
    //Hepatocyte mass
    constexpr Types::Scalar mass_hepatocyte = 1.; // [ kg ]
    //Initial positions
    const Types::Position x_init_1 = Types::Position::Zero(); // [ m ]
    const Types::Position x_init_2 = 30e-6 * Types::Position::UnitX(); // [ m ]
    //Initial velocity
    const Types::Vector v_init = 10. * Types::Vector::UnitX(); // [ micro m / min ]
    //Initial external local force
    const Types::Vector F_loc = 100. * Types::Vector::UnitX(); // [ kg micro m / min^2 ]
    //Spheres radius
    constexpr Types::Scalar r = 5e-6; // [ m ]
    //10% of sphere volume
    constexpr Types::Scalar V_lim = 0.1 * 4. / 3. * Math::pi * Math::pow< 3 >( r ); // [ m^3 ]
    //Young's modulus
    constexpr Types::Scalar E = 750.; // [ Pa ]
    //Poisson's ratio
    constexpr Types::Scalar nu = 0.5; // [ 1 ]
    //Friction coefficient
    const Types::Matrix gamma = 10. * Types::Matrix::Identity(); // [ kg / min ]
    //Adhesion energy density
    constexpr Types::Scalar adhesion_energy_density = 1e-4; // [ J / m^2 ]

    // - Collision parameters:
    //Tangential friction coefficient
    constexpr Types::Scalar gamma_tang = 1e8; // [ Pa s / m ]
    //Normal friction coefficient
    constexpr Types::Scalar gamma_norm = 1e8; // [ Pa s / m ]
    //Contact interfacial tension
    constexpr Types::Scalar tau = 1e-4; // [ N / m ]

    // - IO
    const std::string output_dir = result["output-dir"].as< std::string >();

    //Create unverse and sphere
    auto universe = [&]() {
        // View for universe
        auto u_view = Particles::make_particles_view( Access::Modes::read_write, universes );
        auto u = u_view.add();

        // Set values for universe
        u.set< Types::Scalar >( Access::Modes::read_write, "dt", SIUnits::minute, dt );
        u.set< Types::Scalar >( Access::Modes::read_write, "t_end", SIUnits::minute, t_end );
        u.set< Types::Scalar >( Access::Modes::read_write, "tension", SIUnits::newton / SIUnits::meter, tau );
        u.set< Types::Scalar >( Access::Modes::read_write, "gamma_tangential", SIUnits::pascal * SIUnits::second / SIUnits::meter, gamma_tang );
        u.set< Types::Scalar >( Access::Modes::read_write, "gamma_normal", SIUnits::pascal * SIUnits::second / SIUnits::meter, gamma_norm );
        u.set< Types::Scalar >( Access::Modes::read_write, "relative_tolerance", SIUnits::dimensionless, Math::relative_tolerance );
        u.set< Types::Scalar >( Access::Modes::read_write, "V_limit", SIUnits::meter ^ 3, V_lim );
        u.set< Types::Scalar >( Access::Modes::read_write, "r", SIUnits::meter, r );

        // View for spheres
        auto s_view = Particles::make_particles_view( Access::Modes::read_write, spheres );
        auto s1 = s_view.add( u );
        auto s2 = s_view.add( u );

        // Set values for first sphere
        s1.set< Types::Scalar >( Access::Modes::read_write, "m", SIUnits::kilogram, mass_hepatocyte );
        s1.set< Types::Position >( Access::Modes::read_write, "x", SIUnits::meter, x_init_1 );
        s1.set< Types::Vector >( Access::Modes::read_write, "v", SIUnits::micro * SIUnits::meter / SIUnits::minute, v_init );
        s1.set< Types::Scalar >( Access::Modes::read_write, "r", SIUnits::meter, r );
        s1.set< Types::Vector >( Access::Modes::read_write, "F_loc", SIUnits::kilogram * ( SIUnits::micro * SIUnits::meter ) / ( SIUnits::minute ^ 2 ), F_loc );
        s1.set< Types::Matrix >( Access::Modes::read_write, "gamma", SIUnits::kilogram / SIUnits::minute, gamma );
        s1.set< Types::Scalar >( Access::Modes::read_write, "E", SIUnits::pascal, E );
        s1.set< Types::Scalar >( Access::Modes::read_write, "nu", SIUnits::dimensionless, nu );
        s1.set< Types::Scalar >( Access::Modes::read_write, "e_adh", SIUnits::joule / ( SIUnits::meter ^ 2 ), adhesion_energy_density );
        s1.set< Types::Matrix >( Access::Modes::read_write, "id", SIUnits::dimensionless, Types::Matrix::Identity() );

        // Set values for second sphere
        s2.set< Types::Scalar >( Access::Modes::read_write, "m", SIUnits::kilogram, mass_hepatocyte );
        s2.set< Types::Position >( Access::Modes::read_write, "x", SIUnits::meter, x_init_2 );
        s2.set< Types::Vector >( Access::Modes::read_write, "v", SIUnits::micro * SIUnits::meter / SIUnits::minute, -v_init );
        s2.set< Types::Scalar >( Access::Modes::read_write, "r", SIUnits::meter, r );
        s2.set< Types::Vector >( Access::Modes::read_write, "F_loc", SIUnits::kilogram * ( SIUnits::micro * SIUnits::meter ) / ( SIUnits::minute ^ 2 ), -F_loc );
        s2.set< Types::Matrix >( Access::Modes::read_write, "gamma", SIUnits::kilogram / SIUnits::minute, gamma );
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
            // -- reset overlap volume
            {
                auto action = geom_pipeline->add( create_executable( "Elementary::Reset", "Zero volume overlap" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/V_overlap" ) );
            }
            // -- get the overlap
            {
                auto action = geom_pipeline->add( create_executable( "Contact::Models::Geometry::Overlap::SphereSphere", "Get Sphere-Sphere contact overlap" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
                action->set_parameter_value( "overlap", absolute_path( "Universes/overlap" ) );
            }
            // -- get the volume overlap
            {
                auto action = geom_pipeline->add( create_executable( "Contact::Models::Geometry::OverlapVolume::SphereSphere", "Get Sphere-Sphere contact volume overlap" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
                action->set_parameter_value( "overlap_volume", absolute_path( "Universes/V_overlap" ) );
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

            // -- reset the mass tensor
            {
                auto action = forces->add( create_executable( "Elementary::Reset", "Reset mass tensor" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Spheres" ) );
                action->set_parameter_value( "dof", absolute_path( "Universes/Spheres/M" ) );
            }

            // -- set mass tensor
            {
                auto action = forces->add( create_executable( "Elementary::Algebraic::Multiply", "Set mass tensor" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Spheres/M" ) );
                action->set_parameter_value( "a", absolute_path( "Universes/Spheres/id" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/Spheres/m" ) );
            }

            // -- external force reset
            {
                auto external_force = forces->add( create_executable( "OnActions::Queue", "Reset external force at trigger point" ) );
                // --- execution condition
                {
                    auto action = external_force->add( create_executable( "OnActions::Triggers::ExecuteWhileLess", "Execute when overlap volume is higher than 10% of sphere volume" ) );
                    action->set_parameter_value( "a", absolute_path( "Universes/V_limit" ) );
                    action->set_parameter_value( "b", absolute_path( "Universes/V_overlap" ) );
                }
                // --- clears force (forever)
                {
                    auto action = external_force->add( create_executable( "Elementary::Reset", "Clear local force" ) );
                    action->set_parameter_value( "dof", absolute_path( "Universes/Spheres/F_loc" ) );
                }
            }

            // -- apply external force
            {
                auto action = forces->add( create_executable( "Elementary::Algebraic::Add", "Apply local force" ) );
                action->set_parameter_value( "result", absolute_path( "Universes/Spheres/F" ) );
                action->set_parameter_value( "b", absolute_path( "Universes/Spheres/F_loc" ) );
            }

            // -- compute JKR interaction force and set mass matrix
            {
                auto action = forces->add( create_executable( "Contact::Models::Collisions::JKR::Damped::SphereSphere::Overdamped", "Sphere-Sphere JKR contact model" ) );
                action->set_parameter_value( "collection", absolute_path( "Universes/Contacts" ) );
                action->set_parameter_value( "r_contact", absolute_path( "Universes/r_contact" ) );
                action->set_parameter_value( "M", absolute_path( "Universes/M" ) );
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
                auto action = io_pipeline->add( create_executable( "IO::Save", "Write VTK files for faces" ) );
                action->set_parameter_value( "root", absolute_path( "Universes" ) );
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
              << "    Final simulation time: " << t / 60. << "\n"
              << "    Elapsed time: " << t_elapsed << "\n";

    return 0;
}
