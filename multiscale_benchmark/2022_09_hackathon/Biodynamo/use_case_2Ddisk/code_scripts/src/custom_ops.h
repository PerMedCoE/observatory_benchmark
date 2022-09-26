#ifndef CUSTOM_OPS_H_
#define CUSTOM_OPS_H_

#include "biodynamo.h"
#include "core/environment/uniform_grid_environment.h"

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

  struct CountCells : public StandaloneOperationImpl {
    // This macro will generate the boilerplate code. It must be included.
    BDM_OP_HEADER(CountCells);

    void operator()() override {
      auto* sim = Simulation::GetActive();
      auto* rm = sim->GetResourceManager();

      (*total_cells_).push_back(rm->GetNumAgents());
    }

    std::vector<size_t>* total_cells_;

  };

}  // namespace bdm

#endif
