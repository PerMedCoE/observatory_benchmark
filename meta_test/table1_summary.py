#!/usr/bin/env python3
"""
table1_summary.py: reproduce the quantitative summaries of the benchmark manuscript
(Table 1 and the numbers quoted in the Results) from the result files stored in the
PerMedCoE/observatory_benchmark repository.

Written for the repository cross-check of 29 to 30 September 2026 (project doc
"plan-step1-repository-crosscheck.md", sections 5.1 to 5.5). It consolidates the three
working scripts used in that session (quant_diffusion.py, quant_mechanics.py,
quant_cc_mono.py) into one repository-relative script. It reads result files only and
writes its outputs to a separate folder; it never modifies the result files.

Usage
-----
    python ResultAnalysis/table1_summary.py [--repo PATH] [--out PATH]

    --repo   repository root (default: the first parent folder of this script, or of the
             current working directory, that contains a "ResultAnalysis" folder)
    --out    output folder (default: <repo>/ResultAnalysis/table1_summary)

Outputs (in --out)
------------------
    diffusion_decay_all_runs.csv, diffusion_uptake_all_runs.csv   one row per run (all resolutions)
    diffusion_decay_finest.csv, diffusion_uptake_finest.csv       finest run per tool
    mechanics_external_impulse.csv
    mechanics_common_extended_hertz.csv                          one row per drag and tool
    mechanics_builtin_pushing.csv
    cell_cycle.csv
    monolayer.csv
    table1_summary.md                                            the ranges quoted in Table 1

Dependencies: numpy, pandas, pyyaml, scipy (tested with numpy 2.4, pandas 3.0, PyYAML 6.0,
scipy 1.17, Python 3.11).

Conventions and criteria (stated once here, applied everywhere)
----------------------------------------------------------------
* Units are converted to um, uM, s (or min where the test is defined in minutes) with the
  same conversions as the ResultAnalysis notebooks: BioDynaMo diffusion time columns are read
  as minutes (the README says seconds; the data follow the analytical solution only when read
  as minutes); CompuTiX seconds are divided by 60 and mol/m3 multiplied by 1000; TiSim
  relaxation distances are in units of 10 um; BioDynaMo impulse files are in nm and nm/s;
  TiSim impulse positions are multiplied by 0.01 (as in the notebook).
* "t_end" is the last sample of each file.
* Steady state: the first time after which the quantity stays within 1 % of its final value,
  the 1 % being taken relative to the total change over the run (|c(0) - c(t_end)|).
* Relative errors are 100 * (tool - analytical) / analytical at the nearest analytical
  sample in time (signed); mean relative error is the mean of |.| over the run.
* Finest run per tool: BioDynaMo N = 48, Chaste N = 48, CompuTiX N = 63 with dt = 0.006 s,
  PhysiCell dx = 5 um, TiSim N = 40 (the runs the notebooks select by lowest error).
* Extended Hertz reference: overdamped ODE d(delta)/dt = -2 F(delta) / zeta with
  F = (4/3) E* sqrt(R~) delta^1.5 - pi gamma R~, E* = E / (2 (1 - nu^2)) for two identical
  cells, E = 450 Pa, nu = 0.4, R~ = 2.5 um, gamma = 8.56e-15 J/m2, delta(0) = 1 um. The
  factor 2 accounts for both cells moving at F/zeta. The uncorrected curve of the analysis
  notebook (R1 = R2 = 1 um, no factor 2) is also evaluated for comparison.
* Division events in the cell-cycle test: volume drops of more than 25 % of V0 between
  consecutive samples.
* Monolayer deviation: simulated diameter minus the linear interpolation of the Bru et al.
  points, over 14.0 to 26.92 days (336 to 646 h).

Changes
-------
30 September 2026: the TiSim cell-cycle row is relabelled "TiSim (file used in Figure 4B)",
because repository commit 6aa51a3 replaced the hourly export in
Tisim/fixed_cell_cycle/cell cycle fix.csv by the phase-resolved output. No computation changed.
2 November 2026: paths updated to the folder layout of commit 83e512b (24 October 2026):
analytical_solutions and experimental_data moved under ResultAnalysis/analytical_solutions;
Chaste results moved to <test>/results/ and two Chaste folders renamed (FixedCellCycle,
MonolayerUseCase); BioDynaMo cell cycle read from results/cell-0.csv; CompuTiX built-in
contact run read from pushing_benchmark.yaml; PhysiCell impulse read from the file that
replaced dt_0.001/; the TiSim impulse file of 19 October states its
units (s, um, um/s) and gives the position in um, so the factor 0.01 is applied only to the
older file without units. Each path is resolved by trying the current location first and the
30 September location second, so the script runs at both commits. A file absent at both
locations (Chaste built-in contact results, deleted on 24 October) gives a row marked
absent instead of stopping the run. No computation changed.
"""
from __future__ import annotations

import argparse
import glob
import json
import os
import sys

import numpy as np
import pandas as pd
import yaml
from scipy.integrate import solve_ivp

TOOLS = ["BioDynaMo", "Chaste", "CompuTiX", "PhysiCell", "TiSim"]
BOX_UM = 240.0  # side of the diffusion domain; dx = BOX_UM / N for tools that only give N


# ----------------------------------------------------------------------------------------
# helpers
# ----------------------------------------------------------------------------------------
def find_repo(start: str) -> str | None:
    p = os.path.abspath(start)
    while True:
        if os.path.isdir(os.path.join(p, "ResultAnalysis")) and os.path.isdir(os.path.join(p, "Biodynamo")):
            return p
        parent = os.path.dirname(p)
        if parent == p:
            return None
        p = parent


def t_steady(t, c, frac: float = 0.01) -> float:
    """First time after which |c(t) - c(t_end)| <= frac * |c(0) - c(t_end)| for all later samples."""
    t = np.asarray(t, float)
    c = np.asarray(c, float)
    total = abs(c[0] - c[-1])
    if total == 0:
        return float("nan")
    inside = np.abs(c - c[-1]) <= frac * total
    idx = len(c) - 1
    while idx > 0 and inside[idx - 1]:
        idx -= 1
    return float(t[idx])


