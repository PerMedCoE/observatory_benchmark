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

#ifndef SIM_PARAM_H_
#define SIM_PARAM_H_

#include "biodynamo.h"

namespace bdm {

// Parameters specific for this simulation
struct SimParam : public ParamGroup {
  BDM_PARAM_GROUP_HEADER(SimParam, 1);

  // Forces: attraction coeff default 1, unit is mass/time^2 or N/m
  real_t attraction_coeff = 1*std::pow(10, -12);

  // Forces: repulsion coeff default 2, unit is mass/time^2 or N/m
  real_t repulsion_coeff = 2*std::pow(10, -12);


};

}  // namespace bdm

#endif  // SIM_PARAM_H_
