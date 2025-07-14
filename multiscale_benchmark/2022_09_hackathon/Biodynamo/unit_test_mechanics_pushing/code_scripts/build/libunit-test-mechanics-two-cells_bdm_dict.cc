
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
    idirs << "/opt/homebrew/Cellar/open-mpi/5.0.7/include" << ":";
    idirs << "/Users/hp024/buildroadrunner/llvm-13.x/install-msvc2019/include" << ":";
    idirs << "/Users/hp024/buildroadrunner/llvm-13.x/install-msvc2019/include" << ":";
    idirs << "/Users/hp024/buildroadrunner/roadrunner/install-Release/include" << ":";
    idirs << "/Users/hp024/buildroadrunner/roadrunner/install-Release/include/rr" << ":";
    idirs << "/Users/hp024/buildroadrunner/roadrunner/install-Release/include/sbml" << ":";
    idirs << "/Users/hp024/buildroadrunner/roadrunner/install-Release/include/cvode" << ":";
    idirs << std::getenv("ROOTSYS") << "/include" << ":";
    idirs << "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/build/omp" << ":";
    idirs << "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/build/opencl" << ":";
    idirs << std::getenv("BDMSYS") << "/include" << ":";
    idirs << std::getenv("BDMSYS") << "/include/optim" << ":";
    idirs << "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/src" << ":";
    bdm::JitHeaders::Register("behaviours.h");
    bdm::JitHeaders::Register("cell_cell_force.h");
    bdm::JitHeaders::Register("custom_ops.h");
    bdm::JitHeaders::Register("moving_cell.h");
    bdm::JitHeaders::Register("sim_param.h");
    bdm::JitHeaders::Register("unit-test-mechanics-two-cells.h");

    AppendEnvVar(idirs, "ROOT_INCLUDE_PATH", "");
    setenv("ROOT_INCLUDE_PATH", idirs.str().c_str(), true);
  }
} bdm_dict_initializer;

}

  