def nearest_rows(ref_t, t):
    """Index of the analytical sample nearest to each time in t (ref_t sorted ascending)."""
    ref_t = np.asarray(ref_t, float)
    t = np.asarray(t, float)
    hi = np.clip(np.searchsorted(ref_t, t), 0, len(ref_t) - 1)
    lo = np.clip(hi - 1, 0, len(ref_t) - 1)
    return np.where(np.abs(ref_t[lo] - t) < np.abs(ref_t[hi] - t), lo, hi)


def first_time_below(t, y, threshold) -> float:
    idx = np.where(np.asarray(y) <= threshold)[0]
    return float(np.asarray(t)[idx[0]]) if len(idx) else float("nan")


def rel(path: str, repo: str) -> str:
    return os.path.relpath(path, repo)


def pick(repo: str, *candidates: str) -> str:
    """Absolute path of the first candidate that exists (current layout first), else of the first one."""
    for c in candidates:
        p = os.path.join(repo, c)
        if os.path.exists(p):
            return p
    return os.path.join(repo, candidates[0])


def gpick(repo: str, *patterns: str) -> list:
    """Sorted matches of the first glob pattern that matches anything (current layout first)."""
    for pat in patterns:
        m = sorted(glob.glob(os.path.join(repo, pat)))
        if m:
            return m
    return []


# ----------------------------------------------------------------------------------------
# 1 and 2: reaction-diffusion tests
# ----------------------------------------------------------------------------------------
def load_diffusion_runs(repo: str, test: str) -> dict:
    """Return {run label: (time_min, average_uM, centre_uM, file)} for 'decay' or 'uptake'."""
    runs = {}
    if test == "decay":
        bdm_dir, chaste_dir, ctx_dir, pc_glob, tisim_dir = (
            "Biodynamo/diffusion_decay_test", "Chaste/DiffusionNoCells", "CompuTiX/diffusion_single/Decay/",
            "PhysiCell/results/diffusion_decay/size_*/physicell_decay_plot_data.csv", "Tisim/diffusion_decay_test")
    else:
        bdm_dir, chaste_dir, ctx_dir, pc_glob, tisim_dir = (
            "Biodynamo/diffusion_uptake_test", "Chaste/DiffusionWithCells", "CompuTiX/diffusion_single/CellsAtCenter/",
            "PhysiCell/results/diffusion_uptake/size_*_uptake/physicell_uptake_plot_data.csv", "Tisim/diffusion_uptake_test")

    for p in sorted(glob.glob(os.path.join(repo, bdm_dir, "data_*.csv"))):
        n = int(os.path.basename(p).split("_")[1].split(".")[0])
        df = pd.read_csv(p, sep=r"\s+", header=None, names=["t", "avg", "cen"])
        runs[f"BioDynaMo N={n} dx={BOX_UM / n:g}"] = (df.t.values, df.avg.values, df.cen.values, p)

    if test == "decay":
        for p in gpick(repo, chaste_dir + "/results/*.dat", chaste_dir + "/*.dat"):
            n = int(os.path.basename(p).split(".")[0])
            df = pd.read_csv(p, sep=r"\s+")
            runs[f"Chaste N={n} dx={BOX_UM / n:g}"] = (df["time(minutes)"].values, df["average_concentration(uM)"].values,
                                                   df["centre_concentration(uM)"].values, p)
    else:
        for p in gpick(repo, chaste_dir + "/results/*.txt", chaste_dir + "/*.txt"):
            n = int(os.path.basename(p).split(".")[0])
            # unlabelled columns; the notebook reads them as time, centre, average
            df = pd.read_csv(p, sep=r"\s+", header=None, names=["t", "cen", "avg"])
            runs[f"Chaste N={n} dx={BOX_UM / n:g}"] = (df.t.values, df.avg.values, df.cen.values, p)

    # CompuTiX: the runs with dt = 0.006 s (the notebook's choice); dt = 0.0006 s runs also exist
    for p in sorted(glob.glob(os.path.join(repo, ctx_dir, "/results/dt-s-0-006_N-*.yaml"))):
        d = yaml.load(open(p), Loader=getattr(yaml, "CSafeLoader", yaml.SafeLoader))
        n = int(d["N"]["values"])
        dx = float(d["dx"]["values"]) * 1e6
        ts = d["time_series"]["values"]
        runs[f"CompuTiX N={n} dx={dx:.2f} dt=0.006s"] = (np.array(ts["t"]["values"], float) / 60.0,
                                                        1e3 * np.array(ts["c_domain"]["values"], float),
                                                        1e3 * np.array(ts["c_central"]["values"], float), p)

    for p in sorted(glob.glob(os.path.join(repo, pc_glob))):
        df = pd.read_csv(p)
        runs[f"PhysiCell dx={df.dx_um.iloc[0]:g}"] = (df.time_min.values, df.average_uM.values, df.center_uM.values, p)

    for p in sorted(glob.glob(os.path.join(repo, tisim_dir, "data_*.csv"))):
        n = int(os.path.basename(p).split("_")[1].split(".")[0])
        df = pd.read_csv(p)
        runs[f"TiSim N={n} dx={BOX_UM / n:g}"] = (df.time_min.values, df.average_uM.values, df.center_uM.values, p)
    return runs


FINEST = ("BioDynaMo N=48", "Chaste N=48", "CompuTiX N=63", "PhysiCell dx=5", "TiSim N=40")


