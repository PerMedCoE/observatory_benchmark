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

// ----------------------------------------------------------------------
// Taken from cell cycle use case
// ----------------------------------------------------------------------
class MyCell : public Cell {  // our object extends the Cell object
  // create the header with our new data member
  BDM_AGENT_HEADER(MyCell, Cell, 1);

 public:
  MyCell() {}
  explicit MyCell(const Real3 &position) : Base(position) {}
  virtual ~MyCell() {}

  /// If MyCell divides, the daughter has to initialize its attributes
  void Initialize(const NewAgentEvent &event) override {
    Base::Initialize(event);

    if (auto *mother = dynamic_cast<MyCell *>(event.existing_agent)) {
      cycle_ = mother->cycle_;
      delt_ = mother->delt_;
      vmax_ = mother->vmax_;
      delt_ = mother->vinit_;
      vrel_ = mother->vrel_;
      if (event.GetUid() == CellDivisionEvent::kUid) {
        // the daughter will be able to divide
        can_divide_ = true;
      } else {
        can_divide_ = mother->can_divide_;
      }
    }
  }

  // getter and setter for division
  void SetCanDivide(bool d) { can_divide_ = d; }
  bool GetCanDivide() const { return can_divide_; }

  // getter and setter for cells current phase of cell cycle
  void SetCycle(int c) { cycle_ = c; }
  int GetCycle() const { return cycle_; }

  // getter and setter for cells maximum volume
  void SetVmax(double vm) { vmax_ = vm; }
  double GetVmax() const { return vmax_; }

  // getter and setter for cells initial volume
  void SetVinit(double vi) { vinit_ = vi; }
  double GetVinit() const { return vinit_; }

  // getter and setter for delt t
  void SetDelt(double dt) { delt_ = dt; }
  double GetDelt() const { return delt_; }

  // getter and setter for relative cell volume
  void SetVrel(double vr) { vrel_ = vr; }
  double GetVrel() const { return vrel_; }

 private:
  // declare new data member and define their type
  // private data can only be accessed by public function and not directly
  bool can_divide_;
  int cycle_;
  double vmax_;
  double vinit_;
  double delt_;
  double vrel_;
};

// Define growth behaviour
struct Growth : public Behavior {
  BDM_BEHAVIOR_HEADER(Growth, Behavior, 1);

  Growth() { AlwaysCopyToNew(); }
  virtual ~Growth() {}

  void Run(Agent *agent) override {
    if (auto *cell = dynamic_cast<MyCell *>(agent)) {
      auto *random = Simulation::GetActive()->GetRandom();
      double ran = random->Uniform(0, 1) * 1.0;

      // Counter for Delta t at each stage
      // Used for calculating probability of moving to next state.
      cell->SetDelt(cell->GetDelt() + 0.1);

      // If statements for checking what states we are in and if
      // a cell moves to the next state based on cumulitave probability.
      if (cell->GetCycle() == 1) {
        double p1 = (cell->GetDelt() / 7) * cell->GetDelt();
        if (p1 > ran) {
          // Changing cells state number or "cycle" postiion.
          cell->SetCycle(2);
          // Delta t is always reset when exiting a state for use in the next
          // state.
          cell->SetDelt(0);
        }
      } else if (cell->GetCycle() == 2) {
        double p2 = (cell->GetDelt() / 6) * cell->GetDelt();
        if (p2 > ran) {
          cell->SetCycle(3);
          cell->SetDelt(0);
        }
      } else if (cell->GetCycle() == 3) {
        double p3 = (cell->GetDelt() / 3) * cell->GetDelt();
        if (p3 > ran) {
          cell->SetCycle(4);
          cell->SetDelt(0);
        }
      } else {
        double p4 = (cell->GetDelt() / 2) * cell->GetDelt();
        if (p4 > ran) {
          cell->SetCycle(1);
          cell->SetDelt(0);
          // Checking if cell has reached the critical volume which leads to
          // cell division. Here 0.975 Vmax is roughly 195% the initial cell
          // volume.
          if (cell->GetVolume() > cell->GetVmax() * 0.975) {
            cell->Divide();
          }
        }
      }

      // Checking if our cells volume is less than the maximum possible
      // valuable achievalbe. if yes cell grows if no then cell does not grow.
      if (cell->GetVolume() < cell->GetVmax()) {
        double alpha = 1.0;
        cell->ChangeVolume(
            alpha * cell->GetVolume() *
            ((cell->GetVmax() - cell->GetVolume()) / cell->GetVmax()));
      }
    }
  }
};

// ---------------------------------------------------------------------
// Counters
// ---------------------------------------------------------------------

