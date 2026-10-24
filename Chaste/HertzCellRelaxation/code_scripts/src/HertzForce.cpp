/*

Copyright (c) 2005-2025, University of Oxford.
All rights reserved.

University of Oxford means the Chancellor, Masters and Scholars of the
University of Oxford, having an administrative office at Wellington
Square, Oxford OX1 2JD, UK.

This file is part of Chaste.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 * Neither the name of the University of Oxford nor the names of its
   contributors may be used to endorse or promote products derived from this
   software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "HertzForce.hpp"
#include "NodeBasedCellPopulation.hpp"

#include <cmath>
#include <cassert>

#include <iostream>

template<unsigned DIM>
HertzForce<DIM>::HertzForce()
    : AbstractTwoBodyInteractionForce<DIM>(),
    mEffectiveElasticModulus(5.0),   // dimensionless default; adjust for physical units
    mAdhesionParameter(0.0)
{
}

template<unsigned DIM>
double HertzForce<DIM>::GetEffectiveElasticModulus() const
{
    return mEffectiveElasticModulus;
}

template<unsigned DIM>
void HertzForce<DIM>::SetEffectiveElasticModulus(double effectiveElasticModulus)
{
    assert(effectiveElasticModulus > 0.0);
    mEffectiveElasticModulus = effectiveElasticModulus;
}

template<unsigned DIM>
double HertzForce<DIM>::GetAdhesionParameter() const
{
    return mAdhesionParameter;
}

template<unsigned DIM>
void HertzForce<DIM>::SetAdhesionParameter(double adhesionParameter)
{
    assert(adhesionParameter >= 0.0);
    mAdhesionParameter = adhesionParameter;
}

template<unsigned DIM>
c_vector<double, DIM> HertzForce<DIM>::CalculateForceBetweenNodes(
        unsigned nodeAGlobalIndex,
        unsigned nodeBGlobalIndex,
        AbstractCellPopulation<DIM>& rCellPopulation)
{
    // This force class is defined for NodeBasedCellPopulations only
    assert(dynamic_cast<NodeBasedCellPopulation<DIM>*>(&rCellPopulation) != nullptr);

    // We should only ever calculate the force between two distinct nodes
    assert(nodeAGlobalIndex != nodeBGlobalIndex);

    Node<DIM>* p_node_a = rCellPopulation.GetNode(nodeAGlobalIndex);
    Node<DIM>* p_node_b = rCellPopulation.GetNode(nodeBGlobalIndex);

    // Get the node locations
    const c_vector<double, DIM>& r_node_a_location = p_node_a->rGetLocation();
    const c_vector<double, DIM>& r_node_b_location = p_node_b->rGetLocation();

    // Vector pointing from B to A
    c_vector<double, DIM> unit_vector =
            (static_cast<NodeBasedCellPopulation<DIM>*>(&rCellPopulation))
            ->rGetMesh().GetVectorFromAtoB(r_node_b_location, r_node_a_location);

    // Centre-to-centre distance
    double distance_between_nodes = norm_2(unit_vector);

    assert(distance_between_nodes > 0.0);
    assert(!std::isnan(distance_between_nodes));

    // Apply optional cut-off
    if (this->mUseCutOffLength)
    {
        if (distance_between_nodes >= this->GetCutOffLength())
        {
            return zero_vector<double>(DIM);
        }
    }

    // Normalise the direction vector
    unit_vector /= distance_between_nodes;

    // Cell radii from the node radii set on the mesh
    double radius_a = p_node_a->GetRadius();
    double radius_b = p_node_b->GetRadius();

    assert(radius_a > 0.0);
    assert(radius_b > 0.0);
    
    // Hertz force magnitude with adhesive correction (zero when no overlap)
    double magnitude = GetMagnitudeOfForce(distance_between_nodes, radius_a, radius_b);

    // Force on A points from B toward A when repulsive, and reverses when attractive.
    return magnitude * unit_vector;
}

template<unsigned DIM>
double HertzForce<DIM>::GetMagnitudeOfForce(double distanceBetweenNodes,
                                             double radiusOfCellOne,
                                             double radiusOfCellTwo) const
{
    // Overlap (indentation): positive when cells overlap
    double delta = radiusOfCellOne + radiusOfCellTwo - distanceBetweenNodes;

    if (delta <= 0.0)
    {
        return 0.0;  // cells are not in contact: no Hertz force
    }

    // Effective (reduced) radius:  R* = R_A * R_B / (R_A + R_B)
    double effective_radius = (radiusOfCellOne * radiusOfCellTwo)
                              / (radiusOfCellOne + radiusOfCellTwo);

    // Hertz contact force with adhesion:
    // F = (4/3) * E* * sqrt(R*) * delta^(3/2) - pi * gamma * R*
    double magnitude = (4.0 / 3.0) * mEffectiveElasticModulus
                       * std::sqrt(effective_radius)
                       * std::pow(delta, 1.5)
                       - M_PI * mAdhesionParameter * effective_radius;

    return magnitude;
}

template<unsigned DIM>
void HertzForce<DIM>::OutputForceParameters(out_stream& rParamsFile)
{
    *rParamsFile << "\t\t\t<EffectiveElasticModulus>"
                 << mEffectiveElasticModulus
                 << "</EffectiveElasticModulus>\n";
    *rParamsFile << "\t\t\t<AdhesionParameter>"
                 << mAdhesionParameter
                 << "</AdhesionParameter>\n";

    // Call method on direct parent class
    AbstractTwoBodyInteractionForce<DIM>::OutputForceParameters(rParamsFile);
}

// Explicit instantiation
template class HertzForce<1>;
template class HertzForce<2>;
template class HertzForce<3>;

// Serialization for Boost >= 1.36
#include "SerializationExportWrapperForCpp.hpp"
EXPORT_TEMPLATE_CLASS_SAME_DIMS(HertzForce)
