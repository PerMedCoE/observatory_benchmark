import pandas as pd

# Set the file path and sheet name
xlsx_file = 'result (1).xlsx'
sheet_name = 'diffusion 1k cells'  # Change this to the name of the sheet you want
csv_file = './diffusion_1k_cell.csv'

# Read the specific sheet
df = pd.read_excel(xlsx_file, sheet_name=sheet_name)

# Save to CSV
df.to_csv(csv_file, index=False)
