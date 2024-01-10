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
#ifndef CELLCYCLE1_H_
#define CELLCYCLE1_H_

#include "biodynamo.h"

namespace bdm {

const int BiologyCellCycle_A  = -1; // Apoptosis
const int BiologyCellCycle_G0 =  0; // Resting phase
const int BiologyCellCycle_G1 =  1; // Interphase: Gap 1
const int BiologyCellCycle_S  =  2; // Interphase: Synthesis
const int BiologyCellCycle_G2 =  3; // Interphase: Gap 2
const int BiologyCellCycle_M  =  4; // Cell division: mitosis



class BiologyCell : public Cell {  // our object extends the Cell object
  BDM_AGENT_HEADER(BiologyCell, Cell, 1);

public:
  // class constructor(s) and destructor
  BiologyCell() {}
  explicit BiologyCell(const Real3& position) : Base(position) {
    age_ = 0;
    cycle_time_ = 0;
    phase_ = BiologyCellCycle_G0;
  }
  virtual ~BiologyCell() {}

  void SetAge(int age) { age_ = age; }
  int GetAge() const { return age_; }
  void IncrementAge() { age_ += 1; }

  void ResetCycleTime() { cycle_time_ = 0; }
  int GetCycleTime() const { return cycle_time_; }
  void IncrementCycleTime() { cycle_time_ += 1; }

  void SetPhase(int phase) { phase_ = phase; }
  int GetPhase() const { return phase_; }

  // Initialize data if agent divides by passing information
  // from the mother to the daughter agent
  void Initialize(const NewAgentEvent& event) override {
    Base::Initialize(event);

    if (auto* mother = dynamic_cast<BiologyCell*>(event.existing_agent)) {
      if (event.GetUid() == CellDivisionEvent::kUid) {
        age_ = 0;
        cycle_time_ = 0;
        phase_ = BiologyCellCycle_G0;
        if (BiologyCellCycle_M!=mother->GetPhase()) {
          bdm::Log::Fatal("bdm::BiologyCellCycle::Run",
            "error @line "+std::to_string(__LINE__));
        }
      }
    }
  }

private:
  // member data
  int age_, cycle_time_;
  int phase_;
};



// Define the behaviour of biology cell cycle
class BiologyCellCycle : public Behavior {
  BDM_BEHAVIOR_HEADER(BiologyCellCycle, Behavior, 1);

public:
  // class constructor and destructor
  BiologyCellCycle() { AlwaysCopyToNew(); }
  virtual ~BiologyCellCycle() {}

  void Run(Agent *agent) override {
    if (auto* cell = dynamic_cast<BiologyCell*>(agent)) {
      auto* param = Simulation::GetActive()->GetParam();
      auto* rand = Simulation::GetActive()->GetRandom();

      cell->IncrementAge();
      cell->IncrementCycleTime();
      // Check for the cell phase
      if (BiologyCellCycle_A == cell->GetPhase()) {
        cell->RemoveBehavior(this);
        cell->RemoveFromSimulation();
      } else if (BiologyCellCycle_M == cell->GetPhase()) {
        cell->ResetCycleTime();
        cell->SetPhase(BiologyCellCycle_G0);
      }

      const double V_min = (Math::kPi/6.0)*pow(10.0, 3),
                   V_max = 2.0 * V_min;
      const double T = cell->GetCycleTime()
                     * param->simulation_time_step;
      if        (T <= 7.0) {
        cell->SetPhase(BiologyCellCycle_G1);
      } else if (T <= 13.0) {
        cell->SetPhase(BiologyCellCycle_S);
        const double probability = 0.9999;
        if (rand->Uniform(0.0,1.0) <= probability) {
          const double V = V_min*(-0.00908*T*T+0.316*T-0.752);
          cell->SetVolume(V>V_max?V_max:V);
        }
      } else if (T <= 18.0) {
        cell->SetPhase(BiologyCellCycle_G2);
        const double probability = 0.9999;
        if (rand->Uniform(0.0,1.0) <= probability) {
          const double V = V_min*(-0.00908*T*T+0.316*T-0.752);
          cell->SetVolume(V>V_max?V_max:V);
        }
      } else {
        cell->SetPhase(BiologyCellCycle_M);
        const double probability = 0.9999;
        if (rand->Uniform(0.0,1.0) <= probability) {
          cell->Divide(1.0);
        }
      }
    }
  }
};



inline int Simulate(int argc, const char** argv) {
  // Define the simulation parameters
  auto set_param = [](Param* param) {
    param->bound_space = Param::BoundSpaceMode::kOpen;
    param->simulation_time_step = 0.01;
    param->visualization_interval = 100;
    param->min_bound = -100.0;
    param->max_bound = +100.0;
    param->statistics = true;
  };

  // Create a new simulation
  Simulation simulation(argc, argv, set_param);
  // Access some important data structures
  auto* rm = simulation.GetResourceManager();
  auto* param = simulation.GetParam();

  std::string s;
  s = "rm " + param->output_dir + "/cell-*.csv";
  std::system(s.c_str());

  {

    double x, y, z;
    x = y = z = 0.0;

    auto* cell = new BiologyCell({x, y, z});
    cell->SetVolume((Math::kPi/6.0)*pow(10.0, 3));
    cell->AddBehavior(new BiologyCellCycle());

    rm->AddAgent(cell); // insert the agent created in the simulation

  }

  // Run the simulation for multiple time-steps
  const int n_time_steps = 4800;
  for (int t=1; t<=n_time_steps; ++t) {

    simulation.GetScheduler()->Simulate(1);

    rm->ForEachAgent([&] (bdm::Agent* a) {
      if (auto* cell = dynamic_cast<BiologyCell*>(a)) {
        const std::string id = std::to_string(cell->GetUid().GetIndex());
        s = param->output_dir + "/cell-" + id + ".csv";

        std::ofstream out(s, std::ofstream::app);
        out << (t*param->simulation_time_step)
            << ',' << cell->GetVolume()
            << ',' << cell->GetPhase()
            << ',' << cell->GetAge()
            << std::endl;
      }
    });

  }

  simulation.GetScheduler()->PrintInfo(std::cout);

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // CELLCYCLE1_H_
