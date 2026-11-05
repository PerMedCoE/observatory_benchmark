# Thaleia's priority plan (from 3 November 2026)

Basis: self-test run at commit 8ee428e8d (4 November, current HEAD), file 14 (manuscript check 22 October), file 15 (session summary 2 November), file 16 (developer follow-up 2 November), email responses (incorporated 3 November). No outreach to Arnau. Tasks are grouped into what can be done now versus what is blocked on developers.

Previous self-test run was at commit d2093f516 (3 November). The baseline remains frozen at commit 6aa51a3 (30 September) — the expected values as quoted in the v7 manuscript.

---

## Changelog from email responses (incorporated 3 November)

The following developer replies arrived and change the plan:

**Nicolò (BioDynaMo) — confirmed:**
- All tests rerun at v1.05.158-c4704305 (single version for the whole paper).
- Three friction folders rerun into `results_drag_0.01`, `results_drag_0.1`, `results_drag_1` — these are now the correct runs.
- Scheme: FD + explicit Euler on a uniform grid; no default lower threshold. README updated at commit af94af6.
- Overdamped dynamics: only the external impulse test uses the overdamped equation v = F/µ. All other tests use the standard velocity-Verlet update v(n+1) = v(n) - f_c Δt (including the relaxation tests).
- `tumor_diameter` agreed for the monolayer plot; updated data and plots pushed with both metrics.

**Ryan (BioDynaMo diffusion) — confirmed:**
- Time steps: 6 and 12 voxels → 0.01 min for 1,000 steps; 24 and 48 voxels → 0.001 min for 10,000 steps.
- No clamping applied; no negative concentrations occurred.

**James Osborne (Chaste) — partial:**
- Confirmed: velocity in cell_velocities.dat is out by a factor of 10.
- Asked: "Can you send the position one. Is that also out?" → **Thaleia to send James the position file `node_locations.dat` from MechanicsWithFriction/results/.**

**Jieling Zhao (TiSim) — confirmed:**
- Code availability: use Dirk's INRIA email address.
- Fixed cell-cycle SD = 0 (not 2 h). The 2 h SD applies only to the monolayer/stochastic tests.
- Random motility off for all mechanical tests (impulse and 2-cell push).
- Friction equation of motion: `Mu_(cell-ECM) * v_i + sum_j((v_i - v_j) * Mu_(cell-cell)) = sum_j(F_ij) + F_i`; cell-ECM friction dominates. Built-in contact test uses drag = 0.01 N s m⁻¹.
- Diffusion time step: `dt = 0.1 * (L/N)^2 / (6D)` for stability; uptake dt = 0.1 min; impulse and cell-cycle use a dynamic dt (halved until displacement per step < 0.1 × cell radius).
- Growth law: cubic root of the volume curve mapped to the experimental curve (not linear as assumed in question 8.20).

