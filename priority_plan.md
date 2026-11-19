Claude


Thalia priority plan · MD
# Thaleia's action plan — 5 November 2026
 
Baseline: commit 6aa51a3 (30 September, frozen). Current HEAD: 928e37c4b.
Meta-test scripts live in `meta_test/`. No outreach to Arnau.
 
**DONE:** D1 (Chaste notebook paths), B9 (CompuTiX diffusion glob renamed files fixed), Step 1 (meta-test clean at 928e37c4b — all diffusion rows present, all moved values known).
 
---
 
## STEP 1 — ✅ DONE at commit 928e37c4b
 
Meta-test run on 5 November 2026 with `/tmp/table1_fresh`. All CompuTiX diffusion rows are present. Result summary:
 
| Output table | Values moved | Rows added/removed |
|---|---|---|
| diffusion_decay_finest.csv | 0 | 0 ✅ |
| diffusion_uptake_finest.csv | 0 | 0 ✅ |
| diffusion_decay_all_runs.csv | 0 | 0 ✅ |
| diffusion_uptake_all_runs.csv | 0 | 0 ✅ |
| mechanics_external_impulse.csv | 4 | 0 |
| mechanics_common_extended_hertz.csv | 13 | 0 |
| mechanics_builtin_pushing.csv | 11 | 0 |
| cell_cycle.csv | 0 | 0 |
| monolayer.csv | 9 | 0 |
 
The moved values in mechanics and monolayer are all known and explained:
- **13 in `mechanics_common_extended_hertz`**: BioDynaMo 4/3 prefactor fix → manuscript changes M1–M3.
- **4 in `mechanics_external_impulse`**: PhysiCell dt path change (active_from, active_to), TiSim unit note now in header, Chaste unit note changed → tracked in BLOCKED table.
- **11 in `mechanics_builtin_pushing`**: BioDynaMo min distance 8→8.39 μm (M4) + Chaste results file absent (blocked on James).
- **9 in `monolayer`**: BioDynaMo monolayer rerun → R4 pending.
---
 
## REPOSITORY / CODE changes
 
### R1 — Push meta-test branch (A1 + A2)
Commit everything in `meta_test/` plus the GitHub Actions file and push.
 
Create `.github/workflows/metatest.yml`:
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
 
CI will be **red** after this push — that is correct. It is flagging real differences with the manuscript baseline. It turns green once the baseline is updated alongside the manuscript text.
 
### R2 — Fix CompuTiX uptake glob in notebook (D2)
File: the diffusion uptake notebook (Figure 2C).
The glob currently looks for `dt-s-006_N-*.yaml`. Update the pattern to match the actual CompuTiX uptake file names (the same rename you just fixed in the script applies here too).
 
