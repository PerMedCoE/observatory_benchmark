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

#ifndef TESTCELLSRELAXATION_HERTZ_HPP_
#define TESTCELLSRELAXATION_HERTZ_HPP_

#include <cxxtest/TestSuite.h>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "AbstractCellBasedTestSuite.hpp"
#include "CellsGenerator.hpp"
#include "ConstantVelocityForce.hpp"
#include "GeneralisedLinearSpringForce.hpp"
#include "HertzForce.hpp"
#include "RepulsionForce.hpp"
#include "NoCellCycleModel.hpp"
#include "NodeBasedCellPopulation.hpp"
#include "NodeLocationWriter.hpp"
#include "NodesOnlyMesh.hpp"
#include "OffLatticeSimulation.hpp"
#include "RandomNumberGenerator.hpp"
#include "StoppingVelocityModifier.hpp"

// PETSc must be initialized to solve linear algebra problems in Chaste.
// For sequential code, FakePetscSetup.hpp starts PETSc on a single rank.
#include "FakePetscSetup.hpp"

class TestCellsRelaxationHertz : public AbstractCellBasedTestSuite
{
public:
    void Test2CellsHertzRelaxation()
    {
        // Description: two overlapping cells relax to their equilibrium separation
        // under a purely repulsive Hertz contact force.
        //
        // The Hertz force magnitude is:
        //   F = (4/3) * E* * sqrt(R*) * delta^(3/2) - pi * gamma * R* 
        // where delta = R_A + R_B - d is the overlap and R* = R_A*R_B/(R_A+R_B).

        EXIT_IF_PARALLEL;

        const double sim_end_time = 3*3600; // 3 hours in seconds (or chosen time unit)
        const double sim_dt = 3;
        const unsigned int sim_sampling = 10;
        const std::vector<double> cell_drag_values = {0.01, 0.1, 1.0};
        const std::vector<std::string> output_suffixes = {"001", "01", "1"};

        for (unsigned i = 0; i < cell_drag_values.size(); ++i)
        {
          // Reset global singletons so each sweep point runs from a clean state.
          SimulationTime::Destroy();
          SimulationTime::Instance()->SetStartTime(0.0);
          RandomNumberGenerator::Instance()->Reseed(0);

          double cell_drag = cell_drag_values[i];
          std::string output_directory = "PerMedCoE/TestCellHertzRelaxation_drag_" + output_suffixes[i];

          // Two cells placed 9.0e-6 apart with radius 5.0e-6 each, so they overlap by 1.0e-6.
          std::vector<double> coords = {0.0, 0.0, 0.0};
          auto p_node_0 = std::make_unique<Node<3> >(0u, coords, false);

          coords[0] = 9e-6;
          auto p_node_1 = std::make_unique<Node<3> >(1u, coords, false);

          std::vector<Node<3>*> nodes = {p_node_0.get(), p_node_1.get()};

          double max_interaction_radius = 15e-6;
          NodesOnlyMesh<3> mesh;
          mesh.ConstructNodesWithoutMesh(nodes, max_interaction_radius);

          // Set node radius here
          mesh.GetNode(0)->SetRadius(5e-6);
          mesh.GetNode(1)->SetRadius(5e-6);

          std::vector<CellPtr> cells;
          CellsGenerator<NoCellCycleModel, 1> cells_generator;
          cells_generator.GenerateBasic(cells, 2);

          NodeBasedCellPopulation<3> cell_population(mesh, cells);
          cell_population.SetDampingConstantNormal(cell_drag);

          auto p_writer = boost::make_shared<NodeLocationWriter<3, 3> >();
          cell_population.AddPopulationWriter(p_writer);
          p_writer->SetFileName("node_locations.dat");

          OffLatticeSimulation<3> simulator(cell_population);
          simulator.SetOutputDirectory(output_directory);
          simulator.SetEndTime(sim_end_time);
          simulator.SetDt(sim_dt);
          simulator.SetSamplingTimestepMultiple(sim_sampling);

          // Add the Hertz contact force
          // E* = 268.0 Pa;
          // gamma = 8.56e-15 J/m^2
          auto p_hertz_force = boost::make_shared<HertzForce<3> >();
          p_hertz_force->SetEffectiveElasticModulus(268.0);
          p_hertz_force->SetAdhesionParameter(8.56e-15);
          simulator.AddForce(p_hertz_force);

          simulator.Solve();

          // After relaxation the cells should have separated.
          Node<3>* p_final_node_0 = cell_population.GetNode(0);
          Node<3>* p_final_node_1 = cell_population.GetNode(1);
          double final_separation = norm_2(p_final_node_1->rGetLocation()
                          - p_final_node_0->rGetLocation());
          TS_ASSERT_LESS_THAN(9.9e-6, final_separation);  // cells have moved apart
        }

        SimulationTime::Destroy();
        RandomNumberGenerator::Destroy();
    }
};

#endif // TESTCELLSRELAXATION_HERTZ_HPP_
