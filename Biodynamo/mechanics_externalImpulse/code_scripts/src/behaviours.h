#ifndef BEHAVIOURS_H_
#define BEHAVIOURS_H_

#include "core/behavior/behavior.h"
#include "biodynamo.h"
#include "moving_cell.h"

namespace bdm {

struct Move : public Behavior {
  BDM_BEHAVIOR_HEADER(Move, Behavior, 1);

  Move() { AlwaysCopyToNew(); }

  void Run(Agent* a) override {

    real_t time = bdm::Simulation::GetActive()->GetScheduler()->GetSimulatedTime();
    real_t timestep = bdm::Simulation::GetActive()->GetParam()->simulation_time_step;


    if (auto* cell = bdm_static_cast<Moving_cell*>(a)) {
      if (time >= cell->GetInitialForceTime() && time < cell->GetFinalForceTime()) {
        speed = {cell->GetForce()[0] / cell->GetFrictionCoefficient(), 0.0, 0.0}; // Constant speed due to constant force and friction
        cell->SetSpeed(speed);
        cell->ApplyDisplacement(cell->GetSpeed()*timestep);
        distance_covered += cell->GetSpeed();
      }
      else {
        cell->SetSpeed({0.0, 0.0, 0.0});
      }
  }
}
  Double3 distance_covered = {0.0, 0.0, 0.0};
  Double3 speed = {0.0, 0.0, 0.0};
};

}  // namespace bdm

#endif  // BEHAVIOURS_H_