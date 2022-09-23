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
    if (auto* cell = bdm_static_cast<Moving_cell*>(a)) {
      if (distance_covered.Norm()<15.)
      {
      cell->ApplyDisplacement(cell->GetSpeed());
      distance_covered += cell->GetSpeed();
    } else {
      cell->SetSpeed({0.0, 0.0, 0.0});
    }
  }
  }
  Double3 distance_covered = {0.0, 0.0, 0.0};
};

}  // namespace bdm

#endif  // BEHAVIOURS_H_