#include <cxxtest/TestSuite.h>
#include "CheckpointArchiveTypes.hpp"
#include "AbstractCellBasedTestSuite.hpp"
#include "HoneycombMeshGenerator.hpp"
#include "GeneralisedLinearSpringForce.hpp"
#include "RandomNumberGenerator.hpp"
#include "SmartPointers.hpp"
/*
 * The {{{SimpleOxygenBasedCellCycleModel}}} header file defines a cell-cycle model in which
 * a cell's rate of progress through G1 phase changes over time in a simple manner, according
 * to the local oxygen concentration. We also include the {{{WildTypeCellMutationState}}}
 * header file, which defines a wild type cell mutation state that we will use to construct
 * cells. A cell mutation state is always required when constructing a cell, however
 * in earlier simulation tutorial we used a helper classes (({{{CellsGenerator}}} and {{{CryptCellsGenerator}}}) that
 * allowed us to avoid having to construct cells directly.
 */
#include "StochasticOxygenBasedCellCycleModel.hpp"
#include "WildTypeCellMutationState.hpp"
#include "StemCellProliferativeType.hpp"
#include "ApoptoticCellKiller.hpp"
#include "CellsGenerator.hpp"
#include "CellLabelWriter.hpp"

/*
 * The next three header files define: a PDE that describes how oxygen is transported via through the
 * domain via diffusion and is consumed by live cells; a constant-valued boundary condition to
 * associate with the PDE; and a PDE modifier class, which is passed to the simulation object and
 * handles the numerical solution of any PDEs.
 */
#include "CellwiseSourceEllipticPde.hpp"
#include "ConstBoundaryCondition.hpp"
#include "EllipticGrowingDomainPdeModifier.hpp"

/*
 * We use an {{{OffLatticeSimulation}}}.
 */
#include "FixedG1GenerationalCellCycleModel.hpp"
#include "OffLatticeSimulation.hpp"
/*
 * The header file {{{PetscSetupAndFinalize.hpp}}} must be included in all tests which use Petsc. This is
 * a suite of data structures and routines that are used in the finite element
 * PDE solvers, which is how we solve the oxygen transport PDE.
 */
#include "VoronoiDataWriter.hpp"
#include "PetscSetupAndFinalize.hpp"

/*
 * Having included all the necessary header files, we proceed by defining the test class.
 */
