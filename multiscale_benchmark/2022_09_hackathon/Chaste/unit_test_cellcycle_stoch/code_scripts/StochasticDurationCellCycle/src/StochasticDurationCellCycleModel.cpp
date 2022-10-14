/*

Copyright (c) 2005-2022, University of Oxford.
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

#include <algorithm>

#include "AbstractSimplePhaseBasedCellCycleModel.hpp"
#include "CellCyclePhases.hpp"
#include "DifferentiatedCellProliferativeType.hpp"
#include "RandomNumberGenerator.hpp"

#include "StochasticDurationCellCycleModel.hpp"

template<class Archive>
void StochasticDurationCellCycleModel::serialize(Archive & archive, const unsigned int version)
{
    // Archive cell-cycle model using serialization code from AbstractSimplePhaseBasedCellCycleModel
    archive & boost::serialization::base_object<AbstractSimplePhaseBasedCellCycleModel>(*this);
    
    // Archive RandomNumberGenerator singleton.
    // Must be done carefully: first serialize directly, then via pointer.
    // This prevents tripping an assertion when a second class instance is created on de-serialization.
    RandomNumberGenerator* pRandomGenerator = RandomNumberGenerator::Instance();
    archive & *pRandomGenerator; // First serialize directly
    archive & pRandomGenerator; // Then serialize via pointer
}

StochasticDurationCellCycleModel::StochasticDurationCellCycleModel()
    : AbstractSimplePhaseBasedCellCycleModel()
{
  SetPhaseDurations();
}

void StochasticDurationCellCycleModel::SetPhaseDurations()
{
    double g1Duration = RandomNumberGenerator::Instance()->NormalRandomDeviate(7.0, 0.7);
    double sDuration = RandomNumberGenerator::Instance()->NormalRandomDeviate(6.0, 0.6);
    double g2Duration = RandomNumberGenerator::Instance()->NormalRandomDeviate(3.0, 0.3);
    double mDuration = RandomNumberGenerator::Instance()->NormalRandomDeviate(2.0, 0.2);

    SetStemCellG1Duration(g1Duration);
    SetTransitCellG1Duration(g1Duration);
    SetSDuration(sDuration);
    SetG2Duration(g2Duration);
    SetMDuration(mDuration);
    SetMinimumGapDuration(std::min(g1Duration, g2Duration));
}

void StochasticDurationCellCycleModel::SetG1Duration()
{
    assert(mpCell != NULL);  // Make sure cell exists
    
    mG1Duration = mStemCellG1Duration;
}

AbstractCellCycleModel* StochasticDurationCellCycleModel::CreateCellCycleModel()
{
    // Create a new cell-cycle model
    StochasticDurationCellCycleModel* pCellCycleModel = new StochasticDurationCellCycleModel();
    return pCellCycleModel;
}

void StochasticDurationCellCycleModel::UpdateCellCyclePhase()
{
    double timeSinceBirth = GetAge();
    assert(timeSinceBirth >= 0);

    if (mpCell->GetCellProliferativeType()->IsType<DifferentiatedCellProliferativeType>())
    {
        mCurrentCellCyclePhase = G_ZERO_PHASE;
    }
    else if (timeSinceBirth < GetG1Duration())
    { 
        // Reset phase durations after each cycle
        if (GetCurrentCellCyclePhase() == M_PHASE)
        {
            SetPhaseDurations();
            SetG1Duration();
        }
        mCurrentCellCyclePhase = G_ONE_PHASE;
    }
    else if (timeSinceBirth <  GetG1Duration() + GetSDuration())
    {
        mCurrentCellCyclePhase = S_PHASE;
    }
    else if (timeSinceBirth < GetG1Duration() + GetSDuration() + GetG2Duration())
    {
        mCurrentCellCyclePhase = G_TWO_PHASE;
    }
    else if (timeSinceBirth < GetG1Duration() + GetSDuration() + GetG2Duration() + GetMDuration())
    {
        mCurrentCellCyclePhase = M_PHASE;
    }
}

#include "SerializationExportWrapperForCpp.hpp"
CHASTE_CLASS_EXPORT(StochasticDurationCellCycleModel)
