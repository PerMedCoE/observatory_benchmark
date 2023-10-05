import pandas as pd

physicell_results = "/home/thalia/BSC/pctk/microenv_data.csv"
biodynamo_results = "/home/thalia/BSC/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_diffusion/marenostrum_results//concentration.csv"


bd_df = pd.read_csv(biodynamo_results,header = None,index_col = 0)
print(bd_df)