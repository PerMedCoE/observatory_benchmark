import csv
import math

RADIUS_UM = 570.0
CELL_DIAMETER_UM = 10.0  # Replace with your model's initial cell diameter
CELL_TYPE = 0  # Must match the cell type name in your XML

# Keep each centre one cell radius inside the measured edge.
centre_limit = RADIUS_UM - CELL_DIAMETER_UM / 2
row_spacing = CELL_DIAMETER_UM * math.sqrt(3) / 2

positions = []
row = 0
y = -centre_limit

while y <= centre_limit:
    x_offset = 0 if row % 2 == 0 else CELL_DIAMETER_UM / 2
    x = -centre_limit + x_offset

    while x <= centre_limit:
        if x * x + y * y <= centre_limit * centre_limit:
            positions.append((x, y, 0))
        x += CELL_DIAMETER_UM

    y += row_spacing
    row += 1

with open("cells.csv", "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["x", "y", "z", "cell type"])
    for x, y, z in positions:
        writer.writerow([x, y, z, CELL_TYPE])

print(f"Wrote {len(positions)} cell positions")