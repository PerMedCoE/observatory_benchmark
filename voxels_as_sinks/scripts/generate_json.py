
import json
from itertools import product

def main():
    # Two variables with arrays of different possible values
    dd = [20,10,5,2]
    files = ["../centers_20um.csv","../centers_10um.csv","../centers_5um.csv","../centers_2um.csv"]
    uptake = [12044,20]
    result = [(dd[i], files[i])for i in range(len(dd))]

    # Creating combinations of values using itertools.product
    combinations = [
        {
            'domain.dx': val1[0],  # `val1` is a tuple from `result`
            'domain.dy': val1[0],
            'domain.dz': val1[0],
            'user_parameters.sinks': val1[1],
            'user_parameters.uptake': val2,
            'microenvironment_setup.variable.oxygen.Dirichlet_boundary_condition' : val2/2,
            'microenvironment_setup.variable.oxygen.Dirichlet_boundary_condition.Dirichlet_options.boundary_value':  val2/2
        }
        for val1, val2 in product(result, uptake)
    ]

    with open("data/bulk_dx_sinks_uptake.txt", 'w') as fh:
        for combo in combinations:
            json_data = json.dumps(combo)
            fh.write(json_data + '\n')  # Write each dictionary followed by a newline character



main()