def analyse_diffusion(repo: str, test: str, out: str) -> tuple[pd.DataFrame, pd.DataFrame, dict]:
    sub = "diffusion/" + ("Decay" if test == "decay" else "Cellsatcenter") + "/analytical_values.csv"
    ana_path = pick(repo, "ResultAnalysis/analytical_solutions/" + sub, "analytical_solutions/" + sub)
    ana = pd.read_csv(ana_path)
    ana_t = ana.time_min.values
    ana_avg = ana.average_concentration_uM.values
    ana_cen = ana.center_concentration_uM.values
    ref = dict(file=rel(ana_path, repo), t_end_min=float(ana_t[-1]), average_uM=float(ana_avg[-1]),
               centre_uM=float(ana_cen[-1]), t_ss_average_min=t_steady(ana_t, ana_avg),
               t_ss_centre_min=t_steady(ana_t, ana_cen))
    rows = []
    for label, (t, avg, cen, path) in load_diffusion_runs(repo, test).items():
        idx = nearest_rows(ana_t, t)
        a_avg, a_cen = ana_avg[idx], ana_cen[idx]
        with np.errstate(divide="ignore", invalid="ignore"):
            re_avg = 100 * np.abs(avg - a_avg) / np.abs(a_avg)
            re_cen = 100 * np.abs(cen - a_cen) / np.abs(a_cen)
        rows.append(dict(
            tool=label.split()[0], run=label, file=rel(path, repo), samples=len(t), t_end_min=float(t[-1]),
            average_uM=float(avg[-1]), analytical_average_uM=float(a_avg[-1]),
            average_rel_error_pct=float(100 * (avg[-1] - a_avg[-1]) / a_avg[-1]),
            average_mean_rel_error_pct=float(np.nanmean(re_avg)), average_max_rel_error_pct=float(np.nanmax(re_avg)),
            t_ss_average_min=t_steady(t, avg),
            centre_uM=float(cen[-1]), analytical_centre_uM=float(a_cen[-1]),
            centre_rel_error_pct=float(100 * (cen[-1] - a_cen[-1]) / a_cen[-1]),
            centre_mean_rel_error_pct=float(np.nanmean(re_cen)), t_ss_centre_min=t_steady(t, cen),
            min_centre_uM=float(np.min(cen)), min_average_uM=float(np.min(avg))))
    allruns = pd.DataFrame(rows)
    finest = pd.concat([allruns[allruns.run.str.startswith(k)] for k in FINEST], ignore_index=True)
    allruns.to_csv(os.path.join(out, f"diffusion_{test}_all_runs.csv"), index=False)
    finest.to_csv(os.path.join(out, f"diffusion_{test}_finest.csv"), index=False)
    return allruns, finest, ref


# ----------------------------------------------------------------------------------------
# 3: external impulse
# ----------------------------------------------------------------------------------------
def analyse_impulse(repo: str, out: str) -> tuple[pd.DataFrame, dict]:
    ana_path = pick(repo, "ResultAnalysis/analytical_solutions/mechanics/analytical_values.csv",
                    "analytical_solutions/mechanics/analytical_values.csv")
    ana = pd.read_csv(ana_path)
    active = (ana.time_s > 3.0) & (ana.time_s < 6.0)
    ref = dict(file=rel(ana_path, repo), plateau_um_per_s=float(ana.velocity_um_per_s[active].iloc[0]),
               displacement_um=float(ana.distance_um.iloc[-1]))
    rows = []

    def bdm_x(path):
        df = pd.read_csv(path, sep="\t", header=None, names=["t", "v"])
        return df.t.values, df.v.str.strip().str.split(",").str[0].astype(float).values

    p_v = os.path.join(repo, "Biodynamo/mechanics_externalImpulse/results_3s_force/speeds.csv")
    p_x = os.path.join(repo, "Biodynamo/mechanics_externalImpulse/results_3s_force/positions.csv")
    t, vx = bdm_x(p_v)
    _, x = bdm_x(p_x)
    nz = vx != 0
    rows.append(dict(tool="BioDynaMo", file=rel(p_v, repo) + "; " + rel(p_x, repo), unit_note="nm and nm/s in file",
                     plateau_um_per_s=float(vx[nz].mean() * 1e-3), active_from_s=float(t[nz].min()),
                     active_to_s=float(t[nz].max()), displacement_um=float(x[-1] * 1e-3), sampling_s=0.2))

    p = os.path.join(repo, "CompuTiX/external_impulse/results/external_impulse.yaml")
    c = yaml.safe_load(open(p))
    tt = np.array(c["t"]["values"], float)
    vi = np.array(c["v_implicit"]["values"], float)
    xi = np.array(c["x_implicit"]["values"], float)
    nz = np.abs(vi) > 1e-15
    rows.append(dict(tool="CompuTiX", file=rel(p, repo), unit_note="SI (m, m/s); implicit overdamped series",
                     plateau_um_per_s=float(vi[nz].mean() * 1e6), active_from_s=float(tt[nz].min()),
                     active_to_s=float(tt[nz].max()), displacement_um=float(xi[-1] * 1e6), sampling_s=0.1))

    p = pick(repo, "PhysiCell/results/mechanics_external_impulse/physicell_mechanics_external_impulse_data.csv",
             "PhysiCell/results/mechanics_external_impulse/dt_0.001/physicell_mechanics_external_impulse_data.csv")
    pc = pd.read_csv(p)
    nz = pc.mvx != 0
    rows.append(dict(tool="PhysiCell", file=rel(p, repo), unit_note="dt in min, x in um, mvx in um/min",
                     plateau_um_per_s=float(pc.mvx[nz].mean() / 60), active_from_s=float(pc.dt[nz].min() * 60),
                     active_to_s=float(pc.dt[nz].max() * 60), displacement_um=float(pc.x.iloc[-1]), sampling_s=0.06))

    p = os.path.join(repo, "Tisim/mechanics_external_impulse/mechanics_external_impulse.csv")
    ts = pd.read_csv(p)
    if "position(um)" in ts.columns:  # file of 19 October 2026: units in the header, position already in um
        ts = ts.rename(columns={"time(s)": "time", "position(um)": "position", "velocity(um/s)": "velocity"})
        pos_factor, note = 1.0, "units in header (s, um, um/s)"
    else:  # file of 30 September 2026: no units, position 100 times too large
        pos_factor, note = 0.01, "no units in file; velocity read as um/s, position multiplied by 0.01 (as in the notebook)"
    nz = ts.velocity != 0
    rows.append(dict(tool="TiSim", file=rel(p, repo), unit_note=note,
                     plateau_um_per_s=float(ts.velocity[nz].mean()), active_from_s=float(ts.time[nz].min()),
                     active_to_s=float(ts.time[nz].max()), displacement_um=float(ts.position.iloc[-1] * pos_factor), sampling_s=0.2))

    p_loc = pick(repo, "Chaste/MechanicsWithFriction/results/node_locations.dat", "Chaste/MechanicsWithFriction/node_locations.dat")
    p_vel = pick(repo, "Chaste/MechanicsWithFriction/results/cell_velocities.dat", "Chaste/MechanicsWithFriction/cell_velocities.dat")
    ch = pd.read_csv(p_loc, sep=r"\s+", header=None)
    chv = pd.read_csv(p_vel, sep=r"\s+", header=None)
    moving = ch[1] > 0
    rows.append(dict(tool="Chaste", file=rel(p_loc, repo) + "; " + rel(p_vel, repo),
                     unit_note=f"units not stated: position rises to {ch[1].max():g} units, velocity column 4 plateau "
                               f"{chv[4][chv[4] > 0].mean():.6g} units; excluded from the error comparison",
                     plateau_um_per_s=float("nan"), active_from_s=float(ch[0][moving].min()),
                     active_to_s=float(ch[0][ch[1] >= ch[1].max()].min()), displacement_um=float("nan"), sampling_s=0.2))

    df = pd.DataFrame(rows)
    df["plateau_rel_error_pct"] = 100 * (df.plateau_um_per_s - ref["plateau_um_per_s"]) / ref["plateau_um_per_s"]
    df["displacement_rel_error_pct"] = 100 * (df.displacement_um - ref["displacement_um"]) / ref["displacement_um"]
    df.to_csv(os.path.join(out, "mechanics_external_impulse.csv"), index=False)
    return df, ref


