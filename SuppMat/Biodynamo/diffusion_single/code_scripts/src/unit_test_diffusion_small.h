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
#ifndef UNIT_TEST_DIFFUSION_SMALL_H_
#define UNIT_TEST_DIFFUSION_SMALL_H_

#include "biodynamo.h"
#include "core/diffusion/euler_grid.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  auto set_param = [&](Param* param) {
          param->bound_space = Param::BoundSpaceMode::kClosed;
          param->diffusion_boundary_condition = "Dirichlet";
          param->min_bound = -30;
          param->max_bound = 30;
  };
  Simulation simulation(argc, argv, set_param);
  simulation.GetEnvironment()->Update();
  auto* rm = simulation.GetResourceManager();

  int tot = 1000;
  double simulation_time_step = 0.01;
  double decay_coef = 0.0;
  double diff_coef = 2000.0;
  double sink = 20.0;
  size_t res = 3;
  auto* dgrid = new EulerGrid(0, "Substance", diff_coef, decay_coef, res);

  dgrid->Initialize();
  dgrid->SetBoundaryCondition(
		  std::make_unique<ConstantBoundaryCondition>(10.0));
  dgrid->SetUpperThreshold(1e15);
  rm->AddContinuum(dgrid);

  std::ofstream outdata;
  outdata.open("data.csv");

  for (int t=0; t<tot; t++) {

    double total_conc = 0.0;
    for (size_t c=0; c<res*res*res; c++) {
       total_conc += dgrid->GetConcentration(c);
    }
    outdata << t*simulation_time_step << " " 
	    << total_conc/(res*res*res) << " " 
	    << dgrid->GetValue({0,0,0}) << std::endl;

    dgrid->Diffuse(simulation_time_step);
    dgrid->ChangeConcentrationBy({0,0,0}, -sink*simulation_time_step);
  }

  return 0;
}

}  // namespace bdm

#endif  // UNIT_TEST_DIFFUSION_SMALL_H_
