#include "custom_ops.h"

namespace bdm {
    BDM_REGISTER_OP(MoveCellsPlane, "move_cells_plane", kCpu);
    BDM_REGISTER_OP(CountCells, "count_cells", kCpu);
}  // namespace bdm