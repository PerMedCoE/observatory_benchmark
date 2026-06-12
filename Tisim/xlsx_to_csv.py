from pathlib import Path

import pandas as pd


ROOT = Path(__file__).resolve().parent
WORKBOOK = ROOT / 'result_new.xlsx'


def export_sheet(sheet_name: str, output_path: Path) -> None:
	frame = pd.read_excel(WORKBOOK, sheet_name=sheet_name)
	frame.to_csv(output_path, index=False)


def export_decay_sheet() -> None:
	output_dir = ROOT / 'diffusion_decay_test'
	output_dir.mkdir(parents=True, exist_ok=True)

	raw = pd.read_excel(WORKBOOK, sheet_name='decay', header=None)
	block_specs = [
		('10', 1),
		('20', 3),
		('40', 5),
	]

	for resolution, concentration_col in block_specs:
		frame = raw.iloc[2:, [0, concentration_col]].copy()
		frame.columns = ['time_min', 'average_uM']
		frame = frame.dropna(how='all')
		frame['time_min'] = pd.to_numeric(frame['time_min'], errors='coerce')
		frame['average_uM'] = pd.to_numeric(frame['average_uM'], errors='coerce')
		frame = frame.dropna(subset=['time_min', 'average_uM']).reset_index(drop=True)
		frame.to_csv(output_dir / f'data_{resolution}.csv', index=False)


def export_uptake_sheets() -> None:
	output_dir = ROOT / 'diffusion_uptake_test'
	output_dir.mkdir(parents=True, exist_ok=True)

	average_raw = pd.read_excel(WORKBOOK, sheet_name='uptake average', header=None)
	center_raw = pd.read_excel(WORKBOOK, sheet_name='uptake center', header=None)
	block_specs = [
		('10', 1),
		('20', 3),
		('40', 5),
	]

	for resolution, concentration_col in block_specs:
		average_frame = average_raw.iloc[2:, [0, concentration_col]].copy()
		average_frame.columns = ['time_min', 'average_uM']
		center_frame = center_raw.iloc[2:, [0, concentration_col]].copy()
		center_frame.columns = ['time_min', 'center_uM']

		frame = average_frame.merge(center_frame, on='time_min', how='inner', validate='one_to_one')
		frame = frame.dropna(how='all')
		frame['time_min'] = pd.to_numeric(frame['time_min'], errors='coerce')
		frame['average_uM'] = pd.to_numeric(frame['average_uM'], errors='coerce')
		frame['center_uM'] = pd.to_numeric(frame['center_uM'], errors='coerce')
		frame = frame.dropna(subset=['time_min', 'average_uM', 'center_uM']).reset_index(drop=True)
		frame.to_csv(output_dir / f'data_{resolution}.csv', index=False)


if __name__ == '__main__':
	workbook_sheets = pd.ExcelFile(WORKBOOK).sheet_names
	if 'diffusion 1k cells' in workbook_sheets:
		export_sheet('diffusion 1k cells', ROOT / 'diffusion_1k_cell.csv')
	export_decay_sheet()
	export_uptake_sheets()
