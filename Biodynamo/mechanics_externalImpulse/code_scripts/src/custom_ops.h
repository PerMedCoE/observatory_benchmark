#ifndef CUSTOM_OPS_H_
#define CUSTOM_OPS_H_

#include "biodynamo.h"
#include "moving_cell.h"

namespace bdm {

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

struct TrackSpeed : public AgentOperationImpl {
  BDM_OP_HEADER(TrackSpeed);

  // GetUid()

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      (*speeds_)[cell->GetId()].push_back(cell->GetSpeed());
    }
  }

  std::vector<std::vector<Double3>>* speeds_;
};

}  // namespace bdm

#endif