### R3 — Fix absolute personal paths in four notebooks (D3)
Files: diffusion decay notebook, diffusion uptake notebook, external impulse notebook, extended Hertz notebook.
Each has a hard-coded absolute path like `/home/tntiniak/...`. Replace with a path relative to the repository root (e.g. `../../` from the notebook's location, or use `Path(__file__).parent / '../../'`).
 
### R4 — Switch BioDynaMo monolayer to tumor_diameter (D4)
File: `plot_monolayer.py` (or the monolayer notebook).
Change: replace `env_dims` series with `tumor_diameter` series for BioDynaMo.
Effect: BioDynaMo max deviation drops from 8.8% to 5.7% in Figure 5.
After this: update the manuscript deviation figure (see manuscript section M5 below).
 
### R5 — Correct Figure 3E ODE (D5)
File: extended Hertz notebook.
Two errors to fix: (1) radii are set to R₁ = R₂ = 1 μm, should be 5 μm; (2) only one cell moves, both should move. After correcting, the ODE reference halves the overlap in 741 s at 1 N s m⁻¹.
 
### R6 — Regenerate figures (D6, do last)
Only after R2–R5 are done AND after any pending developer reruns.
- Figure 2C: CompuTiX now present (needs R2)
- Figure 3E: corrected ODE (needs R5)
- Figure 4B: updated notebook
- Figure 5: BioDynaMo tumor_diameter series (needs R4)
- Figures 3C, 3D, 3F: **wait for James** (Chaste data still missing)
---
 
## MANUSCRIPT changes (main text)
 
### M1 — BioDynaMo contact law: Results sentence (B1)
File: Results section, common contact law paragraph.
 
Replace:
> "BioDynaMo relaxed 1.3 to 1.5 times more slowly (1,080 s), consistent with a force prefactor of 1 rather than 4/3 in its implementation of the common law [VERIFY: rerun, or report as an implementation difference, question 8.6]"
 
With:
> "BioDynaMo followed the reference with a mean absolute deviation below 0.01 μm at all three friction values, after correcting a force prefactor of 4/3 that had been evaluated as 1 in an earlier run; at 1 N s m⁻¹ it halved the overlap in 840 s against 741 s."
 
### M2 — BioDynaMo contact law: Table 1 (B1)
File: Table 1, common contact law row.
- Change "BioDynaMo 1,080 s" → "840 s"
- In the mean absolute deviation cell: add BioDynaMo to the list of tools with deviation below 0.01 μm
- Remove the [VERIFY] on question 8.6
### M3 — BioDynaMo contact law: Discussion sentence (B1)
File: Discussion.
Find the sentence about tools relaxing more slowly. Remove BioDynaMo from it. The sentence should now say only TiSim relaxes approximately three times more slowly at 1 N s m⁻¹. Keep [VERIFY] pending Jieling's confirmation of the velocity computation.
 
### M4 — BioDynaMo min distance in built-in pushing (B10)
File: Results paragraph on built-in contact test, and Figure 3F caption.
Search for "8 μm" near BioDynaMo in this section. Change to "8.4 μm" (meta-test shows 8.395 μm at current HEAD).
 
### M5 — Abstract: trim to ≤150 words (B2)
File: Abstract.
Current length: 166 words. Use the 143-word version from file 14 section 2 as starting point.
Four specific fixes:
- "within 5%" → "domain-averaged concentrations within 5%"
- Remove "all tools reproduced the monolayer expansion" (PhysiCell still missing; BioDynaMo now 5.7% after R4)
- Remove or qualify the equilibrium spacing claim (Chaste units still unconfirmed)
- "have never been compared" → "have not been systematically compared under identical conditions"
Restore: "Virtual Human Twins" (capital V H T); availability sentence (GitHub, Zenodo, OpenEBench).
### M6 — Typos (B3)
File: main text. All line numbers from v7 manuscript.
 
| Line | Error | Fix |
|---|---|---|
| 47 | "in space is response" | "in response" |
| 47 | "neighbouring cells (agents)" | "cells (agents), represented as computational agents," |
| 53 | "and and they are" | delete one "and" |
| 53 | "the benchmarks documents" | "the benchmark documents" |
| 89 | "twelve point-sinks evenly distributed" | "twelve point sinks arranged around the centre in the plane z = 0" |
| 89 | garbled analytical solutions sentence | "Both problems have analytical solutions, with which the finest-grid run of each tool was compared over 10 min (Methods)." |
| 111 | stray `)` after "7.2 kg min⁻¹)" | remove |
| 113 | "are let to interact" | "interact" |
| 113–115 | mixed tense | past tense throughout |
| 165 | "BioDynamo" | "BioDynaMo" |
| 175 | "infrastructure²⁴˒³⁸, As CASP" | "infrastructure²⁴˒³⁸, as CASP²⁵ and the MEMOTE test suite³⁹ illustrate." |
| Table 1 caption | "Unit tests of the benchmark" | "Tests of the benchmark" |
| Table 1 header | "Unit Test" | "Test" |
| Methods line 203 | superscript 13 on π γ R̃ | move citation to after "extended Hertz law" |
 
### M7 — Wrong citation numbers (B4)
File: main text, Table 1, Figure 5 legend.
- Table 1 monolayer row and Figure 5 legend: "Brú et al.³³" → "Brú et al.³²"
- Methods, cell-cycle section: "MultiCellDS³⁴" → "MultiCellDS³³"
- Discussion: reference 46 is cited before 45 — renumber to restore first-citation order
- Reference 42 (Bunne et al. 2024): verify it is Cell 187, 7045–7063
- Reference 7 (Mongeon et al. 2024): find the article number (pages listed as 1–13)
### M8 — Methods: add confirmed details (B5)
File: Methods, relevant subsections.
Add these (all confirmed by developers):
- **BioDynaMo diffusion time steps:** "0.01 min at 40 and 20 μm and 0.001 min at 10 and 5 μm"
- **BioDynaMo concentrations:** "BioDynaMo applies no clamping; no negative concentrations occurred (minima: 2.9 μM decay, 3.9 μM uptake)"
- **BioDynaMo impulse dynamics:** "BioDynaMo uses the overdamped equation v = F/µ for the external impulse test only; all other tests use the velocity-Verlet update v(n+1) = v(n) − f_c Δt"
- **TiSim concentrations:** "TiSim suppresses uptake at zero concentration through a Heaviside factor"
- **TiSim time step:** "TiSim uses an adaptive time step, halved until displacement per step is below 0.1 times the cell radius"
- **Adhesion energy:** "γ = 8.56 × 10⁻¹⁵ J m⁻² in CompuTiX and TiSim"
- **BioDynaMo version:** replace whatever version is there with "v1.05.158-c4704305"
- **TiSim growth law:** "the radius at each time point is obtained from a cubic-root mapping of the volume growth curve to the experimental data" — remove any mention of linear growth
- Remove [VERIFY] tags on questions 8.3, 8.4, 8.7
### M9 — Remove internal material before submission (B6)
File: main text.
Delete: journal target list and APC note; red/yellow-highlight note; "Short discussion here?" (×2, lines 137 and 149); open-questions section; CRediT spreadsheet link; "N.C.: None" under Competing interests; Overleaf access line under Supplementary materials.
 
---
 
## SUPPLEMENTARY MATERIAL changes
 
### S1 — Table S2, CompuTiX built-in contact row: adhesion energy (E1)
Change: 10⁻⁸ J m⁻² → 10⁻⁴ J m⁻² per contact (JKR convention, confirmed by Jirka/Matteo).
 
### S2 — Table S1, BioDynaMo version (E2)
Change: whatever version is listed → v1.05.158-c4704305.
 
### S3 — Table S2, TiSim monolayer row (E3)
Add: "proliferation halted above 50 Pa"; cell diameter 20 μm; cycle time SD = 2 h (applies to monolayer only).
 
### S4 — Table S2, TiSim cell-cycle row (E4)
Change: SD = 2 h → SD = 0 h. Remove [VERIFY].
 
### S5 — Table S2, TiSim friction equation (E5)
Add equation: `Mu_(cell-ECM) × v_i + Σ_j ((v_i − v_j) × Mu_(cell-cell)) = Σ_j F_ij + F_i`
Add note: "Mu_(cell-ECM) dominates; built-in contact test uses Mu_(cell-ECM) = 0.01 N s m⁻¹".
 
### S6 — Code availability: TiSim (E6)
Replace placeholder with Dirk's INRIA email address as contact point for TiSim access requests.
 
---
 
## META-TEST: when to update the baseline (A3)
 
Replace `meta_test/baseline_6aa51a3/` only when:
1. A developer pushes a corrected run, AND
2. The manuscript text is updated in the same commit to match.
Never update the baseline alone. The rule is: baseline change = manuscript change, same pull request.
 
---
 
## BLOCKED — waiting for developers
 
| What | Waiting for | Manuscript location |
|---|---|---|
| Chaste impulse: is position file also ×10 wrong? | James Osborne (send him `Chaste/MechanicsWithFriction/results/node_locations.dat`) | Table 1, Figure 3C/D, Results |
| Chaste built-in contact: results file deleted 24 Oct | James Osborne | Table 1, Figure 3F, Results |
| Chaste length unit | James Osborne | Table 1 [VERIFY] on question 8.12 |
| TiSim relaxation: confirm velocity computation | Jieling Zhao | Discussion [VERIFY] |
| TiSim diffusion: implicit vs explicit, time steps per mesh | Jieling Zhao | Supp. Note 1 and Table S2 |
| TiSim version commit | Jieling Zhao | Supp. Table S1 |
| CompuTiX impulse: confirm archived run used mass 0.01 kg | Jirka/Matteo | Results (0.517 nm displacement) |
| CompuTiX software DOI | Jirka Pesek | Intro + Methods ref. 32 |
| CompuTiX Zenodo DOI | Jirka/Matteo | Data availability statement |
| PhysiCell built-in contact data | Randy Heiland | Table 1, Figure 3F, Results |
| PhysiCell monolayer to day 27 | Randy Heiland | Table 1, Figure 5, Results |
 
**Immediate action on your side:** Send James the file `Chaste/MechanicsWithFriction/results/node_locations.dat`. This unblocks all Chaste impulse items above.
 
---
 
## ORDER TO WORK THROUGH THIS
 
1. ✅ Run meta-test, confirm CompuTiX rows back (Step 1 — DONE at 928e37c4b)
2. Push to GitHub with Actions file (R1) ← **next step**
3. Send Chaste position file to James
4. M1 + M2 + M3: BioDynaMo contact law (Results + Table 1 + Discussion)
5. M6: typos — fast, do in one pass
6. M7: citation numbers
7. S1–S6: supplementary table corrections
8. M4: BioDynaMo min distance 8→8.4 μm
9. R2 + R3: fix notebook globs and absolute paths
10. R4 + R5: fix monolayer series and Figure 3E ODE, then M5 deviation update
11. M5: abstract (trim after R4 so deviation % is correct)
12. M8: methods additions
13. R6: regenerate figures (last, after developer reruns)
14. M9: strip internal material (just before submission)
 

