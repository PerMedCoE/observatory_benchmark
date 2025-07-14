#ifndef TEST2DMONOLAYERWITHOUTDIFFUSION_HPP_
#define TEST2DMONOLAYERWITHOUTDIFFUSION_HPP_


/*
 * = Long-range Signalling Example =
 *
 * On this wiki page we describe in detail the code that is used to run this example from the paper.
 *
 * The easiest way to visualize these simulations is with Paraview.
 * 
 * [[EmbedYoutube(Yl2GT2x2ohc)]]
 *
 * == Code overview ==
 *
 * The first thing to do is to include the necessary header files.
 */

#include <cxxtest/TestSuite.h>

// Must be included before other cell_based headers
#include "CellBasedSimulationArchiver.hpp"

#include "SmartPointers.hpp"
#include "AbstractCellBasedWithTimingsTestSuite.hpp"

#include "DefaultCellProliferativeType.hpp"

#include "CellIdWriter.hpp"
#include "CellAgesWriter.hpp"
#include "VoronoiDataWriter.hpp"
#include "CellMutationStatesWriter.hpp"

#include "ParabolicGrowingDomainPdeModifier.hpp"
#include "VolumeTrackingModifier.hpp"

#include "FixedDurationCellCycleModelWithGrowthInhibition.hpp"
#include "CellDataItemWriter.hpp"
#include "CellVolumesWriter.hpp"
#include "TissueWidthWriter.hpp"
#include "OffLatticeSimulation.hpp"
#include "OnLatticeSimulation.hpp"
#include "CellsGenerator.hpp"
#include "RandomCellKiller.hpp"

#include "MeshBasedCellPopulationWithGhostNodes.hpp"
#include "HoneycombMeshGenerator.hpp"
#include "GeneralisedLinearSpringForceWithMinDistanceItem.hpp"

#include "NodeBasedCellPopulation.hpp"
#include "RepulsionForce.hpp"

#include "VertexBasedCellPopulation.hpp"
#include "HoneycombVertexMeshGenerator.hpp"
#include "NagaiHondaForce.hpp"
#include "SimpleTargetAreaModifier.hpp"
#include "GrowthInhibitionModifier.hpp"

#include "PottsBasedCellPopulation.hpp"
#include "PottsMeshGenerator.hpp"
#include "VolumeConstraintPottsUpdateRule.hpp"
#include "AdhesionPottsUpdateRule.hpp"
#include "SurfaceAreaConstraintPottsUpdateRule.hpp"

#include "CaBasedCellPopulation.hpp"
#include "DiffusionCaUpdateRule.hpp"

#include "RandomNumberGenerator.hpp"

#include "PetscSetupAndFinalize.hpp"


class Test2DMonolayerWithoutDiffusion : public AbstractCellBasedWithTimingsTestSuite
{
private:

    /*
     * This is a helper method to generate cells and is used in all simulations.
     */ 
    void GenerateCells(unsigned num_cells, std::vector<CellPtr>& rCells, bool randomiseBirthTime)
    {
        MAKE_PTR(WildTypeCellMutationState, p_state);
        MAKE_PTR(TransitCellProliferativeType, p_transit_type);

        for (unsigned i=0; i<num_cells; i++)
        {
            //UniformlyDistributedCellCycleModel* p_cycle_model = new UniformlyDistributedCellCycleModel();
            FixedDurationCellCycleModelWithGrowthInhibition* p_cycle_model = new FixedDurationCellCycleModelWithGrowthInhibition();
            p_cycle_model->SetDimension(2);

            CellPtr p_cell(new Cell(p_state, p_cycle_model));
            p_cell->SetCellProliferativeType(p_transit_type);

            double birth_time = 0.0;
            if (randomiseBirthTime) {
                birth_time = -RandomNumberGenerator::Instance()->ranf() * 18.0;
            }
            p_cell->SetBirthTime(birth_time);
            p_cycle_model->SetPhaseTimer(birth_time);


            p_cell->InitialiseCellCycleModel();

            // Set Target Area so dont need to use a growth model in vertex simulations
            p_cell->GetCellData()->SetItem("target area", 1.0);
            p_cell->GetCellData()->SetItem("growth inhibited", 0.0);
            p_cell->GetCellData()->SetItem("Radius", 0.1);
            p_cell->GetCellData()->SetItem("cell age", birth_time);
            rCells.push_back(p_cell);
        }
     }

public:

