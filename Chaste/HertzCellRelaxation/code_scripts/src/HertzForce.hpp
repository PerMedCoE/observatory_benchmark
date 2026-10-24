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

#ifndef HERTZFORCE_HPP_
#define HERTZFORCE_HPP_

#include "AbstractTwoBodyInteractionForce.hpp"

#include "ChasteSerialization.hpp"
#include <boost/serialization/base_object.hpp>

/**
 * A Hertz contact force law for node-based cell simulations in which cells
 * are represented as elastic spheres.
 *
 * The Hertz contact model computes a purely repulsive force between two
 * overlapping spherical cells.  For cells A and B with radii R_A and R_B
 * whose centres are separated by distance d, the overlap (indentation) is
 *
 *   delta = R_A + R_B - d  (positive when cells overlap)
 *
 * The effective (reduced) radius combines both cell radii:
 *
 *   R* = (R_A * R_B) / (R_A + R_B)
 *
 * The effective elastic modulus accounts for the material properties of
 * both cells.  For two cells sharing Young's modulus E and Poisson ratio nu:
 *
 *   E* = E / (2 * (1 - nu^2))
 *
 * In general, the effective modulus is exposed directly via
 * mEffectiveElasticModulus so that any combination of per-cell properties
 * can be represented.
 *
 * The Hertz force magnitude with a constant adhesive correction is:
 *
 *   F = (4/3) * E* * sqrt(R*) * delta^(3/2) - pi * gamma * R*
 *
 * and it acts along the unit vector pointing from B to A (pushing cells
 * apart when the magnitude is positive, or attracting them when it is
 * negative. No force is applied when cells are not in contact (delta <= 0).
 *
 * This force is designed for use with NodeBasedCellPopulation only.
 *
 * References:
 *   Hertz, H. (1882). Über die Berührung fester elastischer Körper.
 *   J. Reine Angew. Math. 92, 156–171.
 */
template<unsigned DIM>
class HertzForce : public AbstractTwoBodyInteractionForce<DIM>
{
private:

    /** Needed for serialization. */
    friend class boost::serialization::access;

    /**
     * Archive the object and its member variables.
     *
     * @param archive the archive
     * @param version the current version of this class
     */
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & boost::serialization::base_object<AbstractTwoBodyInteractionForce<DIM> >(*this);
        archive & mEffectiveElasticModulus;
      archive & mAdhesionParameter;
    }

    /**
     * Effective elastic modulus E* (Pa, or whatever pressure unit is used).
     *
     * Combines the Young's moduli and Poisson ratios of both cells:
     *   1/E* = (1 - nu_A^2)/E_A + (1 - nu_B^2)/E_B
     *
     * When both cells share the same material properties E and nu:
     *   E* = E / (2*(1 - nu^2))
     *
     * Default value corresponds to a soft-cell estimate (dimensionless units
     * where cell diameter = 1).
     */
    double mEffectiveElasticModulus;

    /**
     * Adhesion parameter gamma used in the adhesive correction term
     *   -pi * gamma * R*
     * where R* is the reduced radius.
     */
    double mAdhesionParameter;

public:

    /**
     * Constructor.
     */
    HertzForce();

    /**
     * Destructor.
     */
    virtual ~HertzForce() = default;

    /**
     * @return mEffectiveElasticModulus
     */
    double GetEffectiveElasticModulus() const;

    /**
     * Set mEffectiveElasticModulus.
     *
     * @param effectiveElasticModulus the new value of mEffectiveElasticModulus (must be > 0)
     */
    void SetEffectiveElasticModulus(double effectiveElasticModulus);

    /**
     * @return mAdhesionParameter
     */
    double GetAdhesionParameter() const;

    /**
     * Set mAdhesionParameter.
     *
     * @param adhesionParameter the new value of mAdhesionParameter (must be >= 0)
     */
    void SetAdhesionParameter(double adhesionParameter);

    /**
     * Compute the Hertz repulsive force between two overlapping nodes.
     *
     * Returns zero_vector if the nodes are not in contact (delta <= 0).
     * The returned vector points from node B toward node A (repulsion on A).
     *
     * @param nodeAGlobalIndex index of node A
     * @param nodeBGlobalIndex index of node B
     * @param rCellPopulation the NodeBasedCellPopulation
     * @return force on node A due to node B
     */
    c_vector<double, DIM> CalculateForceBetweenNodes(unsigned nodeAGlobalIndex,
                                                     unsigned nodeBGlobalIndex,
                                                     AbstractCellPopulation<DIM>& rCellPopulation) override;

    /**
    * Compute the scalar magnitude of the Hertz force with adhesion.
     *
     * @param distanceBetweenNodes centre-to-centre distance
     * @param radiusOfCellOne radius of cell A
     * @param radiusOfCellTwo radius of cell B
    * @return force magnitude, zero if no overlap
     */
    double GetMagnitudeOfForce(double distanceBetweenNodes,
                               double radiusOfCellOne,
                               double radiusOfCellTwo) const;

    /**
     * Overridden OutputForceParameters() method.
     *
     * @param rParamsFile the file stream to which the parameters are output
     */
    void OutputForceParameters(out_stream& rParamsFile) override;
};

#include "SerializationExportWrapper.hpp"
EXPORT_TEMPLATE_CLASS_SAME_DIMS(HertzForce)

#endif /*HERTZFORCE_HPP_*/
