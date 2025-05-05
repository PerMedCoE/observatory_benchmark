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
#ifndef UNIT_TEST_MECHANICS_H_
#define UNIT_TEST_MECHANICS_H_

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
    param->statistics = true;
    param->simulation_time_step = 0.1;  // 0.1 minutes
  };

  Simulation simulation(argc, argv, set_param);
  auto *scheduler = simulation.GetScheduler();

  double const cell_diameter = 10.;  // um
  double const PI = 3.14159265;
  double const cell_volume = 4. / 3. * PI * pow(cell_diameter / 2., 3);  // um^3
  double const cell_density = pow(10, -15);  // 1kg/m^3 = 10^-15g/um^3
  double const cell_mass = cell_volume * cell_density;

  auto* rm = simulation.GetResourceManager();
  auto* cell = new Moving_cell({0.0, 0.0, 0.0});
  cell->SetDiameter(10.);
  cell->SetMass(cell_mass);

  rm->AddAgent(cell);

  const int time_steps = 100;

  // Track positions

  std::vector<Real3> cell_positions;
  auto* track_pos_op = NewOperation("track_position");
  track_pos_op->GetImplementation<TrackPosition>()->positions_ =
      &cell_positions;
  track_pos_op->frequency_ = 1;  // 0.1 min
  scheduler->ScheduleOp(track_pos_op);

  // Apply force
  
  auto* apply_force = NewOperation("apply_force");
  apply_force->GetImplementation<ApplyForce>()->initial_speed_ = {10.0, 0.0, 0.0};
  scheduler->ScheduleOp(apply_force);
  apply_force->frequency_ = time_steps;  // 0.1 min

  // Simulate dissipative force (e.g. friction from extracellular matrix)
  auto* friction = NewOperation("dissipative_force");
  // F_loc = m*Dv/Dt = m*(1um/Dt * 1/Dt) = m Newton (for Dt = 1)
  // friction coeff = 0.1 F_loc

  double friction_coefficient = 0.1;
  friction->GetImplementation<DissipativeForce>()->friction_coefficient_ =
      friction_coefficient;
  friction->frequency_ = 1;  // 0.1 min
  scheduler->ScheduleOp(friction);

  // Run simulation for 10 minutes (100 steps, 1 step = 0.1 min )
  scheduler->Simulate(time_steps);

  std::cout << "Simulation completed successfully!" << std::endl;

  std::ofstream file;
  if (!file.is_open()) {
    file.open("positions.csv");
  }

  for (size_t i = 0; i < cell_positions.size(); i++) {
    file << i << "\t " << cell_positions[i] << std::endl;
  }

  file.close();

  return 0;
}

}  // namespace bdm

#endif  // UNIT_TEST_MECHANICS_H_
