#include "custom_ops.h"

namespace bdm {
    BDM_REGISTER_OP(TrackPosition, "track_position", kCpu);
    BDM_REGISTER_OP(DissipativeForce, "dissipative_force", kCpu);
}  // namespace bdm