// -----------------------------------------------------------------------------
//
// Copyright (C) 2021 CERN & University of Surrey for the benefit of the
// BioDynaMo collaboration. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef DIFFUSION_DECAY_H_
#define DIFFUSION_DECAY_H_

#include "biodynamo.h"
#include "core/diffusion/euler_grid.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  auto set_param = [&](Param* param) {
          param->bound_space = Param::BoundSpaceMode::kClosed;
          param->diffusion_boundary_condition = "Dirichlet";
          param->min_bound = -120;
          param->max_bound = 120;
  };
  Simulation simulation(argc, argv, set_param);
  simulation.GetEnvironment()->Update();
  auto* rm = simulation.GetResourceManager();

  int tot = 10000;
  double simulation_time_step = 0.001;
  double decay_coef = 1;
  double diff_coef = 2000.0;
  double sink = 12;
  size_t res = 48;
  auto* dgrid = new EulerGrid(0, "Substance", diff_coef, decay_coef, res);

  dgrid->Initialize();
  dgrid->SetBoundaryCondition(
                  std::make_unique<ConstantBoundaryCondition>(10.0));
  dgrid->SetUpperThreshold(1e15);
  rm->AddContinuum(dgrid);

  std::ofstream outdata;
  outdata.open("data.csv");

  for (size_t c=0; c<res*res*res; c++) {
     double c_value= dgrid->GetConcentration(c);
     dgrid->ChangeConcentrationBy(c, 10-c_value);
  }

  for (int t=0; t<tot; t++) {

    double total_conc = 0.0;
    for (size_t c=0; c<res*res*res; c++) {
       total_conc += dgrid->GetConcentration(c);
    }
    outdata << t*simulation_time_step << " "
            << total_conc/(res*res*res) << " "
            << dgrid->GetValue({0,0,0}) << std::endl;

    dgrid->Diffuse(simulation_time_step);
  }
  outdata.close();

  outdata.open("contour.csv");

  real_t bl = 240/res;

  for (real_t y=-120+bl/2.; y<120; y+=bl) {
      for (real_t x=-120+bl/2.; x<120; x+=bl) {
           real_t conc = dgrid->GetValue({x,y,0});
	   outdata << conc << " ";
      }
      outdata << std::endl;
  }
  outdata.close();

  return 0;
}

}  // namespace bdm

#endif  // DIFFUSION_DECAY_H_
