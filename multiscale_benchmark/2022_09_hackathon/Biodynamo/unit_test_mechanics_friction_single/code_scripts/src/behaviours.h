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
      cell->ApplyDisplacement(cell->GetSpeed());
    }
  }
};

}  // namespace bdm

#endif  // BEHAVIOURS_H_