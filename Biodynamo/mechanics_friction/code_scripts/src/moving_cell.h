#ifndef MOVING_CELL_H_
#define MOVING_CELL_H_

#include "biodynamo.h"
#include "core/agent/cell.h"

namespace bdm {

class Moving_cell : public Cell {
  BDM_AGENT_HEADER(Moving_cell, Cell, 1);

 public:
  Moving_cell() {}
  explicit Moving_cell(const Real3& position) : Base(position) {}
  virtual ~Moving_cell() {}

  Real3 GetSpeed() { return speed_; }

  void SetSpeed(Real3 speed) { speed_ = speed; }

  void UpdateSpeed(Real3 delta_speed) {
    speed_ += delta_speed;
  }

 private:
  // 10 um/min -> 1um/0.1 min
  Real3 speed_ = {0.0, 0.0, 0.0};
};

}  // namespace bdm

#endif  // MOVING_CELL_H_