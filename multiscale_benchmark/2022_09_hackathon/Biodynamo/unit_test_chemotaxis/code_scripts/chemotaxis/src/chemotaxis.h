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

/// Operation to export agent position to csv
class ExportPosition : public StandaloneOperationImpl {
  BDM_OP_HEADER(ExportPosition);

 public:
  ExportPosition(const std::string &filename) : filename_(filename) {}

  void operator()() override {
    std::ofstream file1;
    if (!file1.is_open()) {
      file1.open(filename_, std::ios_base::app);
    }
    file1 << Simulation::GetActive()->GetScheduler()->GetSimulatedSteps()
          << ", ";
    auto *rm = Simulation::GetActive()->GetResourceManager();
    rm->ForEachAgent([&file1](Agent *agent) {
      auto &position = agent->GetPosition();
      file1 << agent->GetUid() << ", " << position[0] << ", " << position[1]
            << ", " << position[2] << "\n";
    });
    file1.close();
  };

 private:
  std::string filename_ = "agent_position.csv";
};

/// Operation to add a substance to the simulation
class SourceTerm : public StandaloneOperationImpl {
  BDM_OP_HEADER(SourceTerm);

 public:
  SourceTerm(const std::string &substance, const Real3 &source_position,
             real_t source_concentration)
      : substance_(substance),
        source_position_(source_position),
        dgrid_(nullptr),
        source_index_(0),
        source_concentration_(source_concentration),
        initialized_(false) {}

  void operator()() override {
    if (!initialized_) {
      dgrid_ = Simulation::GetActive()->GetResourceManager()->GetDiffusionGrid(
          substance_);
      source_index_ = dgrid_->GetBoxIndex(source_position_);
      initialized_ = true;
    }
    dgrid_->ChangeConcentrationBy(source_index_, source_concentration_);
  };

 private:
  std::string substance_;
  Real3 source_position_;
  DiffusionGrid *dgrid_;
  size_t source_index_;
  real_t source_concentration_;
  bool initialized_ = false;
};

// --------------------------------------------------------------------
/// Follow the gradient of the substance
// --------------------------------------------------------------------
class FollowGradient : public Behavior {
  BDM_BEHAVIOR_HEADER(FollowGradient, Behavior, 0);

 public:
  FollowGradient() = default;
  explicit FollowGradient(const std::string &substance,
                          real_t gradient_scale_factor = 1)
      : substance_(substance), gradient_scale_factor_(gradient_scale_factor) {}

  virtual ~FollowGradient() = default;

  void Initialize(const NewAgentEvent &event) override { return; }

  void Run(Agent *agent) override {
    if (!initialized_) {
      dgrid_ = Simulation::GetActive()->GetResourceManager()->GetDiffusionGrid(
          substance_);
      initialized_ = true;
    }
    auto *cell = bdm_static_cast<Cell *>(agent);
    auto &position = cell->GetPosition();
    Real3 gradient;
    dgrid_->GetGradient(position, &gradient, false);
    auto gradient_norm = gradient.Norm();
    if (gradient_norm < 1e-6) {
      return;
    } else {
      cell->ApplyDisplacement(gradient * gradient_scale_factor_);
    }
  }

 private:
  const std::string substance_;
  DiffusionGrid *dgrid_ = nullptr;
  real_t gradient_scale_factor_ = 1;
  bool initialized_ = false;
};

inline int Simulate(int argc, const char **argv) {
  // ------------------------------------------------------------------
  // Define simulation parameters
  // ------------------------------------------------------------------

  // Export to CSV (introduces overhead)
  bool export_to_csv = false;
  // Boundary concentrations [uM]
  double c_0 = 0;
  // Diffusion coefficient [uM^2/min]
  double D = 200;
  // Source term [uM/min]
  real_t source = 0.2 / 0.01;
  // Simulation time [min]
  double t_max = 10;
  // Time step [min]
  double dt = 0.01;
  // Number of time steps
  int n_steps = t_max / dt;
  // Domain size
  double domain_size = 120;
  // Scale factor for gradient (determines speed of movement)
  double gradient_scale_factor = 850;
  // Source position
  Real3 source_position = {55, 55, 55};

  // Print information about simulation parameters for the user
  std::cout << "Simulation parameters:"
            << "\n";
  std::cout << "  Boundary concentration: " << c_0 << " uM"
            << "\n";
  std::cout << "  Diffusion coefficient: " << D << " uM^2/min"
            << "\n";
  std::cout << "  Source term: " << source << " uM/min"
            << "\n";
  std::cout << "  Simulation time: " << t_max << " min"
            << "\n";
  std::cout << "  Time step: " << dt << " min"
            << "\n";
  std::cout << "  Number of time steps: " << n_steps << "\n";
  std::cout << "  Domain size: " << domain_size << " um"
            << "\n";
  std::cout << "  Scale factor for gradient: " << gradient_scale_factor << "\n";

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
    param->calculate_gradients = true;
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
  // Add cell to simulation
  // ------------------------------------------------------------------

  Cell *cell = new Cell(10);
  cell->AddBehavior(new FollowGradient("Substance", gradient_scale_factor));
  rm->AddAgent(cell);

  // ------------------------------------------------------------------
  // Operation to export agent position at each time step
  // ------------------------------------------------------------------

  if (export_to_csv) {
    OperationRegistry::GetInstance()->AddOperationImpl(
        "ExportPosition", OpComputeTarget::kCpu,
        new ExportPosition(param->output_dir + "/position.csv"));
    auto *export_concentration = NewOperation("ExportPosition");
    scheduler->ScheduleOp(export_concentration, OpType::kPreSchedule);
  }

  // ------------------------------------------------------------------
  // Operation to add source term to substance
  // ------------------------------------------------------------------

  OperationRegistry::GetInstance()->AddOperationImpl(
      "SourceTerm", OpComputeTarget::kCpu,
      new SourceTerm("Substance", source_position,
                     source * param->simulation_time_step));
  auto *source_term = NewOperation("SourceTerm");
  scheduler->ScheduleOp(source_term, OpType::kPreSchedule);

  // ------------------------------------------------------------------
  // Run simulation
  // ------------------------------------------------------------------

  scheduler->Simulate(n_steps);
  scheduler->PrintInfo(std::cout);  // Print information about the simulation

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // DIFFUSION_SMALL_H_
