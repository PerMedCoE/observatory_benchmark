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
  ExportConcentration(std::string filename, DiffusionGrid *dg)
      : filename_(filename), dg_(dg){};

  void operator()() override {
    std::ofstream file;
    if (!file.is_open()) {
      file.open(filename_, std::ios_base::app);
    }
    int nboxes = dg_->GetNumBoxes();
    auto *data = dg_->GetAllConcentrations();
    file << Simulation::GetActive()->GetScheduler()->GetSimulatedSteps()
         << ", ";
    for (int i = 0; i < nboxes; i++) {
      file << data[i];
      if (i == nboxes - 1) {
        file << std::endl;
      } else {
        file << ", ";
      }
    }
    file.close();
  };

 private:
  std::string filename_ = "concentration.csv";
  DiffusionGrid *dg_;
};

/// Consume substance at Agent position
class Consumption : public Behavior {
  BDM_BEHAVIOR_HEADER(Consumption, Behavior, 0);

 public:
  Consumption() = default;
  explicit Consumption(const std::string &substance, real_t quantity = 1)
      : quantity_(quantity) {
    dgrid_ = Simulation::GetActive()->GetResourceManager()->GetDiffusionGrid(
        substance);
  }

  virtual ~Consumption() = default;

  void Initialize(const NewAgentEvent &event) override { return; }

  void Run(Agent *agent) override {
    auto &position = agent->GetPosition();
    auto concentration = dgrid_->GetConcentration(position);
    auto quantity = std::min(quantity_, concentration);
    dgrid_->ChangeConcentrationBy(position, -quantity);
  }

 private:
  DiffusionGrid *dgrid_ = nullptr;
  real_t quantity_ = 1;
};

inline int Simulate(int argc, const char **argv) {
  // ------------------------------------------------------------------
  // Define simulation parameters
  // ------------------------------------------------------------------

  // Export to CSV (introduces overhead)
  bool export_to_csv = true;
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

  // ------------------------------------------------------------------
  // Define simulation
  // ------------------------------------------------------------------

  auto set_param = [&](Param *param) {
    param->bound_space = Param::BoundSpaceMode::kClosed;
    param->min_bound = -30;
    param->max_bound = 30;
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
                                    3);
  auto SetInitialValues = [&](double x, double y, double z) { return c_0; };
  ModelInitializer::InitializeSubstance(Substances::kSubstance,
                                        SetInitialValues);

  // ------------------------------------------------------------------
  // Add cell as sink
  // ------------------------------------------------------------------

  auto *cell = new Cell(10.0);
  cell->AddBehavior(
      new Consumption("Substance", sink * param->simulation_time_step));
  rm->AddAgent(cell);

  // ------------------------------------------------------------------
  // Operation to export continuum values to file
  // ------------------------------------------------------------------

  if (export_to_csv) {
    OperationRegistry::GetInstance()->AddOperationImpl(
        "ExportConcentration", OpComputeTarget::kCpu,
        new ExportConcentration(param->output_dir + "/concentration.csv",
                                rm->GetDiffusionGrid("Substance")));
    auto *export_concentration = NewOperation("ExportConcentration");
    scheduler->ScheduleOp(export_concentration, OpType::kPreSchedule);
  }

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