# ----------------------------------------------------------------------------------------
# 4: two-cell relaxation with the common extended Hertz model
# ----------------------------------------------------------------------------------------
E_PA, NU, R_M = 450.0, 0.4, 5e-6
E_STAR = 1.0 / (2.0 * (1.0 - NU**2) / E_PA)  # composite modulus of two identical cells (Pa)
R_TILDE = R_M / 2.0                          # effective radius of two equal spheres (m)
GAMMA_ADH = 8.56e-15                         # adhesion energy density used by the analysis notebook (J/m2)
DELTA0_M = 1e-6


def hertz_ode(drag: float, t_max: float, factor: float = 2.0, r_tilde: float = R_TILDE, prefactor: float = 4.0 / 3.0,
              gamma: float = GAMMA_ADH):
    """Overdamped relaxation d(delta)/dt = -factor * F(delta) / drag, delta in m, t in s."""
    def rhs(_t, y):
        d = max(y[0], 0.0)
        force = prefactor * E_STAR * np.sqrt(r_tilde) * d**1.5 - np.pi * gamma * r_tilde
        return [-factor * force / drag]
    return solve_ivp(rhs, (0.0, t_max), [DELTA0_M], rtol=1e-9, atol=1e-16, dense_output=True, max_step=t_max / 2000)


def load_hertz(repo: str, drag: float) -> dict:
    """Return {tool: (time_s, overlap_um, file)} for one drag value (0.01, 0.1 or 1)."""
    ds = "1" if drag == 1 else str(drag)
    out = {}
    p = os.path.join(repo, f"Biodynamo/mechanics_hertz_relaxation/results_drag_{ds}/positions.csv")
    df = pd.read_csv(p, sep=r"\t|,", header=None, engine="python")
    # column 0 is a row index; rows are 60 s apart (dt = 1 s, positions tracked every 60 steps),
    # except row 1, which is written after the first step (1 s); see the cross-check, section 3.2
    tb = df[0].values.astype(float) * 60.0
    if len(tb) > 1:
        tb[1] = 1.0
    out["BioDynaMo"] = (tb, np.maximum(0.0, 10.0 - (df[4] - df[1]).abs().values), p)

    p = os.path.join(repo, f"CompuTiX/overlap_relaxation/results/overlap_relaxation_mu_{ds}.yaml")
    c = yaml.safe_load(open(p))
    tc = np.array(c["t"]["values"], float)
    xc = np.array(c["Cells"]["values"]["x"]["values"], float)
    out["CompuTiX"] = (tc, np.maximum(0.0, 10.0 - np.abs(xc[:, 1] - xc[:, 0]) * 1e6), p)

    p = os.path.join(repo, f"PhysiCell/results/mechanics_pushing_extended_hertz/drag_{ds}/physicell_mechanics_pushing_extended_hertz.csv")
    pc = pd.read_csv(p)
    out["PhysiCell"] = (pc.time_min.values * 60.0, pc.overlap_um.values, p)

    p = os.path.join(repo, f"Tisim/mechanics_relaxation/data_drag_{ds}.csv")
    ts = pd.read_csv(p)
    out["TiSim"] = (ts.time_s.values.astype(float), np.maximum(0.0, 10.0 - ts.distance_10um.values * 10.0), p)

    if drag == 1:  # Chaste ran the largest friction coefficient only (as read by the notebook)
        p = pick(repo, "Chaste/HertzCellRelaxation/results/node_locations.dat", "Chaste/HertzCellRelaxation/node_locations.dat")
        ch = pd.read_csv(p, sep=r"\s+", header=None)
        out["Chaste"] = (ch[0].values.astype(float), np.maximum(0.0, 10.0 - (ch[4] - ch[1]).abs().values * 1e6), p)
    return out


def analyse_hertz(repo: str, out: str) -> pd.DataFrame:
    rows = []
    for drag in (0.01, 0.1, 1):
        data = load_hertz(repo, drag)
        t_max = max(v[0][-1] for v in data.values())
        sol = hertz_ode(drag, t_max)
        sol_nb = hertz_ode(drag, t_max, factor=1.0, r_tilde=0.5e-6)  # uncorrected notebook curve
        ode_t = sol.t
        ode_ov = sol.y[0] * 1e6
        for tool, (t, ov, path) in data.items():
            m = t <= 10800.0  # common window (the shortest run apart from CompuTiX lasts 3 h)
            rows.append(dict(
                drag_N_s_per_m=drag, tool=tool, file=rel(path, repo), samples=len(t), t_end_s=float(t[-1]),
                sampling_s=float(np.median(np.diff(t))) if len(t) > 2 else float("nan"),
                overlap_end_um=float(ov[-1]), distance_end_um=float(10.0 - ov[-1]),
                ode_overlap_at_t_end_um=float(sol.sol(t[-1])[0] * 1e6),
                t_half_overlap_s=first_time_below(t, ov, 0.5), ode_t_half_overlap_s=first_time_below(ode_t, ode_ov, 0.5),
                t_overlap_below_0p1um_s=first_time_below(t, ov, 0.1),
                ode_t_overlap_below_0p1um_s=first_time_below(ode_t, ode_ov, 0.1),
                mean_abs_dev_from_ode_um=float(np.mean(np.abs(ov[m] - sol.sol(t[m])[0] * 1e6))),
                mean_abs_dev_from_notebook_curve_um=float(np.mean(np.abs(ov[m] - sol_nb.sol(t[m])[0] * 1e6)))))
    df = pd.DataFrame(rows)
    df.to_csv(os.path.join(out, "mechanics_common_extended_hertz.csv"), index=False)
    return df


