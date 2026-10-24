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

#include "cell_cell_force.h"
#include "sim_param.h"

namespace bdm {

/// Custom force. Changed adhesive and repulsive parameters compared to standard.
Real4 CellCellForce::Calculate(const Agent* lhs, const Agent* rhs) const {
  real_t timesteps = bdm::Simulation::GetActive()->GetScheduler()->GetSimulatedSteps();

  // No force at time 0 to replicate initial conditions
  if (timesteps < 1) {
    return {0.0, 0.0, 0.0, 0.0};
  }

  const Real3& ref_mass_location = lhs->GetPosition();
  real_t ref_diameter = lhs->GetDiameter();
  const Real3& nb_mass_location = rhs->GetPosition();
  real_t nb_diameter = rhs->GetDiameter();

  auto c1 = ref_mass_location;
  real_t r1 = 0.5 * ref_diameter;
  auto c2 = nb_mass_location;
  real_t r2 = 0.5 * nb_diameter;
  // We take virtual bigger radii to have a distant interaction, to get a
  // desired density.
  real_t additional_radius_multiplier = 1.00; // We assume an interaction distance 0% larger then the agent's radius
  r1 *= additional_radius_multiplier;
  r2 *= additional_radius_multiplier;
  // the 3 components of the vector c2 -> c1
  real_t comp1 = c1[0] - c2[0];
  real_t comp2 = c1[1] - c2[1];
  real_t comp3 = c1[2] - c2[2];
  real_t center_distance =
      std::sqrt(comp1 * comp1 + comp2 * comp2 + comp3 * comp3);
  // the overlap distance (how much one penetrates in the other)
  real_t delta = r1 + r2 - center_distance;
  // std::cout << "The center distance is " << center_distance << "\n" << std::endl;
  // std::cout << "Delta is " << delta << "\n" << std::endl;
  // if no overlap : no force
  if (delta < 0) {
    return {0.0, 0.0, 0.0, 0.0};
  }
  // to avoid a division by 0 if the centers are (almost) at the same
  //  location
  if (center_distance < 0.00000001) {
    auto* random = Simulation::GetActive()->GetRandom();
    auto force2on1 = random->template UniformArray<3>(-3.0, 3.0);
    // std::cout << "\n\nRandom force being applied\n\n" << std::endl;
    return {force2on1[0], force2on1[1], force2on1[2], 0};
  }
  // the force itself
  const auto* sparam =
      Simulation::GetActive()
          ->GetParam()
          ->Get<SimParam>();  // get a pointer to an instance of SimParam
  real_t r = (r1 * r2) / (r1 + r2);
  real_t gamma = sparam->attraction_coeff;
  real_t k = sparam->repulsion_coeff;
  real_t f = k * delta - gamma * std::sqrt(r * delta);

  // std::cout << "The force is " << f << "\n" << std::endl;

  real_t module = f / center_distance;
  // std::cout << "The force module is " << module << "\n" << std::endl;
  Real3 force2on1({module * comp1, module * comp2, module * comp3});
  // std::cout << "The force is " << force2on1[0] << " " << force2on1[1] << " " << force2on1[2] << "\n" << std::endl;
  return {force2on1[0], force2on1[1], force2on1[2], 0};
}

}  // namespace bdm