using experimental::Counter;
using experimental::GenericReducer;

inline void DefineAndRegisterCollectors() {
  // Get population statistics, i.e. extract data from simulation
  // Get the pointer to the TimeSeries
  auto *ts = Simulation::GetActive()->GetTimeSeries();

  // Define how to get the time values of the TimeSeries
  auto get_time = [](Simulation *sim) {
    return static_cast<double>(sim->GetScheduler()->GetSimulatedTime());
  };

  // Define how to count the agents in state 1
  auto is_state_1 = [](Agent *a) {
    auto *cell = bdm_static_cast<MyCell *>(a);
    bool tmp = (cell->GetCycle() == 1);
    return tmp;
  };
  ts->AddCollector("state1", new Counter<double>(is_state_1), get_time);

  // Define how to count the agents in state 2
  auto is_state_2 = [](Agent *a) {
    auto *cell = bdm_static_cast<MyCell *>(a);
    bool tmp = (cell->GetCycle() == 2);
    return tmp;
  };
  ts->AddCollector("state2", new Counter<double>(is_state_2), get_time);

  // Define how to count the agents in state 3
  auto is_state_3 = [](Agent *a) {
    auto *cell = bdm_static_cast<MyCell *>(a);
    bool tmp = (cell->GetCycle() == 3);
    return tmp;
  };
  ts->AddCollector("state3", new Counter<double>(is_state_3), get_time);

  // Define how to count the agents in state 4
  auto is_state_4 = [](Agent *a) {
    auto *cell = bdm_static_cast<MyCell *>(a);
    bool tmp = (cell->GetCycle() == 4);
    return tmp;
  };
  ts->AddCollector("state4", new Counter<double>(is_state_4), get_time);

  // Define how to count the agents in state 4
  auto count_all = [](Agent *a) {
    auto *cell = bdm_static_cast<MyCell *>(a);
    if (cell) {
      return true;
    } else {
      return false;
    }
  };
  ts->AddCollector("all", new Counter<double>(count_all), get_time);
}

inline void PlotAndSaveTimeseries() {
  // Get pointers for simulation and TimeSeries data
  auto sim = Simulation::GetActive();
  auto *ts = sim->GetTimeSeries();

  // Save the TimeSeries Data as JSON to the folder <date_time>
  ts->SaveJson(Concat(sim->GetOutputDir(), "/time-series-data.json"));

  // Create a bdm LineGraph that visualizes the TimeSeries data
  {
    bdm::experimental::LineGraph g(ts, "Spheroid", "Time", "Number of agents",
                                   true);
    g.Add("state1", "State 1", "L", kBlue, 1.0);
    g.Add("state2", "State 2", "L", kGreen, 1.0);
    g.Add("state3", "State 3", "L", kRed, 1.0);
    g.Add("state4", "State 4", "L", kOrange, 1.0);
    g.Draw();
    g.SaveAs(Concat(sim->GetOutputDir(), "/spheroid"), {".svg", ".png"});
  }
  {
    bdm::experimental::LineGraph g(ts, "Spheroid", "Time", "Number of agents",
                                   true);
    g.Add("all", "All states", "L", kBlue, 1.0);
    g.Draw();
    g.SaveAs(Concat(sim->GetOutputDir(), "/all-cells"), {".svg", ".png"});
  }
}

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
  auto *scheduler = simulation.GetScheduler();  // Get the Scheduler

  // ------------------------------------------------------------------
  // Add initial spheroid
  // ------------------------------------------------------------------

  auto create_cell = [&](const Real3 &position) {
    MyCell *cell = new MyCell(position);
    cell->SetDiameter(10.0);
    cell->SetVinit(cell->GetVolume());
    cell->SetVrel(100.0);
    double x = cell->GetVolume() * 2.0;
    cell->SetVmax(x);
    cell->SetDelt(0.0);
    cell->SetCycle(1);
    cell->SetCanDivide(true);
    cell->AddBehavior(new Growth());
    return cell;
  };
  ModelInitializer::CreateAgentsInSphereRndm({0, 0, 0}, 40, 100, create_cell);

  // ------------------------------------------------------------------
  // Extract information from simulation
  // ------------------------------------------------------------------

  DefineAndRegisterCollectors();

  // ------------------------------------------------------------------
  // Run simulation
  // ------------------------------------------------------------------

  scheduler->Simulate(n_steps);
  scheduler->PrintInfo(std::cout);  // Print information about the simulation

  // ------------------------------------------------------------------
  // Extract information from simulation
  // ------------------------------------------------------------------

  PlotAndSaveTimeseries();

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // DIFFUSION_SMALL_H_
