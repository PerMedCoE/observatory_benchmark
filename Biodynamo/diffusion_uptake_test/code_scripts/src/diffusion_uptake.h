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
#ifndef DIFFUSION_UPTAKE_H_
#define DIFFUSION_UPTAKE_H_

#include "biodynamo.h"
#include "core/diffusion/euler_grid.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  auto set_param = [&](Param* param) {
          param->bound_space = Param::BoundSpaceMode::kClosed;
          param->diffusion_boundary_condition = "Dirichlet";
          param->min_bound = -120;
          param->max_bound = 120;
          param->statistics = true;
  };
  Simulation simulation(argc, argv, set_param);
  simulation.GetEnvironment()->Update();
  auto* rm = simulation.GetResourceManager();

  int tot = 10000;
  double simulation_time_step = 0.001;
  double conc_initial = 10;
  double decay_coef = 0;
  double diff_coef = 2000.0;
  double sink = -1.6e-10;
  size_t res = 24;
  auto* dgrid = new EulerGrid(0, "Substance", diff_coef, decay_coef, res);

  double bl = 240/res;
  double conversion = bl*bl*bl/1e+15;

  dgrid->Initialize();
  dgrid->SetBoundaryCondition(
                  std::make_unique<ConstantBoundaryCondition>(conc_initial*conversion));
  dgrid->SetUpperThreshold(1e15);
  rm->AddContinuum(dgrid);




  std::string file = "pos.csv";
  int number_of_lines = 0;
  std::string line;
  std::ifstream myfile(file);
  while (std::getline(myfile, line))
      ++number_of_lines;

  std::ifstream inFile;
  inFile.open(file.c_str());
  std::vector<Real3> positions;
  real_t x, y, z;
  for (int i=0; i < number_of_lines; i++) {
    inFile >> x >> y >> z;
    Real3 pos = {x, y, z};
    positions.push_back(pos);
  }



  std::ofstream outdata;
  outdata.open("data.csv");

  for (size_t c=0; c<res*res*res; c++) {
     double c_value= dgrid->GetConcentration(c);
     dgrid->ChangeConcentrationBy(c, (conc_initial*conversion)-c_value);
  }

  for (int t=0; t<tot; t++) {

    double total_conc = 0.0;
    for (size_t c=0; c<res*res*res; c++) {
       total_conc += dgrid->GetConcentration(c)/conversion;
    }
    outdata << t*simulation_time_step << " "
            << total_conc/(res*res*res) << " "
            << dgrid->GetValue({0,0,0})/conversion << std::endl;

    dgrid->Diffuse(simulation_time_step);

    for (int i=0; i<positions.size(); i++) {
        dgrid->ChangeConcentrationBy(positions[i], sink*simulation_time_step);
    }

  }
  outdata.close();

  outdata.open("contour.csv");

  for (double y=-120+bl/2.; y<120; y+=bl) {
      for (double x=-120+bl/2.; x<120; x+=bl) {
           double conc = dgrid->GetValue({x,y,0})/conversion;
           outdata << conc << " ";
      }
      outdata << std::endl;
  }
  outdata.close();

  return 0;
}

}  // namespace bdm

#endif  // DIFFUSION_UPTAKE_H_
