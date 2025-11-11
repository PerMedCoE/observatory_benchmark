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
#ifndef UNIT_TEST_MECHANICS_EXTERNAL_IMPULSE_H_
#define UNIT_TEST_MECHANICS_EXTERNAL_IMPULSE_H_

#include "behaviours.h"
#include "biodynamo.h"
#include "custom_ops.h"
#include "moving_cell.h"
#include "core/environment/uniform_grid_environment.h"
#include "core/interaction_force.h"
#include "core/operation/mechanical_forces_op.h"
#include "sim_param.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  auto set_param = [](auto* param) {
    // Closed domain, 27 voxel (3x3x3), voxel size = 20um per side
    param->bound_space = Param::BoundSpaceMode::kClosed;
    param->min_bound = -30;
    param->max_bound = 30;
    param->export_visualization = false;
    param->visualize_agents["Moving_cell"] = {};
    param->statistics = true;
    param->simulation_time_step = 0.2;  // 0.2 seconds
    param->simulation_max_displacement = 100.0;  // um
  };
  
  // Before we create a simulation we have to tell BioDynaMo about
  // the new parameters.
  Param::RegisterParamGroup(new SimParam());

  Simulation simulation(argc, argv, set_param);
  auto* scheduler = simulation.GetScheduler();

  double const cell_diameter = 10.;  // um
  double const PI = 3.14159265;
  double const cell_volume = 4. / 3. * PI * pow(cell_diameter / 2., 3);  // um^3
  double const cell_density = pow(10, -15);  // 1kg/m^3 = 10^-15g/um^3
  double const cell_mass = cell_volume * cell_density;
  int number_of_cells = 1;
  double const F0 = 20.0*pow(10, -12); // External Impulse force in N
  double const mu = 7.2/60.; // Friction coefficient in kg/s. v = F/mu

  auto* rm = simulation.GetResourceManager();
  auto* cell1 = new Moving_cell({0.0, 0.0, 0.0});  // Cells' centers 30um
                                                     // apart
  cell1->SetDiameter(10.);
  cell1->SetMass(cell_mass);
  cell1->SetForce({F0, 0.0, 0.0}); // Apply external impulse in x direction
  cell1->SetFrictionCoefficient(mu);
  cell1->AddBehavior(new Move());
  cell1->SetId(0);

  rm->AddAgent(cell1);

  // Track positions
  const int time_steps = 61; // 12 seconds of simulation

  std::vector<std::vector<Double3>> cell_positions(number_of_cells);
  auto* track_pos_op = NewOperation("track_position");
  track_pos_op->GetImplementation<TrackPosition>()->positions_ =
      &cell_positions;
  track_pos_op->frequency_ = 1;
  scheduler->ScheduleOp(track_pos_op);

  // Track speeds
  std::vector<std::vector<Double3>> cell_speeds(number_of_cells);
  auto* track_speed_op = NewOperation("track_speed");
  track_speed_op->GetImplementation<TrackSpeed>()->speeds_ =
      &cell_speeds;
  track_speed_op->frequency_ = 1;
  scheduler->ScheduleOp(track_speed_op);

  // Move behaviour
  auto* behavior_op = scheduler->GetOps("behavior")[0];
  behavior_op->frequency_ = 1; // Every time step (0.2s each)

  // Run simulation for 12 seconds (60 time steps, 0.2s each)
  scheduler->Simulate(time_steps);

  std::cout << "Simulation completed successfully!" << std::endl;

  std::ofstream file;
  if (!file.is_open()) {
    file.open("positions.csv");
  }

  for (size_t j = 0; j < time_steps; j++) {
    for (size_t i = 0; i < cell_positions.size(); i++) {
      file << j*simulation.GetParam()->simulation_time_step << "\t " << cell_positions[i][j] * pow(10,6); // Convert from m to um
    }
    file << std::endl;
  }

  file.close();

  std::ofstream speed_file;
  if (!speed_file.is_open()) {
    speed_file.open("speeds.csv");
  }

  for (size_t j = 0; j < time_steps; j++) {
    for (size_t i = 0; i < cell_speeds.size(); i++) {
      speed_file << j*simulation.GetParam()->simulation_time_step << "\t " << cell_speeds[i][j] * pow(10,6); // Convert from m/s to um/s
    }
    speed_file << std::endl;
  }

  speed_file.close();

  return 0;
}

}  // namespace bdm

#endif  // UNIT_TEST_MECHANICS_TWO_CELLS_H_
