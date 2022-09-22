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

#ifndef DIFFUSION_SMALL_H_
#define DIFFUSION_SMALL_H_

#include "biodynamo.h"
#include "core/operation/operation.h"

namespace bdm {
enum Substances { kSubstance };

/// Operation to export the values of the substance to a file
class ExportConcentration : public StandaloneOperationImpl {
  BDM_OP_HEADER(ExportConcentration);

 public:
  ExportConcentration(std::string filename_detailed,
                      std::string filename_summary, DiffusionGrid *dg)
      : filename_detail_(filename_detailed),
        filename_summary_(filename_summary),
        dg_(dg){};

  void operator()() override {
    std::ofstream file1;
    if (!file1.is_open()) {
      file1.open(filename_detail_, std::ios_base::app);
    }
    int nboxes = dg_->GetNumBoxes();
    auto *data = dg_->GetAllConcentrations();
    file1 << Simulation::GetActive()->GetScheduler()->GetSimulatedSteps()
          << ", ";
    real_t avg = 0;
    for (int i = 0; i < nboxes; i++) {
      file1 << data[i];
      avg += data[i];
      if (i == nboxes - 1) {
        file1 << std::endl;
      } else {
        file1 << ", ";
      }
    }
    avg /= nboxes;
    file1.close();
    std::ofstream file2;
    if (!file2.is_open()) {
      file2.open(filename_summary_, std::ios_base::app);
    }
    file2 << Simulation::GetActive()->GetScheduler()->GetSimulatedSteps()
          << ", " << avg << std::endl;
    file2.close();
  };

 private:
  std::string filename_detail_ = "concentration_all.csv";
  std::string filename_summary_ = "concentration_avg.csv";
  DiffusionGrid *dg_;
};

inline int Simulate(int argc, const char **argv) {
  // ------------------------------------------------------------------
  // Define simulation parameters
  // ------------------------------------------------------------------

  // Boundary concentrations [uM]
  double c_0 = 10;
  // Diffusion coefficient [uM^2/min]
  double D = 2000;
  // Sink term [uM/min] <NOTE / WARNING THIS VALUE DEVIATES FROM THE TASK
  // DESCRIPTION. LARGER VALUES FOR SINK DO NOT RESULT IN A PHYSICAL STATE.>
  // double sink = 20 / 0.01;
  double sink = 0.2 / 0.01;
  // Simulation time [min]
  double t_max = 10;
  // Time step [min]
  double dt = 0.01;
  // Number of time steps
  int n_steps = t_max / dt;
  // Domain size
  double domain_size = 240;

  // Print information about simulation parameters for the user
  std::cout << "Simulation parameters:"
            << "\n";
  std::cout << "  Boundary concentration: " << c_0 << " uM"
            << "\n";
  std::cout << "  Diffusion coefficient: " << D << " uM^2/min"
            << "\n";
  std::cout << "  Sink term: " << sink << " uM/min"
            << "\n";
  std::cout << "  Simulation time: " << t_max << " min"
            << "\n";
  std::cout << "  Time step: " << dt << " min"
            << "\n";
  std::cout << "  Number of time steps: " << n_steps << "\n";
  std::cout << "  Domain size: " << domain_size << " um"
            << "\n";

  // ------------------------------------------------------------------
  // Define simulation
  // ------------------------------------------------------------------

  auto set_param = [&](Param *param) {
    param->bound_space = Param::BoundSpaceMode::kClosed;
    param->min_bound = -domain_size / 2;
    param->max_bound = domain_size / 2;
    param->simulation_time_step = dt;
    param->diffusion_boundary_condition = "closed";
    param->export_visualization = false;
    param->statistics = true;
  };

  Simulation simulation(argc, argv, set_param);
  auto *rm = simulation.GetResourceManager();   // Get the ResourceManager
  auto *scheduler = simulation.GetScheduler();  // Get the Scheduler
  auto *param = simulation.GetParam();          // Get the Parameters

  // ------------------------------------------------------------------
  // Add continuum model
  // ------------------------------------------------------------------

  ModelInitializer::DefineSubstance(Substances::kSubstance, "Substance", D, 0,
                                    12);
  auto SetInitialValues = [&](double x, double y, double z) { return c_0; };
  ModelInitializer::InitializeSubstance(Substances::kSubstance,
                                        SetInitialValues);

  // ------------------------------------------------------------------
  // Add cell as sink
  // ------------------------------------------------------------------

  auto create_cell = [&param, &sink, &domain_size](const Real3 &position) {
    Real3 offset = {-4.5 * domain_size / 12, -4.5 * domain_size / 12,
                    -4.5 * domain_size / 12};
    Real3 pos = position + offset;
    Cell *cell = new Cell(pos);
    cell->SetDiameter(10);
    cell->AddBehavior(
        new Secretion("Substance", -sink * param->simulation_time_step));
    return cell;
  };
  ModelInitializer::Grid3D(10, domain_size / 12, create_cell);

  // ------------------------------------------------------------------
  // Operation to export continuum values to file
  // ------------------------------------------------------------------

  OperationRegistry::GetInstance()->AddOperationImpl(
      "ExportConcentration", OpComputeTarget::kCpu,
      new ExportConcentration(param->output_dir + "/concentration_all.csv",
                              param->output_dir + "/concentration_avg.csv",
                              rm->GetDiffusionGrid("Substance")));
  auto *export_concentration = NewOperation("ExportConcentration");
  scheduler->ScheduleOp(export_concentration, OpType::kPreSchedule);

  // ------------------------------------------------------------------
  // Run simulation
  // ------------------------------------------------------------------

  scheduler->PrintInfo(std::cout);  // Print information about the simulation
  scheduler->Simulate(n_steps);

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // DIFFUSION_SMALL_H_
