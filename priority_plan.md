# Status before sending v8 to the co-authors (25 November 2026, checked against the v8 text)
 
Sources: GitHub `main` at `27b5b45` (figures-update merged 25 Nov, 12:09 CET), the regenerated PNGs in `ResultAnalysis/plots/` and the stored outputs of the six comparison notebooks, `email responses.docx`, the worksheet of 20 November (doc 18), Thalia's plan of 5 November, and **`Community benchmark paper v8.docx`** from `~/Documents/benchmark` (the only v8 file in the folder; saved 25 Nov 2026, 10:53 UTC), read from the .docx XML with comments and tracked changes.
 
Status labels: **Done**, **Partly done**, **Still open**. "Suggestion" means the change is in v8 as a tracked suggestion, not yet accepted.
 
## 0. Summary of the v8 check
 
1. **The figures in v8 are the old ones.** None of the eleven images embedded in v8 is byte-identical to a PNG in `ResultAnalysis/plots/`, and they are visibly the earlier versions: 2B and 2C without TiSim and titled "Relative error over time for the best run of each tool"; 3E at drag 0.1 ("Two-Cell Relaxation, Drag = 0.1"); 3F with TiSim settling at about 0.33 diameters (the superseded run with the force never removed, which the text no longer uses) and series labelled "Chaste x10res" and "PhysiCell x10res". This is expected (v8 was saved about 15 minutes before the merge), but every figure must be replaced before sending.
2. **The figure-dependent numbers are unchanged since 20 November.** 741 s, BioDynaMo 840 s, "720 to 900 s", the monolayer percentages and the BioDynaMo "100 μm (8.8%) grid-extent" sentence are all still in the Results, Table 1 and legends. Section 1 lists each one.
3. **Text work since 20 November is small.** Thalia's edits of 25 Nov (as tracked suggestions): Chaste impulse sentence, removal of "Chaste test suites", "J.M.O : None". Untracked edits since 20 Nov: the point-sink sentence ("arranged around the centre in the plane z = 0", "consuming"), the second mechanics paragraph (rewritten, now with a "[ref]" placeholder) and the M6 typos. 
4. **Comments:** 35 in v8 (34 on 20 Nov plus Thalia's "Fixed" of 25 Nov). None are marked resolved and none of the 34 listed on 20 Nov has disappeared. The ten comments lost before 20 Nov are still missing.
5. **Useful finding:** Osborne et al. 2017 (PLoS Comput Biol 13, e1005387) is **already reference 15**. The Methods citation "(Osborne et al. 2017)" can become "15" with no new reference and no effect on the 50-reference limit (Arnau to confirm; comment C26 stays open).
## 1. Figures (priority): repository against the v8 text
 
Figure numbering follows the plan of 5 November (2A schema, 2B decay, 2C uptake; 3A, 3B schemas, 3C and 3D impulse, 3E common contact law, 3F built-in contact; 4 cell cycle; 5 monolayer). **Panel order of 3C and 3D:** the v8 legend and Results have **C = velocity, D = position**; the plan of 5 November (and this doc's earlier version) had C = position, D = velocity. The two PNGs on GitHub are separate files, so the order is decided at assembly: fix one order and use it in the legend, Results and Table 1.
 
### 1a. Blocking: fix or disclose before the text goes out
 
| # | Figure | Repository (main, 27b5b45) | v8 text now | Status |
|---|---|---|---|---|
| F1 | Impulse velocity, Chaste | Notebook multiplies the Chaste velocity by 10 (`chaste_vx = chaste_vel[3]*10`, comment "Convert from micrometers per minute to micrometers per second", which would be a division by 60). Chaste is absent from the printed velocity errors. The regenerated velocity panel is in **nm s⁻¹** (plateau about 0.167 nm s⁻¹, which equals 0.01 μm min⁻¹). | Results (Suggestion, Thalia 25 Nov): "Chaste, which reports lengths in μm and time in s, reproduced the 0.5 nm displacement" (no full stop; the [VERIFY 8.12] was deleted with the old sentence). Table 1 impulse row: "Chaste output units not stated [VERIFY: question 8.12]". Legend 3C/3D: "Chaste, whose output units are not stated, is shown for the shape of the response only." Legend C: "the reference plateau is 0.01 μm min-1". Discussion: "overdamped single-cell velocity ... consistent across tools". | **Partly done.** Results now states the displacement only, which the position data support. Still open: (a) the ×10 rescaling is disclosed nowhere; the Results suggestion removed the last [VERIFY] on Chaste units, so restore a caveat (e.g. "[VERIFY: Chaste velocity output, a factor 10 below the slope of the positions, question 8.12]") until James sends the corrected file; (b) Table 1 and the legend still say units "not stated", which now contradicts the Results; (c) legend in μm min⁻¹, figure in nm s⁻¹: give both or change one; (d) the Discussion claim on velocity should exclude Chaste or carry the caveat; (e) add the missing full stop. |
| F2 | 3F, built-in contact | No regenerated 3F and no comparison notebook for it. No Chaste built-in contact results (`Chaste/` has `CellRelaxation`, used by the common-law notebook, and `MechanicsWithFriction`, the impulse test). | Embedded 3F is the old image (TiSim at about 0.33 diameters, "x10res" labels), contradicting the Results value for TiSim (9.88 μm). Table 1 and Results list CompuTiX 9.10, BioDynaMo 9.38, TiSim 9.88, Chaste 9.98 μm, PhysiCell [VERIFY 8.11], Chaste length [VERIFY 8.12]. Legend: "0.91 to 1.00 diameters [VERIFY: panel to be regenerated ...]". Abstract uses 0.91 to 1.00. Arnau's C20 "keep or move to SuppMat?" open. | **Still open.** Decision needed (C20). Whatever is decided, the old image cannot go out: it shows the run the text says was superseded. If 3F stays, the Chaste 9.98 μm rests on the "x10" length scaling, still [VERIFY 8.12]. |
| F3 | 3E, common contact law | Reference uses `drag/2`; notebook prints **"Reference half-time at drag = 1: 734 s (0.204 h)"**. In the zoomed panel CompuTiX, PhysiCell and Chaste cross δ/δ₀ = 0.5 at about 0.20 h by eye; BioDynaMo is flat for about 0.017 h then crosses at about 0.21 h by eye; TiSim is still at about 0.66 at 0.35 h. Chaste only at drag 1. The printed end-point table gives final-overlap differences at drag 1 of about 0.02 μm (BioDynaMo), 0.008 μm (PhysiCell, Chaste) and 0.05 μm (CompuTiX, TiSim), assuming overlaps in μm; the mean absolute deviation is not printed. | **741 s** in Table 1, Results and legend 3E ("the reference halves the overlap in 741 s"). Table 1: "720 to 900 s for CompuTiX, PhysiCell and Chaste (Chaste output every 300 s) against 741 s; BioDynaMo 840 s" (840 is Thalia's suggestion of 4 Nov, replacing 1,080) "...; mean absolute deviation below 0.01 μm for BioDynaMo, CompuTiX, PhysiCell and Chaste" (BioDynaMo added as a suggestion). Results: "halved the overlap in 720 to 900 s against 741 s"; "at 1 N s m⁻¹ it halved the overlap in 840 s against 741 s". Legend 3E still has "[VERIFY: panel to be regenerated at 1 N s m-1 ... the v6_1 image shows 0.1 N s m-1 ...]". Methods still has "[VERIFY: corrected reference to be implemented in the repository notebook, cross-check question 8.13]" and "BioDynaMo evaluated the prefactor 4/3 as 1 [VERIFY: rerun or report, question 8.6]", which contradicts the Results (rerun after correction). | **Still open.** Replace 741 s by 734 s in four places. The by-eye crossings do not support "840 s" for BioDynaMo nor the 900 s upper end for the other three: take all half-times from `overlap_drag_1_zoom.csv` (not committed, see F5). Check the "mean absolute deviation below 0.01 μm" claim against the source data: the end-point differences above 0.01 μm for BioDynaMo and CompuTiX need explaining (CompuTiX ran 100 min only, so the end-point comparison may not be like-for-like). Check whether "Chaste output every 300 s" still holds for the file now plotted. Update the Methods (reference now corrected; BioDynaMo rerun with 4/3). Legend: say Chaste ran at 1 N s m⁻¹ only. Keep TiSim [VERIFY 8.2]. |
| F4 | 5, monolayer | All five tools. PhysiCell data to day 28.0 (plot limited to 27.5); BioDynaMo `tumor_diameter`, ends at about day 26.5. Deviation panel in **μm**. By eye: BioDynaMo about -130 μm near day 21.5; PhysiCell about +95 μm near day 16; CompuTiX about -80 μm near day 21; TiSim about -65 μm near day 21; Chaste about +75 μm at the end. | Table 1: "Maximum absolute deviation 58 to 84 μm (2.0% to 3.7%) for Chaste, TiSim and CompuTiX; 100 μm (8.8%) for BioDynaMo, grid-extent series [VERIFY: 8.11, 8.13]"; set-up "to day 26 to 27". Results: "within 58, 67 and 84 μm (2.0%, 3.0% and 3.7%)" and "The BioDynaMo curve deviates by up to 100 μm (8.8%) at day 14 because the plotted series is the extent of its uniform grid ... [VERIFY ... PhysiCell deviations, whose data are not in the repository]". Legend 5C: "within 2.0% to 3.7% ... [VERIFY: BioDynaMo series and PhysiCell data]". Methods: "Simulations ended between day 25.9 and day 27 [VERIFY: PhysiCell run to day 27, question 8.11]"; BioDynaMo diameter "as the extent of the cell centres along the coordinate axes". Discussion: "[VERIFY: BioDynaMo and PhysiCell monolayer curves]". | **Still open.** Every monolayer number must be retaken from `diameter_deviation.csv`, in μm (with % in brackets only if computed from the same file). By eye, Chaste exceeds the 58 μm in the text: check. Delete the grid-extent sentence; add PhysiCell; say BioDynaMo ends at about day 26.5 and PhysiCell runs to day 28; describe what `tumor_diameter` measures in the Methods; remove the PhysiCell [VERIFY]s. The abstract's "all tools reproduced ... the measured monolayer expansion rate" can stay only if the new deviations support it. |
| F5 | All | `figures/` (PNG, SVG, source-data CSV) is still not in the repository; only `ResultAnalysis/plots/` PNGs are. | n/a | **Still open.** Commit `figures/` or at least `source_data/`. Needed for the journal's source data and for F3 and F4 above. |
| F8 (moved up) | 2B, 2C decay and uptake | Decay PNG is 0 to 5 min (`..._0_5min`); uptake has 0 to 5 min and 0 to 7 min versions. Each figure now has three panels (average concentration, absolute error in μM, relative error in %). The relative error is plotted **unsigned** (CompuTiX and PhysiCell, which lie below the analytical curve, appear positive). TiSim has a kink at about 1.25 min. Uptake CompuTiX run is `N_63_dt_0.006min`. | Results: "compared over 10 min"; Table 1 "at 10 min"; legend 2B: "at 10 min the errors range from -3.1% to +4.8%" (signed) with "[VERIFY: panel to be regenerated; the v6_1 image shows four tools, unsigned errors ...]"; legend 2C "[VERIFY ... the v6_1 image lacks TiSim]"; Table 1 and Results "[VERIFY: CompuTiX to be added to Figure 2C, question 8.13]". Methods: "1 × 10-4 min in CompuTiX". | **Still open.** (a) Say "first 5 min shown; values at 10 min" or plot to 10 min; (b) signed in the text, unsigned in the figure: align; (c) legends describe one panel, figures have three; (d) remove the resolved [VERIFY]s (TiSim and CompuTiX are now in both panels); (e) CompuTiX time step 0.006 min in the uptake run against 1 × 10⁻⁴ min in the Methods: give both. Values themselves (6.65 to 7.18 μM, 6.86 μM analytical) are consistent with the regenerated panel by eye. |
 
### 1b. Figure items resolved in the repository (the v8 text and images do not yet show them)
 
- TiSim in 2B and 2C (Vasileios C16); CompuTiX back in 2C.
- Chaste in 3E (drag 1 only).
- BioDynaMo common-law runs redone with 4/3 at three frictions. "1.3 to 1.5 times slower" no longer in v8 (Done).
- BioDynaMo monolayer as `tumor_diameter`; PhysiCell monolayer to day 28.
- All tools in Figure 4. Cell-cycle maxima in v8 (198.4% PhysiCell to 201.0% Chaste) match the notebook output (198.42% and 200.96%). The regenerated panel stops at 36.5 h, while the text and legend say 48 h; the reference trajectory in the notebook ends at 24 h and is labelled "Experimental_reference" (question 8.10). Legend 4B's "[VERIFY: panel to be regenerated ...]" can go once the new image is inserted.
- Absolute machine paths removed.
### 1c. Figure items still open (not blocking; list in the cover email)
 
| # | Item | v8 status |
|---|---|---|
| F6 | Schemas with dimensions, 2A, 3A, 3B (Paul C14, C10, C19) | **Still open.** The point-sink sentence in the Results was changed to "twelve point-sinks evenly arranged around the centre in the plane z = 0" (Thalia's "Fixed" on C10/C11), but legend 2A still says "twelve point sinks near the centre" and the 2A image is the old single-cell schema. Figure 1 [VERIFY 8.17] (four logos) also open. |
| F7 | Same legend information for every tool (Paul C15) | **Still open.** |
| F9 | Monolayer before day 14 (Paul C23) | **Still open** (answer in the cover email). |
| F10 | TiSim decay kink at about 1.25 min | **Still open** (Jieling). |
| F11 | BioDynaMo impulse starts about 0.2 s early | **Still open** (Nicolò). |
| F12 | CompuTiX impulse 0.517 nm | Text keeps "0.52 nm ... offset by one 0.1 s time step". **Still open** (mass 0.01 vs 1 kg unconfirmed). |
| F13 | Supplementary figures not regenerated | **Still open.** |
| F14 | Regression check (R1) | **Still open.** No `.github/workflows/` on main; Methods still "[VERIFY: to be added to the repository and run in its continuous-integration workflow ...]". Rerun the meta-test and update the baseline together with Table 1. |
 
## 2. Main text (checked against v8)
 
1. **Numbers that follow the figures** (section 1a): **Still open** except the Chaste displacement sentence (Partly done, F1).
2. **Lost comments and untracked edits:** **Still open.** The ten comments listed in doc 18 section 0A are still absent. New untracked edits since 20 Nov: the point-sink sentence and "consuming" (Results RD), the rewritten second mechanics paragraph, and the M6 typo fixes. Today's three edits were made as suggestions (good).
3. **Three small errors of 20 November:**
   - Missing space "question 8.18].BioDynaMo, Chaste, CompuTiX and PhysiCell do not clamp": **Still open.**
   - Missing full stop "questions 8.1 and 8.8]PhysiCell was compiled": **Still open.**
   - "(Osborne et al. 2017)" in the Methods: **Still open, but easy**: it is reference 15; replace by the superscript 15 (no new reference).
4. **Developer answers into the Methods:**
   - BioDynaMo RD time steps (0.01 min at 40 and 20 μm, 0.001 min at 10 and 5 μm): **Still open** ("[VERIFY: time steps of BioDynaMo, Chaste and TiSim ...]").
   - BioDynaMo FD with explicit Euler: in the text, but BioDynaMo is still inside the [VERIFY] on schemes: **Partly done.**
   - BioDynaMo no clamping, no negatives (minima 2.9 and 3.9 μM): **Done.**
   - BioDynaMo v1.05.158-c4704305: **Done.**
   - BioDynaMo overdamped update only in the impulse test: **Still open** (only "BioDynaMo and PhysiCell impose the resulting velocity directly").
   - TiSim: adaptive time step, radius from the cube root of a fitted volume curve, 50 Pa threshold, friction 0.01 N s m⁻¹ in the built-in test: **Still open**. Heaviside factor: **Done**. Note: Thalia's comment C21 ("How? Quadratically or linearly?") is anchored on the **TiSim** "doubles its volume", so Jieling's cube-root answer addresses it.
   - Chaste: impulse time step "0.1 s in CompuTiX and Chaste": **Done**; lengths in μm and time in s: **Partly done** (Results impulse only); no clamping: **Done**; contact law: **Done** (citation format, item 3); one cell diameter added to the monolayer: **Done**.
   - CompuTiX adhesion energy 10⁻⁴ J m⁻² (JKR): not in the main text; Supplementary item S1.
5. **Worksheet section 2 wording:**
   - (8) "Cell-based multiscale simulations" (Vasileios C1): **Still open**, unchanged.
   - (12) point sinks: **Partly done**. v8: "replaces decay with twelve point-sinks evenly arranged around the centre in the plane z = 0, each consuming 1.6 × 10-16 mol min⁻1". Remove "evenly" or the hyphen in "point-sinks"; align legend 2A.
   - (14b) Methods relaxation: **Done** ("so the law reduces to Hertzian repulsion, under which the overlap decreases monotonically towards zero").
   - (11) tense: **Partly done.** "are let to interact" is gone, but the rewritten paragraph is in the present tense and adds a placeholder: "In the second unit test, two 10 μm-diameter agents are positioned such that cell centre to cell centre distance is 9 μm (10% overlap) and interact via the  extended Hertz law [ref]. Identical elastic parameters are assumed ...". Needs past tense and a reference (none is cited for the extended Hertz law in the Methods either; Arnau to choose, any proposal to be flagged as a new reference).
   - (13) "four significant figures" (Vasileios C18 "digits?"): **Still open.**
   - JMO #7/8, Results impulse: **Partly done** (F1). Table 1 impulse row: **Still open.**
   - Code availability "Chaste test suites": **Done** (Suggestion).
   - "J.M.O.: None": **Done** (Suggestion) but typed "J.M.O : None"; correct to "J.M.O.: None". Only N.C. and J.M.O. are listed under the [VERIFY 8.16].
   - M6 typos: "and and", "the benchmarks documents", "BioDynamo", "are let to interact" no longer found: **Done**. Table 1 header still "Unit Test": **Still open**. Reference 1 reads "Axenie ,Cristian, Bauer ,Roman & and Vavourakis": fix.
6. **Citations (M7):**
   - Brú et al.: reference 32. Correct in the Introduction, Results ("ref. 32"), Methods and Data availability; **still 33 in Table 1 ("Brú et al.33") and the Figure 5 legend**. **Partly done.**
   - MultiCellDS: reference 33. Correct in the Results ("ref. 33"); **still "34" in the Methods cell-cycle paragraph**. **Partly done.**
   - First-citation order 45/46: Discussion still cites "33,46" before "45": **Still open.**
   - Bunne et al. 2024 (still arXiv) and Mongeon et al. 2024 (no article number, "1-13"): **Still open.**
   - Question 8.21 still describes reference 32 as CompuTiX and reference 37 as Viceconti 2021; update the numbering in the questions list.
7. **Abstract:** **Still open.** 166 words with Alexander's suggestions accepted, 161 with them rejected (limit 150). The claims on contact spacings (0.91 to 1.00) and the monolayer depend on F2 and F4.
8. **Checks with Thalia:** all **Still open** in v8: PhysiCell target volume "doubles on entry into S"; adhesion energy "8.6 × 10-14 J m-2 in PhysiCell" (C25 "These should all be the same"); Chaste monolayer initial condition still "[VERIFY: Chaste initial condition, question 8.12]" in Results and Methods (C22: single cell, no division until day 4); point sink still "from the voxel that contains it" (C24).
**Other text issues found in v8** (not in the 20 Nov list):
- Results RD: "Analytical solutions to both tests can be derived, with which the finest grid was run by each tool was compared over 10 min (Methods)." Garbled sentence.
- Discussion: "tied to public infrastructure24,38, As CASP25 and ..." (comma and capital).
- Double spaces: "none  asks", "the  extended Hertz", "lay  in", "concentrations,  overdamped", "links to  initiatives".
- Results subheading-like lines "Short discussion here?" (twice) still in the text (C17).
## 3. Supplementary (not changed; v8 does not change it)
 
S1 CompuTiX adhesion energy 10⁻⁸ → 10⁻⁴ J m⁻², JKR convention; S2 BioDynaMo version v1.05.158-c4704305 in Table S1; S3 TiSim monolayer row (50 Pa, 20 μm diameter, SD 2 h); S4 TiSim cell-cycle SD 0 h; S5 TiSim friction equation; S6 TiSim contact (Dirk Drasdo's INRIA address, to be typed by Thalia); move Jieling's "ANSWER" tables into Table S2 (they are still inside question 8.1 of v8); regenerate the Supplementary figures with the new style (F13). Jirka and Matteo were asked to make the CompuTiX corrections in the Overleaf directly; not checked (Overleaf not reachable from here).
 
## 4. Still waiting for developers (no change in v8)
 
- **Chaste (James):** corrected velocity file (F1); built-in contact results (F2); runs at 0.01 and 0.1 N s m⁻¹ (optional); RD scheme and sink handling on element interfaces (C24); unit of the 0.1 time step (v8 writes "0.1 s").
- **TiSim (Jieling):** factor of about three in 3E (F3); RD scheme (stability-based time step implies explicit, text says Crank-Nicolson); version as a commit; decay kink (F10).
- **CompuTiX (Jirka, Matteo):** Zenodo DOI and library version (Paul C4; "[VERIFY: REF missing ...]" in Introduction and Methods); mass in the impulse run; solver tolerance.
- **BioDynaMo (Nicolò):** 60 s flat start in 3E and 0.2 s offset in 3C/3D (F3, F11).
- **PhysiCell:** built-in contact data if 3F stays.
## 5. Co-author comments open in v8 (none resolved; leave open)
 
All 35 comments are open (none marked done). The 34 of 20 November are all still present; one is new (C11, Thalia, 25 Nov, "Fixed", reply to Paul's C10 on the point-sink sentence). Comment IDs are those of the v8 .docx.
 
| ID | Author | Comment | Anchor in v8 | Note |
|---|---|---|---|---|
| C0 | Arnau | remove from v1 | Journal list under the abstract | keep until submission |
| C34 | Arnau | remove from v1 | Overleaf line | keep until submission |
| C1 | Vasileios | "maybe remove this ... confuse ... biological cells" | "Cell-based" (Introduction) | item 2.5 (8) |
| C2, C3 | Arnau / Vasileios | remove? / keep | "No comparable initiative exists for off-lattice CBMs." | decision |
| C4 | Paul | CompuTiX not published as a paper | CompuTiX [VERIFY: REF missing] | developers |
| C5 | Vasileios | call them benchmarks? (consistency) | "unit tests" (Introduction) | terminology decision |
| C7 | Vasileios | or "unit test"; keep terminology consistent | "use case" (Results) | terminology decision |
| C33 | Thalia (for James) | we present comparisons, not "benchmarks" yet | Discussion | terminology decision |
| C6 | Jieling | added version and tables for 8.1 | "questions 8.1" | tables to Table S2 |
| C8 | Vasileios | move the Table 1 footnote to the main body | Table 1 footnote | decision |
| C9 | Paul | equations per test in Results | "Reaction-diffusion unit tests" heading | decision |
| C10, C11 | Paul / Thalia | text not corresponding to Figure A / "Fixed" | point-sink sentence | text changed; 2A legend and image still old |
| C12, C13 | Paul / Thalia | replace by consuming / Ok | "consuming" | text done |
| C14 | Paul | figure should contain dimensions | Figure 2 image | F6 |
| C15 | Paul | legend information not the same for all codes | Figure 2 image | F7 |
| C16 | Vasileios | TiSim missing in the plots | Figure 2 legend | resolved in repository, not in v8 images |
| C17 | Paul | short discussion here? | Figure 2 legend / "Short discussion here?" | decision |
| C18 | Vasileios | digits? | "four significant figures" | item 2.5 (13) |
| C19 | Paul | figure should contain the text's details | Figure 3 image | F6 |
| C20 | Arnau | keep or move to SuppMat? | Figure 3F legend | F2, decision |
| C21 | Thalia | How? Quadratically or linearly? | TiSim "doubles" | Jieling answered (cube root of fitted volume) |
| C22 | Thalia | Chaste starts with a single cell, no division until day 4 | "condition" (Results monolayer) | item 2.8 |
| C23 | Paul | time lapse before 14 days not shown? | Figure 5 image | F9 |
| C24 | Thalia (for James) | voxel vs FE element; interface sinks | Methods point sinks | item 2.8 |
| C25 | Thalia | these should all be the same | adhesion energies, Methods | item 2.8 |
| C26 | Thalia | Osborne 2017 would exceed 50 references | "(Osborne et al. 2017)" | already reference 15 |
| C27 | Thalia | log repulsion, exponential attraction (Osborne 2017) | built-in contact sentence | text done |
| C28 | Thalia | why are the release criteria not the same? | release criteria, Methods | decision (James #34) |
| C29 | Thalia | extra cell diameter added | Methods monolayer | text done |
| C30 | Vasileios | comparison metrics at the start of the Methods | "Comparison metrics and analysis" | decision |
| C31, C32 | Arnau / Thalia | important? / could remove | threads and compiler sentence | decision |
 
Other decisions for Arnau and the co-authors (unchanged): Osborne et al. 2017 (now only a citation-format fix); Alexander Fletcher's 15 pending suggestions (abstract; deletion of the "Community impact" and "Future directions" subheadings; "Natural next steps are: ..."); JMO.docx rewordings not carried into v8; the ten comments lost before 20 November.
 
**Disappeared since 20 November:** none. Caveat: the 20 November export was overwritten, so this is checked by count (34 → 35, the extra one dated 25 Nov) and by finding every comment cited in doc 18 in v8, not by a file comparison.
 
## 6. What is left before sending to co-authors (in order)
 
1. **Replace all embedded figures** with the regenerated ones from GitHub main and fix the 3C/3D order; decide 3F (C20). Do not send the old 3F.
2. **Commit `figures/source_data/`** (F5) and take from it: per-tool half-times at drag 1 (F3), the mean absolute deviations, and the monolayer maxima in μm (F4).
3. **Update the numbers in Table 1, Results, legends and Methods:** 734 s (four places); BioDynaMo, Chaste, CompuTiX, PhysiCell half-times; monolayer sentence, row and legend (delete grid-extent text, add PhysiCell, day 28 and BioDynaMo end at about day 26.5, `tumor_diameter` definition); decay "first 5 min shown" and signed vs unsigned error; Methods 3E VERIFYs and the 4/3 sentence; resolved [VERIFY]s on TiSim and CompuTiX in Figure 2.
4. **Chaste velocity disclosure** (F1) in Results, Table 1 and legend, unless James's corrected file arrives; units in the velocity legend; Discussion velocity claim.
5. **Small fixes:** missing space and full stop; Osborne → 15; Brú 33 → 32 in Table 1 and Figure 5 legend; MultiCellDS 34 → 33 in the Methods; "J.M.O.: None"; "Unit Test" → "Test"; reference 1 authors; garbled RD sentence; "24,38, As"; double spaces; "[ref]" and tense in the second mechanics paragraph; full stop after the Chaste sentence.
6. **Developer answers into the Methods** (item 2.4): BioDynaMo time steps and scheme, TiSim growth law, time steps, 50 Pa and 0.01 friction, uptake CompuTiX time step.
7. **Abstract** to 150 words after steps 2 to 4 (now 166 or 161).
8. **Lost comments and tracking:** add a note on each sentence changed without tracking (including the post-20 Nov edits listed in item 2.2), or send a Google Docs comparison with the 20 November version.
9. Re-run the meta-test and update the baseline with Table 1 (F14).
10. Name the version ("v8, [date]"), export .docx, and send with the cover email: what changed (1b, 2), decisions (5), what is awaited (4), Supplementary not yet updated (3).
 