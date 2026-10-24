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

#ifndef TESTCELLMOVEMENTWITHFRICTION_HPP_
#define TESTCELLMOVEMENTWITHFRICTION_HPP_

#include <cxxtest/TestSuite.h>
/* Most Chaste code uses PETSc to solve linear algebra problems.  This involves starting PETSc at the beginning of a test-suite
 * and closing it at the end.  (If you never run code in parallel then it is safe to replace PetscSetupAndFinalize.hpp with FakePetscSetup.hpp)
 */
#include "CheckpointArchiveTypes.hpp"
#include "SmartPointers.hpp"
#include "VoronoiDataWriter.hpp"
#include "NodeLocationWriter.hpp"
#include "NodeVelocityWriter.hpp"
#include "AbstractCellBasedTestSuite.hpp"
#include "PetscSetupAndFinalize.hpp"
#include "CellsGenerator.hpp"
#include "NoCellCycleModel.hpp"
#include "NodeBasedCellPopulation.hpp"
#include "OffLatticeSimulation.hpp"
#include "TransitCellProliferativeType.hpp"
#include "HoneycombMeshGenerator.hpp"
#include "RepulsionForce.hpp"
#include "FakePetscSetup.hpp"

#include "InstantaneousVelocityForce.hpp"



class TestCellMovementWithFriction : public AbstractCellBasedTestSuite
{
public:
/*
 * No cell interactions so can set 1 unit of length = 1 um and time to be seconds
 * 
 * The cell should move with a velocity of 10nm/minute, when the force is applied.
 * 
 * drag = 1.0 (assuming damping constant is 1.0)
 * 
 * Applied force  = 0.01/60 
 * 
 * Total time = 12s, 
 */
    void TestCellMechanicsCellMovement() {

      // Generate a mesh
      HoneycombMeshGenerator generator(1, 1);
      MutableMesh<2,2>* p_generating_mesh = generator.GetMesh().get();
      NodesOnlyMesh<2> mesh;
      mesh.ConstructNodesWithoutMesh(*p_generating_mesh, 1.5);

      // Add the cell 
      std::vector<CellPtr> cells;
      CellsGenerator<NoCellCycleModel, 2> cells_generator;
      cells_generator.GenerateBasicRandom(cells, mesh.GetNumNodes());

      // Set initial conditions
      // Expressed in units of simulation units/hour
      // Assuming 1 unit = 1um
      c_vector<double, 2> initialVelocity;
      initialVelocity[0] = 0.01/60.0;
      initialVelocity[1] = 0.0;

      double velocity_start_time = 3; // seconds
      double velocity_end_time = 6; // seconds

      MAKE_PTR(InstantaneousVelocityForce<2>, force);
      force->SetVelocity(initialVelocity);
      force->SetStartTime(velocity_start_time);
      force->SetEndTime(velocity_end_time);

      // Setup cell population
      NodeBasedCellPopulation<2> cell_population(mesh, cells);
      cell_population.Update();
      cell_population.SetDampingConstantNormal(1.0);//7.2);

      // Add node location writer
      using LocationWriter = NodeLocationWriter<2, 2>;
      MAKE_PTR(LocationWriter, writer);
      writer->SetFileName("node_locations.dat");
      cell_population.AddPopulationWriter(writer);

      using VelocitiyWriter = NodeVelocityWriter<2, 2>;
      MAKE_PTR(VelocitiyWriter, velocities_writer);
      velocities_writer->SetFileName("cell_velocities.dat");
      cell_population.AddPopulationWriter(velocities_writer);


      // Set up simulator
      OffLatticeSimulation<2> simulator(cell_population);
      simulator.SetOutputDirectory("PerMedCoE/TestCellMovementWithFriction");
      simulator.SetEndTime(12); // 12 seconds
      simulator.SetDt(0.1); // 0.1 seconds, so 120 time steps in total
      simulator.SetSamplingTimestepMultiple(2); // output every 0.2 second      
      simulator.AddForce(force);

      // Perform simulation
      simulator.Solve();  

      // Check that the cell has moved approximately the right distance.
      c_vector<double, 2> final_location = cell_population.GetNode(0)->rGetLocation();
      double distance_moved = sqrt(final_location[0]*final_location[0] + final_location[1]*final_location[1]);
      TS_ASSERT_DELTA(distance_moved, 0.0005, 0.000001); 
    }
};

#endif // TESTCELLMOVEMENTWITHFRICTION_HPP_
