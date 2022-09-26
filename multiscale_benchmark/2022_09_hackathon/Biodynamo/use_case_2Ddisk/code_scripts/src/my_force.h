#ifndef MY_FORCE_H_
#define MY_FORCE_H_

#include "biodynamo.h"
#include "core/interaction_force.h"

namespace bdm {

class MyForce : public InteractionForce {
 public:
  MyForce() {}
  virtual ~MyForce() {}

  virtual Double4 Calculate(const Agent* lhs, const Agent* rhs) const override;

 private:
  void ForceBetweenCells(const Agent* sphere_lhs, const Agent* sphere_rhs,
                           Double3* result) const;

};

}  // namespace bdm

#endif