# ----------------------------------------------------------------------------------------
# 5: two-cell pushing with the built-in contact models
# ----------------------------------------------------------------------------------------
def analyse_builtin(repo: str, out: str) -> pd.DataFrame:
    rows = []
    p = os.path.join(repo, "Biodynamo/mechanics_pushing/results_timestep0.1/positions.csv")
    df = pd.read_csv(p, sep=r"\t|,", header=None, engine="python")
    d = (df[4] - df[1]).values
    rows.append(dict(tool="BioDynaMo", file=rel(p, repo), length_unit_note="um", start_distance_um=30.0,
                     min_distance_um=float(d.min()), t_min="step %d" % int(np.argmin(d)),
                     final_distance_um=float(d[-1]), t_final="step %d (10 min at dt = 0.1 min)" % (len(d) - 1)))

    p = pick(repo, "Chaste/mechanics_pushing/results/results.viznodelocations")
    if os.path.exists(p):
        ch = pd.read_csv(p, sep=r"\t| ", header=None, engine="python")
        dch = (ch[4] - ch[1]).abs().values
        rows.append(dict(tool="Chaste", file=rel(p, repo),
                         length_unit_note="dimensionless; multiplied by 10 as in olderplotscripts/plot_mechanics_pushing.py",
                         start_distance_um=float(dch[0] * 10), min_distance_um=float(dch.min() * 10),
                         t_min="%g time units" % ch[0][np.argmin(dch)], final_distance_um=float(dch[-1] * 10),
                         t_final="%g time units (5 min if hours)" % ch[0].iloc[-1]))
    else:
        rows.append(dict(tool="Chaste", file=rel(p, repo) + " (absent)",
                         length_unit_note="not computable: results file absent at this commit (deleted on 24 October 2026)",
                         start_distance_um=float("nan"), min_distance_um=float("nan"), t_min="",
                         final_distance_um=float("nan"), t_final=""))



    p = pick(repo, "CompuTiX/mechanics_pushing/results/mechanics_pushing.yaml")
    c = yaml.safe_load(open(p))
    t = np.array(c["t"]["values"], float)
    x = np.array(c["Cells"]["values"]["x"]["values"], float)
    d = np.abs(x[:, 1] - x[:, 0]) * 1e6
    rows.append(dict(tool="CompuTiX", file=rel(p, repo), length_unit_note="m in file; overdamped JKR run matching main.cpp",
                     start_distance_um=float(d[0]), min_distance_um=float(d.min()), t_min="%g s" % t[np.argmin(d)],
                     final_distance_um=float(d[-1]), t_final="%g s" % t[-1]))

    rows.append(dict(tool="PhysiCell", file="PhysiCell/results/mechanics_pushing/ (snapshots only)",
                     length_unit_note="not computable: no derived CSV and the .mat payload is gitignored",
                     start_distance_um=9.0, min_distance_um=float("nan"), t_min="", final_distance_um=float("nan"), t_final=""))

    p = os.path.join(repo, "Tisim/mechanics_pushing/mechanics_pushing.csv")
    tp = pd.read_csv(p)
    d = tp["distance (um)"].values
    tt = tp["time (min)"].values
    rows.append(dict(tool="TiSim", file=rel(p, repo), length_unit_note="um; approach stopped at 9.0 um",
                     start_distance_um=float(d[0]), min_distance_um=float(d.min()), t_min="%g min" % tt[np.argmin(d)],
                     final_distance_um=float(d[-1]), t_final="%g min" % tt[-1]))
    p = os.path.join(repo, "Tisim/mechanics_pushing/mechanical pushing.csv")
    if os.path.exists(p):
        tp = pd.read_csv(p)
        d = tp["distance (um)"].values
        tt = tp["time (min)"].values
        rows.append(dict(tool="TiSim (older run, force never removed)", file=rel(p, repo), length_unit_note="um",
                         start_distance_um=float(d[0]), min_distance_um=float(d.min()), t_min="%g min" % tt[np.argmin(d)],
                         final_distance_um=float(d[-1]), t_final="%g min" % tt[-1]))
    df = pd.DataFrame(rows)
    df["residual_overlap_um"] = 10.0 - df.final_distance_um
    df.to_csv(os.path.join(out, "mechanics_builtin_pushing.csv"), index=False)
    return df


# ----------------------------------------------------------------------------------------
# 6: fixed-duration cell cycle
# ----------------------------------------------------------------------------------------
def cycle_summary(tool, t_h, vol, path, repo, note=""):
    t_h = np.asarray(t_h, float)
    vol = np.asarray(vol, float)
    v0 = vol[0]
    imax = int(np.argmax(vol))
    drops = np.where((vol[1:] - vol[:-1]) < -0.25 * v0)[0]
    return dict(tool=tool, file=rel(path, repo) if os.path.isabs(path) else path, note=note, samples=len(vol),
                t_first_h=float(t_h[0]), t_last_h=float(t_h[-1]), V0=float(v0), Vmax=float(vol[imax]),
                Vmax_pct_of_V0=float(100 * vol[imax] / v0), t_Vmax_h=float(t_h[imax]),
                division_events=";".join(f"{t_h[i]:.3f}->{t_h[i + 1]:.3f}" for i in drops))


