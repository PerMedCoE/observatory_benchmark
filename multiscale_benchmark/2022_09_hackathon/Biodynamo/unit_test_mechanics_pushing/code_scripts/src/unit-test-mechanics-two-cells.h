// -----------------------------------------------------------------------------
//
// Copyright (C) 2021 CERN & University of Surrey for the benefit of the
// BioDynaMo collaboration. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef UNIT_TEST_MECHANICS_TWO_CELLS_H_
#define UNIT_TEST_MECHANICS_TWO_CELLS_H_

#include "behaviours.h"
#include "biodynamo.h"
#include "custom_ops.h"
#include "moving_cell.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  auto set_param = [](auto* param) {
    // Closed domain, 27 voxel (3x3x3), voxel size = 20um per side
    param->bound_space = Param::BoundSpaceMode::kClosed;
    param->min_bound = -30;
    param->max_bound = 30;
    param->export_visualization = false;
    param->visualize_agents["Moving_cell"] = {};
  };

  Simulation simulation(argc, argv, set_param);
  auto* scheduler = simulation.GetScheduler();

  double const cell_diameter = 10.;  // um
  double const PI = 3.14159265;
  double const cell_volume = 4. / 3. * PI * pow(cell_diameter / 2., 3);  // um^3
  double const cell_density = pow(10, -15);  // 1kg/m^3 = 10^-15g/um^3
  double const cell_mass = cell_volume * cell_density;
  int number_of_cells = 2;

  auto* rm = simulation.GetResourceManager();
  auto* cell1 = new Moving_cell({-15.0, 0.0, 0.0});  // Cells' centers 30um
                                                     // apart
  auto* cell2 = new Moving_cell({15.0, 0.0, 0.0});
  cell1->SetDiameter(10.);
  cell1->SetMass(cell_mass);
  cell1->SetSpeed({1.0, 0.0, 0.0});  // Movement along x-axis, 1um/0.1min
  cell1->AddBehavior(new Move());
  cell1->SetId(0);
  cell2->SetDiameter(10.);
  cell2->SetMass(cell_mass);
  cell2->SetSpeed(
      {-1.0, 0.0,
       0.0});  // Movement along x-axis, negative directions 1um/0.1min
  cell2->AddBehavior(new Move());
  cell2->SetId(1);

  rm->AddAgent(cell1);
  rm->AddAgent(cell2);

  // Track positions
  const int time_steps = 100;

  std::vector<std::vector<Double3>> cell_positions(number_of_cells);
  auto* track_pos_op = NewOperation("track_position");
  track_pos_op->GetImplementation<TrackPosition>()->positions_ =
      &cell_positions;
  track_pos_op->frequency_ = 1;  // 0.1 min
  scheduler->ScheduleOp(track_pos_op);

  // Move behaviour
  auto* behavior_op = scheduler->GetOps("behavior")[0];
  behavior_op->frequency_ = 1;  // Set behaviors' frequency

  // Run simulation for 10 minutes (100 steps, 1 step = 0.1 min )
  scheduler->Simulate(time_steps);

  std::cout << "Simulation completed successfully!" << std::endl;

  std::ofstream file;
  if (!file.is_open()) {
    file.open("positions.csv");
  }

  for (size_t j = 0; j < time_steps; j++) {
    for (size_t i = 0; i < cell_positions.size(); i++) {
      file << j << "\t " << cell_positions[i][j];
    }
    file << std::endl;
  }

  file.close();

  return 0;
}

}  // namespace bdm

#endif  // UNIT_TEST_MECHANICS_TWO_CELLS_H_
