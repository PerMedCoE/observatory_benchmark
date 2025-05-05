#ifndef CUSTOM_OPS_H_
#define CUSTOM_OPS_H_

#include "biodynamo.h"
#include "moving_cell.h"

namespace bdm {

struct DissipativeForce : public AgentOperationImpl {
  BDM_OP_HEADER(DissipativeForce);

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      Double3 decrease_speed = cell->GetSpeed() * (-friction_coefficient_);

      cell->UpdateSpeed(decrease_speed);
    }
  }

  double friction_coefficient_ = 0.;
};

struct TrackPosition : public AgentOperationImpl {
  BDM_OP_HEADER(TrackPosition);

  // GetUid()

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      (*positions_)[cell->GetId()].push_back(cell->GetPosition());
    }
  }

  std::vector<std::vector<Double3>>* positions_;
};

}  // namespace bdm

#endif