    /*
     * Simulate growth of a tissue monolayer without diffusion. Starts with a single cell
     */
    void Test2DMonolayerWithoutDiffusionSingleCell()
    {
        static const double end_time = 28*24; // 28 days first 14 days and second 14 days can be separated 


        NodesOnlyMesh<2>* p_mesh = new NodesOnlyMesh<2>;
        std::vector<double> center = {0.0, 0.0};
        double cut_off_length = 1.5; //this is the default
        Node<2> node(0, center.data(), false);
        p_mesh->AddNode(&node);
        p_mesh->SetMaximumInteractionDistance(cut_off_length);

        std::vector<CellPtr> cells;
        GenerateCells(p_mesh->GetNumNodes(),cells,false);

        NodeBasedCellPopulation<2> cell_population(*p_mesh, cells);
        cell_population.AddCellWriter<CellIdWriter>();
        cell_population.AddCellWriter<CellAgesWriter>();
        cell_population.AddCellWriter<CellMutationStatesWriter>();
        cell_population.AddCellWriter<CellVolumesWriter>();
        cell_population.AddPopulationWriter<TissueWidthWriter>();
        cell_population.SetUseVariableRadii(true);

        OffLatticeSimulation<2> simulator(cell_population);
        simulator.SetOutputDirectory("2DMonolayerWithoutDiffusion/SingleCell");
        simulator.SetDt(0.05);
        simulator.SetSamplingTimestepMultiple(10); // Every 30 minutes
        simulator.SetEndTime(end_time);

        simulator.SetOutputDivisionLocations(true);

        // Create a force law and pass it to the simulation
        MAKE_PTR(GeneralisedLinearSpringForceWithMinDistanceItem<2>, p_linear_force);
        p_linear_force->SetMeinekeSpringStiffness(2.70);
        p_linear_force->SetCutOffLength(cut_off_length);
        simulator.AddForce(p_linear_force);
        
        MAKE_PTR(GrowthInhibitionModifier<2>, p_growth_inhibition_modifier);
        simulator.AddSimulationModifier(p_growth_inhibition_modifier);


        simulator.Solve();

    }
    /*
     * Simulate growth of a tissue monolayer without diffusion. Starts with a tissue of diameter
     * of 57 cells.
     */
    void Test2DMonolayerWithoutDiffusionMultipleCells()
    {
        double end_time = 14*24; // Now run for 14 days
        double initial_tissue_radius = 57; // initial radius

        HoneycombMeshGenerator generator(2.0 * initial_tissue_radius, 2.0 * initial_tissue_radius,0);
        boost::shared_ptr<MutableMesh<2,2> > p_generating_mesh = generator.GetMesh();

        p_generating_mesh->Translate(-initial_tissue_radius / 2.0, -initial_tissue_radius / 2.0);

        //Remove all elements outside the specified initial radius
        for (AbstractMesh<2, 2>::NodeIterator node_iter = p_generating_mesh->GetNodeIteratorBegin();
             node_iter != p_generating_mesh->GetNodeIteratorEnd();
             ++node_iter)
        {
            unsigned node_index = node_iter->GetIndex();
            c_vector<double,2> node_location = node_iter->rGetLocation();

            if (norm_2(node_location)>0.5*initial_tissue_radius + 1e-5)
            {
                p_generating_mesh->DeleteNodePriorToReMesh(node_index);
            }
        }
        p_generating_mesh->ReMesh();

        double cut_off_length = 1.5; //this is the default

        NodesOnlyMesh<2>* p_mesh = new NodesOnlyMesh<2>;
        p_mesh->ConstructNodesWithoutMesh(*p_generating_mesh, cut_off_length);

        std::vector<CellPtr> cells;
        GenerateCells(p_mesh->GetNumNodes(),cells,true);

        NodeBasedCellPopulation<2> cell_population(*p_mesh, cells);
        cell_population.AddCellWriter<CellIdWriter>();
        cell_population.AddCellWriter<CellAgesWriter>();
        cell_population.AddCellWriter<CellMutationStatesWriter>();
        cell_population.AddCellWriter<CellVolumesWriter>();
        cell_population.AddPopulationWriter<TissueWidthWriter>();
        cell_population.SetUseVariableRadii(true);

        OffLatticeSimulation<2> simulator(cell_population);
        simulator.SetOutputDirectory("2DMonolayerWithoutDiffusion/MultipleCells");
        simulator.SetDt(0.05);
        simulator.SetSamplingTimestepMultiple(10); // Every 30 minutes
        simulator.SetEndTime(end_time);

        simulator.SetOutputDivisionLocations(true);

        // Create a force law and pass it to the simulation
        MAKE_PTR(GeneralisedLinearSpringForceWithMinDistanceItem<2>, p_linear_force);
        p_linear_force->SetMeinekeSpringStiffness(3.00);
        p_linear_force->SetCutOffLength(cut_off_length);
        simulator.AddForce(p_linear_force);
        
        MAKE_PTR(GrowthInhibitionModifier<2>, p_growth_inhibition_modifier);
        simulator.AddSimulationModifier(p_growth_inhibition_modifier);


        simulator.Solve();

    }

};

#endif /* TEST2DMONOLAYERWITHOUTDIFFUSION_HPP_ */
