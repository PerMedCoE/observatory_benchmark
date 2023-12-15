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

#ifndef _TEST_DIFFUSION_SMALL_HPP_
#define _TEST_DIFFUSION_SMALL_HPP_

#include <cxxtest/TestSuite.h>

#include "BoundaryConditionsContainer.hpp"
#include "ConstBoundaryCondition.hpp"
#include "ColumnDataWriter.hpp"
#include "FileFinder.hpp"
#include "Hdf5DataReader.hpp"
#include "OutputFileHandler.hpp"
#include "SimpleLinearEllipticSolver.hpp"
#include "SimpleLinearParabolicSolver.hpp"
#include "TetrahedralMesh.hpp"
#include "TrianglesMeshReader.hpp"
#include "UblasCustomFunctions.hpp"

#include "DiffusionEquationWithSinkTerm.hpp"
#include "DiffusionEquationWithSinkTerms.hpp"

/* The following header must be included in every test that uses PETSc. Note that it
 * cannot be included in the source code. */
#include "PetscSetupAndFinalize.hpp"

/**
 *
 */
class TestDiffusion : public CxxTest::TestSuite
{

public:
    void Test3x3x3()
    {
        // Target number of nodes in each dimension, so we have num_nodes x num_nodes x num_nodes in the domain
        const unsigned num_nodes = 3;

        // Simulation parameters from PerMedCoE document
        const double width_xyz = 60.0; // 60 x 60 x 60 micrometers,
        const double vox_size = width_xyz / (num_nodes - 1u);
        const double initial_concentration = 0.0; // no concentration initially
        const double source_strength = 10.0; // constant concentration on the boundary
        const double sink_strength = 20.0; // 20 microMol per minute
        const double sink_square_radius = 10.0; // sink-size, diameter in inf norm
        const double diffusion_coefficient = 2000.0; // 2000 micrometer^2 per minute

        // Create a 60 by 60 by 60 mesh in 3D. The first parameter is the cartesian space-step and the
        // other three parameters are the width, height and depth of the mesh.
        TetrahedralMesh<3, 3> mesh;
        mesh.ConstructRegularSlabMesh(vox_size, width_xyz, width_xyz, width_xyz);

        // Custom PDE for this unit test
        DiffusionEquationWithSinkTerm<3> pde;

        pde.setUptake(sink_strength);
        pde.setSinkLocation(Create_c_vector(width_xyz / 2.0, width_xyz / 2.0, width_xyz / 2.0));
        pde.setSinkRadius(sink_square_radius);
        pde.setDiffusionCoefficient(diffusion_coefficient);

        // Create a new boundary conditions container and specify u=1.0 on the boundary.
        BoundaryConditionsContainer<3, 3, 1> bcc;
        bcc.DefineConstantDirichletOnMeshBoundary(&mesh, source_strength);

        // Create an instance of the solver, passing in the mesh, pde and boundary conditions.
        SimpleLinearParabolicSolver<3, 3> solver(&mesh, &pde, &bcc);

        /* For parabolic problems, initial conditions are also needed. The solver will expect
         * a PETSc vector, where the i-th entry is the initial solution at node i, to be passed
         * in. To create this PETSc Vec, we will use a helper function in the PetscTools
         * class to create a Vec of size num_nodes, with each entry set to 1.0. Then we
         * set the initial condition on the solver. */
        Vec initial_condition = PetscTools::CreateAndSetVec(mesh.GetNumNodes(), initial_concentration);
        solver.SetInitialCondition(initial_condition);

        // Next define the start time, end time, and timestep, and set them.
        const double t_start = 0.0;
        const double t_end = 10.0;
        const double dt = 0.01;
        solver.SetTimes(t_start, t_end);
        solver.SetTimeStep(dt);

        // Set where to output solution
        solver.SetOutputDirectoryAndPrefix("TestDiffusionSmall03", "results");
        solver.SetOutputToVtk(true);
        solver.SetOutputToTxt(true);
        solver.SetPrintingTimestepMultiple(1);

        // Solve the model
        Vec solution = solver.Solve();
        ReplicatableVector solution_repl(solution);

        // Get the middle node, and check it corresponds to a node in the very centre of the domain
        const unsigned middle_node_idx = (num_nodes * num_nodes * num_nodes - 1u) / 2u;
        TS_ASSERT_DELTA(mesh.GetNode(middle_node_idx)->rGetLocation()[0], 30.0, 1e-12);
        TS_ASSERT_DELTA(mesh.GetNode(middle_node_idx)->rGetLocation()[1], 30.0, 1e-12);
        TS_ASSERT_DELTA(mesh.GetNode(middle_node_idx)->rGetLocation()[2], 30.0, 1e-12);

        auto output_dir = FileFinder("TestDiffusionSmall03", RelativeTo::ChasteTestOutput);

        auto hdf5_reader = Hdf5DataReader(output_dir, "results", "Data");

        const std::vector<double> time_values = hdf5_reader.GetUnlimitedDimensionValues();
        const std::vector<double> soln_values = hdf5_reader.GetVariableOverTime("Variable_0", middle_node_idx);
        TS_ASSERT_EQUALS(time_values.size(), 1001ul);
        TS_ASSERT_EQUALS(soln_values.size(), 1001ul);

        ColumnDataWriter data_writer("TestDiffusion", "TestDiffusionSmall03", false);
        const int time_id_var = data_writer.DefineUnlimitedDimension("time","minutes");
        const int sln_id_var = data_writer.DefineVariable("concentration", "uM");
        data_writer.EndDefineMode();

        for (unsigned i = 0; i < time_values.size(); ++i)
        {
            data_writer.PutVariable(time_id_var, time_values.at(i));
            data_writer.PutVariable(sln_id_var, soln_values.at(i));
            data_writer.AdvanceAlongUnlimitedDimension();
        }

        // All PETSc vectors should be destroyed when they are no longer needed.
        PetscTools::Destroy(initial_condition);
        PetscTools::Destroy(solution);
    }

