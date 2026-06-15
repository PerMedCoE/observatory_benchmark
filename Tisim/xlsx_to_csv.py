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


def export_1_cell_sheet() -> None:
	raw = pd.read_excel(WORKBOOK, sheet_name='1 cell', header=None)
	output_dir = ROOT / 'mechanics_external_impulse'
	frame = raw.iloc[1:].copy()
	frame.columns = raw.iloc[0]
	frame = frame.dropna(how='all').reset_index(drop=True)
	for col in frame.columns:
		frame[col] = pd.to_numeric(frame[col], errors='coerce')
	frame = frame.dropna().reset_index(drop=True)
	frame.to_csv(output_dir / 'mechanics_external_impulse.csv', index=False)


def export_2_cells_sheet() -> None:
	output_dir = ROOT / 'mechanics_relaxation'
	output_dir.mkdir(parents=True, exist_ok=True)

	raw = pd.read_excel(WORKBOOK, sheet_name='2 cells', header=None)
	block_specs = [
		('drag_0.01', 1, 2),
		('drag_0.1', 3, 4),
		('drag_1', 5, 6),
	]

	for label, distance_col, force_col in block_specs:
		frame = raw.iloc[2:, [0, distance_col, force_col]].copy()
		frame.columns = ['time_s', 'distance_10um', 'force_nN']
		frame = frame.dropna(how='all')
		frame['time_s'] = pd.to_numeric(frame['time_s'], errors='coerce')
		frame['distance_10um'] = pd.to_numeric(frame['distance_10um'], errors='coerce')
		frame['force_nN'] = pd.to_numeric(frame['force_nN'], errors='coerce')
		frame = frame.dropna(subset=['time_s', 'distance_10um', 'force_nN']).reset_index(drop=True)
		frame.to_csv(output_dir / f'data_{label}.csv', index=False)


if __name__ == '__main__':
	workbook_sheets = pd.ExcelFile(WORKBOOK).sheet_names
	if 'diffusion 1k cells' in workbook_sheets:
		export_sheet('diffusion 1k cells', ROOT / 'diffusion_1k_cell.csv')
	if '1 cell' in workbook_sheets:
		export_1_cell_sheet()
	if '2 cells' in workbook_sheets:
		export_2_cells_sheet()
	# export_decay_sheet()
	# export_uptake_sheets()
