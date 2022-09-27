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
#ifndef SPHERE_H_
#define SPHERE_H_

#include "behaviours.h"
#include "biodynamo.h"
#include "core/environment/uniform_grid_environment.h"
#include "core/interaction_force.h"
#include "core/operation/mechanical_forces_op.h"
#include "custom_ops.h"
#include "my_cell.h"
#include "my_force.h"
#include "evaluate.h"

namespace bdm {

using experimental::TimeSeries;

inline int Simulate(int argc, const char** argv) {
  // Adding space edge of but to be used in larger use case.
  auto set_param = [](Param* param) {
    param->bound_space = Param::BoundSpaceMode::kOpen;
    param->min_bound = -2000;
    param->max_bound = 2000;
    param->export_visualization = false;
    param->visualization_interval = 500;
    param->visualize_agents["MyCell"] = {};
    param->statistics = true;
    param->simulation_max_displacement = 100;  // 3 is the default value
  };

  // Create a new simulation
  Simulation simulation(argc, argv, set_param);
  SetupResultCollection(&simulation);
  auto* rm = simulation.GetResourceManager();
  auto* scheduler = simulation.GetScheduler();  // Get the Scheduler

  double const cell_diam = 20.;

  double const nn = 1140;  // should be 1140
  double const pos0 = -(nn / 2.) + (cell_diam / 2.);
  double const posN = nn / 2.;
  double x_coord = pos0, y_coord;
  // for (size_t i = pos0; i < posN; i += 20.0) {
  while (x_coord < posN) {
    y_coord = pos0;
    while (y_coord < posN) {
        MyCell* cell = new MyCell({x_coord, y_coord, 0});

        cell->SetDiameter(cell_diam);
        cell->SetVinit(cell->GetVolume());
        cell->SetVrel(100.0);
        double x = cell->GetVolume() * 2.0;
        cell->SetVmax(x);
        cell->SetDelt(0.0);
        cell->SetCycle(1);
        cell->SetCanDivide(true);
        cell->AddBehavior(new Growth());
        rm->AddAgent(cell);  // put the created cell in our cells structure
        y_coord += cell_diam;
      }
      x_coord += cell_diam;
    }

    // Set the box length
    auto* env =
        dynamic_cast<UniformGridEnvironment*>(simulation.GetEnvironment());
    env->SetBoxLength(cell_diam * 2);

    // Check if the cells have moved along the z direction and, if so, move them
    // back
    auto* move_cells_back = NewOperation("move_cells_plane");
    move_cells_back->frequency_ = 1;  // 0.1 min
    simulation.GetScheduler()->ScheduleOp(move_cells_back);

    // Count number of cells every 30 min (half hour = 5 time steps)
    auto* count_cells = NewOperation("count_cells");
    int count_cell_freq = 5;
    count_cells->frequency_ = count_cell_freq;
    simulation.GetScheduler()->ScheduleOp(count_cells);

    // Set time series freq (will measure the size of the uniform grid environment)
    size_t ts_freq = 200;
    auto* updatetimeseries_op = scheduler->GetOps("update time series")[0];
    updatetimeseries_op->frequency_ = ts_freq;

    // Custom force module
    auto* custom_force = new MyForce();
    auto* op = scheduler->GetOps("mechanical forces")[0];
    auto* force_implementation = op->GetImplementation<MechanicalForcesOp>();
    force_implementation->SetInteractionForce(custom_force);

    // Run simulation for 310 hours (1 timestep = 0.1 hours)
    simulation.GetScheduler()->Simulate(3100);  // 3100

    scheduler->PrintInfo(std::cout);

    // Export cell number
    std::ofstream file1;
    if (!file1.is_open()) {
      file1.open("total_cells.csv");
    }

    std::vector<size_t> cells_measurements = count_cells->GetImplementation<CountCells>()->GetMeasurements();

    for (size_t i = 0; i < cells_measurements.size(); i++) {
      file1 << i * count_cell_freq << "\t " << cells_measurements[i] << std::endl;
    }

    file1.close();

    std::cout << "Simulation completed successfully!" << std::endl;

    // Export grid size
    std::vector<TimeSeries> results;
    results.push_back(*simulation.GetTimeSeries());
    PlotResults(results, "output");

    return 0;
  }

}  // namespace bdm

#endif  // SPHERE_H_
