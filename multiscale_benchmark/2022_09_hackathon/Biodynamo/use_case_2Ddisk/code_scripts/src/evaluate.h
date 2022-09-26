// -----------------------------------------------------------------------------
//
// Copyright (C) Lukas Breitwieser.
// All Rights Reserved.
//
// -----------------------------------------------------------------------------

#ifndef EVALUATE_H_
#define EVALUATE_H_

#include <TAxis.h>
#include <TLegend.h>
#include <TMultiGraph.h>
#include <cmath>
#include <vector>
#include "biodynamo.h"

using namespace bdm::experimental;

namespace bdm {

// ---------------------------------------------------------------------------
inline void SetupResultCollection(Simulation* sim) {
  auto* ts = sim->GetTimeSeries();
  auto get_env_dims = [](Simulation* sim) {
    auto* env = dynamic_cast<UniformGridEnvironment*>(sim->GetEnvironment());
    double env_dim_x, env_dim_y;
    env_dim_x = env->GetDimensions()[1]-env->GetDimensions()[0];
    env_dim_y = env->GetDimensions()[3]-env->GetDimensions()[2];
    return std::max(env_dim_x, env_dim_y);
  };
  auto get_time = [](Simulation* sim) {
    auto* scheduler = sim->GetScheduler();
    double t0 = 14.;  // Initial time
    return (double)(t0+scheduler->GetSimulatedSteps()*0.1/24.); // 1 step = 0.1h -> /24 -> days
  };

  ts->AddCollector("env_dims", get_env_dims, get_time);
}

// ---------------------------------------------------------------------------
inline void PlotResults(const std::vector<TimeSeries>& individual_rd,
                        const std::string& folder,
                        const bool plot_legend = true,
                        const std::string& filename = "result") {
  TimeSeries allts;
  std::vector<double> times;
  std::vector<double> sizes;
  
  int i = 0;
  for (auto& ind_ts : individual_rd) {
    allts.Add(ind_ts, Concat("i", i++));
    times = ind_ts.GetXValues("env_dims");
    sizes = ind_ts.GetYValues("env_dims");
  }

  // Add exp data from Figure 1 from Drasdo and Hoehme (2005)
  allts.Add("experimental_data", {336/24., 386/24., 408/24., 481/24., 506/24., 646/24.}, {1140, 1400, 1590, 2040, 2250, 3040});

  LineGraph lg(&allts, "", "Time [days]", "2D Monolayer size (um)", plot_legend,
  nullptr, 350, 250);

  for (uint64_t i = 0; i < individual_rd.size(); ++i) {
    lg.Add(Concat("env_dims-i", i), "Sim data ", "LP", kBlue, 0.2, kSolid, 2, kBlue,
           0.7, kFullCircle, 0.5);
  }

  // Add style for exp data
  lg.Add("experimental_data", "Exp data ", "LP", kBlack, 0.2, kSolid, 2, kBlack,
   0.7, kFullCircle, 0.5);

  if (plot_legend) {
    lg.SetLegendPosNDC(0.1, 0.7, 0.3, 0.9);
  }

  // Export monolayer size
  std::ofstream file;
  if (!file.is_open()) {
    file.open("monolayer_diam.csv");
  }

  for (size_t i = 0; i < times.size(); i++) {
    file << (int)times[i] << "\t " << sizes[i] << std::endl;
  }

  file.close();

  //lg.GetTMultiGraph()->SetMinimum(0.);
  lg.SaveAs(Concat(folder, "/", filename), {".svg", ".root", ".C"});
}

}  // namespace bdm

#endif  // EVALUATE_H_
