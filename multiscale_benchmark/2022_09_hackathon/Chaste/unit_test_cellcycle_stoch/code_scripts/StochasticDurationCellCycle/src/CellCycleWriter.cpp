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

#include "AbstractCellPopulation.hpp"
#include "AbstractPhaseBasedCellCycleModel.hpp"
#include "CellCyclePhases.hpp"

#include "CellCycleWriter.hpp"

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
template<class Archive>
void CellCycleWriter<ELEMENT_DIM, SPACE_DIM>::serialize(Archive & archive, const unsigned int version)
{
    archive & boost::serialization::base_object<AbstractCellWriter<ELEMENT_DIM, SPACE_DIM> >(*this);
}

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
CellCycleWriter<ELEMENT_DIM, SPACE_DIM>::CellCycleWriter()
    : AbstractCellWriter<ELEMENT_DIM, SPACE_DIM>("cellcycle.dat")
{
    this->mVtkCellDataName = "Cell cycle";
}

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
double CellCycleWriter<ELEMENT_DIM, SPACE_DIM>::GetCellDataForVtkOutput(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation)
{
    double cellVolume = pCell->GetCellData()->GetItem("Volume");
    return cellVolume;
}

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
void CellCycleWriter<ELEMENT_DIM, SPACE_DIM>::VisitCell(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation)
{
    unsigned id = pCell->GetCellId();
    *this->mpOutStream << id << " ";

    c_vector<double, SPACE_DIM> coordinates = pCellPopulation->GetLocationOfCellCentre(pCell);
    for (unsigned i=0; i<SPACE_DIM; i++)
    {
        *this->mpOutStream << coordinates[i] << " ";
    }

    auto pCellCycleModel = static_cast<AbstractPhaseBasedCellCycleModel*>(pCell->GetCellCycleModel());

    double phaseG1Duration = pCellCycleModel->GetG1Duration();
    *this->mpOutStream << phaseG1Duration << " ";

    double phaseSDuration = pCellCycleModel->GetSDuration();
    *this->mpOutStream << phaseSDuration << " ";

    double phaseG2Duration = pCellCycleModel->GetG2Duration();
    *this->mpOutStream << phaseG2Duration << " ";

    double phaseMDuration = pCellCycleModel->GetMDuration();
    *this->mpOutStream << phaseMDuration << " ";

    CellCyclePhase currentCellCyclePhase = pCellCycleModel->GetCurrentCellCyclePhase();
    switch (currentCellCyclePhase)
    {
        case G_ZERO_PHASE:
            *this->mpOutStream << "G0 ";
            break;
        case G_ONE_PHASE:
            *this->mpOutStream << "G1 ";
            break;
        case S_PHASE:
            *this->mpOutStream << "S ";
            break;
        case G_TWO_PHASE:
            *this->mpOutStream << "G2 ";
            break;
        case M_PHASE:
            *this->mpOutStream << "M ";
            break;
        default:
            *this->mpOutStream << "ERROR ";
            NEVER_REACHED;
    }

    double relativeVolume = pCell->GetCellData()->GetItem("TargetVolume");
    *this->mpOutStream << relativeVolume << " ";

    double volume = pCell->GetCellData()->GetItem("Volume");
    *this->mpOutStream << volume << " ";
}

// Explicit instantiation
template class CellCycleWriter<3,3>;

#include "SerializationExportWrapperForCpp.hpp"
// Declare identifier for the serializer
EXPORT_TEMPLATE_CLASS_ALL_DIMS(CellCycleWriter)
