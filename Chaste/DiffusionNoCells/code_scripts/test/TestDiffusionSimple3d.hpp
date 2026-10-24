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

#ifndef _TEST_DIFFUSION_SIMPLE_3D_HPP_
#define _TEST_DIFFUSION_SIMPLE_3D_HPP_

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
#include "DiffusionEquationWithUniformSinkTerm.hpp"

#include "Debug.hpp"

/* The following header must be included in every test that uses PETSc. Note that it
 * cannot be included in the source code. */
#include "PetscSetupAndFinalize.hpp"

/**
 *
 */
class TestDiffusionSimple3d : public CxxTest::TestSuite
{

public:
    
    // Convergence on 240X240x240 Domain with Dirichlet Boundary
    void TestConstantUptakeDirichletBoundary()
    {
        bool hasCells = true;

        // Target number of points in each dimension, so we have num_vox_each_dim^3 nodes in the domain
        const unsigned num_vox_each_dim_array[6] = {6, 12, 24, 48, 96, 192};

        for (unsigned num_vox_each_dim_index = 0; num_vox_each_dim_index != 6; num_vox_each_dim_index++)
        {
            double num_vox_each_dim = num_vox_each_dim_array[num_vox_each_dim_index];

            std::stringstream num_vox_string;
            num_vox_string << (double) num_vox_each_dim;

            std::string base_name = "TestSimpleDiffusionConvergence3d";

            if (hasCells)
            {
                base_name += "_with_cells";
            }
            else
            {
                base_name += "_no_cells";
            }

            std::string simulation_output_dir = base_name + "/" + num_vox_string.str();
    
            PRINT_VARIABLE(simulation_output_dir);

            // Simulation parameters from PerMedCoE document
            const double width_xyz = 240.0; // 240 x 240 x 240 micrometers,  
            //const double box_volume = width_xyz*width_xyz*width_xyz; 
            const double vox_size = width_xyz / (num_vox_each_dim);
            //const double vox_volume = vox_size*vox_size*vox_size;
            const double initial_concentration = 10.0; // initial concnetration to match BCS!
            const double source_strength = 10.0; // constant concentration on the boundary
            const double sink_strength = 1.0; // 20 microMol per minute
            const double diffusion_coefficient = 2000.0; // 2000 micrometer^2 per minute

            // 3D
            const std::size_t num_nodes = (num_vox_each_dim + 1) * (num_vox_each_dim + 1) * (num_vox_each_dim + 1);

            // Create a size 240 by 240 by 240 mesh in 3D. The first parameter is the 
            // cartesian space-step and the other three parameters are the width, height and depth of the mesh.
            TetrahedralMesh<3, 3> mesh;
            mesh.ConstructRegularSlabMesh(vox_size, width_xyz, width_xyz, width_xyz);
            mesh.Translate(-width_xyz/2.0, -width_xyz/2.0, -width_xyz/2.0);

            TS_ASSERT_EQUALS(mesh.GetNumNodes(), num_nodes);

            AbstractLinearParabolicPde<3,3>* p_pde;
            if (hasCells)
            {
                //double sink_square_radius = 10;
                
                p_pde = new DiffusionEquationWithSinkTerms<3>();
                dynamic_cast<DiffusionEquationWithSinkTerms<3>*>(p_pde)->setDiffusionCoefficient(diffusion_coefficient);
                
                double cell_centers_x[12]= {-10,-10, 10, 10,-30,-30, 30, 30, 10,-10, 10,-10};
                double cell_centers_y[12]= { 10,-10, 10,-10,-10, 10, 10,-10, 30, 30,-30,-30};
                double cell_centers_z[12]= { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

                for (unsigned i = 0; i < 12; ++i)
                {
                    //0.01*box_volume*sink_strength/vox_volume
                    double local_sink_strength = 16.0;//sink_strength; // scale sink strength by the ratio of the box volume to the voxel volume, so that we get the same total uptake regardless of voxel size
                    dynamic_cast<DiffusionEquationWithSinkTerms<3>*>(p_pde)->AddSink(Create_c_vector(cell_centers_x[i], cell_centers_y[i], cell_centers_z[i]), local_sink_strength, 0.0);
                }
            }
            else
            {
                p_pde = new DiffusionEquationWithUniformSinkTerm<3>();
                dynamic_cast<DiffusionEquationWithUniformSinkTerm<3>*>(p_pde)->setDiffusionCoefficient(diffusion_coefficient);
                dynamic_cast<DiffusionEquationWithUniformSinkTerm<3>*>(p_pde)->setUptake(sink_strength);
                //pde.setUptake(sink_strength/vox_size/vox_size/vox_size);
            }
            

            // Create a new boundary conditions container and specify u=source_strength on the boundary.
            BoundaryConditionsContainer<3, 3, 1> bcc;
            bcc.DefineConstantDirichletOnMeshBoundary(&mesh, source_strength);

            // Create an instance of the solver, passing in the mesh, pde and boundary conditions.
            SimpleLinearParabolicSolver<3, 3> solver(&mesh, p_pde, &bcc);
            
            Vec initial_condition = PetscTools::CreateAndSetVec(mesh.GetNumNodes(), source_strength);
            
            // Now set inital concentration on middle cells
            unsigned num_sinks = 0;
            for (unsigned i = 0; i < mesh.GetNumNodes(); ++i)
            {
                double x_pos = mesh.GetNode(i)->rGetLocation()[0];
                double y_pos = mesh.GetNode(i)->rGetLocation()[1];
                double z_pos = mesh.GetNode(i)->rGetLocation()[2];
                
                if (x_pos>-width_xyz/2.0 && x_pos<width_xyz/2.0)
                {
                    if (y_pos>-width_xyz/2.0 && y_pos<width_xyz/2.0)
                    {
                        if (z_pos>-width_xyz/2.0 && z_pos<width_xyz/2.0)
                        {
                            VecSetValue(initial_condition, i, initial_concentration, INSERT_VALUES);
                            num_sinks++;
                        }
                    }
                }
            }
            unsigned num_boundary_nodes = mesh.GetNumNodes() - num_sinks;
            PRINT_2_VARIABLES(num_sinks,num_boundary_nodes);

            solver.SetInitialCondition(initial_condition);

            // Next define the start time, end time, and timestep, and set them.
            const double t_start = 0.0;
            const double t_end = 10.0; // 10.0;
            const double dt = 0.01;
            solver.SetTimes(t_start, t_end);
            solver.SetTimeStep(dt);

            const auto num_timesteps = 1ul + static_cast<std::size_t>(std::round((t_end - t_start) / dt));

            // Set where to output solution
            solver.SetOutputDirectoryAndPrefix(simulation_output_dir, "results");
            solver.SetOutputToVtk(true);
            solver.SetOutputToTxt(true);
            solver.SetPrintingTimestepMultiple(1);

            // Solve the model
            Vec solution = solver.Solve();

            ReplicatableVector solution_repl(solution);

            auto output_dir = FileFinder(simulation_output_dir, RelativeTo::ChasteTestOutput);
            auto hdf5_reader = Hdf5DataReader(output_dir, "results", "Data");

            const std::vector<double> time_values = hdf5_reader.GetUnlimitedDimensionValues();
            const std::vector<std::vector<double> > soln_values = hdf5_reader.GetVariableOverTimeOverMultipleNodes("Variable_0", 0, num_nodes);
            TS_ASSERT_EQUALS(time_values.size(), num_timesteps);
            TS_ASSERT_EQUALS(soln_values.size(), num_nodes);
            TS_ASSERT_EQUALS(soln_values.at(1).size(), num_timesteps);

            // Output averages etc for plotting
            ColumnDataWriter data_writer(base_name, num_vox_string.str(), false);
            const int time_id_var = data_writer.DefineUnlimitedDimension("time","minutes");
            const int cen_sln_id_var = data_writer.DefineVariable("centre_concentration","uM");
            const int ave_sln_id_var = data_writer.DefineVariable("average_concentration", "uM");
            const int cell_sln_id_var = data_writer.DefineVariable("average_concentration_only_cells", "uM");
            const int min_sln_id_var = data_writer.DefineVariable("minimum_concentration", "uM");
            data_writer.EndDefineMode();

            for (unsigned i = 0; i < time_values.size(); ++i)
            {
                double centre_solution = 0.0;
                double average_solution = 0.0;
                double minimum_solution = DBL_MAX;
                for (unsigned j = 0; j < soln_values.size(); ++j)
                {
                    double local_solution = soln_values.at(j).at(i);
                    
                    average_solution += local_solution;

                    if (local_solution < minimum_solution) 
                    {
                        minimum_solution = local_solution;
                    }

                    double x_pos = mesh.GetNode(j)->rGetLocation()[0];
                    double y_pos = mesh.GetNode(j)->rGetLocation()[1];
                    double z_pos = mesh.GetNode(j)->rGetLocation()[2];
                    if (x_pos*x_pos+y_pos*y_pos+z_pos*z_pos  < 1e-6) 
                    {
                        centre_solution = local_solution;
                    }
                }


                double average_solution_only_cells = average_solution - num_boundary_nodes * source_strength;
                
                average_solution /= static_cast<double>(soln_values.size());
                average_solution_only_cells /= static_cast<double>(num_sinks);
               
                data_writer.PutVariable(time_id_var, time_values.at(i));
                data_writer.PutVariable(cen_sln_id_var, centre_solution);
                data_writer.PutVariable(ave_sln_id_var, average_solution);
                data_writer.PutVariable(cell_sln_id_var, average_solution_only_cells);
                data_writer.PutVariable(min_sln_id_var, minimum_solution);
                data_writer.AdvanceAlongUnlimitedDimension();
            }

            // All PETSc vectors should be destroyed when they are no longer needed.
            PetscTools::Destroy(initial_condition);
            PetscTools::Destroy(solution);
        
            // Reset for next pde
        }
    }
};

#endif /*_TEST_DIFFUSION_SIMPLE_3DHPP_*/
