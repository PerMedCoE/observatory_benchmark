#ifndef CUSTOM_OPS_H_
#define CUSTOM_OPS_H_

#include "biodynamo.h"

namespace bdm {

struct MoveCellsPlane : public AgentOperationImpl {
  BDM_OP_HEADER(MoveCellsPlane);

  void operator()(Agent* agent) override {
      Double3 cell_position = agent->GetPosition();
      if (cell_position[2]!=0.0)
      {
        cell_position[2] = 0.0;
        agent->SetPosition(cell_position);
      }
  }

};

}  // namespace bdm

#endif
