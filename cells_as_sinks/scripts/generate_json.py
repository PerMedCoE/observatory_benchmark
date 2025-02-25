
import json
from itertools import product

def main():
    # Two variables with arrays of different possible values
    dd = [20, 10, 5, 2]  # Different dx values
    files = ["centers_20um.csv", "centers_10um.csv", "centers_5um.csv", "centers_2um.csv"]
    ocu = [0.01, 0.1, 0.2, 0.5, 0.8, 1]  # Occupancy percentages
    uptake = [12044, 20, 0.0000617]

    # Pair (dx, file, volume)
    result = [(dx, file, dx**3) for dx, file in zip(dd, files)]

    # Generate all combinations of (dx, file, adjusted volume)
    results = [(dx, file, vol * oc) for dx, file, vol in result for oc in ocu]

    # Ensure we only loop over the number of `ocu` values that match `dx`
    combinations = [
        {
            'domain.dx': val1[0],  
            'domain.dy': val1[0],
            'domain.dz': val1[0],
            'cell_definitions.cell_definition.phenotype.volume.total': val1[2],  
            'cell_definitions.cell_definition.phenotype.volume.nuclear': val1[2]*0.25,  # nuclear volume as 10% of total
            'initial_conditions.cell_positions.filename': val1[1],
            'cell_definitions.cell_definition.phenotype.secretion.substrate.uptake_rate': val2,
            'microenvironment_setup.variable.oxygen.Dirichlet_boundary_condition': val2 / 2 if val2 > 1 else 6022,
            'microenvironment_setup.variable.oxygen.Dirichlet_boundary_condition.Dirichlet_options.boundary_value': val2 / 2 if val2 > 1 else 6022,
        }
        for val1, val2 in product(results, uptake) 
    ]

    # Creating a JSON object
    # json_data = json.dumps(combinations)
    # print(json_data)
    with open("data/sinks_dx_volumes_uptake_diriclet.txt", 'w') as fh:
        for combo in combinations:
            json_data = json.dumps(combo)
            fh.write(json_data + '\n')  # Write each dictionary followed by a newline character



main()
