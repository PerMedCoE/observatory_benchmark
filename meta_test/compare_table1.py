#!/usr/bin/env python3
"""
compare_table1.py: compare two output folders of table1_summary.py and report every value
that moved, every row that appeared or disappeared, and every input file that changed.

This is the regression layer of the benchmark self-test (meta-test, layer 4) in stand-alone
form: the values of the baseline folder are the expected ones (those quoted in the v7
manuscript, frozen at repository commit 6aa51a3 on 30 September 2026), and a value counts
as moved when it differs by more than a relative tolerance of 1e-6 (the self-test's
tolerance). Text columns other than the input file name (notes, division times) are
compared as text.

Usage
-----
    python compare_table1.py BASELINE_DIR NEW_DIR [--out report.md] [--rtol 1e-6]

Example
-------
    python compare_table1.py baseline_6aa51a3 ResultAnalysis/table1_summary --out comparison.md

Exit status 0 when nothing moved, 1 otherwise. Dependencies: numpy, pandas.
Written on 2 November 2026 for the v7 rewrite of the benchmark manuscript.
"""
from __future__ import annotations

import argparse
import os
import sys

import numpy as np
import pandas as pd

# output table -> columns that identify a row
KEYS = {
    "diffusion_decay_finest.csv": ["run"],
    "diffusion_uptake_finest.csv": ["run"],
    "diffusion_decay_all_runs.csv": ["run"],
    "diffusion_uptake_all_runs.csv": ["run"],
    "mechanics_external_impulse.csv": ["tool"],
    "mechanics_common_extended_hertz.csv": ["drag_N_s_per_m", "tool"],
    "mechanics_builtin_pushing.csv": ["tool"],
    "cell_cycle.csv": ["tool"],
    "monolayer.csv": ["tool"],
}
# where each table appears in the manuscript (for the report)
WHERE = {
    "diffusion_decay_finest.csv": "Table 1 (decay row), Results, Figure 2",
    "diffusion_uptake_finest.csv": "Table 1 (point-sink row), Results, Figure 2",
    "diffusion_decay_all_runs.csv": "Supplementary Table S3a (all resolutions)",
    "diffusion_uptake_all_runs.csv": "Supplementary Table S3a (all resolutions)",
    "mechanics_external_impulse.csv": "Table 1 (impulse row), Results, Figure 3C, D",
    "mechanics_common_extended_hertz.csv": "Table 1 (common law row), Results, Figure 3E, Supplementary Table S3b",
    "mechanics_builtin_pushing.csv": "Table 1 (built-in models row), Results, Figure 3F",
    "cell_cycle.csv": "Table 1 (cell-cycle row), Results, Figure 4B",
    "monolayer.csv": "Table 1 (monolayer row), Results, Figure 5",
}
IGNORE = {"file"}  # reported separately as an input change, not as a moved value


def fmt(x) -> str:
    if isinstance(x, (float, np.floating)):
        if not np.isfinite(x):
            return "n/a"
        return f"{x:.6g}"
    return str(x)


def compare_table(name: str, a: pd.DataFrame, b: pd.DataFrame, rtol: float):
    keys = KEYS[name]
    a = a.set_index(keys)
    b = b.set_index(keys)
    moved, files, gone, new = [], [], [], []
    for k in a.index.difference(b.index):
        gone.append(k)
    for k in b.index.difference(a.index):
        new.append(k)
    for k in a.index.intersection(b.index):
        ra, rb = a.loc[k], b.loc[k]
        if "file" in a.columns and str(ra["file"]) != str(rb["file"]):
            files.append((k, ra["file"], rb["file"]))
        for col in a.columns:
            if col in IGNORE or col not in b.columns:
                continue
            va, vb = ra[col], rb[col]
            na, nb = pd.api.types.is_number(va), pd.api.types.is_number(vb)
            if na and nb:
                va, vb = float(va), float(vb)
                if np.isnan(va) and np.isnan(vb):
                    continue
                if np.isnan(va) != np.isnan(vb) or not np.isclose(vb, va, rtol=rtol, atol=1e-12):
                    rel = (vb - va) / abs(va) * 100 if np.isfinite(va) and va != 0 and np.isfinite(vb) else np.nan
                    moved.append((k, col, va, vb, rel))
            elif str(va) != str(vb) and not (pd.isna(va) and pd.isna(vb)):
                moved.append((k, col, va, vb, np.nan))
    return moved, files, gone, new


def label(k) -> str:
    return " / ".join(fmt(x) for x in k) if isinstance(k, tuple) else fmt(k)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("baseline")
    ap.add_argument("new")
    ap.add_argument("--out", default=None, help="Markdown report (default: print only)")
    ap.add_argument("--rtol", type=float, default=1e-6)
    args = ap.parse_args(argv)

    L = [f"# Table 1 regression: `{args.new}` against `{args.baseline}`\n",
         f"Relative tolerance {args.rtol:g}. A moved value means that the manuscript text, Table 1 or a figure "
         f"quoting it must be checked before the new value is accepted.\n"]
    n_moved = 0
    summary = []
    for name in KEYS:
        pa, pb = os.path.join(args.baseline, name), os.path.join(args.new, name)
        if not os.path.exists(pa) or not os.path.exists(pb):
            L.append(f"## {name}\n\nMissing in {'baseline' if not os.path.exists(pa) else 'new run'}.\n")
            n_moved += 1
            summary.append((name, "missing", "", "", ""))
            continue
        moved, files, gone, new = compare_table(name, pd.read_csv(pa), pd.read_csv(pb), args.rtol)
        n_moved += len(moved) + len(gone) + len(new)
        summary.append((name, len(moved), len(gone) + len(new), len(files), WHERE[name]))
        if not (moved or files or gone or new):
            continue
        L.append(f"## {name}\n\nUsed in: {WHERE[name]}.\n")
        if gone:
            L.append("Rows no longer produced: " + "; ".join(label(k) for k in gone) + ".\n")
        if new:
            L.append("New rows: " + "; ".join(label(k) for k in new) + ".\n")
        if files:
            L.append("Input file changed: " + "; ".join(f"{label(k)}: `{fa}` to `{fb}`" for k, fa, fb in files) + ".\n")
        if moved:
            L.append("| Row | Quantity | Baseline | New | Change (%) |")
            L.append("|---|---|---|---|---|")
            for k, col, va, vb, rel in moved:
                L.append(f"| {label(k)} | {col} | {fmt(va)} | {fmt(vb)} | {'' if not np.isfinite(rel) else f'{rel:+.3g}'} |")
            L.append("")
    head = ["## Summary\n", "| Output table | Values moved | Rows added or removed | Input files changed | Used in |",
            "|---|---|---|---|---|"]
    head += [f"| {n} | {m} | {g} | {f} | {w} |" for n, m, g, f, w in summary]
    head.append("")
    text = "\n".join(L[:2] + head + L[2:]) + "\n"
    print(text)
    if args.out:
        with open(args.out, "w") as fh:
            fh.write(text)
    return 0 if n_moved == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