def analyse_cell_cycle(repo: str, out: str) -> pd.DataFrame:
    rows = []
    p = pick(repo, "Biodynamo/fixed_cell_cycle/results/cell-0.csv", "Biodynamo/fixed_cell_cycle/new_results/cell-0-sim1.csv")
    bd = pd.read_csv(p, header=None, names=["t", "V", "phase", "age"])
    rows.append(cycle_summary("BioDynaMo", bd.t, bd.V, p, repo, "mother cell; time in hours, volume in um3"))

    p = pick(repo, "Chaste/FixedCellCycle/results/cellcycle_fixed.dat", "Chaste/fixed_cell_cycle/results/cellcycle_fixed.dat")
    recs = []
    for line in open(p):
        f = line.split()
        if f:
            recs.append((float(f[0]), float(f[11])))  # time and volume of the first cell record (11 fields per cell)
    ch = np.array(recs)
    rows.append(cycle_summary("Chaste", ch[:, 0], ch[:, 1], p, repo, "first cell record; dimensionless volume"))

    p = os.path.join(repo, "CompuTiX/fixed_cell_cycle/results/cell_volume.yaml")
    cx = yaml.safe_load(open(p))
    tcx = np.array(cx["time"]["values"], float)
    rows.append(cycle_summary("CompuTiX", tcx, np.array(cx["volume_per_parent_cell"]["values"], float), p, repo,
                              "volume_per_parent_cell (the simulation; the notebook plots data/cell_cycle.csv, which is the reference)"))
    rows.append(cycle_summary("CompuTiX (volume_per_child_cell)", tcx, np.array(cx["volume_per_child_cell"]["values"], float),
                              p, repo, "per daughter during division, hence no drop"))

    p = os.path.join(repo, "PhysiCell/results/cell_cycle_fixed/cell_volumes.csv")
    pc = pd.read_csv(p)
    pc0 = pc[pc.id == 0].sort_values("dt")
    rows.append(cycle_summary("PhysiCell", pc0.dt / 60.0, pc0.total_volume, p, repo, "cell id 0; 30 min sampling; um3"))

    p = os.path.join(repo, "Tisim/fixed_cell_cycle/cell cycle fix.csv")
    ts = pd.read_csv(p)
    rows.append(cycle_summary("TiSim (file used in Figure 4B)", ts["time (hour)"], ts["cell 1 volume"], p, repo,
                              "relative volume; phase-resolved output (0.48 h sampling) since commit 6aa51a3, hourly export before"))
    p = os.path.join(repo, "Tisim/results/cell cycle fix.csv")
    if os.path.exists(p):
        ts2 = pd.read_csv(p)
        rows.append(cycle_summary("TiSim (phase-resolved file)", ts2["time (hour)"], ts2["cell 1 volume"], p, repo,
                                  "relative volume, 0.48 h sampling, with phase labels"))

    p = pick(repo, "ResultAnalysis/analytical_solutions/experimental_data/Cell cycle volume dynamics.txt",
             "experimental_data/Cell cycle volume dynamics.txt", "analytical_solutions/experimental_data/Cell cycle volume dynamics.txt")
    ref = pd.read_csv(p, sep="\t")
    rows.append(cycle_summary("Reference data", ref.Hours, ref["total_volume (um^3)"], p, repo,
                              "reference trajectory of Figure 4B; identical to CompuTiX/fixed_cell_cycle/data/cell_cycle.csv"))
    df = pd.DataFrame(rows)
    df.to_csv(os.path.join(out, "cell_cycle.csv"), index=False)
    return df


# ----------------------------------------------------------------------------------------
# 7: monolayer growth use case
# ----------------------------------------------------------------------------------------
def analyse_monolayer(repo: str, out: str) -> tuple[pd.DataFrame, dict]:
    p_ref = pick(repo, "ResultAnalysis/analytical_solutions/experimental_data/2D monolayer data from Bru et al 1998.txt",
                 "experimental_data/2D monolayer data from Bru et al 1998.txt",
                 "analytical_solutions/experimental_data/2D monolayer data from Bru et al 1998.txt")
    ref = pd.read_csv(p_ref, sep="\t")
    ref_t = ref["Total time (hours)"].values / 24.0
    ref_d = ref["Diameter (um)"].values.astype(float)
    ref_info = dict(file=rel(p_ref, repo), days=ref_t.tolist(), diameters_um=ref_d.tolist())
    t_lo, t_hi = ref_t[0], ref_t[-1]

    def dev(tool, t_d, d, path, cells_first=None, cells_last=None, note=""):
        t_d = np.asarray(t_d, float)
        d = np.asarray(d, float)
        m = (t_d >= t_lo) & (t_d <= t_hi)
        interp = np.interp(t_d[m], ref_t, ref_d)
        dv = d[m] - interp
        i14 = int(np.argmin(np.abs(t_d - 14.0)))
        return dict(tool=tool, file=rel(path, repo), note=note, samples_in_window=int(m.sum()),
                    d_at_day14_um=float(d[i14]), day_of_last_sample=float(t_d[-1]), d_last_um=float(d[-1]),
                    deviation_min_um=float(dv.min()), deviation_max_um=float(dv.max()), deviation_mean_um=float(dv.mean()),
                    deviation_mean_abs_um=float(np.abs(dv).mean()), deviation_max_abs_um=float(np.abs(dv).max()),
                    deviation_max_abs_pct=float(100 * np.abs(dv).max() / interp[np.argmax(np.abs(dv))]),
                    cells_first=int(cells_first) if cells_first is not None else None,
                    cells_last=int(cells_last) if cells_last is not None else None)

    rows = []
    p = os.path.join(repo, "Biodynamo/monolayer/results/monolayer_growth.json")
    bj = json.load(open(p))
    series = {d["first"]: d["second"] for d in bj["data_"]}
    rows.append(dev("BioDynaMo (env_dims, the series plotted by plot_monolayer.py)", series["env_dims"]["x_values"],
                    series["env_dims"]["y_values"], p, series["total_cells"]["y_values"][0], series["total_cells"]["y_values"][-1],
                    "uniform-grid extent in 40 um steps"))
    rows.append(dev("BioDynaMo (tumor_diameter, cell-centre extent)", series["tumor_diameter"]["x_values"],
                    series["tumor_diameter"]["y_values"], p, series["total_cells"]["y_values"][0],
                    series["total_cells"]["y_values"][-1], "max of x and y extent of cell centres"))

    p = pick(repo, "Chaste/MonolayerUseCase/results/monolayer.dat", "Chaste/monolayer/results/monolayer.dat")
    ch = np.loadtxt(p, delimiter=",")
    rows.append(dev("Chaste", ch[:, 0] / 24.0, ch[:, 1], p, int(ch[0, 2]), int(ch[-1, 2]), "undocumented run (monolayer_readme.txt)"))

    p = os.path.join(repo, "CompuTiX/monolayer/results/monolayer.yaml")
    cx = yaml.safe_load(open(p))
    rows.append(dev("CompuTiX", np.array(cx["time"]["values"], float) / 24.0, np.array(cx["d"]["values"], float), p,
                    cx["N"]["values"][0], cx["N"]["values"][-1], "largest pairwise centre distance"))

    rows.append(dict(tool="PhysiCell", file="PhysiCell/results/monolayer/monolayer_t_diam.csv (absent)",
                     note="not computable: derived CSV absent, .mat payload gitignored, archived run stops at day 16.08"))

    p = os.path.join(repo, "Tisim/monolayer/2D disk.csv")
    ts = pd.read_csv(p)
    rows.append(dev("TiSim", ts["time (day)"], ts["diameter (um)"], p, int(ts["number"].iloc[0]), int(ts["number"].iloc[-1]),
                    "twice the population radius"))
    df = pd.DataFrame(rows)
    df.to_csv(os.path.join(out, "monolayer.csv"), index=False)
    return df, ref_info


