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

#ifndef TEST2DMONOLAYERWITHOUTDIFFUSION_HPP_
#define TEST2DMONOLAYERWITHOUTDIFFUSION_HPP_

/*
 * = 2D Monolayer Without Diffusion =
 *
 * This test suite sets up and runs simulations of a 2D cell monolayer without considering diffusion effects.
 * 
 * Parmeters are chosen to match experimental data from Drasdo and Hoehme (2005)
 * 
 * Once we add 4 days to the time recorded here the tissue width is comapred against  
 * 
 * Time (days/hours) Width
 * 
 * 14/336 1140
 * 16.1/386 1400
 * 17/408 1590
 * 20.0/481 2040
 * 21.1/506 2250
 * 26.9/646 3040
 */ 
#include <cxxtest/TestSuite.h>

// Must be included before other cell_based headers
#include "CellBasedSimulationArchiver.hpp"

#include "SmartPointers.hpp"
#include "AbstractCellBasedWithTimingsTestSuite.hpp"

#include "TransitCellProliferativeType.hpp"
#include "WildTypeCellMutationState.hpp"

#include "CellIdWriter.hpp"
#include "CellAgesWriter.hpp"
#include "CellMutationStatesWriter.hpp"

#include "FixedDurationCellCycleModelWithGrowthInhibition.hpp"
#include "CellVolumesWriter.hpp"
#include "TissueWidthWriter.hpp"
#include "OffLatticeSimulation.hpp"

#include "GeneralisedLinearSpringForceWithMinDistanceItem.hpp"

#include "NodeBasedCellPopulation.hpp"

#include "GrowthInhibitionModifier.hpp"

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
        // Note we conside tie =0 here to be 4 days (96 hours) to compare with the experimental data
        static const double end_time = 23*24; 

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
        simulator.SetDt(0.02);
        simulator.SetSamplingTimestepMultiple(200); // Every 4 hours
        simulator.SetEndTime(end_time);

        simulator.SetOutputDivisionLocations(true);

        // Create a force law and pass it to the simulation
        MAKE_PTR(GeneralisedLinearSpringForceWithMinDistanceItem<2>, p_linear_force);
        p_linear_force->SetMeinekeSpringStiffness(10.0); // 2.7 //5 Low!
        p_linear_force->SetCutOffLength(cut_off_length);
        simulator.AddForce(p_linear_force);
        
        MAKE_PTR(GrowthInhibitionModifier<2>, p_growth_inhibition_modifier);
        simulator.AddSimulationModifier(p_growth_inhibition_modifier);


        simulator.Solve();

    }
};

#endif /* TEST2DMONOLAYERWITHOUTDIFFUSION_HPP_ */