class TestPlosThalia : public AbstractCellBasedTestSuite
{
private:
    MutableMesh<3,3>* Make3dMesh(unsigned width=3, unsigned height=3, unsigned depth=3)
    {
        MutableMesh<3,3>* p_mesh = new MutableMesh<3,3>;
        p_mesh->ConstructCuboid(width, height, depth);
        TrianglesMeshWriter<3,3> mesh_writer("", "3dSpringMesh");
        mesh_writer.WriteFilesUsingMesh(*p_mesh);

        return p_mesh;
    }
public:
    void TestSpheroidTumourPlosThalia()
    {
        /*
         * This first line can be ignored: it is a macro which just says
         * don't run this test if in parallel.
         */
        EXIT_IF_PARALLEL;

        /*
         * First we want to create a '''non-periodic''' 'honeycomb' mesh.
         * We use the honeycomb mesh generator, as before, saying 10 cells wide
         * and 10 cells high. Note that the thickness of the ghost nodes layer is
         * 0, i.e. there are no ghost nodes, and the {{{false}}} indicates that the
         * returned mesh is '''not''' cylindrical. In contrast to the crypt simulation
         * tutorial, here we call {{{GetMesh()}}} on the {{{HoneycombMeshGenerator}}}
         * object to return the mesh, which is of type {{{MutableMesh}}}.
         */
        std::vector<Node<3>*> nodes;
        nodes.push_back(new Node<3>(0, true,  0.0, 0.0, 0.0));
        nodes.push_back(new Node<3>(1, true,  1.0, 1.0, 0.0));
        nodes.push_back(new Node<3>(2, true,  1.0, 0.0, 1.0));
        nodes.push_back(new Node<3>(3, true,  0.0, 1.0, 1.0));
        nodes.push_back(new Node<3>(4, true, 0.5, 0.5, 0.5));
        MutableMesh<3,3> mesh(nodes);

        MAKE_PTR(WildTypeCellMutationState, p_state);
        MAKE_PTR(StemCellProliferativeType, p_stem_type);

        std::vector<CellPtr> cells;
        /*
         * Next, we need to create some cells. Unlike in the the crypt simulation
         * tutorial, we don't just use a {{{CellsGenerator}}} class, but do it manually,
         * in a loop. First, we define a {{{std::vector}}} of cell pointers.
         */

        /*
         * This line defines a mutation state to be used for all cells, of type
         * `WildTypeCellMutationState` (i.e. 'healthy'):
         */


        /*
         * Now we loop over the nodes...
         */
        for (unsigned i=0; i<nodes.size(); i++)
        {
            StochasticOxygenBasedCellCycleModel* p_model = new StochasticOxygenBasedCellCycleModel();
            p_model->SetDimension(3);
            p_model->SetStemCellG1Duration(4.0);
            p_model->SetHypoxicConcentration(0.1);
            p_model->SetQuiescentConcentration(0.3);
            p_model->SetCriticalHypoxicDuration(8);
            double birth_time = -RandomNumberGenerator::Instance()->ranf()*
                                (  p_model->GetStemCellG1Duration()
                                 + p_model->GetSG2MDuration() );

            CellPtr p_cell(new Cell(p_state, p_model));
            p_cell->SetBirthTime(birth_time);
            p_cell->SetCellProliferativeType(p_stem_type);
            cells.push_back(p_cell);
        }

        

        /*
         * Now that we have defined the cells, we can define the {{{CellPopulation}}}. We use a
         * {{{MeshBasedCellPopulation}}} since although the cell population is mesh-based, it does
         * not include any ghost nodes. The constructor takes in the mesh and the cells vector.
         */
        MeshBasedCellPopulation<3> cell_population(mesh, cells);
        cell_population.SetAbsoluteMovementThreshold(DBL_MAX);
        cell_population.SetWriteVtkAsPoints(false);

        cell_population.SetDataOnAllCells("oxygen", 1.0);
        // cell_population.AddPopulationWriter<VoronoiDataWriter>();
        // cell_population.AddCellWriter<CellLabelWriter>();
        /*
         * Next we instantiate an instance of the PDE class which we defined above.
         * This will be passed into the {{{OffLatticeSimulationWithPdes}}} object. The
         * {{{CellwiseSourceEllipticPde}}} is a {{{PDE}}} class which inherits from
         * {{{AbstractLinearEllipticPde}}} and represents
         * the PDE ''u_xx'' + ''u_yy'' = ''k''(''x'',''y'') ''u'', where ''u''(''x'',''y'') denotes
         * the oxygen concentration at
         * position (''x'',''y'') and the function ''k''(''x'',''y'') specifies the rate of consumption by live cells
         * there. Here ''k''(''x'',''y'') takes the value -0.03 (the coefficient below) if
         * the cell located at (''x'',''y'') is a live cell, and zero if the cell has died due
         * to oxygen deprivation.
         */
        MAKE_PTR_ARGS(CellwiseSourceEllipticPde<3>, p_pde, (cell_population, -0.03));

        /*
         * We also create a constant-valued boundary condition to associate with the PDE.
         * This boundary condition object takes in a single argument in its constructor,
         * the value at the boundary. We also introduce a boolean to specify whether this value is the flux at the boundary
         * (a Neumann boundary condition) or the value of the state variable at the boundary
         * (a Dirichlet boundary condition) below.
         */
        MAKE_PTR_ARGS(ConstBoundaryCondition<3>, p_bc, (1.0));
        bool is_neumann_bc = false;

        /*
         * To pass the PDE to our simulator, it must first be encapsulated in a
         * cell-based PDE modifier object, together with the boundary condition for
         * the PDE. The latter is specified by the second and third arguments of the
         * constructor below: the second argument defines the value
         * of the boundary condition and the third argument defines whether it is of Neumann type
         * (true) or Dirichlet type (false). Thus, in our case, we are a specifying a constant-value
         * boundary condition. Note that we currently cannot impose more than one boundary
         * condition for each PDE (so that e.g. we cannot impose a zero-flux boundary condition
         * on some part of the boundary and a fixed-value boundary condition on the rest), although
         * the boundary condition itself can be made spatially varying or time-dependent.
         *
         * The PDE is tagged to show that the quantity to be solved for (the quantity of interest in
         * the cells' data is "oxygen".
         *
         * The {{{CellData}}} class, is used to stores the value of the current nutrient concentration for each cell.
         */
        MAKE_PTR_ARGS(EllipticGrowingDomainPdeModifier<3>, p_pde_modifier, (p_pde, p_bc, is_neumann_bc));
        p_pde_modifier->SetDependentVariableName("oxygen");

        /*
         * We are now in a position to construct an {{{OffLatticeSimulationWithPdes}}} object,
         * using the cell population. We then pass the PDE modifier object to the simulation.
         */
        OffLatticeSimulation<3> simulator(cell_population);
        simulator.AddSimulationModifier(p_pde_modifier);

        /*
         * We next set the output directory and end time.
         */
        simulator.SetSamplingTimestepMultiple(30);
        simulator.SetOutputDirectory("PlosPaper2013Thalia");
        simulator.SetEndTime(100);

        /*
         * We must now create one or more force laws, which determine the mechanics of
         * the cell population. As in the crypt simulation tutorial, we assume that a cell
         * experiences a force from each neighbour that can be represented as a linear overdamped
         * spring, so we use a {{{GeneralisedLinearSpringForce}}} object.
         * Note that we have called the method {{{SetCutOffLength}}} on the
         * {{{GeneralisedLinearSpringForce}}} before passing it to the simulator: this call
         * modifies the force law so that two neighbouring cells do not impose
         * a force on each other if they are located more than 3 units (=3 cell widths)
         * away from each other. This modification is necessary when no ghost nodes are used,
         * for example to avoid artificially large forces between cells that lie close together
         * on the spheroid boundary.
         */
        MAKE_PTR(GeneralisedLinearSpringForce<3>, p_force);
        p_force->SetCutOffLength(1.5);
        p_force->SetMeinekeSpringStiffness(30.0); 
        simulator.AddForce(p_force);

        /*
         * We call {{{Solve()}}} on the simulator to run the simulation.
         */
        MAKE_PTR_ARGS(ApoptoticCellKiller<3>, p_killer, (&cell_population));
        simulator.AddCellKiller(p_killer);

        // Run cell-based simulation
        simulator.Solve();
        // TS_ASSERT_THROWS_NOTHING(simulator.Solve());   
        }
    /*
     * EMPTYLINE
     *
     * To visualize the results, open a new terminal, {{{cd}}} to the Chaste directory,
     * then {{{cd}}} to {{{anim}}}. Then do: {{{java Visualize2dCentreCells /tmp/$USER/testoutput/SpheroidTutorial/results_from_time_0}}}.
     *
     * Or use Paraview, see [wiki:UserTutorials/VisualizingWithParaview] for details.
     *
     * EMPTYLINE
     */
};

