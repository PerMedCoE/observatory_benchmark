#include "my_force.h"

namespace bdm {

Double4 MyForce::Calculate(const Agent* lhs, const Agent* rhs) const {
  if (lhs->GetShape() == Shape::kSphere && rhs->GetShape() == Shape::kSphere) {
    Double3 result;
    ForceBetweenCells(lhs, rhs, &result);
    return {result[0], result[1], result[2], 0};
  } else {
    Log::Fatal("InteractionForce",
               "InteractionForce only supports sphere or cylinder shapes");
    return {0, 0, 0, 0};
  }
}

void MyForce::ForceBetweenCells(const Agent* sphere_lhs,
                                  const Agent* sphere_rhs,
                                  Double3* result) const {
  const Double3& ref_mass_location = sphere_lhs->GetPosition();
  double ref_diameter = sphere_lhs->GetDiameter();
  double ref_iof_coefficient = 0.15;
  const Double3& nb_mass_location = sphere_rhs->GetPosition();
  double nb_diameter = sphere_rhs->GetDiameter();
  double nb_iof_coefficient = 0.15;

  auto c1 = ref_mass_location;
  double r1 = 0.5 * ref_diameter;
  auto c2 = nb_mass_location;
  double r2 = 0.5 * nb_diameter;
  // We take virtual bigger radii to have a distant interaction, to get a
  // desired density.
  double additional_radius =
      10.0 * std::min(ref_iof_coefficient, nb_iof_coefficient);
  r1 += additional_radius;
  r2 += additional_radius;
  // the 3 components of the vector c2 -> c1
  double comp1 = c1[0] - c2[0];
  double comp2 = c1[1] - c2[1];
  double comp3 = c1[2] - c2[2];
  double center_distance =
      std::sqrt(comp1 * comp1 + comp2 * comp2 + comp3 * comp3);
  // the overlap distance (how much one penetrates in the other)
  double delta = r1 + r2 - center_distance;
  // if no overlap : no force
  if (delta < 0) {
    *result = {0.0, 0.0, 0.0};
    return;
  }
  // to avoid a division by 0 if the centers are (almost) at the same
  //  location
  if (center_distance < 0.00000001) {
    auto* random = Simulation::GetActive()->GetRandom();
    auto force2on1 = random->template UniformArray<3>(-3.0, 3.0);
    *result = force2on1;
    return;
  }
  // the force itself
  double r = (r1 * r2) / (r1 + r2);
  double gamma = 0.001;  // attraction coeff was 1
  double k = 30000;      // repulsion coeff was 2
  double f = k * delta - gamma * std::sqrt(r * delta);

  double module = f / center_distance;
  Double3 force2on1({module * comp1, module * comp2, module * comp3});
  *result = force2on1;
}

}  // namespace bdm