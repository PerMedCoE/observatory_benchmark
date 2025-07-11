#ifndef CUSTOM_OPS_H_
#define CUSTOM_OPS_H_

#include "biodynamo.h"
#include "moving_cell.h"

namespace bdm {

struct DissipativeForce : public AgentOperationImpl {
  BDM_OP_HEADER(DissipativeForce);

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      Real3 decrease_speed = cell->GetSpeed() * (-friction_coefficient_);

      cell->UpdateSpeed(decrease_speed);
    }
  }

  double friction_coefficient_ = 0.;
};

struct ApplyForce : public AgentOperationImpl {
  BDM_OP_HEADER(ApplyForce);

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      real_t dt = Simulation::GetActive()->GetParam()->simulation_time_step;
      Real3 displacement = initial_speed_ * dt;

      cell->ApplyDisplacement(displacement);
    }
  }

  Real3 initial_speed_ = {0., 0., 0.};
};

struct TrackPosition : public AgentOperationImpl {
  BDM_OP_HEADER(TrackPosition);

  // GetUid()

  void operator()(Agent* agent) override {
    (*positions_).push_back(agent->GetPosition());
  }

  std::vector<Real3>* positions_;
};

}  // namespace bdm

#endif
