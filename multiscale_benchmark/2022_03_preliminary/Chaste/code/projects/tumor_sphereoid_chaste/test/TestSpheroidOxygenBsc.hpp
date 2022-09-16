#include <cxxtest/TestSuite.h>
#include "CheckpointArchiveTypes.hpp"
#include "AbstractCellBasedTestSuite.hpp"
#include "HoneycombMeshGenerator.hpp"
#include "GeneralisedLinearSpringForce.hpp"
#include "RandomNumberGenerator.hpp"
#include "SmartPointers.hpp"
#include "StochasticOxygenBasedCellCycleModel.hpp"
#include "WildTypeCellMutationState.hpp"
#include "StemCellProliferativeType.hpp"
#include "ApoptoticCellKiller.hpp"
#include "CellsGenerator.hpp"
#include "CellLabelWriter.hpp"
#include "CellwiseSourceEllipticPde.hpp"
#include "ConstBoundaryCondition.hpp"
#include "EllipticGrowingDomainPdeModifier.hpp"
#include "FixedG1GenerationalCellCycleModel.hpp"
#include "OffLatticeSimulation.hpp"
#include "VoronoiDataWriter.hpp"
#include "PetscSetupAndFinalize.hpp"

class TestSpheroidOxygenBsc : public AbstractCellBasedTestSuite
{
private:
    MutableMesh<3,3>* MakeMesh(unsigned width=3, unsigned height=3, unsigned depth=3)
    {
        MutableMesh<3,3>* p_mesh = new MutableMesh<3,3>;
        p_mesh->ConstructCuboid(width, height, depth);
        TrianglesMeshWriter<3,3> mesh_writer("", "SpringMesh");
        mesh_writer.WriteFilesUsingMesh(*p_mesh);

        return p_mesh;
    }
    /**
     * Helper method to generate a simple mesh that works in parallel
     *
     * @param nx number of nodes in the x direction
     * @param ny number of nodes in the y direction
     * @param nz number of nodes in the z direction
     * @return the nodes for the nodes only mesh
     */
    std::vector<Node<3>*> GenerateMesh( unsigned nx, unsigned ny, unsigned nz )
    {
        std::vector<Node<3>*> nodes(nx*ny*nz);
        for ( unsigned k = 0; k < nz; k++ )
        {
            for ( unsigned j = 0; j < ny; j++ )
            {
                for ( unsigned i = 0; i < nx; i++ )
                {
                    double x = (double)i + 0.5*(double)(j%2) + 0.5*(double)(k%2) - (double)( ((j+2)*k)%2);
                    double y = sqrt(3.0)/2.0 * (double)j;
                    double z = sqrt(3.0)/2.0 * (double)k;
                    nodes[ k*nx*ny + j*nx + i ] = new Node<3>(i+j*nx+k*nx*ny, false, x, y, z );
                }
            }
        }
        return nodes;
    }

public:
    void TestMeshBasedSpheroidWithPde()
    {


        std::vector<Node<3>*> nodes;
        nodes.push_back(new Node<3>(0, true,  0.0, 0.0, 0.0));
        nodes.push_back(new Node<3>(1, true,  1.0, 1.0, 0.0));
        nodes.push_back(new Node<3>(2, true,  1.0, 0.0, 1.0));
        nodes.push_back(new Node<3>(3, true,  0.0, 1.0, 1.0));
        nodes.push_back(new Node<3>(4, false, 0.5, 0.5, 0.5));
        MutableMesh<3,3> mesh(nodes);

        MAKE_PTR(WildTypeCellMutationState, p_state);
        MAKE_PTR(StemCellProliferativeType, p_stem_type);

        std::vector<CellPtr> cells;

        for (unsigned i=0; i<nodes.size(); i++)
        {
            StochasticOxygenBasedCellCycleModel* p_model = new StochasticOxygenBasedCellCycleModel();
            p_model->SetDimension(3);
            p_model->SetStemCellG1Duration(5.0);
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
        // Create cell population - a mapping between a mesh and cells.
        MeshBasedCellPopulation<3> cell_population(mesh, cells);
        cell_population.SetAbsoluteMovementThreshold(DBL_MAX);
        cell_population.SetWriteVtkAsPoints(false);
        cell_population.SetOutputMeshInVtk(true);
	// Set up cell data on the cell population
        cell_population.SetDataOnAllCells("oxygen", 1.0);
        //Set up cell-based simulation 
        OffLatticeSimulation<3> simulator(cell_population);
        simulator.SetEndTime(200000); // hours

        simulator.SetSamplingTimestepMultiple(30);
        simulator.SetOutputDirectory("LastOne");

        // Set up PDE and boundary condition
        MAKE_PTR_ARGS(CellwiseSourceEllipticPde<3>, p_pde, (cell_population, -0.03));
        MAKE_PTR_ARGS(ConstBoundaryCondition<3>, p_bc, (1.0));
        bool is_neumann_bc = false;
        // Create a handler (for any number of PDEs+BCs, in this case we just add one).
        MAKE_PTR_ARGS(EllipticGrowingDomainPdeModifier<3>, p_pde_modifier, (p_pde, p_bc, is_neumann_bc));
        p_pde_modifier->SetDependentVariableName("oxygen");

        // Pass PDE handler to the simulation
        simulator.AddSimulationModifier(p_pde_modifier);

        //Create a force law and pass it to the simulation 
        MAKE_PTR(GeneralisedLinearSpringForce<3>, p_force);
        p_force->SetCutOffLength(1.5);
        p_force->SetMeinekeSpringStiffness(30.0); 
        simulator.AddForce(p_force);
        // In this simulation the cell cycle model gives cells an ApoptoticCellProperty if they are in low oxygen (as defined by the PDE). This cell killer removes cells that have this property.
        MAKE_PTR_ARGS(ApoptoticCellKiller<3>, p_killer, (&cell_population));
        simulator.AddCellKiller(p_killer);
        // Run cell-based simulation
        simulator.Solve();

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
    
    // void TestTriangleMeshReaderSpheroidOxygenBsc()
    // {

    //     TrianglesMeshReader<3,3> mesh_reader("mesh/test/data/cube_1626_elements");
    //     MutableMesh<3,3> mesh;
    //     mesh.ConstructFromMeshReader(mesh_reader);

    //     TrianglesMeshWriter<3,3> mesh_writer("SpheroidTutorial3DMesh", "StartMesh");
    //     mesh_writer.WriteFilesUsingMesh(mesh);

    //     std::vector<CellPtr> cells;
    //     CellsGenerator<StochasticOxygenBasedCellCycleModel, 3> cells_generator;
    //     cells_generator.GenerateBasicRandom(cells, mesh.GetNumNodes());

    //     MAKE_PTR(WildTypeCellMutationState, p_state);
    //     MAKE_PTR(StemCellProliferativeType, p_stem_type);

    //     for (unsigned i=0; i<cells.size(); i++)
    //     {
    //         dynamic_cast<StochasticOxygenBasedCellCycleModel*>(cells[i]->GetCellCycleModel())->SetStemCellG1Duration(4.0);
    //         dynamic_cast<StochasticOxygenBasedCellCycleModel*>(cells[i]->GetCellCycleModel())->SetTransitCellG1Duration(4.0);
    //         dynamic_cast<StochasticOxygenBasedCellCycleModel*>(cells[i]->GetCellCycleModel())->SetHypoxicConcentration(0.1);
    //         dynamic_cast<StochasticOxygenBasedCellCycleModel*>(cells[i]->GetCellCycleModel())->SetQuiescentConcentration(0.3);
    //         dynamic_cast<StochasticOxygenBasedCellCycleModel*>(cells[i]->GetCellCycleModel())->SetCriticalHypoxicDuration(8);
    //         dynamic_cast<StochasticOxygenBasedCellCycleModel*>(cells[i]->GetCellCycleModel())->SetDimension(3);
    //         cells[i]->SetCellProliferativeType(p_stem_type);
    //         // double birth_time = - RandomNumberGenerator::Instance()->ranf() *
    //         //             cells[i]->GetStemCellG1Duration()
    //         //             + cells[i]->GetSG2MDuration();
    //         cells[i]->SetBirthTime(0.0);

    //     }


    //     MeshBasedCellPopulation<3> cell_population(mesh, cells);
    //     cell_population.SetAbsoluteMovementThreshold(DBL_MAX);
    //     cell_population.SetWriteVtkAsPoints(false);

    //     cell_population.SetDataOnAllCells("oxygen", 1.0);

    //     MAKE_PTR_ARGS(CellwiseSourceEllipticPde<3>, p_pde, (cell_population, -0.03));

    //     MAKE_PTR_ARGS(ConstBoundaryCondition<3>, p_bc, (1.0));
    //     bool is_neumann_bc = false;
    //     // Create a PDE modifier and set the name of the dependent variable in the PDE
    //     MAKE_PTR_ARGS(EllipticGrowingDomainPdeModifier<3>, p_pde_modifier, (p_pde, p_bc, is_neumann_bc));
    //     p_pde_modifier->SetDependentVariableName("oxygen");

    //     // Pass PDE handler to the simulation
    //     simulator.AddSimulationModifier(p_pde_modifier);

    //     //Create a force law and pass it to the simulation 
    //     MAKE_PTR(GeneralisedLinearSpringForce<3>, p_force);
    //     p_force->SetCutOffLength(1.5);
    //     p_force->SetMeinekeSpringStiffness(30.0); 
    //     simulator.AddForce(p_force);
    //     // In this simulation the cell cycle model gives cells an ApoptoticCellProperty if they are in low oxygen (as defined by the PDE). This cell killer removes cells that have this property.
    //     MAKE_PTR_ARGS(ApoptoticCellKiller<3>, p_killer, (&cell_population));
    //     simulator.AddCellKiller(p_killer);
    //     // Run cell-based simulation
    //     simulator.Solve();
    //     }

    // void TestSpheroidOxygenBsc_NodesGenerateMEsh(){
    //     std::vector<Node<3>*> nodes = GenerateMesh(5,5,5);
    //     MutableMesh<3,3> mesh(nodes);
    //     MAKE_PTR(WildTypeCellMutationState, p_state);
    //     MAKE_PTR(StemCellProliferativeType, p_stem_type);

    //     std::vector<CellPtr> cells;

    //     for (unsigned i=0; i<nodes.size(); i++)
    //     {
    //         StochasticOxygenBasedCellCycleModel* p_model = new StochasticOxygenBasedCellCycleModel();
    //         p_model->SetDimension(3);
    //         p_model->SetStemCellG1Duration(4.0);
    //         p_model->SetHypoxicConcentration(0.1);
    //         p_model->SetQuiescentConcentration(0.3);
    //         p_model->SetCriticalHypoxicDuration(8);
    //         double birth_time = -RandomNumberGenerator::Instance()->ranf()*
    //                             (  p_model->GetStemCellG1Duration()
    //                              + p_model->GetSG2MDuration() );

    //         CellPtr p_cell(new Cell(p_state, p_model));
    //         p_cell->SetBirthTime(birth_time);
    //         p_cell->SetCellProliferativeType(p_stem_type);
    //         cells.push_back(p_cell);
    //     }
    //     MeshBasedCellPopulation<3> cell_population(mesh, cells);
    //     cell_population.SetAbsoluteMovementThreshold(DBL_MAX);
    //     cell_population.SetWriteVtkAsPoints(false);

    //     cell_population.SetDataOnAllCells("oxygen", 1.0);

    //     MAKE_PTR_ARGS(CellwiseSourceEllipticPde<3>, p_pde, (cell_population, -0.03));

    //     MAKE_PTR_ARGS(ConstBoundaryCondition<3>, p_bc, (1.0));
    //     bool is_neumann_bc = false;

    //     MAKE_PTR_ARGS(EllipticGrowingDomainPdeModifier<3>, p_pde_modifier, (p_pde, p_bc, is_neumann_bc));
    //     p_pde_modifier->SetDependentVariableName("oxygen");


    //     OffLatticeSimulation<3> simulator(cell_population);
    //     simulator.AddSimulationModifier(p_pde_modifier);


    //     simulator.SetSamplingTimestepMultiple(12);
    //     simulator.SetOutputDirectory("TestSpheroidOxygenBsc_NodesGenerateMEsh");
    //     simulator.SetEndTime(20);


    //     MAKE_PTR(GeneralisedLinearSpringForce<3>, p_force);
    //     p_force->SetCutOffLength(1.5);
    //     p_force->SetMeinekeSpringStiffness(30.0); 
    //     simulator.AddForce(p_force);

    //     MAKE_PTR_ARGS(ApoptoticCellKiller<3>, p_killer, (&cell_population));
    //     simulator.AddCellKiller(p_killer);

    //     // Run cell-based simulation
    //     simulator.Solve();
    //     }
        
};
