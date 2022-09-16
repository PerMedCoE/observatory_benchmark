#include <cxxtest/TestSuite.h>

// Must be included before other cell_based headers
// #include "CellBasedSimulationArchiver.hpp"
#include "CheckpointArchiveTypes.hpp"
#include "AbstractCellBasedTestSuite.hpp"
#include "HoneycombMeshGenerator.hpp"
#include "GeneralisedLinearSpringForce.hpp"
#include "RandomNumberGenerator.hpp"
#include "SmartPointers.hpp"

#include "ApoptoticCellKiller.hpp"
#include "CellsGenerator.hpp"
#include "TrianglesMeshReader.hpp"
#include "OffLatticeSimulation.hpp"
#include "TrianglesMeshWriter.hpp"
#include "FixedG1GenerationalCellCycleModel.hpp"
#include "AbstractCellBasedWithTimingsTestSuite.hpp"
#include "CellVolumesWriter.hpp"

#include "CellwiseSourceEllipticPde.hpp"
#include "ConstBoundaryCondition.hpp"
#include "EllipticGrowingDomainPdeModifier.hpp"


#include "WildTypeCellMutationState.hpp"
#include "StemCellProliferativeType.hpp"
#include "ApoptoticCellKiller.hpp"
#include "CellLabelWriter.hpp"
#include "StochasticOxygenBasedCellCycleModel.hpp"

// Cell population writers
#include "CellProliferativeTypesCountWriter.hpp"
#include "CellMutationStatesCountWriter.hpp"


class TestOffLatice3d : public AbstractCellBasedWithTimingsTestSuite
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
    void TestOffLattice3dSimulationSpheroid()
    {
        unsigned width = 3;
        unsigned height = 3;
        unsigned depth = 3;

        MutableMesh<3,3>* p_mesh = Make3dMesh(width, height, depth);
        TrianglesMeshWriter<3,3> mesh_writer("TestOffLattice3d", "StartMesh");
        mesh_writer.WriteFilesUsingMesh(*p_mesh);

        c_vector<double, 3> spheroid_centre;
        spheroid_centre[0] = 0.5*((double) width);
        spheroid_centre[1] = 0.5*((double) height);
        spheroid_centre[2] = 0.5*((double) depth);

        // Set up cells by iterating through the mesh nodes
        unsigned num_nodes = p_mesh->GetNumAllNodes();

        std::vector<CellPtr> cells;
        // std::vector<CellPtr> cells2;
        std::vector<unsigned> location_indices;

        MAKE_PTR(WildTypeCellMutationState, p_state);
        MAKE_PTR(StemCellProliferativeType, p_stem_type);

        for (unsigned i=0; i<num_nodes; i++)
        {
            c_vector<double, 3> node_location = p_mesh->GetNode(i)->rGetLocation();

            unsigned min_spatial_dimension;
            if (width <= height && width <= depth)
            {
                min_spatial_dimension = width;
            }
            else
            {
                if (height <= depth)
                {
                    min_spatial_dimension = height;
                }
                else
                {
                    min_spatial_dimension = depth;
                }
            }

            FixedG1GenerationalCellCycleModel* p_model = new FixedG1GenerationalCellCycleModel();
            // p_model->SetGeneration(0);
            p_model->SetStemCellG1Duration(4.0);
            p_model->SetTransitCellG1Duration(4.0);
            p_model->SetHypoxicConcentration(0.1);
            p_model->SetQuiescentConcentration(0.3);
            p_model->SetCriticalHypoxicDuration(8);
            p_model->SetDimension(3);
            CellPtr p_cell(new Cell(p_state, p_model));
            p_cell->SetCellProliferativeType(p_stem_type);
            p_cell->SetBirthTime(-RandomNumberGenerator::Instance()->ranf()*
                                 (p_model->GetStemCellG1Duration() + p_model->GetSG2MDuration()));

            cells.push_back(p_cell);

        }

        // Test Save() with a MeshBasedCellPopulationWithGhostNodes
        MeshBasedCellPopulation<3> cell_population(*p_mesh, cells, location_indices);
        cell_population.SetAbsoluteMovementThreshold(DBL_MAX);
        cell_population.SetWriteVtkAsPoints(true);
         cell_population.SetDataOnAllCells("oxygen", 1.0);
        cell_population.AddCellPopulationCountWriter<CellProliferativeTypesCountWriter>();
        cell_population.AddCellPopulationCountWriter<CellMutationStatesCountWriter>();
        cell_population.AddCellWriter<CellVolumesWriter>();

        MAKE_PTR_ARGS(CellwiseSourceEllipticPde<3>, p_pde, (cell_population, -0.03));
        MAKE_PTR_ARGS(ConstBoundaryCondition<3>, p_bc, (1.0));
        bool is_neumann_bc = false;

        MAKE_PTR_ARGS(EllipticGrowingDomainPdeModifier<3>, p_pde_modifier, (p_pde, p_bc, is_neumann_bc));
        p_pde_modifier->SetDependentVariableName("oxygen");

        OffLatticeSimulation<3> simulator(cell_population);
        simulator.SetOutputDirectory("ThaliaTestOffLattice3d");
        simulator.SetEndTime(0.1);

        // Create a force law and pass it to the simulation
        MAKE_PTR(GeneralisedLinearSpringForce<3>, p_linear_force);
        p_linear_force->SetCutOffLength(1.5);
        p_linear_force->SetMeinekeSpringStiffness(30.0); 
        simulator.AddForce(p_linear_force);

        MAKE_PTR_ARGS(ApoptoticCellKiller<3>, p_killer, (&cell_population));
        simulator.AddCellKiller(p_killer);

        simulator.Solve();
    }

}