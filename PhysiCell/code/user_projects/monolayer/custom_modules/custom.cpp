/*
###############################################################################
# If you use PhysiCell in your project, please cite PhysiCell and the version #
# number, such as below:                                                      #
#                                                                             #
# We implemented and solved the model using PhysiCell (Version x.y.z) [1].    #
#                                                                             #
# [1] A Ghaffarizadeh, R Heiland, SH Friedman, SM Mumenthaler, and P Macklin, #
#     PhysiCell: an Open Source Physics-Based Cell Simulator for Multicellu-  #
#     lar Systems, PLoS Comput. Biol. 14(2): e1005991, 2018                   #
#     DOI: 10.1371/journal.pcbi.1005991                                       #
#                                                                             #
# See VERSION.txt or call get_PhysiCell_version() to get the current version  #
#     x.y.z. Call display_citations() to get detailed information on all cite-#
#     able software used in your PhysiCell application.                       #
#                                                                             #
# Because PhysiCell extensively uses BioFVM, we suggest you also cite BioFVM  #
#     as below:                                                               #
#                                                                             #
# We implemented and solved the model using PhysiCell (Version x.y.z) [1],    #
# with BioFVM [2] to solve the transport equations.                           #
#                                                                             #
# [1] A Ghaffarizadeh, R Heiland, SH Friedman, SM Mumenthaler, and P Macklin, #
#     PhysiCell: an Open Source Physics-Based Cell Simulator for Multicellu-  #
#     lar Systems, PLoS Comput. Biol. 14(2): e1005991, 2018                   #
#     DOI: 10.1371/journal.pcbi.1005991                                       #
#                                                                             #
# [2] A Ghaffarizadeh, SH Friedman, and P Macklin, BioFVM: an efficient para- #
#     llelized diffusive transport solver for 3-D biological simulations,     #
#     Bioinformatics 32(8): 1256-8, 2016. DOI: 10.1093/bioinformatics/btv730  #
#                                                                             #
###############################################################################
#                                                                             #
# BSD 3-Clause License (see https://opensource.org/licenses/BSD-3-Clause)     #
#                                                                             #
# Copyright (c) 2015-2021, Paul Macklin and the PhysiCell Project             #
# All rights reserved.                                                        #
#                                                                             #
# Redistribution and use in source and binary forms, with or without          #
# modification, are permitted provided that the following conditions are met: #
#                                                                             #
# 1. Redistributions of source code must retain the above copyright notice,   #
# this list of conditions and the following disclaimer.                       #
#                                                                             #
# 2. Redistributions in binary form must reproduce the above copyright        #
# notice, this list of conditions and the following disclaimer in the         #
# documentation and/or other materials provided with the distribution.        #
#                                                                             #
# 3. Neither the name of the copyright holder nor the names of its            #
# contributors may be used to endorse or promote products derived from this   #
# software without specific prior written permission.                         #
#                                                                             #
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" #
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   #
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  #
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   #
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         #
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        #
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    #
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     #
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     #
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  #
# POSSIBILITY OF SUCH DAMAGE.                                                 #
#                                                                             #
###############################################################################
*/

#include "./custom.h"

#include <cmath>

namespace {

double base_fluid_change_rate = 0.0;
double base_cytoplasmic_biomass_change_rate = 0.0;
double base_nuclear_biomass_change_rate = 0.0;

}

void create_cell_types( void )
{
	// set the random seed 
	// SeedRandom( parameters.ints("random_seed") );  
	
	/* 
	   Put any modifications to default cell definition here if you 
	   want to have "inherited" by other cell types. 
	   
	   This is a good place to set default functions. 
	*/ 
	
	initialize_default_cell_definition(); 
	cell_defaults.phenotype.secretion.sync_to_microenvironment( &microenvironment ); 
	
	cell_defaults.functions.volume_update_function = standard_volume_update_function;
	cell_defaults.functions.update_velocity = standard_update_cell_velocity;

	cell_defaults.functions.update_migration_bias = NULL; 
	cell_defaults.functions.update_phenotype = NULL; // update_cell_and_death_parameters_O2_based; 
	cell_defaults.functions.custom_cell_rule = NULL; 
	cell_defaults.functions.contact_function = NULL; 
	
	cell_defaults.functions.add_cell_basement_membrane_interactions = NULL; 
	cell_defaults.functions.calculate_distance_to_membrane = NULL; 
	
	/*
	   This parses the cell definitions in the XML config file. 
	*/
	
	initialize_cell_definitions_from_pugixml(); 

	/*
	   This builds the map of cell definitions and summarizes the setup. 
	*/
		
	build_cell_definitions_maps(); 

	/*
	   This intializes cell signal and response dictionaries 
	*/

	setup_signal_behavior_dictionaries(); 	

	/* 
	   Put any modifications to individual cell definitions here. 
	   
	   This is a good place to set custom functions. 
	*/ 
	
	Cell_Definition* pCD = find_cell_definition( "agent" );
	if( pCD == NULL )
	{
		std::cerr << "Could not find the 'agent' cell definition for crowding control." << std::endl;
		exit( EXIT_FAILURE );
	}
	base_fluid_change_rate = pCD->phenotype.volume.fluid_change_rate;
	base_cytoplasmic_biomass_change_rate = pCD->phenotype.volume.cytoplasmic_biomass_change_rate;
	base_nuclear_biomass_change_rate = pCD->phenotype.volume.nuclear_biomass_change_rate;
	pCD->functions.update_phenotype = phenotype_function;
	// cell_defaults.functions.contact_function = contact_function; 
	
	/*
	   This builds the map of cell definitions and summarizes the setup. 
	*/
		
	display_cell_definitions( std::cout ); 
	
	return; 
}