# ----------------------------------------------------------------------------------------
# Markdown summary in the Table 1 format
# ----------------------------------------------------------------------------------------
def rng(values, fmt):
    v = np.asarray([x for x in values if np.isfinite(x)], float)
    return f"{fmt.format(v.min())} to {fmt.format(v.max())}"


def write_summary(out, repo, decay, decay_fin, decay_ref, upt, upt_fin, upt_ref, imp, imp_ref, eh, bi, cc, mono, mono_ref):
    L = []
    L.append("# Table 1 quantities recomputed from the repository\n")
    L.append(f"Repository: `{repo}`. Criteria and unit conventions are documented in the header of `table1_summary.py`.\n")

    for name, fin, ref, allr in (("Reaction-diffusion, decay", decay_fin, decay_ref, decay),
                                 ("Reaction-diffusion, twelve point sinks", upt_fin, upt_ref, upt)):
        L.append(f"## {name}\n")
        L.append(f"Analytical reference `{ref['file']}` at {ref['t_end_min']:g} min: average {ref['average_uM']:.4f} uM, "
                 f"centre {ref['centre_uM']:.4f} uM; analytical steady state (1 %) at {ref['t_ss_average_min']:.2f} min "
                 f"(average) and {ref['t_ss_centre_min']:.2f} min (centre).\n")
        L.append("| Tool, finest run | Average at t_end (uM) | Rel. error (%) | Centre at t_end (uM) | Centre rel. error (%) | "
                 "t_ss average (min) | t_ss centre (min) | File |")
        L.append("|---|---|---|---|---|---|---|---|")
        for _, r in fin.iterrows():
            L.append(f"| {r.run} | {r.average_uM:.4f} | {r.average_rel_error_pct:+.2f} | {r.centre_uM:.4f} | "
                     f"{r.centre_rel_error_pct:+.2f} | {r.t_ss_average_min:.2f} | {r.t_ss_centre_min:.2f} | `{r.file}` |")
        L.append("")
        L.append(f"Across the five finest runs: average {rng(fin.average_uM, '{:.2f}')} uM against {ref['average_uM']:.2f} uM "
                 f"(relative errors {fin.average_rel_error_pct.min():+.2f} % to {fin.average_rel_error_pct.max():+.2f} %, largest "
                 f"magnitude {fin.average_rel_error_pct.abs().max():.2f} %); centre {rng(fin.centre_uM, '{:.2f}')} uM against "
                 f"{ref['centre_uM']:.2f} uM (magnitudes {fin.centre_rel_error_pct.abs().min():.2f} % to "
                 f"{fin.centre_rel_error_pct.abs().max():.2f} %); steady state at {rng(fin.t_ss_average_min, '{:.1f}')} min "
                 f"against {ref['t_ss_average_min']:.1f} min.\n")
        L.append("Average-concentration relative error at t_end for every resolution (coarsest to finest):\n")
        for tool in TOOLS:
            sub = allr[allr.tool == tool].copy()
            sub["dx"] = sub.run.str.extract(r"dx=([\d.]+)").astype(float)
            sub = sub.sort_values("dx", ascending=False)
            L.append(f"- {tool}: " + "; ".join(f"dx = {r.dx:g} um: {r.average_rel_error_pct:+.2f} % (centre {r.centre_rel_error_pct:+.2f} %)"
                                                for _, r in sub.iterrows()))
        L.append("")

    L.append("## Mechanics, external impulse\n")
    L.append(f"Analytical reference `{imp_ref['file']}`: plateau velocity {imp_ref['plateau_um_per_s']:.6e} um/s "
             f"({imp_ref['plateau_um_per_s'] * 60:.4g} um/min), displacement {imp_ref['displacement_um']:.6e} um.\n")
    L.append("| Tool | Plateau (um/s) | Rel. error (%) | Active window (s) | Displacement (um) | Rel. error (%) | Notes |")
    L.append("|---|---|---|---|---|---|---|")
    for _, r in imp.iterrows():
        pl = f"{r.plateau_um_per_s:.6e}" if np.isfinite(r.plateau_um_per_s) else "n/a"
        pe = f"{r.plateau_rel_error_pct:+.2f}" if np.isfinite(r.plateau_rel_error_pct) else "n/a"
        di = f"{r.displacement_um:.4e}" if np.isfinite(r.displacement_um) else "n/a"
        de = f"{r.displacement_rel_error_pct:+.2f}" if np.isfinite(r.displacement_rel_error_pct) else "n/a"
        L.append(f"| {r.tool} | {pl} | {pe} | {r.active_from_s:g} to {r.active_to_s:g} | {di} | {de} | {r.unit_note} |")
    L.append("")

    L.append("## Mechanics, two-cell relaxation with the common extended Hertz law\n")
    L.append(f"Reference ODE: d(delta)/dt = -2 F/zeta, F = (4/3) E* sqrt(R~) delta^1.5 - pi gamma R~, E* = {E_STAR:.2f} Pa, "
             f"R~ = {R_TILDE * 1e6:g} um, gamma = {GAMMA_ADH:g} J/m2; equilibrium overlap "
             f"{(3 * np.pi * GAMMA_ADH * np.sqrt(R_TILDE) / (4 * E_STAR)) ** (2 / 3) * 1e6:.2e} um.\n")
    L.append("| Drag (N s/m) | Tool | Overlap at t_end (um) | ODE at t_end (um) | t_half tool / ODE (s) | t(overlap < 0.1 um) (s) | "
             "Mean abs. dev. from ODE, t <= 3 h (um) | Mean abs. dev. from notebook curve (um) | t_end (s) | File |")
    L.append("|---|---|---|---|---|---|---|---|---|---|")
    for _, r in eh.iterrows():
        L.append(f"| {r.drag_N_s_per_m:g} | {r.tool} | {r.overlap_end_um:.3g} | {r.ode_overlap_at_t_end_um:.3g} | "
                 f"{r.t_half_overlap_s:g} / {r.ode_t_half_overlap_s:.1f} | {r.t_overlap_below_0p1um_s:g} | "
                 f"{r.mean_abs_dev_from_ode_um:.4f} | {r.mean_abs_dev_from_notebook_curve_um:.4f} | {r.t_end_s:g} | `{r.file}` |")
    L.append("")
    d1 = eh[eh.drag_N_s_per_m == 1]
    L.append("At 1 N s/m: time to halve the overlap " + "; ".join(f"{r.tool} {r.t_half_overlap_s:g} s" for _, r in d1.iterrows())
             + f"; ODE {d1.ode_t_half_overlap_s.iloc[0]:.1f} s. Final centre-to-centre distances at 1 N s/m: "
             + "; ".join(f"{r.tool} {r.distance_end_um:.4f} um at {r.t_end_s:g} s" for _, r in d1.iterrows()) + ".\n")

    L.append("## Mechanics, pushing with the built-in contact models\n")
    L.append("| Tool | Start (um) | Minimum distance (um) at | Final distance (um) at | Residual overlap (um) | Notes | File |")
    L.append("|---|---|---|---|---|---|---|")
    for _, r in bi.iterrows():
        mn = f"{r.min_distance_um:.4f} ({r.t_min})" if np.isfinite(r.min_distance_um) else "n/a"
        fn = f"{r.final_distance_um:.4f} ({r.t_final})" if np.isfinite(r.final_distance_um) else "n/a"
        ro = f"{r.residual_overlap_um:.4f}" if np.isfinite(r.residual_overlap_um) else "n/a"
        L.append(f"| {r.tool} | {r.start_distance_um:g} | {mn} | {fn} | {ro} | {r.length_unit_note} | `{r.file}` |")
    L.append("")

    L.append("## Cell cycle and volume growth\n")
    L.append("| Tool | V0 | Vmax (% of V0) at (h) | Division events (h) | Samples, span (h) | Notes | File |")
    L.append("|---|---|---|---|---|---|---|")
    for _, r in cc.iterrows():
        L.append(f"| {r.tool} | {r.V0:g} | {r.Vmax:.5g} ({r.Vmax_pct_of_V0:.1f} %) at {r.t_Vmax_h:.2f} | {r.division_events or 'none'} | "
                 f"{r.samples}, {r.t_first_h:g} to {r.t_last_h:g} | {r.note} | `{r.file}` |")
    sims = cc[cc.tool.isin(["BioDynaMo", "Chaste", "CompuTiX", "PhysiCell", "TiSim (file used in Figure 4B)"])]
    L.append("")
    L.append(f"Maximum volume across the five tools (TiSim file used in Figure 4B): {sims.Vmax_pct_of_V0.min():.1f} % to "
             f"{sims.Vmax_pct_of_V0.max():.1f} % of V0.\n")

    L.append("## Monolayer growth use case\n")
    L.append(f"Reference `{mono_ref['file']}`: diameters {mono_ref['diameters_um']} um at days "
             f"{[round(x, 2) for x in mono_ref['days']]}.\n")
    L.append("| Tool | d at day 14 (um) | d at last sample (um, day) | Deviation range (um) | Mean abs. dev. (um) | "
             "Max abs. dev. (um, % of reference) | Cells first to last | Notes | File |")
    L.append("|---|---|---|---|---|---|---|---|---|")
    for _, r in mono.iterrows():
        if pd.isna(r.get("d_at_day14_um", np.nan)):
            L.append(f"| {r.tool} | n/a | n/a | n/a | n/a | n/a | n/a | {r.note} | `{r.file}` |")
            continue
        L.append(f"| {r.tool} | {r.d_at_day14_um:.0f} | {r.d_last_um:.0f} (day {r.day_of_last_sample:.2f}) | "
                 f"{r.deviation_min_um:+.1f} to {r.deviation_max_um:+.1f} | {r.deviation_mean_abs_um:.1f} | "
                 f"{r.deviation_max_abs_um:.1f} ({r.deviation_max_abs_pct:.2f} %) | {int(r.cells_first)} to {int(r.cells_last)} | {r.note} | `{r.file}` |")
    L.append("")
    with open(os.path.join(out, "table1_summary.md"), "w") as f:
        f.write("\n".join(L) + "\n")
    return "\n".join(L)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--repo", default=None, help="repository root")
    ap.add_argument("--out", default=None, help="output folder")
    args = ap.parse_args(argv)
    repo = args.repo or find_repo(os.path.dirname(os.path.abspath(__file__))) or find_repo(os.getcwd())
    if repo is None or not os.path.isdir(os.path.join(repo, "ResultAnalysis")):
        sys.exit("repository root not found; pass --repo")
    out = args.out or os.path.join(repo, "ResultAnalysis", "table1_summary")
    os.makedirs(out, exist_ok=True)
    print(f"repository: {repo}\noutput folder: {out}")

    decay, decay_fin, decay_ref = analyse_diffusion(repo, "decay", out)
    upt, upt_fin, upt_ref = analyse_diffusion(repo, "uptake", out)
    imp, imp_ref = analyse_impulse(repo, out)
    eh = analyse_hertz(repo, out)
    bi = analyse_builtin(repo, out)
    cc = analyse_cell_cycle(repo, out)
    mono, mono_ref = analyse_monolayer(repo, out)
    text = write_summary(out, repo, decay, decay_fin, decay_ref, upt, upt_fin, upt_ref, imp, imp_ref, eh, bi, cc, mono, mono_ref)
    print(text)


if __name__ == "__main__":
    main()