**CompuTiX (Jirka and Matteo via Arnau's email) — new issue:**
- Adhesion energy 10⁻⁴ J m⁻² per cell confirmed; JKR convention (per-contact) confirmed.
- **Impulse mass issue:** `main.cpp` comment now gives 0.001 μm min⁻¹ whereas 1.67 × 10⁻¹⁰ m s⁻¹ is 0.01 μm min⁻¹. Sphere mass changed from 0.01 to 1 kg in the code while `impulse_benchmark.yaml` is still the June run. They must confirm which mass the archived results used and rerun if the code now differs.
- Archived run applies force for 31 steps (3.1 to 6.1 s) → displacement 0.517 nm, not 0.500 nm as currently in the text.
- Zenodo DOI pending; they will rerun all simulations before release.

---

## Meta-test run results — commit 8ee428e8d (4 November 2026)

Run against baseline 6aa51a3. Scripts are in `meta_test/` (not `ResultAnalysis/`). Rerun command:

    cd ~/Work/observatory_benchmark
    COMMIT=$(git log -1 --format='%h')
    python meta_test/table1_summary.py --repo . --out /tmp/table1_${COMMIT}
    python meta_test/compare_table1.py \
        meta_test/baseline_6aa51a3 /tmp/table1_${COMMIT} \
        --out /tmp/table1_${COMMIT}/comparison_vs_6aa51a3.md

Summary of what moved:

| Table | Values moved | Rows lost | Cause |
|---|---|---|---|
| diffusion_decay_finest.csv | 0 | 1 (CompuTiX) | CompuTiX diffusion files not found — see B9 |
| diffusion_uptake_finest.csv | 0 | 1 (CompuTiX) | same |
| diffusion_decay_all_runs.csv | 0 | 4 (all CompuTiX) | same |
| diffusion_uptake_all_runs.csv | 0 | 4 (all CompuTiX) | same |
| mechanics_external_impulse.csv | 4 | 0 | PhysiCell path change (minor timing); TiSim/Chaste unit notes only |
| mechanics_common_extended_hertz.csv | 13 | 0 | BioDynaMo 4/3 fix — all expected; B1 covers them |
| mechanics_builtin_pushing.csv | 11 | 0 | BioDynaMo min_dist 8→8.395 μm; Chaste absent (D.O.); CompuTiX rounding |
| cell_cycle.csv | 0 | 0 | Path normalisation only; all values stable |
| monolayer.csv | 9 | 0 | BioDynaMo tumor_diameter series (D4 fix); new values listed below |

**Confirmed OK — no manuscript action:**
- Diffusion (all tools except CompuTiX missing): zero values moved. Chaste files now read from `results/` subfolder correctly.
- Cell cycle: stable across all tools.
- Hertz relaxation, BioDynaMo: all 13 moves are the 4/3 prefactor correction, already captured in B1. Key values: t½ at 1 N s m⁻¹ = 840 s (was 1,080 s); mean abs. dev. from ODE at 1 N s m⁻¹ = 0.005 μm (was 0.043 μm). ✓

**New issues found (need action):**

1. **CompuTiX diffusion rows absent** — all CompuTiX rows disappeared from both diffusion tables, finest and all-resolutions. The script cannot find the CompuTiX diffusion result files at the current commit. See new item B9.

2. **BioDynaMo built-in pushing min distance: 8.000 → 8.395 μm (+4.9%)** — the manuscript and Figure 3F may quote 8 μm. The new value is 8.4 μm. See new item B10.

3. **BioDynaMo monolayer tumor_diameter series** — new values at 8ee428e8d: final diameter 2902 μm (was 2909 μm), max absolute deviation 131 μm (5.68% of reference), mean abs deviation 80 μm. The env_dims series still gives max deviation 8.77%. Once D4 switches Figure 5 to tumor_diameter, the quoted deviation drops from 8.8% to 5.7%. Update abstract item B2 accordingly.

4. **PhysiCell external impulse timing: minor path-induced change** — active_from_s 3.06→3.00 s, active_to_s 6.00→5.94 s. These arise because the PhysiCell file moved out of the `dt_0.001/` subdirectory. If the manuscript quotes these timing values, update to 3 and 5.94 s, or round to "3 to 6 s" which is unchanged.

5. **TiSim unit note updated** — file now has explicit units in header (s, μm, μm/s). No manuscript action; just confirms the file is now self-documenting.

6. **Chaste built-in pushing absent** — confirmed by test; blocked on James (see C).

---

## A. Meta-test — make it a permanent part of the repository

The two-script regression layer (table1_summary.py + compare_table1.py) is already working locally. Scripts are in `meta_test/` in the repository.

**A1 — NOW.** Commit and push the meta-test scripts branch (`add-meta-test`) with the corrected workflow file. The scripts are already in `meta_test/` — no internal changes needed.

**A2 — NOW.** Add a GitHub Actions workflow at `.github/workflows/metatest.yml`:

```yaml
name: table1-regression
on: [push, pull_request]
jobs:
  regression:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-python@v5
        with:
          python-version: "3.12"
      - name: Install dependencies
        run: pip install -r meta_test/requirements.txt
      - name: Recompute Table 1 values
        run: python meta_test/table1_summary.py --repo . --out /tmp/run
      - name: Compare against baseline
        run: |
          python meta_test/compare_table1.py \
            meta_test/baseline_6aa51a3 /tmp/run \
            --out /tmp/run/comparison.md
          cat /tmp/run/comparison.md
```

Note: CI will currently exit with status 1 (red) because of the BioDynaMo and monolayer moved values. That is correct behaviour — it is flagging real differences between HEAD and the manuscript baseline. The check turns green once the baseline is replaced simultaneously with the manuscript text.

**A3 — ONGOING.** Update the baseline whenever a manuscript value is accepted.

When a developer pushes a corrected run and the new value is accepted, regenerate the baseline from that commit and replace `meta_test/baseline_6aa51a3/` in the same pull request as the manuscript text change.

---

## B. Main manuscript — can be done now

**B1 — BioDynaMo common contact law. CONFIRMED BY SELF-TEST.**

In the Results, replace:
> "BioDynaMo relaxed 1.3 to 1.5 times more slowly (1,080 s), consistent with a force prefactor of 1 rather than 4/3 in its implementation of the common law [VERIFY: rerun, or report as an implementation difference, question 8.6]"

with:
> "BioDynaMo followed the reference with a mean absolute deviation below 0.01 μm at all three friction values, after correcting a force prefactor of 4/3 that had been evaluated as 1 in an earlier run; at 1 N s m⁻¹ it halved the overlap in 840 s against 741 s."

In Table 1 (common contact law row):
- Change "BioDynaMo 1,080 s" → "840 s"
- Add BioDynaMo to "mean absolute deviation below 0.01 μm for CompuTiX, PhysiCell and Chaste" → "for BioDynaMo, CompuTiX, PhysiCell and Chaste"
- Remove the [VERIFY] on question 8.6

In the Discussion, only TiSim now shows slower relaxation (approximately three times at 1 N s m⁻¹). Remove BioDynaMo from that sentence; keep the [VERIFY] pending Jieling's confirmation of the velocity computation.

**B2 — Abstract: trim from 166 to ≤150 words.**

File 14 section 2 gives a proposed 143-word abstract. Use it as the starting point. The four claims that need correcting are: "within 5%" → "domain-averaged concentrations within 5%"; remove the claim that "all tools reproduced the monolayer expansion" (PhysiCell data still missing); remove or qualify the equilibrium spacing claim (excludes PhysiCell and assumes the Chaste length unit); soften "have never been compared" to "have not been systematically compared under identical conditions".

Also: restore "Virtual Human Twins" (capitalised, project terminology); put back the availability sentence (GitHub, Zenodo, OpenEBench).

Note on BioDynaMo monolayer: once D4 switches Figure 5 to the tumor_diameter series, BioDynaMo's max deviation drops from 8.8% to 5.7%. If the abstract is drafted before D4, write "deviates up to 9%" and update after D4.

**B3 — Typos and errors from file 14, section 3.**

| Location | Error | Fix |
|---|---|---|
| Line 47 | "in space is response" | "in response" |
| Line 47 | "neighbouring cells (agents)" | "cells (agents), represented as computational agents," — define once |
| Line 53 | "and and they are" | delete one "and" |
| Line 53 | "the benchmarks documents" | "the benchmark documents" |
| Line 89 | "twelve point-sinks evenly distributed" | "twelve point sinks arranged around the centre in the plane z = 0" |
| Line 89 | garbled sentence on analytical solutions | "Both problems have analytical solutions, with which the finest-grid run of each tool was compared over 10 min (Methods)." |
| Line 111 | stray closing parenthesis after "7.2 kg min⁻¹)" | remove |
| Line 113 | "are let to interact" | "interact" |
| Lines 113–115 | mixed tense (agents positioned / approached / were released) | past tense throughout |
| Line 165 | "BioDynamo" | "BioDynaMo" |
| Line 175 | "tied to public infrastructure²⁴˒³⁸, As CASP" | "tied to public infrastructure²⁴˒³⁸, as CASP²⁵ and the MEMOTE test suite³⁹ illustrate." |
| Table 1 caption | "Unit tests of the benchmark"; header "Unit Test" | "Tests of the benchmark"; header "Test" |
| Methods line 203 | superscript 13 reads as exponent on π γ R̃ | move the citation after "extended Hertz law" |

**B4 — Fix three wrong citation numbers (file 14, section 5).**

After the CompuTiX reference was removed the numbers shifted, but three citations were not updated:
- Table 1 (monolayer row) and Figure 5 legend: "Brú et al.³³" → "Brú et al.³²"
- Methods, cell-cycle test: "MultiCellDS³⁴" → "MultiCellDS³³"
- Discussion: reference 46 cited before 45 — renumber so the order of first citation holds.

Also from file 14: reference 42 (Bunne et al. 2024) may be published in Cell 187, 7045–7063; verify. Reference 7 (Mongeon et al. 2024) gives pages 1–13 — find the article number.

**B5 — Methods updates from confirmed developer replies.**

All of the following are now confirmed and can be added to Methods:

- BioDynaMo diffusion time steps: "0.01 min at 40 and 20 μm and 0.001 min at 10 and 5 μm in BioDynaMo" (confirmed by Ryan and Nicolò). Chaste and TiSim still open.
- BioDynaMo negative concentrations: "BioDynaMo applies no clamping, and no negative concentrations occurred (minima: 2.9 μM decay, 3.9 μM uptake)."
- BioDynaMo overdamped dynamics: only the external impulse test uses the overdamped equation v = F/µ; all other BioDynaMo tests use the standard velocity update v(n+1) = v(n) - f_c Δt. Write this explicitly in the impulse Methods section.
- TiSim negative concentrations: "TiSim switches off uptake at zero concentration through a Heaviside factor."
- TiSim dynamic time step in impulse and cell-cycle: "TiSim uses an adaptive time step, halved until displacement per step is below 0.1 times the cell radius."
- Adhesion energy γ: "8.56 × 10⁻¹⁵ J m⁻² in CompuTiX and TiSim" (TiSim E and ν confirmed as 450 Pa and 0.4; this is 10⁵ m⁻² × 20 k_B T at 310 K).
- BioDynaMo version: update to v1.05.158-c4704305 (confirmed by Nicolò for all tests).
- TiSim growth law: "the radius at each time point is obtained from a cubic-root mapping of the volume growth curve to the experimental data"; remove any reference to linear growth.
- Remove [VERIFY] tags on questions 8.3, 8.4, 8.7 (all resolved in the repository).

**B6 — Remove internal material (file 14, section 6).**

Before submission, delete: the list of target journals and APC, the note on red text and yellow highlights, "Short discussion here?" (twice, lines 137 and 149), the open-questions section, the link to the CRediT spreadsheet, "N.C.: None" under Competing interests, and the Overleaf access line under Supplementary materials.

**B7 — CompuTiX impulse displacement in manuscript. PENDING CONFIRMATION.**

The manuscript currently states the displacement is 0.500 nm. The archived CompuTiX run applies force for 31 steps (3.1 to 6.1 s) giving 0.517 nm — update from 0.500 nm to 0.517 nm once Jirka/Matteo confirm the archived run used mass 0.01 kg. Keep as [VERIFY] until that confirmation arrives (see C below).

**B8 — Send Chaste position file to James — ACTION REQUIRED.**

James confirmed the velocity is out by a factor of 10 and asked whether the position file is also out. Send him `node_locations.dat` (the current file at `Chaste/MechanicsWithFriction/results/node_locations.dat`). This is the only action needed from Thaleia to unblock the Chaste impulse items in section C.

**B9 — CompuTiX diffusion data missing from repository. INVESTIGATE NOW. NEW.**

The meta-test at 8ee428e8d shows all CompuTiX diffusion rows absent: neither the finest run (N=63) nor any coarser run appears in the output. The script uses a glob to locate CompuTiX diffusion files; either the files were deleted/reorganised in a recent commit, or the glob pattern no longer matches.

Action: check whether the CompuTiX diffusion result files still exist in the repository and at what path. Run:

    find ~/Work/observatory_benchmark/CompuTiX -name "*.yaml" | grep -i diffusion

If the files exist at a different path, the glob in `meta_test/table1_summary.py` needs updating. If the files are absent, this must go to Jirka/Matteo (blocked). Until resolved: Table 1 diffusion row loses CompuTiX; Figure 2 loses CompuTiX; Supplementary Table S3a loses all CompuTiX resolution rows.

**B10 — BioDynaMo built-in pushing minimum distance: 8.000 → 8.395 μm. NEW.**

The meta-test shows BioDynaMo min_distance changed from 8.000 to 8.395 μm (+4.9%) in the built-in contact test. Check whether the manuscript or Figure 3F caption quotes "8 μm" for BioDynaMo and update to "8.4 μm" (or "approximately 8.4 μm"). No other built-in pushing values changed significantly.

---

## C. Main manuscript — blocked on developers

These cannot be finalised until replies arrive.

| Item | Blocked on | What to change when it arrives |
|---|---|---|
| Chaste impulse velocity (×10 error confirmed; position file sent) | James Osborne | Results: confirm displacement 0.50 nm; Table 1 and Figure 3C, D legend updated; Chaste units clarified (μm and s) |
| Chaste built-in contact values (results file deleted 24 October) | James Osborne | Results and Table 1: restore or update Chaste final distance 9.98 μm |
| Chaste length unit in impulse | James Osborne | Table 1 and Figure 3C, D legend: remove [VERIFY] on question 8.12 |
| TiSim relaxation (3.1× slower, cell-ECM friction equation now known) | Jieling Zhao | Results and Discussion: attribute to cell-ECM term in the equation of motion once Jieling confirms the velocity computation explicitly |
| TiSim diffusion scheme and exact time steps per mesh | Jieling Zhao | Supplementary Note 1 and Table S2: confirm implicit vs explicit; add the per-mesh time steps |
| CompuTiX impulse mass discrepancy | Jirka Pesek / Matteo Boulitrop | Confirm archived run used mass 0.01 kg; if code now uses 1 kg they must rerun; update displacement (0.517 nm if force window unchanged) |
| CompuTiX diffusion result files (see B9) | Jirka Pesek / Matteo Boulitrop | Restore files or update glob; Table 1 diffusion row and Figure 2 |
| CompuTiX software reference (ref. 32 placeholder) | Jirka Pesek | Introduction and Methods: insert DOI; list then has 51 entries, one above the limit — one reference must go |
| CompuTiX Zenodo release DOI | Jirka Pesek / Matteo Boulitrop | Data availability statement; update once released |
| PhysiCell built-in contact data (not in repository) | Randy Heiland | Results and Table 1: add PhysiCell final distance; remove [VERIFY] on question 8.11 |
| PhysiCell monolayer to day 27 | Randy Heiland | Results, Table 1, Figure 5: add PhysiCell deviations |

---

## D. Notebooks and figures — can be done now

**D1 — Fix Chaste paths (broken since the 24 October reorganisation).**

Four notebooks still read old paths. Update each:
- `Chaste/fixed_cell_cycle/results/cellcycle_fixed.dat` → `Chaste/FixedCellCycle/results/cellcycle_fixed.dat`
- `Chaste/monolayer/results/monolayer.dat` → `Chaste/MonolayerUseCase/results/monolayer.dat`
- `Chaste/MechanicsWithFriction/node_locations.dat` and `cell_velocities.dat` → add `/results/` subfolder
- `Chaste/HertzCellRelaxation/node_locations.dat` → `Chaste/HertzCellRelaxation/results/node_locations.dat`

Without these fixes, the Chaste curves cannot be regenerated for any figure.

**D2 — Fix CompuTiX glob in the uptake notebook (Figure 2C).**

The notebook looks for `dt-s-006_N-*.yaml`; this pattern does not match the CompuTiX uptake files. Fix the glob so CompuTiX appears in Figure 2C. Note: also investigate B9 — CompuTiX diffusion result files may have moved.

**D3 — Fix the four notebooks with absolute personal paths.**

The diffusion decay, diffusion uptake, external impulse and extended Hertz notebooks each contain a hard-coded absolute path. Replace with repository-relative paths.

**D4 — Fix BioDynaMo monolayer series (Figure 5).**

`plot_monolayer.py` currently hard-codes the BioDynaMo grid-extent series (env_dims). Re-plot using the cell-centre extent (tumor_diameter series), which removes the 40 μm stepping artefact and is what Nicolò agreed to plot. After D4, the max absolute deviation for BioDynaMo drops from 8.8% (env_dims) to 5.7% (tumor_diameter) — update abstract and manuscript accordingly.

**D5 — Regenerate Figure 3E reference curve.**

The current reference uses R₁ = R₂ = 1 μm (should be 5 μm) and moves only one cell (should be both). Correct the ODE in the notebook, then regenerate the panel. The corrected reference halves the overlap in 741 s at 1 N s m⁻¹.

**D6 — Regenerate figures after D1–D5 are done.**

Order: fix notebooks (D1–D5), then regenerate: Figure 2C (CompuTiX now present if B9 resolved), Figure 3E (corrected reference), Figure 4B (updated notebook with CompuTiX simulation), Figure 5 BioDynaMo series (cell-centre extent). Figures 3C, 3D and 3F wait for the Chaste file to be restored (item C).

---

## E. Supplementary material — can be done now

**E1 — Supplementary Table S2, CompuTiX built-in contact row.**

Adhesion energy: change 10⁻⁸ J m⁻² to 10⁻⁴ J m⁻² per cell (JKR convention per contact; confirmed from the repository and from Jirka/Matteo's reply to Arnau). Note that this is the adhesion energy per contact, not per unit area.

**E2 — Supplementary Table S1: BioDynaMo version.**

Update to v1.05.158-c4704305 (confirmed by Nicolò for all tests, already in the repository metadata files).

**E3 — Supplementary Table S2, TiSim monolayer row.**

Add growth criterion: "proliferation halted in cells under a pressure above 50 Pa" (confirmed from Jieling's reply). Add cell diameter: 20 μm. Standard deviation of cycle time: 2 h, confirmed as applying only to the monolayer stochastic runs (see E4 below).

**E4 — Supplementary Table S2, TiSim cell-cycle row. CONFIRMED.**

Jieling confirmed: the fixed cell-cycle test uses SD = 0, not 2 h. The 2 h applies only to the monolayer (and other stochastic runs). Update the cell-cycle table entry to "SD = 0 h". The monolayer entry keeps "SD = 2 h". Remove the [VERIFY] flag.

**E5 — Supplementary Table S2, TiSim friction equation.**

Add the equation of motion from Jieling's reply: `Mu_(cell-ECM) × v_i + Σ_j ((v_i - v_j) × Mu_(cell-cell)) = Σ_j F_ij + F_i`. State that Mu_(cell-ECM) dominates because the cell-cell term requires contact. State that the built-in contact test uses drag Mu_(cell-ECM) = 0.01 N s m⁻¹.

**E6 — Code availability statement: TiSim.**

Replace the placeholder with Dirk's INRIA email address as the contact point for TiSim access requests (confirmed by Jieling).

---

## F. Supplementary material — blocked on developers

| Item | Blocked on | Where |
|---|---|---|
| Reaction-diffusion scheme of TiSim (implicit vs explicit; time steps per mesh) | Jieling Zhao | Supplementary Note 1 and Table S2 |
| Reaction-diffusion scheme and time steps of Chaste | James Osborne | Supplementary Note 1 and Table S2 |
| TiSim version commit (not "dev branch") | Jieling Zhao | Supplementary Table S1 |
| CompuTiX citable references (Pesek et al., Boulitrop et al., in preparation) | Jiri Pesek | Supplementary Table S1 |
| CompuTiX impulse: confirmation that archived run used mass 0.01 kg | Jirka Pesek / Matteo Boulitrop | Supplementary Table S2 (impulse parameters) and Results (displacement 0.517 nm vs 0.500 nm) |
| Supplementary Table S3d: PhysiCell monolayer values | Randy Heiland | Supplementary Table S3 |
| Supplementary File 2 (per-run CSV metrics) | all reruns complete | generate after CI is green |
| CompuTiX Overleaf fixes (JKR formula, diffusion scheme, cell-cycle section) | Jiri Pesek | LaTeX Supplementary (Overleaf) — Arnau asked Paul to give them access |

---

## G. Final steps (after all reruns and developer replies)

1. Run the meta-test against the final repository commit; all checks should pass except any explicitly marked as expected failures.
2. Regenerate every figure from the corrected notebooks.
3. Tag the release on GitHub.
4. Mint the new Zenodo version; update reference 51 (dataset citation) and the Data availability statement with the DOI.
5. Upload current results to OpenEBench OEBC009; remove [VERIFY] on question 8.14.

---

## Quick reference: what to tackle first

| Priority | Task | Section |
|---|---|---|
| 1 | **Send Chaste position file to James** (unblocks impulse items) | B8 |
| 2 | **Investigate CompuTiX diffusion data missing** (`find … -name "*.yaml" | grep -i diffusion`) | B9 |
| 3 | BioDynaMo contact law: update Results, Table 1, Discussion | B1 |
| 4 | Fix Chaste notebook paths (unblocks figure regeneration) | D1 |
| 5 | Add regression scripts and workflow to repository | A1, A2 |
| 6 | Fix typos and wrong citation numbers | B3, B4 |
| 7 | BioDynaMo built-in pushing min distance: check/update 8→8.4 μm | B10 |
| 8 | TiSim cell-cycle SD: update table entry to SD = 0 | E4 |
| 9 | CompuTiX adhesion energy and code availability (TiSim) | E1, E6 |
| 10 | Fix CompuTiX glob (Figure 2C) | D2 |
| 11 | Fix absolute paths in notebooks | D3 |
| 12 | Fix BioDynaMo monolayer series (tumor_diameter); update deviation 8.8%→5.7% | D4 |
| 13 | Abstract: trim to 150 words | B2 |
| 14 | Correct Figure 3E reference curve | D5 |
| 15 | Supplementary friction equation and version updates | E2, E3, E5 |
| 16 | Methods updates from confirmed replies (BioDynaMo, TiSim) | B5 |
| 17 | Regenerate figures (after D1–D5 and developer reruns) | D6 |
| — | Everything in C and F | awaiting developers |
| — | Final steps (G) | awaiting all reruns |