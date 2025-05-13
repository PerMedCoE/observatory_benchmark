import pandas as pd

# Set the file path and sheet name
xlsx_file = 'result.xlsx'
sheet_name = '2D disk'  # Change this to the name of the sheet you want
csv_file = './use_case_2Ddisk/2D disk.csv'

# Read the specific sheet
df = pd.read_excel(xlsx_file, sheet_name=sheet_name)

# Save to CSV
df.to_csv(csv_file, index=False)
