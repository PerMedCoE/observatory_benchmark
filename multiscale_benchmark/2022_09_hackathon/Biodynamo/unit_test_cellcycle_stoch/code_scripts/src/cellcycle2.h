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
#ifndef CELLCYCLE2_H_
#define CELLCYCLE2_H_

#include "biodynamo.h"

namespace bdm {

class MyCell : public Cell {  // our object extends the Cell object
                              // create the header with our new data member
  BDM_AGENT_HEADER(MyCell, Cell, 1);

 public:
  MyCell() {}
  explicit MyCell(const Real3& position) : Base(position) {}
  virtual ~MyCell() {}

  /// If MyCell divides, the daughter has to initialize its attributes
  void Initialize(const NewAgentEvent& event) override {
    Base::Initialize(event);

    if (auto* mother = dynamic_cast<MyCell*>(event.existing_agent)) {
        cycle_ = mother-> cycle_;
        delt_ = mother-> delt_;
        vmax_ = mother-> vmax_;
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
  int  cycle_;
  double  vmax_;
  double vinit_;
  double delt_;
  double vrel_;
};  

// Define growth behaviour
struct Growth : public Behavior {
  BDM_BEHAVIOR_HEADER(Growth, Behavior, 1);

  Growth() { AlwaysCopyToNew(); }
  virtual ~Growth() {}

  void Run(Agent* agent) override {
    if (auto* cell = dynamic_cast<MyCell*>(agent)) {
      auto* random = Simulation::GetActive()->GetRandom();
      double ran = random->Uniform(0,1)*1.0;
      double gaus = random->Gaus(0.9,1.0)*1.0;
      
      // Counter for Delta t at each stage
      // Used for calculating probability of moving to next state.
      cell->SetDelt(cell->GetDelt() + 0.1);
      
      // If statements for checking what states we are in and if 
      // a cell moves to the next state based on cumulitave probability.
     if (cell->GetCycle() == 1){
       double p1 = (cell->GetDelt()/7) * cell->GetDelt();
          if(p1 > ran){
              // Changing cells state number or "cycle" postiion.
              cell->SetCycle(2);
              // Delta t is always reset when exiting a state for use in the next state.
              cell->SetDelt(0);
        }
          
      } else if (cell->GetCycle() == 2){
       double p2 = (cell->GetDelt()/6) * cell->GetDelt();
         if(p2 > ran){
              cell->SetCycle(3);
              cell->SetDelt(0);
        }
       
      } else if (cell->GetCycle() == 3){
       double p3 = (cell->GetDelt()/3) * cell->GetDelt();
        if(p3 > ran){
             cell->SetCycle(4);
             cell->SetDelt(0);
        }
       
      } else {
       double p4 = (cell->GetDelt()/2) * cell->GetDelt();
        if(p4 > ran){
             cell->SetCycle(1);
             cell->SetDelt(0);
             // Checking if cell has reached the critical volume which leads to cell division.
             // Here 0.975 Vmax is roughly 195% the initial cell volume.  
            if (cell->GetVolume() > cell->GetVmax()*0.975){
             cell->Divide();
             }
        }
       
      }
          
      // Checking if our cells volume is less than the maximum possible valuable achievalbe.
      // if yes cell grows if no then cell does not grow.
      if (cell->GetVolume() < cell->GetVmax()) {
        double alpha = 1.0;
        //cell->ChangeVolume(cell->GetVmax() - cell->GetVolume());
        cell->ChangeVolume(alpha * cell->GetVolume()*((cell->GetVmax() - cell->GetVolume())/cell->GetVmax())*gaus);
      }
      
      //cell->SetVrel((cell->GetVolume()/cell->GetVinit())*100.0);
    }
  }
};
    
inline int Simulate(int argc, const char** argv) {
    
// Adding space edge of but to be used in larger use case.    
  /*auto set_param = [](Param* param) {
    param->bound_space = Param::BoundSpaceMode::kOpen;
    param->min_bound = 0;
    param->max_bound = 60;  // cube of 100*100*100
  }; */   
    
  // Create a new simulation
  Simulation simulation(argc, argv);
  auto* rm = simulation.GetResourceManager();
  auto *scheduler = simulation.GetScheduler();  // Get the Scheduler

  size_t nb_of_cells = 1;  // number of cells in the simulation
  
  for (size_t i = 0; i < nb_of_cells; ++i) {
    MyCell* cell = new MyCell({30, 30, 30});
    cell->SetDiameter(10.0);
    cell->SetVinit(cell->GetVolume());
    cell->SetVrel(100.0);
    double x = cell->GetVolume() * 2.0;
    cell->SetVmax(x);
    cell->SetDelt(0.0);
    cell->SetCycle(1);
    cell->SetCanDivide(true);
    cell->AddBehavior(new Growth());
    rm->AddAgent(cell);  // put the created cell in our cells structure
  }

  // Run simulation for one timestep
  // time steps are in tenths of an hour for a total of 48 hours equivalent in time steps.
  simulation.GetScheduler()->Simulate(480);

  scheduler->PrintInfo(std::cout);
  
  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // CELLCYCLE2_H_
