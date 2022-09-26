#ifndef MY_CELL_H_
#define MY_CELL_H_

#include "biodynamo.h"
#include "core/agent/cell.h"

namespace bdm {

class MyCell : public Cell {  // our object extends the Cell object
                              // create the header with our new data member
  BDM_AGENT_HEADER(MyCell, Cell, 1);

 public:
  MyCell() {}
  explicit MyCell(const Double3& position) : Base(position) {}
  virtual ~MyCell() {}

  /// If MyCell divides, the daughter has to initialize its attributes
  void Initialize(const NewAgentEvent& event) override {
    Base::Initialize(event);

    if (auto* mother = dynamic_cast<MyCell*>(event.existing_agent)) {
      cycle_ = mother->cycle_;
      delt_ = mother->delt_;
      vmax_ = mother->vmax_;
      delt_ = mother->vinit_;
      vrel_ = mother->vrel_;
      if (event.GetUid() == CellDivisionEvent::kUid) {
        // the daughter will be able to divide
        can_divide_ = true;
      } else {
        can_divide_ = mother->can_divide_;
      }
    }
  }

  // getter and setter for division
  void SetCanDivide(bool d) { can_divide_ = d; }
  bool GetCanDivide() const { return can_divide_; }

  // getter and setter for cells current phase of cell cycle
  void SetCycle(int c) { cycle_ = c; }
  int GetCycle() const { return cycle_; }

  // getter and setter for cells maximum volume
  void SetVmax(double vm) { vmax_ = vm; }
  double GetVmax() const { return vmax_; }

  // getter and setter for cells initial volume
  void SetVinit(double vi) { vinit_ = vi; }
  double GetVinit() const { return vinit_; }

  // getter and setter for delt t
  void SetDelt(double dt) { delt_ = dt; }
  double GetDelt() const { return delt_; }

  // getter and setter for relative cell volume
  void SetVrel(double vr) { vrel_ = vr; }
  double GetVrel() const { return vrel_; }

 private:
  // declare new data member and define their type
  // private data can only be accessed by public function and not directly
  bool can_divide_;
  int cycle_;
  double vmax_;
  double vinit_;
  double delt_;
  double vrel_;
};

}  // namespace bdm

#endif  // MY_CELL_H_