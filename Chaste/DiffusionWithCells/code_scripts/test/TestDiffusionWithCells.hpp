/*

Copyright (c) 2005-2025, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of Chaste.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of the University of Oxford nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef TESTDIFFUSIONWITHCELLS_HPP_
#define TESTDIFFUSIONWITHCELLS_HPP_

#include <cxxtest/TestSuite.h>
#include "SmartPointers.hpp"
#include "AbstractCellBasedWithTimingsTestSuite.hpp"
#include "TransitCellProliferativeType.hpp"
#include "DifferentiatedCellProliferativeType.hpp"
#include "CellIdWriter.hpp"
#include "VoronoiDataWriter.hpp"
#include "CellMutationStatesWriter.hpp"
#include "ParabolicBoxDomainPdeModifier.hpp"
#include "AveragedSourceParabolicPde.hpp"
#include "SimpleOxygenBasedCellCycleModel.hpp"
#include "OffLatticeSimulation.hpp"
#include "OnLatticeSimulation.hpp"
#include "CellsGenerator.hpp"
#include "RandomCellKiller.hpp"
#include "MeshBasedCellPopulationWithGhostNodes.hpp"
#include "HoneycombMeshGenerator.hpp"
#include "GeneralisedLinearSpringForce.hpp"
#include "NodeBasedCellPopulation.hpp"
#include "RepulsionForce.hpp"
#include "CellLabel.hpp"
#include "VertexBasedCellPopulation.hpp"
#include "HoneycombVertexMeshGenerator.hpp"
#include "NagaiHondaForce.hpp"
#include "SimpleTargetAreaModifier.hpp"
#include "PottsBasedCellPopulation.hpp"
#include "PottsMeshGenerator.hpp"
#include "VolumeConstraintPottsUpdateRule.hpp"
#include "AdhesionPottsUpdateRule.hpp"
#include "SurfaceAreaConstraintPottsUpdateRule.hpp"
#include "CaBasedCellPopulation.hpp"
#include "DiffusionCaUpdateRule.hpp"

// This test is always run sequentially (never in parallel)
#include "FakePetscSetup.hpp"

#include "Debug.hpp"

static const double M_TIME_FOR_SIMULATION = 10.0;

class TestSimulationsWithParabolicBoxDomainPdeModifier : public AbstractCellBasedWithTimingsTestSuite
{
private:

    void GenerateCells(unsigned num_cells, std::vector<CellPtr>& rCells, double EquilibriumVolume)
    {
        MAKE_PTR(WildTypeCellMutationState, p_state);
        MAKE_PTR(TransitCellProliferativeType, p_transit_type);
        boost::shared_ptr<AbstractCellProperty> p_label(CellPropertyRegistry::Instance()->Get<CellLabel>());

        for (unsigned i=0; i<num_cells; i++)
        {
            SimpleOxygenBasedCellCycleModel* p_cycle_model = new SimpleOxygenBasedCellCycleModel();
            p_cycle_model->SetDimension(2);
            CellPtr p_cell(new Cell(p_state, p_cycle_model));
            p_cell->SetCellProliferativeType(p_transit_type);
            p_cell->GetCellData()->SetItem("oxygen",10.0);
            rCells.push_back(p_cell);
        }
     }

public:

    void TestDiffusion3DWithCells()
    {
// Target number of points in each dimension, so we have num_vox_each_dim^3 nodes in the domain
        const unsigned num_vox_each_dim_array[5] = {6, 12, 24, 48, 96};

        for (unsigned num_vox_each_dim_index = 0; num_vox_each_dim_index != 4; num_vox_each_dim_index++)
        {
            double num_vox_each_dim = num_vox_each_dim_array[num_vox_each_dim_index];

            std::stringstream num_vox_string;
            num_vox_string << (double) num_vox_each_dim;

            std::string base_name = "TestDiffusionConvergence3d_with_cells";
            std::string simulation_output_dir = base_name + "/" + num_vox_string.str();
    
            PRINT_VARIABLE(simulation_output_dir);     
            
            // Simulation parameters from PerMedCoE document
            const double width_xyz = 240.0; // 240 x 240 x 240 micrometers,   
            const double vox_size = width_xyz / (num_vox_each_dim);
            //const double initial_concentration = 10.0; // initial concnetration to match BCS!
            const double source_strength = 10.0; // constant concentration on the boundary
            const double sink_strength = 16000; // 1.0*(20*20*20); // 20 microMol per minute (per 20^3 size cell)
            const double diffusion_coefficient = 2000.0; // 2000 micrometer^2 per minute
            const double dudt_coefficient = 1.0;
            const double dt = 0.01;

            std::vector<Node<3>*> nodes;
            nodes.push_back(new Node<3>(0, false,  -10, 10, 0));
            nodes.push_back(new Node<3>(1, false, -10, -10, 0));
            nodes.push_back(new Node<3>(2, false,  10,  10, 0));
            nodes.push_back(new Node<3>(3, false,  10, -10, 0));
            nodes.push_back(new Node<3>(4, false, -30,  10, 0));
            nodes.push_back(new Node<3>(5, false, -30, -10, 0));
            nodes.push_back(new Node<3>(6, false,  30,  10, 0));
            nodes.push_back(new Node<3>(7, false,  30, -10, 0));
            nodes.push_back(new Node<3>(8, false,  10,  30, 0));
            nodes.push_back(new Node<3>(9, false, -10,  30, 0));
            nodes.push_back(new Node<3>(10, false,  10, -30, 0));
            nodes.push_back(new Node<3>(11, false, -10, -30, 0));

            NodesOnlyMesh<3>* p_mesh = new NodesOnlyMesh<3>;
            p_mesh->ConstructNodesWithoutMesh(nodes, 1.5);

            std::vector<CellPtr> cells;
            GenerateCells(p_mesh->GetNumNodes(),cells,1.0);

            NodeBasedCellPopulation<3> cell_population(*p_mesh, cells);
            cell_population.AddCellWriter<CellIdWriter>();
            cell_population.AddCellWriter<CellMutationStatesWriter>();

            OffLatticeSimulation<3> simulator(cell_population);
            simulator.SetOutputDirectory(simulation_output_dir);
            simulator.SetDt(dt);
            simulator.SetSamplingTimestepMultiple(0.1/dt);
            simulator.SetEndTime(M_TIME_FOR_SIMULATION);

            // Create a PDE modifier and pass it to the simulation Add this first so in place for SimpleTargetArea one (calls cell pop update)

            // Create PDE and boundary condition objects
            //MAKE_PTR_ARGS(AveragedSourceParabolicPde<2>, p_pde, (cell_population, M_CONSTANT_UPTAKE_RATE, M_LINEAR_UPTAKE_RATE, M_DIFFUSION_CONSTANT, M_DUDT_COEFFICIENT));
            MAKE_PTR_ARGS(AveragedSourceParabolicPde<3>, p_pde, (cell_population, -sink_strength*10, 0.0, 0.0, 0.0, diffusion_coefficient, dudt_coefficient, false));
            MAKE_PTR_ARGS(ConstBoundaryCondition<3>, p_bc, (source_strength));

            // Create a ChasteCuboid on which to base the finite element mesh used to solve the PDE
            ChastePoint<3> lower(-width_xyz/2.0, -width_xyz/2.0, -width_xyz/2.0);
            ChastePoint<3> upper(width_xyz/2.0, width_xyz/2.0, width_xyz/2.0);
            MAKE_PTR_ARGS(ChasteCuboid<3>, p_cuboid, (lower, upper));

            // Create a PDE modifier and set the name of the dependent variable in the PDE
            MAKE_PTR_ARGS(ParabolicBoxDomainPdeModifier<3>, p_pde_modifier, (p_pde, p_bc, false, p_cuboid, vox_size));
            p_pde_modifier->SetDependentVariableName("oxygen");
            p_pde_modifier->SetOutputSolutionAtPdeNodes(true);

            simulator.AddSimulationModifier(p_pde_modifier);

            simulator.Solve();

            delete p_mesh; // to stop memory leaks


            // Reset for next simulation
            SimulationTime::Instance()->Destroy();
            SimulationTime::Instance()->SetStartTime(0.0);

        }
    }
};

#endif /*TESTDIFFUSIONWITHCELLS_HPP_*/
