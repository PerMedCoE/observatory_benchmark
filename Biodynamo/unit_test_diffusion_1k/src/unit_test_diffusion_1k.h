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
#ifndef UNIT_TEST_LARGE_H_
#define UNIT_TEST_LARGE_H_

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

  double simulation_time_step = 0.01;
  int tot = 1000;
  double decay_coef = 0.0;
  double diff_coef = 2000.0;
  double sink = 20.0;
  size_t res = 12;
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
	    << total_conc/(res*res*res) << std::endl;

    dgrid->Diffuse(simulation_time_step);
    for (int z=0; z<10; z++) {
      for (int y=0; y<10; y++) {
        for (int x=0; x<10; x++) {
	  dgrid->ChangeConcentrationBy({double(-90)+(x*double(20)),
			                double(-90)+(y*double(20)),
					double(-90)+(z*double(20))},
			               -sink*simulation_time_step);
	}
      }
    }

  }

  return 0;
}

}  // namespace bdm


#endif  // UNIT_TEST_LARGE_H_
