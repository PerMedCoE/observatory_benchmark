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

    if (auto* cell = bdm_static_cast<Moving_cell*>(a)) {
      if ((6-epsilon) <= time && time <= (6+epsilon)) {
        speed = {cell->GetForce()[0] / cell->GetFrictionCoefficient(), 0.0, 0.0}; // Constant speed due to constant force and friction
        cell->SetSpeed(speed);
        cell->ApplyDisplacement(cell->GetSpeed());
        distance_covered += cell->GetSpeed();
      }
      else {
        cell->SetSpeed({0.0, 0.0, 0.0});
      }
  }
}
  Double3 distance_covered = {0.0, 0.0, 0.0};
  const real_t epsilon = 1e-6;
  Double3 speed = {0.0, 0.0, 0.0};
};

}  // namespace bdm

#endif  // BEHAVIOURS_H_