void setup_microenvironment( void )
{
	// initialize BioFVM 
	
	initialize_microenvironment(); 	

    int idx_oxygen = 0;
    double oxy_value = 6022.0;

    int idx_xmax = microenvironment.mesh.x_coordinates.size() - 1; 
    int idx_ymax = microenvironment.mesh.y_coordinates.size() - 1;
    int idx_zmax = microenvironment.mesh.z_coordinates.size() - 1;

    microenvironment.update_dirichlet_node( 
        microenvironment.voxel_index(idx_xmax, idx_ymax, idx_zmax), 
        idx_oxygen, oxy_value);
    microenvironment.set_substrate_dirichlet_activation( idx_oxygen, 
        microenvironment.voxel_index(idx_xmax, idx_ymax, idx_zmax), true);
	
	return; 
}

void setup_tissue( void )
{
	Cell_Definition* pCD = find_cell_definition( "agent" );
	if( pCD == NULL )
	{
		std::cerr << "Could not find the 'agent' cell definition for the monolayer seed." << std::endl;
		exit( EXIT_FAILURE );
	}

	constexpr double target_diameter = 1140.0;
	const double cell_radius = pCD->phenotype.geometry.radius;
	const double disk_radius = target_diameter / 2.0;
	const double cell_spacing = 2.0 * cell_radius;
	const double row_spacing = cell_spacing * std::sqrt(3.0) / 2.0;

	int cell_count = 0;
	const int row_limit = static_cast<int>(std::floor(disk_radius / row_spacing));
	for( int row = -row_limit; row <= row_limit; ++row )
	{
		const double y = row * row_spacing;
		const double row_offset = (row % 2 == 0) ? 0.0 : cell_spacing / 2.0;
		const double x_limit = std::sqrt(disk_radius * disk_radius - y * y);
		const int column_min = static_cast<int>(std::ceil((-x_limit - row_offset) / cell_spacing));
		const int column_max = static_cast<int>(std::floor((x_limit - row_offset) / cell_spacing));

		for( int column = column_min; column <= column_max; ++column )
		{
			const double x = column * cell_spacing + row_offset;
			Cell* pC = create_cell( *pCD );
			pC->assign_position({x, y, 0.0});
			++cell_count;
		}
	}

	std::cout << "Initialized " << cell_count
	          << " agent cells in a centered hexagonal disk."
	          << " Target diameter: " << target_diameter << " microns."
	          << " Lattice spacing: " << cell_spacing << " microns."
	          << std::endl;
	
	return; 
}

std::vector<std::string> my_coloring_function( Cell* pCell )
{ return paint_by_number_cell_coloring(pCell); }

void phenotype_function( Cell* pCell, Phenotype& phenotype, double dt )
{ 
	if( phenotype.death.dead || phenotype.cycle.model().code != PhysiCell_constants::flow_cytometry_separated_cycle_model )
	{
		return;
	}

	const int phase = phenotype.cycle.current_phase_index();
	const bool growth_phase = (phase == 0 || phase == 2);
	bool overcrowded = false;

	if( growth_phase )
	{
		const double cell_radius = phenotype.geometry.radius;
		for( Cell* neighbor : pCell->state.neighbors )
		{
			const double dx = pCell->position[0] - neighbor->position[0];
			const double dy = pCell->position[1] - neighbor->position[1];
			const double dz = pCell->position[2] - neighbor->position[2];
			const double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
			const double overlap = cell_radius + neighbor->phenotype.geometry.radius - distance;

			if( overlap > 0.2 * cell_radius )
			{
				overcrowded = true;
				break;
			}
		}
	}

	if( growth_phase && overcrowded )
	{
		phenotype.cycle.data.elapsed_time_in_phase -= dt;
		phenotype.volume.fluid_change_rate = 0.0;
		phenotype.volume.cytoplasmic_biomass_change_rate = 0.0;
		phenotype.volume.nuclear_biomass_change_rate = 0.0;
	}
	else
	{
		phenotype.volume.fluid_change_rate = base_fluid_change_rate;
		phenotype.volume.cytoplasmic_biomass_change_rate = base_cytoplasmic_biomass_change_rate;
		phenotype.volume.nuclear_biomass_change_rate = base_nuclear_biomass_change_rate;
	}
}

void custom_function( Cell* pCell, Phenotype& phenotype , double dt )
{ return; } 

void contact_function( Cell* pMe, Phenotype& phenoMe , Cell* pOther, Phenotype& phenoOther , double dt )
{ return; } 