    void Test12x12x12()
    {
        // Target number of points in each dimension, so we have num_pts_each_dim^3 nodes in the domain
        const unsigned num_pts_each_dim = 12;

        // Simulation parameters from PerMedCoE document
        const double width_xyz = 330.0; // 330 x 330 x 330 micrometers,
        const double vox_size = width_xyz / (num_pts_each_dim - 1u);
        const double initial_concentration = 0.0; // no concentration initially
        const double source_strength = 10.0; // constant concentration on the boundary
        const double sink_strength = 20.0; // 20 microMol per minute
        const double diffusion_coefficient = 2000.0; // 2000 micrometer^2 per minute

        const double sink_square_radius = 10.0; // sink-size, diameter in inf norm

        const std::size_t num_nodes = 12ul * 12ul * 12ul;

        // Create a 60 by 60 by 60 mesh in 3D. The first parameter is the cartesian space-step and the
        // other three parameters are the width, height and depth of the mesh.
        TetrahedralMesh<3, 3> mesh;
        mesh.ConstructRegularSlabMesh(vox_size, width_xyz, width_xyz, width_xyz);

        TS_ASSERT_EQUALS(mesh.GetNumNodes(), num_nodes);

        DiffusionEquationWithSinkTerms<3> pde;
        pde.setDiffusionCoefficient(diffusion_coefficient);
        for (unsigned i = 0; i < 12; ++i)
        {
            for (unsigned j = 0; j < 12; ++j)
            {
                for (unsigned k = 0; k < 12; ++k)
                {
                    const double x_pos = static_cast<double>(i) * vox_size;
                    const double y_pos = static_cast<double>(j) * vox_size;
                    const double z_pos = static_cast<double>(k) * vox_size;
                    pde.AddSink(Create_c_vector(x_pos, y_pos, z_pos), sink_strength, sink_square_radius);
                }
            }
        }

        TS_ASSERT_EQUALS(pde.rGetSinkLocations().size(), num_nodes);

        // Create a new boundary conditions container and specify u=1.0 on the boundary.
        BoundaryConditionsContainer<3, 3, 1> bcc;
        bcc.DefineConstantDirichletOnMeshBoundary(&mesh, source_strength);

        // Create an instance of the solver, passing in the mesh, pde and boundary conditions.
        SimpleLinearParabolicSolver<3, 3> solver(&mesh, &pde, &bcc);

        /* For parabolic problems, initial conditions are also needed. The solver will expect
         * a PETSc vector, where the i-th entry is the initial solution at node i, to be passed
         * in. To create this PETSc Vec, we will use a helper function in the PetscTools
         * class to create a Vec of size num_nodes, with each entry set to 1.0. Then we
         * set the initial condition on the solver. */
        Vec initial_condition = PetscTools::CreateAndSetVec(mesh.GetNumNodes(), initial_concentration);
        solver.SetInitialCondition(initial_condition);

        // Next define the start time, end time, and timestep, and set them.
        const double t_start = 0.0;
        const double t_end = 10.0;
        const double dt = 0.01;
        solver.SetTimes(t_start, t_end);
        solver.SetTimeStep(dt);

        const auto num_timesteps = 1ul + static_cast<std::size_t>(std::round((t_end - t_start) / dt));

        // Set where to output solution
        solver.SetOutputDirectoryAndPrefix("TestDiffusionSmall12", "results");
        solver.SetOutputToVtk(true);
        solver.SetOutputToTxt(true);
        solver.SetPrintingTimestepMultiple(1);

        // Solve the model
        Vec solution = solver.Solve();

        ReplicatableVector solution_repl(solution);

        auto output_dir = FileFinder("TestDiffusionSmall12", RelativeTo::ChasteTestOutput);
        auto hdf5_reader = Hdf5DataReader(output_dir, "results", "Data");

        const std::vector<double> time_values = hdf5_reader.GetUnlimitedDimensionValues();
        const std::vector<std::vector<double> > soln_values = hdf5_reader.GetVariableOverTimeOverMultipleNodes("Variable_0", 0, num_nodes);
        TS_ASSERT_EQUALS(time_values.size(), num_timesteps);
        TS_ASSERT_EQUALS(soln_values.size(), num_nodes);
        TS_ASSERT_EQUALS(soln_values.at(1).size(), num_timesteps);

        ColumnDataWriter data_writer("TestDiffusion", "TestDiffusionSmall12", false);
        const int time_id_var = data_writer.DefineUnlimitedDimension("time","minutes");
        const int sln_id_var = data_writer.DefineVariable("average_concentration", "uM");
        data_writer.EndDefineMode();

        for (unsigned i = 0; i < time_values.size(); ++i)
        {
            double average_solution = 0.0;
            for (unsigned j = 0; j < soln_values.size(); ++j)
            {
                average_solution += soln_values.at(j).at(i);
            }
            average_solution /= static_cast<double>(soln_values.size());

            data_writer.PutVariable(time_id_var, time_values.at(i));
            data_writer.PutVariable(sln_id_var, average_solution);
            data_writer.AdvanceAlongUnlimitedDimension();
        }

        // All PETSc vectors should be destroyed when they are no longer needed.
        PetscTools::Destroy(initial_condition);
        PetscTools::Destroy(solution);
    }
};

#endif /*_TEST_DIFFUSION_SMALL_HPP_*/
