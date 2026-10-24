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

#ifndef TESTCELLSRELAXATION_HPP_
#define TESTCELLSRELAXATION_HPP_

#include <cxxtest/TestSuite.h>

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "AbstractCellBasedTestSuite.hpp"
#include "CellsGenerator.hpp"
#include "ConstantVelocityForce.hpp"
#include "GeneralisedLinearSpringForce.hpp"
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

class TestCellsRelaxation : public AbstractCellBasedTestSuite
{
public:
    void Test2CellsRelaxation()
    {
        // Description: two cells moving towards each other's centres at a constant velocity

        // Cannot currently run cell-based simulations in parallel.
        EXIT_IF_PARALLEL;

        // Simulation options
        const double sim_end_time = 10; // total 10 min runtime (in hours)
        const unsigned int sim_sampling = 1; // output every timestep
        const std::vector<double> sim_dt_values = {1.0, 0.5, 0.25, 0.125, 0.0625, 1.0/120.0};
        const std::vector<std::string> output_suffixes = {"1", "05", "025", "0125", "00625", "1_120"};

        for (unsigned i = 0; i < sim_dt_values.size(); ++i)
        {
          // Reset global singletons so each sweep point runs from a clean state.
          SimulationTime::Destroy();
          SimulationTime::Instance()->SetStartTime(0.0);
          RandomNumberGenerator::Instance()->Reseed(0);

          const std::string output_directory = "PerMedCoE/TestCellRelaxation_dt_" + output_suffixes[i];
          const double sim_dt = sim_dt_values[i];

          // Create two 3D nodes
          // Length is dimensionless and based on typical cell diameter i.e. approx 10 um
          // Cell centres are initially 30 um apart
          std::vector<double> coords = {0.0, 0.0, 0.0};
          auto p_node_0 = std::make_unique<Node<3> >(0u, coords, false);

          coords[0] = 0.9;
          auto p_node_1 = std::make_unique<Node<3> >(1u, coords, false);

          std::vector<Node<3>*> nodes = {p_node_0.get(), p_node_1.get()};

          // Create a 3D nodes-only mesh with 15 um neighbour interaction distance.
          double max_interaction_radius = 1.5;
          NodesOnlyMesh<3> mesh;
          mesh.ConstructNodesWithoutMesh(nodes, max_interaction_radius);

          // Create the cells. These cells do not grow.
          std::vector<CellPtr> cells;
          CellsGenerator<NoCellCycleModel, 1> cells_generator;
          cells_generator.GenerateBasic(cells, 2);

          // Create a cell population to connect the mesh and cells
          NodeBasedCellPopulation<3> cell_population(mesh, cells);

          // Add a node location writer to the cell population
          auto p_writer = boost::make_shared<NodeLocationWriter<3, 3> >();
          cell_population.AddPopulationWriter(p_writer);
          p_writer->SetFileName("node_locations.dat");

          // Create an off-lattice simulation with the cell population
          OffLatticeSimulation<3> simulator(cell_population);

          // Set simulation options
          simulator.SetOutputDirectory(output_directory);
          simulator.SetEndTime(sim_end_time);
          simulator.SetDt(sim_dt);
          simulator.SetSamplingTimestepMultiple(sim_sampling);

          // Add a generalised linear spring force law
          auto p_spring_force = boost::make_shared<RepulsionForce<3> >();
          p_spring_force->SetMeinekeSpringStiffness(30.0/60.0); // scaled for minutes
          simulator.AddForce(p_spring_force);

          // Run the simulation
          simulator.Solve();
        }

        SimulationTime::Destroy();
        RandomNumberGenerator::Destroy();
    }
};

#endif // TESTCELLSRELAXATION_HPP_
