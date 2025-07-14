
// BioDynaMo dictionary.
// This file was generated.
// Do NOT change it. 
// Changes will be lost the next time this file is generated.

#include "core/util/jit.h"
#include <cstdlib>
#include <sstream>
namespace {

void AppendEnvVar(std::stringstream& s, const char* var_name,
                  const char* suffix) {
  auto val = std::getenv(var_name);
  if (val) {
    s << val << suffix << ":";
  }
}

static struct BioDynaMoDictInit {
  BioDynaMoDictInit() {
    std::stringstream idirs; 
    idirs << "/opt/homebrew/Cellar/open-mpi/5.0.2/include" << ":";
    idirs << std::getenv("ROOTSYS") << "/include" << ":";
    idirs << "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/code_scripts/build/omp" << ":";
    idirs << "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/code_scripts/build/opencl" << ":";
    idirs << std::getenv("BDMSYS") << "/include" << ":";
    idirs << std::getenv("BDMSYS") << "/include/optim" << ":";
    idirs << "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/code_scripts/src" << ":";
    bdm::JitHeaders::Register("custom_ops.h");
    bdm::JitHeaders::Register("moving_cell.h");
    bdm::JitHeaders::Register("unit-test-mechanics.h");

    AppendEnvVar(idirs, "ROOT_INCLUDE_PATH", "");
    setenv("ROOT_INCLUDE_PATH", idirs.str().c_str(), true);
  }
} bdm_dict_initializer;

}

  
