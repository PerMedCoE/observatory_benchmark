# PerMedCoE community benchmarks

[TOC]

## Executive Summary

PerMedCoE is a Centre of Excellence who, as one of its objectives, focuses on five different tools aimed at cell-based modelling: PhysiCell, MaBoSS, COBREXA, CellNOpt and CARNIVAL. Nevertheless, these tools, that we call “core tools” in the present document, are part of a scientific field that is changing regularly. 

This deliverable presents an update of the work presented in D3.3 “First PerMed technology observatory release and benchmark report” where we introduced the concept of community benchmarking and the different tools that we aimed to compare our own core tools with. These benchmarks should aim to assess the status of the field, defining the best applications to integrate in the CoE activities and engaging with the software users and developers.

In the present deliverable we detail the results of the different benchmarks that we have performed, notably the ones from the hackathon on cell population modelling benchmark in late September 2022.

The observatory is publicly accessible at this link: [https://permedcoe.bio.tools/](https://permedcoe.bio.tools/) and the benchmarks are publicly accessible in these links: [https://openebench.bsc.es/benchmarking/OEBC009](https://openebench.bsc.es/benchmarking/OEBC009) and [https://github.com/PerMedCoE/observatory_benchmark](https://github.com/PerMedCoE/observatory_benchmark). 

## 1. Introduction

In addition to the five core pieces of software that are central to PerMedCoE development, as a part of W3 we observed and benchmarked representatives of other software developments that target different aspects of cell-level simulations. Because many tools with similar aims as those of PerMedCoE exist, the devised tools’ observatory effort aims to gather information on tools being published that could complement and overlap the aims of the core ones from PerMedCoE, allowing us to keep up with the activity in the field, and also differentiate the core tools of the consortium from the “external tools” to avoid implementation redundancy.

The main aim of the benchmark is to set up workflows and methods to compare the tools in a controlled execution environment under controlled inputs, gathering extensive data on various tools’ performance-wise and feature-wise properties. We thus both list the tools capabilities as well as mechanically benchmark them in common test cases with the involvement of the community of tools owners. In the past few months, a substantial amount of communication, meetings and discussions was carried out to agree with the different external tools’ developers upon the metric, scope and use cases of the specific cell population modelling tool sub-category. This effort peaked in a community benchmark event located after the ECCB 22 conference (Sitges, Spain).

The substantial amount of coordination required for organising the community benchmarks led us to aim for varying levels of completeness for each of the available benchmarks. In Section 2, we describe the current status of the different benchmarks, detail how we have organised them, present the main results and describe the forthcoming tasks for the remaining year of the project.

In Section 3, we describe the infrastructure built for the dissemination and long-time maintenance of these benchmarks using Elixir tools, such as the bio.tools repository and the OpenEBench website. These websites will ensure that the community will have access to the generated results, that other tool developers will be able to join the benchmarking in the future, and that the interested users may take advantage of these benchmarks to select a tool that fits their needs.

## 2. Tool observatory and benchmarks

As described in Deliverable 3.3, PerMedCoE devised three types of benchmarks that can be done with different dependence on the tool developers from outside the project. These are:

* **Level A, Community benchmark**: A community benchmark is defined as the coordinated effort from a group of developers to compare their tools in a fair and transparent manner. For this, they need to agree on three sets of features: scope of the benchmark, which metrics will be used and which use cases or reference datasets will be considered.
* **Level B, Preliminary benchmark**: A preliminary benchmark is a comparison of tools that one developer performs on their own without any major input from other developers. The scope, metrics and use cases are defined by this developer.
* **Level C, Table descriptors**: We have gathered from the tools publications and website a set of descriptors such as operating system, coding language, etc. that can inform users of some characteristics of these tools to make a choice of which one is better for their problem or machine.

Since Deliverable 3.3, we have continued including additional tools in the observatory found at [https://permedcoe.bio.tools/](https://permedcoe.bio.tools/). The PerMedCoE collection of bio.tools has now 42 tools with diverse aims, but all related to cell-level simulation. For all tools we have gathered descriptive tables of features. These tables, which have been expanded since D3.3, can inform users to make a choice of which one is better for their problem or machine or to perform any of the benchmarks with their different dependencies or operating systems needed.

In this section, we describe the status of the four different community benchmarks in the PerMedCoE project. In all these benchmarks, we started by identifying interesting tools using literature review and feature-wise comparisons of the external tools to our own PerMedCoE core tools and contacted the tools’ developers. This group of developers is the basis of what we termed “community”: a group of people with diverse backgrounds and experiences working in the same field, who face similar problems and want to collaborate to find the best solutions to these problems.

As we described in D3.3, a PerMedCoE we consider that “comparing tools against others encourages software developers to implement more efficient methods and develop new tools by focusing on challenging areas and methodological blind spots. In addition, users can access the benchmark results, which helps steer the user base towards the latest and better developments in the field.”

Thus, we met with them several times to talk about the aims and motivations of the community benchmarks and to decide about the existing challenges in terms of size, complexity and content. We needed to agree on three features of the benchmark: scope, metrics and use cases.

* **Scope:** The relevant scientific questions that the benchmarked tools need to answer. These can be technical, focusing on the tool’s performance under specific conditions, or scientific, focusing on its performance and quality of the results within clearly defined scientific challenges.
* **Metrics:** A set of quantitative values used to measure the performance of the evaluated tools in the scope of the benchmark. The technical metrics could include e.g. memory use and run time; the scientific metrics may include accuracy and recall.
* **Use case definition:** Reference data sets and desired outcomes that can be used as ground truths and/or baselines for comparison. They need to be well defined, unbiased and their use should be agreed upon and supported by the community.

Once these features have been agreed on, the community needs to run their tools on the defined use cases using the agreed metrics in a common computer architecture to normalise the technical metrics. After the simulations are performed, we need to publicise these efforts in technical papers with the benchmark participants and public websites such as OpenEBench so that they will be of maximal benefit to tool developers and end-users.

### 2.1. Cell population modelling 

For this benchmark, we were particularly interested in overlapping spheres or centre-based models (CBM), where the agents are represented by overlapping spheres as it is a good trade-off between computation efficiency and close-to-reality simulations (Osborne _et al._, 2017; Metzcar _et al._, 2019). In addition, we expected that restricting the benchmark to CBMs would allow us to find unit tests and use cases that are more common to all the tools.

#### 2.1.1. Preparing the hackathon

As we described in D3.3, we started preparing the hackathon in January 2022 by sending mails to the tool developers of the multiscale agent-based community. With the feedback from the interested tools’ developers, BSC organised several meetings. The first of these meetings was on March 1, 2022, where we presented the tools and we started discussing the requirements of these benchmarks.

We met again on May 4, when BSC presented to the community the bio.tools repository of the present project ([https://permedcoe.bio.tools](https://permedcoe.bio.tools)) and announced the organisation of the hackathon on Thursday 22 and Friday 23 September 2022, just after the ECCB 2022 conference. 

BSC presented the results of the preliminary benchmark of multiscale tools, reported in D3.3 and publicly available at [https://openebench.bsc.es/benchmarking/OEBC009](https://openebench.bsc.es/benchmarking/OEBC009). The community discussed the difference in average CPU use and average power needed of the three tools as these were comparisons that they had not seen before. This preliminary benchmark underlined the need to agree on a set of parameters values and model details so that these are more directly comparable. As well as using metrics that capture the computational cost, like “walltime divided by number of cells”. We discussed the need as well to have unit tests focused on the different solvers and different use cases that could be interesting.

Next, we met on July 13 when BSC presented the working document that was prepared with the different unit tests and use cases that needed to be ranked as to prioritise the ones that were easily doable and most informative. Even though the use cases were the ones for which we could find experimental data easier, it was thought that the unit tests were needed to have simpler tests to compare the tools. The parameters values for the unit tests were still not defined. 

In the first weeks of September, BSC had meetings with developers from Chaste, BioDynaMo and CellSys. They already had user accounts available to access the MareNostrum4 cluster to set up and run their tools. The goal of these meetings was to go through the list of unit tests and use-case to be run and check that all tools could run most of them.

From all these meetings we agreed on a set of use cases to test using different technical and scientific metrics. The goal of these tests was to study the simulation results of each tool, their code and their underlying mathematics to be sure that this benchmark was comparing tools that simulate the same behaviour using the same equations. Thus, the focus of the benchmark was not performance, runtime execution or HPC scalability, which was deemed to be the focus of future benchmarks.

Additionally, the different tests aimed to minimise the number of changes to the source code of each software as well as any input from the owners of the tools.

The list of tests that were finally considered was (for a complete description go to Appendix 1):

* Unit tests
    * Cell cycle, fixed duration
    * Cell cycle, stochastic duration
    * Diffusion of molecules, one cell as sink
    * Diffusion of molecules, 1k cells as sinks
    * Mechanics, movement of a cell
    * Mechanics, two cells pushing each other
    * One cell with chemotaxis
    * Stretch goals unit tests
        * Mechanics, friction between two cells
        * Constrained growth
        * Reaction-diffusion unit test
        * Cell sorting/clustering
* Use cases
    * 2D monolayer without diffusion
    * Spheroid without diffusion
    * Spheroid with diffusion
    * Stretch goals use case
        * Aggregation under chemotaxis
        * Predation among cell types with interactions
        * Scratch experiment/wound healing with chemotactic aggregation and competition for space

#### 2.1.2. Multiscale tools benchmarking hackathon

The four tools that committed to be tested in this benchmark were: BioDynaMo, Chaste, PhysiCell and TiSim. We hereby describe these tools as they were described in D3.3:

* **BioDynaMo** (Breitwieser _et al._, 2021)is an open-source simulation tool fully parallelised, able to offload computation to hardware accelerators and load-balance agents and their simulated microenvironment across the available nodes. Being general-purpose, it allows simulating models from various fields by being extensible and modular, showcasing its use in neurite growth, in tumour spheroid and in epidemiology examples. The version used in this benchmark is v1.04.
* **CellSys/TiSim** (Hoehme and Drasdo, 2010) is a source-available software that has been used for multi-cellular biological models, such as liver regeneration (Hoehme _et al._, 2010), introducing the deformability in centre-based models (Van Liedekerke _et al._, 2015) and the inclusion of signalling pathways controlling the agents’ behaviours (Ramis-Conde and Drasdo, 2012). 
* **Chaste** (Cooper _et al._, 2020) is an open-source, general-purpose simulation package for modelling soft tissues and discrete cell populations that can be used with MPI. This tool allows using different modelling frameworks on a given problem, enabling users to select the most appropriate one for their research and to better understand the limitations of each one of them. Chaste has been used for a wide range of projects, such as intestinal (Dunn _et al._, 2013) or colonic crypt (Dunn _et al._, 2012) studies. The version used in this benchmark is v2021.1.
* **PhysiCell** (Ghaffarizadeh _et al._, 2018), an open-source, flexible, off-lattice, centre-based, agent-based framework for multi-scale simulation of multi-cellular systems that currently support shared-memory parallelisation. The main advantage of PhysiCell is its lightweight, very efficient and self-contained framework. Additionally, PhysiCell can be expanded using add-ons, such as PhysiBoSS (Letort _et al._, 2019), allowing the integration of individual Boolean models for the signalling networks embedded into each agent. The version used in this benchmark is v1.10.4.

Developers from BioDynaMo, Chaste, PhysiCell and TiSim gathered on September 22 and 23 to build and run the different tests in a hybrid hackathon: 12 people were present at BSC and 10 others were online; all four teams had people onsite and online. The goal of the hackathon was to adapt the tools to the list of tests and to simulate the maximum number of use cases in this two-day exercise.

*Benchmarks run by the tools*

Not all teams had the time to adapt their tools to all these tests. Thus, we prioritised the implementation of the unit tests to at least compare some of the solvers of each tool (Table 2.1.2a). All the tools were used to simulate some tests in local workstations. BioDynaMo and PhysiCell could run some tests in the MareNostrum4 HPC (MN4) cluster at BSC (Table 2.1.2b).

**Table 2.1.2a: Tests run locally by the different tools in local workstations.**

<table>
  <tr>
   <td>
   </td>
   <td><strong>BioDynaMo</strong>
   </td>
   <td><strong>Chaste</strong>
   </td>
   <td><strong>PhysiCell</strong>
   </td>
   <td><strong>TiSim</strong>
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_cellcycle</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_cellcycle_stoch</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_chemotaxis</strong>
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_diffusion</strong>
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_diffusion_1k</strong>
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_mechanics_friction_single</strong>
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_mechanics_pushing</strong>
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>use_case_2Ddisk</strong>
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>use_case_spheroid</strong>
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong>use_case_spheroid_diff</strong>
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>N
   </td>
  </tr>
</table>

**Table 2.1.2b: Tests run by the different tools in the MareNostrum4 cluster.**

<table>
  <tr>
   <td>
   </td>
   <td><strong>BioDynaMo</strong>
   </td>
   <td><strong>PhysiCell</strong>
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_cellcycle</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_cellcycle_stoch</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_chemotaxis</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_diffusion</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_diffusion_1k</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_mechanics_friction_single</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>unit_test_mechanics_pushing</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>use_case_2Ddisk</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>use_case_spheroid</strong>
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong>use_case_spheroid_diff</strong>
   </td>
   <td>N
   </td>
   <td>N
   </td>
  </tr>
</table>

The complete description of the unit tests and use case can be found in Appendix 1.

*Metrics for the benchmarks*

As the aim of this benchmark was to compare the tests across tools to learn about differences in their implementations and in the simulations’ results, we focused on the scientific metrics more than on the technical (runtime) metrics. 

Performance benchmarks are planned for the future when a better understanding of the simulation methods used by the codes enabled more accurate interpretation of results. 

The non-comprehensive list of reason to not focus presently on the technical metrics to do a performance analysis could be exemplified by:

1. The use cases and unit tests were implemented in two days and there were chances that some hot spots were introduced in the application code which would not really reflect on the tools’ performance, but rather on the proficiency of the developers in their implementation.
    1. Note: We acknowledge that this is a problem common to all hackathons with few solutions at hand to solve it.
2. Some unit tests were much smaller than the typical use cases that these tools were made for; thus, the times computed may have overheads not directly related to the simulation (verification of the container, OpenMP thread management, writing of files, etc.).
    2. Note: We acknowledge that this bias is common to all tools and in fact studying this overhead across tools could be of interest to study algorithm implementations that minimise these overheads.
3. Some tools were not open source; while we discussed the mathematics and algorithms of all the tools, it is not possible to know details about the implementation of the different use cases.
    3. Note: This problem has no easy solution. If we aim to compare open-source and proprietary tools we might need to look only at their simulation results, as studying their implementation is not possible.

We consider these problems a warning against the eagerness to compare performance numbers of the tools with these results, emphasising the fact that this effort was a needed step to have a true performance competition sometime in the future.

Additionally, focusing on the scientific metrics allowed the teams to execute their tools in their own local workstation and bypass compilation problems some of them had in the MN4 cluster.

Furthermore, BioDynaMo and PhysiCell were able to run in MareNostrum4 and technical metrics were gathered, but as the focus of this benchmark was agreed to be on the scientific metrics, we have not analysed these metrics.

MareNostrum4 is a supercomputer based on Intel Xeon Platinum processors from the Skylake generation. It is a Lenovo system composed of SD530 Compute Racks, an Intel Omni-Path high performance network interconnect and running SuSE Linux Enterprise Server as the operating system. This general-purpose block consists of 48 racks housing 3456 nodes with a grand total of 165,888 processor cores and 390 Terabytes of main memory. The compute nodes are equipped with 2 sockets Intel Xeon Platinum 8160 CPU with 24 cores each @ 2.10GHz for a total of 48 cores per node with 2 GB of memory per node.

*Results of the benchmarks*

Although these frameworks are used to model, among other things, the growth of cells and their surrounding microenvironment, we first needed a coordinated effort to implement the different unit tests and use cases in all the tools, so as to use computational configurations, use cases, and model specifications that were as similar as possible across them. Luckily, some of these tests could be completed by adapting already existing use-case-specific code in the different tools. 

All the results and code run by the tools were gathered in a public repository ([https://github.com/PerMedCoE/observatory_benchmark/tree/main/multiscale_benchmark/2022_09_hackathon](https://github.com/PerMedCoE/observatory_benchmark/tree/main/multiscale_benchmark/2022_09_hackathon)).

a) Unit tests

1. Cell cycle, fixed duration

This unit test focused on how the volume changes across a cell cycle model with four phases (G1, S, G2 and M). The goal was to see if the cell cycle models with a fixed duration across tools yielded different results.

As an objective, we set to have the phases with these times (G0/G1: 7 hours, S: 6 hours, G2: 3 hours, M: 2 hours, Total 18 h) and try to imitate the volume change from MultiCellDS preprint (Friedman _et al._, 2016) (Figure 2.1.2.a)

![Figure 2.1.2.a: Simulated time of the volume dynamics targeted in this unit test.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen1.png)

<!-- ![Figure 1. Cell counts for the three cell populations tools after 120 minutes of simulation for Chaste (A), PhysiCell (B) and Timothy (C). Note that the x-axis in panels A and B are in minutes and in panel C is in hours and that y-axis have different ranges across panels.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/prelim/Fig1.svg) -->

**Figure 2.1.2.a: Simulated time of the volume dynamics targeted in this unit test. The data matrix of this curve can be found in the GitHub website ([https://github.com/PerMedCoE/observatory_benchmark/tree/main/multiscale_benchmark/2022_09_hackathon/experimental_data/unit_test_cellcycle](https://github.com/PerMedCoE/observatory_benchmark/tree/main/multiscale_benchmark/2022_09_hackathon/experimental_data/unit_test_cellcycle))**

In this case, the difference of the volume changes of Chaste and PhysiCell can be explained by the different types of functions used to increase this volume (Figure 2.1.2.b). While Chaste has a linear increase of volume in the G1 phase, PhysiCell has non-linear one across the S, G2 and M phases. Both of them divide the volume at the end of the M phase, but with some time differences that increase at each cycle.

![Figure 2.1.2.b: Simulated time of the volume dynamics of cells’ volume in Chaste, PhysiCell and TiSim with a cell cycle of a fixed duration.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen2.png)

**Figure 2.1.2.b: Simulated time of the volume dynamics of cells’ volume in Chaste, PhysiCell and TiSim with a cell cycle of a fixed duration.**

The results indicate that in spite of trying to use similar cell cycle modes, TiSim, Chaste and PhysiCell have simulated models with different dynamics. Future tests will need to be closer to the volume change that we set as objective. Additionally, we will need to correct PhysiCell’s volume change at phase G1, as we see a flat line in the first cycle, but a slightly increasing one in the following two cycles.

1. Cell cycle, stochastic duration

This unit test focused on studying the stochasticity that can be applied to the cell cycle duration. The idea was to have a 10% Gaussian standard deviation around the times from the fixed cell cycle (G0/G1: 7 hours, S: 6 hours, G2: 3 hours, M: 2 hours, Total 18 h). The objective was to see if this 10% was equally applied across tools.

For this test we compared Chaste and PhysiCell and plotted the volume changes of each of the cells. Both start with one cell and each daughter cell has its own line (Figure 2.1.2.c). Chaste seems to have a smaller variation of time duration than PhysiCell, as the green lines have bigger changes in duration than the blue ones.

![Figure 2.1.2.c: Simulated time of the volume dynamics of cells’ volume in Chaste, PhysiCell and TiSim with a cell cycle of stochastic duration.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen3.png)

**Figure 2.1.2.c: Simulated time of the volume dynamics of cells’ volume in Chaste, PhysiCell and TiSim with a cell cycle of stochastic duration.**

As TiSim, Chaste and PhysiCell have a 10% variation for each phase, the cause of the differences among tools might be on different random number generators. This would explain that some phases in PhysiCell are really short and others are quite long, as in the case of some G1 phases.

3. Diffusion of molecules, one cell as sink

The unit test focused on comparing the results of the diffusion solver for the substrate freely roaming in the simulations. The idea was to have a substrate being produced in the boundary of the box and having a cell acting as a sink in the middle of the space. The objective was to see if all the tools reached the same steady state and how they reached this steady state.

The comparison of the results from BioDynaMo and PhysiCell indicate that these tools have been set-up differently (Figure 2.1.2.d).

![Figure 2.1.2.d: Simulated time of the dynamics of the central voxel’s concentration in BioDynaMo and PhysiCell.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen4.png)

**Figure 2.1.2.d: Simulated time of the dynamics of the central voxel’s concentration in BioDynaMo and PhysiCell.**

While BioDynaMo starts with 10 uM in all the 27 voxels, PhysiCell starts with 10 uM in all the voxels except the central one, where the sink is. This causes the dynamics to be different and opposite.

4. Mechanics, movement of a cell with friction

In this unit test a cell is moving through space with a given drag friction that is slowing it down. The idea was that the force is applied once and after that you only have dissipative forces. The goal was to see if the mechanics models of cells moving in a free space yielded different results.

The differences that we can see in the results for BioDynaMo and PhysiCell (Figure 2.1.2.e) come from the different inertial assumptions of both tools. BioDynamo has an inertial component to its movement equation that causes the cell to dampen its velocity at each time step. PhysiCell, on the other hand, assumes that the cell is inertia-less, causing the movement to be different: once the force is applied the velocity hits a spike, it is slowed down by the friction and then remains at a lower speed.

![Figure 2.1.2.e: Simulated time of the dynamics of the distance travelled of the cell in BioDynaMo and PhysiCell.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen5.png)

**Figure 2.1.2.e: Simulated time of the dynamics of the distance travelled of the cell in BioDynaMo and PhysiCell.**

These results are different among the tools as their movement equations are different. This is a case where the definition of the problem was incomplete and should have stated explicitly what the assumptions of the movements were, let it be inertia or inertia-less.

5. Mechanics, two cells pushing each other

This unit test consisted of studying two cells pushing each other. The goal was to see if the mechanics models with collisions across tools yielded different results.

For this test we can compare BioDynamo, PhysiCell and TiSim (Figure 2.1.2.f). First, we see that each tool has a different speed for the cell, which explains the different slopes at the start of the simulation. Second, we see different behaviours once the cells have made contact. In TiSim, the cells approach and they gradually close their distance until they are together. In BioDynamo, the cells rebound once and the cells stay at a distance greater than the minimum one. In PhysiCell, the rebounding between the cells does not stop: once they make contact, the distance between cells varies until the end of the simulation.

![Figures 2.1.2.f: Simulated time of the dynamics of the distance between the two cells in BioDynaMo, PhysiCell and TiSim.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen6.png)

**Figures 2.1.2.f: Simulated time of the dynamics of the distance between the two cells in BioDynaMo, PhysiCell and TiSim.**

These results show that different tools have different underlying mechanical models. While TiSim is a pure inertialess movement with no rebound, BioDynamo shows some rebounding effect. We consider that the cause of PhysiCell’s behaviour is that the cells had a persistence movement that was not needed for this unit test, causing the cells to look for the other one throughout the test.

b) Use cases

1. 2D monolayer without diffusion

With this use case we aimed at simulating a one-cell-thick monolayer of cells growing on a surface. This use case gathered functions that we had tested in different unit tests as the cell cycle and mechanics ones in a different, more complex setup.

As an objective, we set to simulate experimental results from a 1998 work (Brú _et al._, 1998) also reported in other works (Drasdo and Hoehme, 2005; Hoehme and Drasdo, 2010) (Figure 2.1.2.g) and available in the GitHub website ([https://github.com/PerMedCoE/observatory_benchmark/tree/main/multiscale_benchmark/2022_09_hackathon/experimental_data/use_case_2Ddisk](https://github.com/PerMedCoE/observatory_benchmark/tree/main/multiscale_benchmark/2022_09_hackathon/experimental_data/use_case_2Ddisk)). 

![Figure 2.1.2.g: Copy of Figure 1 from Drasdo and Hoehme (2005) where the monolayer data of interest are full circles.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen7.png)

**Figure 2.1.2.g: Copy of Figure 1 from Drasdo and Hoehme (2005) where the monolayer data of interest are full circles.**

For this use case we had data from BioDynamo, PhysiCell and TiSim that we wanted to compare to an experimental dataset. We focused the analysis in the days from 14 to 28, where we can see a linear growth of the diameter (Figure 2.1.2.h). We see that most of the simulated results overlap one another and are close to the experimental ones, with TiSim maybe slightly closer to the first experimental data points than the others. 

![Figure 2.1.2.h: Simulated time of the dynamics of the monolayer’s diameter change in BioDynaMo, PhysiCell and TiSim compared to experimental values.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen8.png)

**Figure 2.1.2.h: Simulated time of the dynamics of the monolayer’s diameter change in BioDynaMo, PhysiCell and TiSim compared to experimental values.**

Interestingly, from Figure 2.1.2.h, we can see that the slopes from each tool are different. This may be caused by the different models of cell cycle or mechanics among tools and/or by a different growth dynamic in the first 14 days of simulation.

2. Spheroid without diffusion

With this use case we aimed at simulating a hanging drop experiment growing on a volume of collagen. Again, this use case gathered functions that we had tested in different unit tests as the cell cycle, mechanics and diffusion ones in a different, more complex setup.

As an objective, we set to simulate experimental results from a 1986 work (Freyer and Sutherland, 1986) also reported in other works (Drasdo and Hoehme, 2005; Hoehme and Drasdo, 2010) and available here ([https://github.com/PerMedCoE/observatory_benchmark/tree/main/multiscale_benchmark/2022_09_hackathon/experimental_data/use_case_spheroid_diff](https://github.com/PerMedCoE/observatory_benchmark/tree/main/multiscale_benchmark/2022_09_hackathon/experimental_data/use_case_spheroid_diff)).

This was also the use case that was closest to the one used in the preliminary benchmark presented in D3.3, where we aimed at using Chaste, PhysiCell and Timothy to simulate the growth of a cell population in the shape of a spheroid and its response to the presence of oxygen for two hours of walltime. Cells would grow until reaching a threshold level where oxygen could not get in the middle of the spheroid, causing cell death.

Unfortunately, we were unable to run long enough simulations with the tools to compare them with the experimental values of Freyer and Sutherland (1986) that were collected for 20 days. This is ongoing work that we plan on performing for the following benchmark report.

#### 2.1.3. Perspectives

We have described how we built and organised a community-driven benchmark for multiscale tools. Despite our best efforts, we still have tests to perform to complete this benchmark. Thus, we plan to finish the proposed use cases and to better detail the tests that were implemented differently among tools. For instance, we found out that the cells pushing or the diffusion unit tests were not completely detailed and that caused developers to deviate in the coding of these tests. 

With the results of these tests, we plan to compare the mathematics of the functions and the implementation of the tools to check that we are comparing exactly the same behaviours. For instance, we suspect that the tools are using different functions in the cell cycle unit tests and have different inertia assumptions for the mechanics of the movement of cells.

In parallel, PerMedCoE will disseminate this benchmark to include more tools to the set. We consider this benchmark to be the first of many and we would like to have more multiscale tools onboard. 

Finally, once we are sure that the tools are simulating the same behaviours, we plan to focus future benchmarks on the performance of the tools and to test their scalability in pre-exascale HPC clusters. We will build on the test performed in MareNostrum4 cluster (Table 2.1.2b) to benchmark the tools and study their strong scaling (where the number of processors is increased while the problem size remains constant) and weak scaling (where both the number of processors and the problem size are increased). In these performance tests we will focus on the technical metrics that have not been inspected in the present deliverable.

### 2.2. Boolean modelling

This benchmark focuses on tools simulating Boolean networks. The tools selected can all simulate these models using asynchronous update and most of them use probabilistic approaches. 

#### 2.2.1. Use cases

A classic task when simulating Boolean networks is to find stable states of the system, which in our case correspond to possible phenotypes of the biological system represented. The most simple type of stable state of a Boolean network is called a fixed point, and is defined as a state where no further transition is possible. The search for these fixed points can either focus on those reachable from a specific set of conditions or be a global search. These fixed points can be very difficult to find when the models get very large, and in practice above a certain size (~50 nodes), only probabilistic approaches are possible. One aspect of the benchmark is the global search of these fixpoints. For this we want to choose multiple models and produce a list of all the fixed points of the models, as well as a list of fixed points only reachable from some specific conditions. We would then compare our tools' performances in finding these fixpoints. 

Another important task of these Boolean simulators is the quantification of the probability of reaching these fixed points. When applying these models to biological systems, this means quantifying the relative abundance of certain phenotypes. To measure these probabilities, multiple simulations are performed, and then usually the software will measure the final distributions of the fixed points reached by these multiple simulations to compute probabilities. 

Both of these use cases focus on the behaviour at steady state, but another interesting aspect of Boolean simulation are the transient effects. One possibility would be to compare simulation trajectories of the Boolean models. For this, two main classes of methods are available: discrete or continuous time. Since some tools in this benchmark are not able to simulate using continuous time, we propose to focus first on comparing trajectories of model simulation in discrete time.

#### 2.2.2. Benchmark framework

We are developing a singularity image with scripts implementing the previously described use cases, and the methods to perform statistics on performance. This framework has been implemented for MaBoSS, with a first selection of models and associated ground-truth results. The singularity image of the framework is already available on the github repository of the observatory benchmark ([https://github.com/PerMedCoE/observatory_benchmark/tree/main/Boolean_benchmark](https://github.com/PerMedCoE/observatory_benchmark/tree/main/boolean_benchmark)).

#### 2.2.3. Next steps of the community benchmark

We are now planning our next meeting to discuss the implementation of the use cases in our benchmarking framework by the tools owners. We will also evaluate the specific models involved in this benchmark.

### 2.3. Constraint-based modelling

The benchmarking approach to constraint-based modelling methods is shaped by two primary concerns. First, the landscape of available tools is extremely diverse, which is caused not only by the relatively wide definition of “constraint-based modelling”, but also by the many use-cases that the tools are used for, allowing much variability and interpretability in the results. 

Second, the output of constraint-based modelling is typically defined algebraically (most frequently as a single optimal solution of a constrained linear or quadratic-objective problem) and both the accuracy and performance of the tool is thus mostly derived from the accuracy and performance of the downstream constrained problem solvers. At the same time, comparison of accuracy is often useless (the solutions are typically either valid or invalid, without any measurable middle ground). In both the benchmark and the observatory we thus selected several observable, benchmarkable properties of various software pieces (not necessarily the whole toolboxes), as described below.

#### 2.3.1. Benchmark framework

To systematise the selection of tools to be benchmarked and the community possibilities, we started the benchmarking effort by preliminary information mail sent to multiple tool authors. We unfortunately received only a relatively small amount of responses, which nevertheless pointed out the lack of common benchmarking ground in the tools and highlighted the necessity to benchmark the downstream constrained problem solvers, and pointed out a related necessity to benchmark various other subroutines (among other, ability to manage loading extremely large models, and flux sampling methods).

The current benchmarking effort thus includes:

1. Linear optimization problem solvers, such as Gurobi ([https://www.gurobi.com/](https://www.gurobi.com/)), CPLEX ([https://www.ibm.com/analytics/cplex-optimizer](https://www.ibm.com/analytics/cplex-optimizer)), CLP ([https://github.com/coin-or/Clp](https://github.com/coin-or/Clp)), GLPK ([https://www.gnu.org/software/glpk/](https://www.gnu.org/software/glpk/)), Tulip (Anjos _et al._, 2021), OSQP ([https://osqp.org/](https://osqp.org/)), and others. 

COBREXA.jl is well-suited base package for executing the benchmarks, as the ecosystem allows direct use of a wide spectrum of available solver software through the JuMP interface (over 40 individual solvers are listed at [https://jump.dev/JuMP.jl/stable/installation/#Supported-solvers](https://jump.dev/JuMP.jl/stable/installation/#Supported-solvers)). 

We observed interesting speedups resulting from application of new quadratic optimization solvers such as Clarabel.jl ([https://github.com/oxfordcontrol/Clarabel.jl](https://github.com/oxfordcontrol/Clarabel.jl)), which could be confirmed by the benchmark to speed up analyses such as minimization of metabolic adjustment. Example output of the benchmarking, useful for user decisions about solver choice, can be seen in Figure 2.3.a. Currently, the comprehensive statistics of solver performance on metabolic modelling tasks are being transformed into a form viable for presentation in the OpenEBench site.

![Figure 2.3.a: Example output of linear optimizer performance benchmark as driven by COBREXA.jl to solve a basic constraint-based metabolic modelling problem on 7 selected models.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen9.png)

**Figure 2.3.a: Example output of linear optimizer performance benchmark as driven by COBREXA.jl to solve a basic constraint-based metabolic modelling problem on 7 selected models. Missing solver entries represent solver failures on the model.**

2. Implementations of individual analysis methods in the specific constraint-based modelling packages that were selected for comparison.

We collected the results as a large feature matrix with a plan to publish it on OpenEBench site if the visualisation support for feature matrices can be achieved; otherwise likely publishing by different means, such as the GitHub repository ([https://github.com/PerMedCoE/observatory_benchmark](https://github.com/PerMedCoE/observatory_benchmark)).

3. Efficiency and parallelization potential of the individual constraint-based modelling packages.

After the preliminary benchmark that we conducted for publication purposes that compared efficiency of flux variability analysis and production envelope analysis of COBREXA.jl to the ones of the main toolboxes (Kratochvíl _et al._, 2022), we aimed to systematise the result collection and plotting for OpenEBench website. An example output of the benchmarks has been presented in Deliverable 1.2, current work is extending the benchmark to other methods.

4. We additionally aim to benchmark flux sampling implementations, but we decided to postpone the effort until the publication of a custom GPU-accelerated sampler for COBREXA.jl that is under development.

#### 2.3.2. Next steps of the community benchmark

As the main next effort, we aim to develop a suitable automated pipeline for streamlining the presentation of the benchmarking results at the OpenEBench website, likely building upon the pipelines developed for publishing the cell population modelling benchmarks (as described in section 2.1.1). The community engagement will continue after the full set of preliminary benchmarks is published, which should provide suitable discussion ground for improvements and inclusion of more tools.

Based on the discussion with the constraint-based modelling community and model authors at recent conferences, we joined the model reproducibility testing effort led by EBI/BioModels team, which resulted in implementation of a dedicated COBREXA.jl-based package FBCModelTests for testing the model contents ([https://github.com/LCSB-BioCore/FBCModelTests.jl/](https://github.com/LCSB-BioCore/FBCModelTests.jl/)). We expect that extensive scrutinization of the existing models will provide a realistic source of benchmarking cases for later inclusion in OpenEBench reports.

Further benchmarking of software is supported by ongoing effort to port the main PoPCoE performance measurement tools to the Julia ecosystem, thus allowing to measure detailed performance statistics of the Julia software and direct comparison thereof with software from other ecosystems. Packaging of Extrae for Julia is currently delayed by minor portability issues (see [https://github.com/JuliaPackaging/Yggdrasil/pull/5710](https://github.com/JuliaPackaging/Yggdrasil/pull/5710)) that can be solved with PoPCoE developers.

### 2.4. CellNOpt/CARNIVAL benchmarks

As was described in D3.3, CellNOpt and CARNIVAL are two similar tools for contextualization of signalling networks. CellNOpt uses (phospho)proteomics data from multiple conditions to infer a signalling network from a scaffold network that is able to explain the observed data, whereas CARNIVAL uses differential expression data to contextualise a scaffold network by selecting the subnetwork that explains the observed changes between conditions.

#### 2.4.1. Benchmark framework

In terms of functionality, CellNOpt does both parameter fitting and simulation. Simulations are used to evaluate how well a network can reproduce a set of experiments, and this information is used by the stochastic optimizer to refine and improve the solution. Given this separation between parameter estimation and simulation, CellNOpt supports a variety of simulation methods, including MaBoSS. In this way, MaBoSS can be used as a simulation tool and CellNOpt as a parameter fitting tool. This particularity leads to a significant overlap between the two methods and therefore the available competing tools. During our analysis, we have not found tools that do exactly the same as CellNOpt (parameter fitting integrated with Boolean simulation), but only tools for Boolean simulations. 

Table 2.4.a shows the main competitor tools for CellNOpt and how they compare in terms of features. CellNOpt supports both time continuous/discrete simulations for ODE based models and sync/async for Boolean networks.


<table>
  <tr>
   <td><strong> </strong>
   </td>
   <td colspan="2" ><strong><em>Simulation w/ continuous states</em></strong>
   </td>
   <td colspan="2" ><strong><em>Simulation w/ Boolean states</em></strong>
   </td>
   <td rowspan="2" ><strong><em> </em></strong>
<p>
<strong><em>Import/export with standards (SBMLqual)</em></strong>
   </td>
   <td><strong><em> </em></strong>
<p>
<strong><em>Model fitting / parameter estimation</em></strong>
   </td>
  </tr>
  <tr>
   <td><strong>Tool</strong>
   </td>
   <td><strong><em>Continuous in time</em></strong>
   </td>
   <td><strong><em>Discrete in time</em></strong>
   </td>
   <td><strong><em>Synchronous updates</em></strong>
   </td>
   <td><strong><em>Asynchronous updates</em></strong>
   </td>
   <td>
   </td>
  </tr>
  <tr>
   <td><strong>CellNOpt </strong>(Terfve et al. 2012)
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong><em>GINsim </em></strong> (Chaouiya, Naldi, and Thieffry 2012)
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong><em>MaBoSS </em></strong>(Stoll et al. 2012)
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong><em>FALCON </em>(Landtsheer et al. 2017)
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong><em>BoolNet </em></strong>(Müssel, Hopfensitz, and Kestler 2010)
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong><em>BooleanNet </em></strong>(Albert et al. 2008)
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong>SQUAD (Di Cara et al. 2007)</strong>
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong><em>optPBN </em>(Trairatphisan et al. 2014)</strong>
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong><em>OptimusQual </em></strong>(Dorier et al. 2016)
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong><em>ViSiBool </em></strong>(Schwab et al. 2018)
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong><em>GNA </em></strong>(Batt et al. 2012)
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong><em>PRUNET </em></strong>(Rodriguez et al. 2015)
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>N
   </td>
   <td>Y
   </td>
  </tr>
  <tr>
   <td><strong><em>Odefy </em></strong>(Krumsiek et al. 2010)
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong><em>Cell Collective </em></strong>(Helikar et al. 2012)
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
  <tr>
   <td><strong><em>BMA </em></strong>(Benque et al. 2012)
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>Y
   </td>
   <td>N
   </td>
   <td>Y
   </td>
   <td>N
   </td>
  </tr>
</table>

**Table 2.4.a: Available competitor tools for logic modelling of biological networks. Green colour indicates presence of a particular feature in the tool. Features are classified according to 4 different categories depending on the supported type of modelling (continuous or discrete in time, sync/async updates for Boolean networks), and also depending on if the tool includes a GUI, ability to import/export SBML/qual standard format, and possibility to fit parameters given data to train a model. From (Hosseini-Gerami _et al._, 2022).**


As can be seen in Table 2.4.a, different tools cover different simulation formalisms and capabilities, which makes the comparison between tools very challenging. One special characteristic of CellNOpt is the ability to fit models to data using different optimization algorithms (e.g. Genetic Algorithms, ILPs), which only few tools support. All these tools used only shared memory, no distributed memory is available for them (except the work on MaBoSS and MPI done in the present project). Likewise, none of these tools are able to use accelerator support.

Table 2.4.b shows a comparison in  terms between the tools that support parameter fitting on Boolean networks (CellNOpt+MaBoSS, CellNOptR, CNORode and FALCON). Results show the best error (Mean Squared Error) and total time in seconds, using a published model with 30 species and 33 reactions, by MacNamara et al. 2012. CellNOptR, using a deterministic Boolean simulator, achieves a good balance between error and training time, being the fastest method for learning the parameters of the Boolean network for this case study.

<table>
  <tr>
   <td><strong>Software</strong>
   </td>
   <td><strong>MSE</strong>
   </td>
   <td><strong>Time (<em>s</em>)</strong>
   </td>
  </tr>
  <tr>
   <td><strong>CellNOpt-MaBoSS</strong>
   </td>
   <td>0.0321
   </td>
   <td>179.797
   </td>
  </tr>
  <tr>
   <td><strong>CellNOptR</strong>
   </td>
   <td>0.0545
   </td>
   <td>0.246
   </td>
  </tr>
  <tr>
   <td><strong>CNORode</strong>
   </td>
   <td>0.0062
   </td>
   <td>405.598
   </td>
  </tr>
  <tr>
   <td><strong>FALCON</strong>
   </td>
   <td>0.0118
   </td>
   <td>14.849
   </td>
  </tr>
</table>

**Table 2.4.b: Comparison between CellNOpt (different formalisms) and FALCON, from (Hosseini-Gerami _et al._, 2022).**

Despite the differences in supported features across the competitor tools, another issue identified is the lack of maintenance for many of the tools, being CellNOpt and MaBoSS the tools with the most latest commits and features.

One current limitation of the methods similar to CARNIVAL is the inability to learn networks given we have multiple perturbations of the same system, in a way similar to CellNOpt related tools, but when a simulable model of the biological system is not known. As it is becoming increasingly common to find datasets with data on multiple perturbations on the same biological system ([http://projects.sanderlab.org/scperturb/](http://projects.sanderlab.org/scperturb/)), current tools need to adapt to this new more challenging problem, both in computational and scientific terms.

We have extended CARNIVAL to support learning from multiple conditions, and we initiated a collaboration with Lauffenburger lab at MIT, as they are currently developing a method based on RNNs (LEMBAS) that learns a network from known perturbations to transcription factors, that could be compared with CARNIVAL multi-condition (Nilsson _et al._, 2022). As part of the PerMed technology observatory task, we contacted and initiated a collaboration between Lauffenburger’s lab and UKHD to compare our extended tools with LEMBAS.  A comparative is planned to be finished by the month 36.

## 3. Conclusions and future work

In this deliverable, we have presented the step taken towards benchmarking all PerMedCoE core tools against relevant tools from their different cell-level modelling fields. These benchmarks should aim to assess the status of the field, defining the best applications to integrate in the CoE activities and engaging with the software users and developers.

We are adamant about publicising and disseminating the PerMedCoE observatory and benchmark results to increase the awareness of these tools in potential users and in facilitating their choice selecting a tool that is the most appropriate for their project. The observatory is publicly accessible at this link: [https://permedcoe.bio.tools/](https://permedcoe.bio.tools/)  and the benchmarks are publicly accessible at these links: [https://openebench.bsc.es/benchmarking/OEBC009](https://openebench.bsc.es/benchmarking/OEBC009) and [https://github.com/PerMedCoE/observatory_benchmark](https://github.com/PerMedCoE/observatory_benchmark). 

## 4. References

Anjos,M.F. _et al._ (2021) Design and implementation of a modular interior-point solver for linear optimization. _arXiv_, **13**, 509–551.

Breitwieser,L. _et al._ (2021) BioDynaMo: a modular platform for high-performance agent-based simulation. _Bioinformatics_.

Brú,A. _et al._ (1998) Super-Rough Dynamics on Tumor Growth. _Phys. Rev. Lett._, **81**, 4008–4011.

Butcher,J.C. (2003) Numerical methods for ordinary differential equations J. Wiley, Chichester, West Sussex, England ; Hoboken, NJ.

Ciavarella,M. _et al._ (2019) The role of adhesion in contact mechanics. _J. R. Soc. Interface_, **16**, 20180738.

Cooper,F. _et al._ (2020) Chaste: Cancer, Heart and Soft Tissue Environment. _J. Open Source Softw._, **5**, 1848.

Drasdo,D. and Hoehme,S. (2005) A single-cell-based model of tumor growth _in vitro_ : monolayers and spheroids. _Phys. Biol._, **2**, 133–147.

Dunn,S.-J. _et al._ (2013) Computational Models Reveal a Passive Mechanism for Cell Migration in the Crypt. _PLOS ONE_, **8**, e80516.

Dunn,S.-J. _et al._ (2012) Modelling the role of the basement membrane beneath a growing epithelial monolayer. _J. Theor. Biol._, **298**, 82–91.

Freyer,J.P. and Sutherland,R.M. (1986) Regulation of Growth Saturation and Development of Necrosis in EMT6/Ro Multicellular Spheroids by the Glucose and Oxygen Supply1. _Cancer Res._, **46**, 3504–3512.

Friedman,S.H. _et al._ (2016) MultiCellDS: a community-developed standard for curating microenvironment-dependent multicellular data. _bioRxiv_, 090456.

Ghaffarizadeh,A. _et al._ (2018) PhysiCell: An open source physics-based cell simulator for 3-D multicellular systems. _PLOS Comput. Biol._, **14**, e1005991.

Hoehme,S. _et al._ (2010) Prediction and validation of cell alignment along microvessels as order principle to restore tissue architecture in liver regeneration. _Proc. Natl. Acad. Sci._, **107**, 10371–10376.

Hoehme,S. and Drasdo,D. (2010) A cell-based simulation software for multi-cellular systems. _Bioinformatics_, **26**, 2641–2642.

Hosseini-Gerami,L. _et al._ (2022) Benchmarking causal reasoning algorithms for gene expression-based compound mechanism of action analysi. _BMC Bioinforma. Prepr._

Kratochvíl,M. _et al._ (2022) COBREXA.jl: constraint-based reconstruction and exascale analysis. _Bioinformatics_, **38**, 1171–1172.

Letort,G. _et al._ (2019) PhysiBoSS: a multi-scale agent-based modelling framework integrating physical dimension and cell signalling. _Bioinformatics_, bty766.

Metzcar,J. _et al._ (2019) A Review of Cell-Based Computational Modeling in Cancer Biology. _JCO Clin. Cancer Inform._, 1–13.

Nilsson,A. _et al._ (2022) Artificial neural networks enable genome-scale simulations of intracellular signaling. _Nat. Commun._, **13**, 3069.

Osborne,J.M. _et al._ (2017) Comparing individual-based approaches to modelling the self-organization of multicellular tissues. _PLOS Comput. Biol._, **13**, e1005387.

Ramis-Conde,I. and Drasdo,D. (2012) From genotypes to phenotypes: classification of the tumour profiles for different variants of the cadherin adhesion pathway. _Phys. Biol._, **9**, 036008.

Van Liedekerke,P. _et al._ (2015) Simulating tissue mechanics with agent-based models: concepts, perspectives and some novel results. _Comput. Part. Mech._, **2**, 401–444.

# Appendix 1: Unit tests and use cases description

## Unit tests
### *Cell cycle, fixed duration*

**Motivation**: compare cell cycle among tools with a fixed-duration model

**Description**: 1 cell dividing using a fixed-duration cell cycle model in a 60um domain size

**Initial conditions**:

* 1 cell
* Cell cycle of 4 phases: G0/G1 -> S -> G2 -> M (look at MulticellDS preprint (Friedman _et al._, 2016), its cell cycle suppfile under the “Separated flow cytometry” name ([https://figshare.com/articles/journal_contribution/Supported_MultiCellDS_Cell_Cycle_Models/4269263/1](https://figshare.com/articles/journal_contribution/Supported_MultiCellDS_Cell_Cycle_Models/4269263/1)))
* Fixed duration: G0/G1: 7 hours, S: 6 hours, G2: 3 hours, M: 2 hours, Total 18 h
* The cell shapes should be spheres, unless the tool allows for different shapes.
* The cell should not die.
* Initial size of cell: 10 um
* Phenotype Δt= 6 min
* Total simulated time= 48 h = 2880 min

![The volume dynamic with the phases from MulticellDS (Friedman _et al._, 2016) used as a standard can be inspected in Figure 2.1.2.a.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/Imagen10.png)

The volume dynamic with the phases from MulticellDS (Friedman _et al._, 2016) used as a standard can be inspected in Figure 2.1.2.a.

**Data expected from the tools and metrics to be compared**:

* Compare volume dynamics across tools. The tools need to print these volumes at each time step (6 min)
* Compare how different tools can have different division of this volume
* Runtime metrics (CPU, memory, energy consumption)

### *Cell cycle, stochastic duration*

**Motivation**: compare cell cycle among tools with a stochastic duration

**Description**: 1 cell dividing using a stochastic-duration cell cycle model

**Initial conditions**:

* 1 cell
* Mean duration: G0/G1: 7 hours, S: 6 hours, G2: 3 hours, M: 2 hours. Total = 18 hours
* Gaussian Standard Deviation duration: 10% of time
* Radius of cell: 10 um
* Phenotype Δt= 6 min
* Total simulated time= 48 h = 2880 min

**Data expected from the tools and metrics to be compared**:

* Compare volume dynamics across tools and with respect to the fixed duration unit test. We need the position of the cell at each time step (6 min). The tools need to print these concentrations at each time step (6 min)
* Compare how different tools can have different division of this volume
* Runtime metrics (CPU, memory, energy consumption)

### *Diffusion of molecules, one cell as sink*

This use case tests the PDE solver of the tool (if there is one). 

The diffusion equation reads:

* Boundary condition: _c(x,t)=c<sub>0</sub>_ on the boundaries of a cube of edge length 60 um, choose as sink location the centre of the domain.
* Simulation domain is 60 x 60 x 60 um<sup>3</sup>
* Initial condition: c(x,t=0)=0 inside the simulation domain.
* c<sub>0</sub> = 10uM, \lamba = 20uM/0.01min, D= 2000 um^2/min

**Motivation**: compare diffusion solvers among tools

**Description**: 1 cell acting as a sink in the centre of the cell localised at the centre of a small domain of 60 um each side

**Initial conditions**:

* 1 cell (acting as sink)
* Each source-voxel produces 10 uM (6022 particles/voxel), at t=0 no voxel has substrate
* The cell uptakes 20uM/min = 12044 substrates/min
* Diffusion Δt = 0.01min 
* Total time= 10 min or until a steady state has been reached (whichever comes first)
* Diffusion coefficient: 2000 um^2/min

**Data expected from the tools and metrics to be compared**:

* The goal is to capture the concentration changes in the domain until the diffusion reaches the equilibrium. For instance, for FVM tools, compare the voxel-specific concentration changes c(i,k,l;t) with i, k, l enumerating the voxels in x, y, z-direction i.e., i=-1, 0, 1, k=-1, 0, 1, l=-1, 0, 1 among tools. For FEM, discretise the domain and have 27 equally spaced measures across the domain.
* The tools need to print these concentrations at each time step (0.01 min)
* Runtime metrics (CPU, memory, energy consumption) (exclude compilation!)

### *Diffusion of molecules, 1k cells as sinks*

**Motivation**: compare diffusion among tools with a bigger workload to take advantage of the OpenMP overhead.

1k cells acting as sinks evenly spaced out on a bigger domain (240 um box)

The rest is the same than the previous unit test

**Data expected from the tools and metrics to be compared**:

* Compare the voxel-specific concentration changes among tools and with respect to the 1 cell diffusion unit test. The tools need to print these concentrations at each time step (0.01 min)
* Compare summary measures: (For 1728 voxels we would probably need a kind of summary measure. This could perhaps be the average concentration in the 1728 voxels, and the total number of molecules N(t) consumed as a function of time.)
    * Average concentration: Cav(t)=(1/1728)\sum_{i=0}^12\sum_{j=0}^12\sum_{k=0}^12 c(i,j,k;t) 
    * Total substrates consumed: N(t) = Vvoxel \sum_{i=0}^12\sum_{j=0}^12\sum_{k=0}^12 c(i,j,k;t) 
* Runtime metrics (CPU, memory, energy consumption)

### *Mechanics, movement of a cell with friction*

**Motivation**: compare movement among tools. Test whether cells move the same distance under the same force, given a homogeneous isotropic friction coefficient that mimics friction of a cell with the ECM in an idealised way (without cells contacting each other). 

This force can have an initial user-defined direction, but then be fixed and constant. Note also that different implementations may use different standard integrators. Ideally one checks here whether a simple Euler-style forward integration (Butcher, 2003) works for all.

**Description**: 1 cell moving in a small domain of 60 um

**Initial conditions**:

* 1 cell
* Apply a force **F<sub>loc</sub>** on the cell to have a velocity of 10 um/min. The force is applied ONCE, after that you only have dissipative forces.
* Friction coefficient is equivalent to 0.1 **F<sub>loc</sub>**.
* The cell is inert, as it does not grow, but moves
* Size of cell: 10 um
* Mechanical Δt= 0.1 min
* total time = 10 min

**Data expected from the tools and metrics to be compared**:

* Compare the movement of the cells among tools. Have they travelled the same distance? Are the force integrators different among tools?
* We need the position of the cell at each time step (0.1 min). The tools need to print these concentrations at each time step (0.1 min)
* Runtime metrics (CPU, memory, energy consumption), but they might not be relevant.

### *Mechanics, two cells pushing each other*

**Motivation**: In the third step, one can model the contact force by pushing or pulling. But here again, one must be sure to use the same model. Some prefer Hertz, JKR, linear models, LJ forces (Ciavarella _et al._, 2019). Possibly here one should test a few of them. 

**Description**: 2 cells pushing in opposite directions in a domain of 60 um

![](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/comm1/imagen11.png )

**Initial conditions**:

* 2 cells that start close and that push each other
* Apply a force on the cells to have a velocity of 10 um/min for each cell
* The cells are inert, they do not grow, but they move
* Size of cell: 10 um
* Mechanical Δt= 0.1 min
* total time = 10 min
* Random force should be disabled.
* Apply a force on the cells to have a velocity of 10 um/min, on opposite directions. The cells are 100% aligned. The vector of forces of each cell is aligned with both cells’ centres. (see figure)
* The cells’ centres are 30 um apart at initial positions

**Data expected from the tools and metrics to be compared**:

* Compare the movement of the two cells among tools. Have they travelled the same distance?
* We need the position of the cell at each time step (0.1 min). The tools need to print these at each time step (0.1 min)
* Runtime metrics (CPU, memory, energy consumption), but they might not be relevant.

### *One cell with chemotaxis*

**Motivation**: a unit test of cells interacting with a substrate in the environment

**Description**: 1 cell is moving alongside a gradient of a substrate. The cell tends moves to the source. The amplitude of the movement vector is linearly correlated with the chemogradient. 

**Initial conditions**:

* 1 cell that does not grow, in the middle of the domain
* 10 um radius
* 120 um box, empty at t=0
* There is a source of chemical in one of the corners, for instance the upper, right, at the front.
* The source secretes 10 uM continuously
* Diffusion coefficient: 2000 um^2/min
* The cell does not uptake the substrate, but is aware of it and moves towards higher concentrations 

**Data expected from the tools and metrics to be compared**:

* Compare the movement of the cells among tools.
* We need the position of the cell at each time step (0.1 min). The tools need to print these concentrations at each time step (0.1 min)
* Runtime metrics (CPU, memory, energy consumption), but they might not be relevant.

## Use cases

### *2D monolayer without diffusion*

**Motivation**: Define a simple relevant case where growth, migration, cell-cell interactions interplay, and experimental data exist. Motivation for choosing two dimensions is that it permits us more easily to visualise differences and the possible cause for differences than in three dimensions.

**Description**: Use components migration, growth & division, cell-cell interaction. Each of these components can be chosen at different complexities (stochastic or not). 

The components should be chosen from the ones tested in the unit tests above.

**Initial conditions**:

* Start with 1 cell in the middle of the space field. 
* Radius of cell: 10 um.
* 2d box of L x L.
* Fit the experimental data from (Brú _et al._, 1998) also reported in (Drasdo and Hoehme, 2005; Hoehme and Drasdo, 2010):

<table>
  <tr>
   <td>
<strong>Relative time (hours)</strong>
   </td>
   <td><strong>Total time (hours)</strong>
   </td>
   <td><strong>Diameter (um)</strong>
   </td>
   <td><strong>Radius (um)</strong>
   </td>
  </tr>
  <tr>
   <td>0
   </td>
   <td>336
   </td>
   <td>1140
   </td>
   <td>570
   </td>
  </tr>
  <tr>
   <td>50
   </td>
   <td>386
   </td>
   <td>1400
   </td>
   <td>700
   </td>
  </tr>
  <tr>
   <td>72
   </td>
   <td>408
   </td>
   <td>1590
   </td>
   <td>795
   </td>
  </tr>
  <tr>
   <td>145
   </td>
   <td>481
   </td>
   <td>2040
   </td>
   <td>1020
   </td>
  </tr>
  <tr>
   <td>170
   </td>
   <td>506
   </td>
   <td>2250
   </td>
   <td>1125
   </td>
  </tr>
  <tr>
   <td>310
   </td>
   <td>646
   </td>
   <td>3040
   </td>
   <td>1520
   </td>
  </tr>
</table>

**Data expected from the tools and metrics to be compared**:

* Compare population dynamics across tools at each 30 min
* Runtime metrics (CPU, memory, energy consumption)

### *Spheroid without diffusion*

**Motivation**: Pick a “target” cell density for a spheroid and tune the mechanics to match

**Description**: Using the stochastic cell cycle and without diffusion have a spheroid of cells match a given cell density

**Initial conditions**:

* 3D spheroid of 100 cells
* Size of cell: 10 um
* Domain size: box of 400 um size
* Total time = 4 days = 96 hours = 5760 minutes
* Cell cycle of 4 phases: Mean duration: G0/G1: 7 hours, S: 6 hours, G2: 3 hours, M: 2 hours = total 18h
* Divide at end of M whenever volume is close to twice the initial one and into 2 daughter cells of half size, random orientation/placement
* Gaussian SD duration: 10% of time
* oxygen dependence: no
* apoptosis: small background rate, for instance 5.31667e-05 1/min is the one from PhysiCell
* necrosis: no necrosis in this test
* movement: Brownian

**Data expected from the tools and metrics to be compared**:

* Compare population dynamics across tools at each 30 min
* Runtime metrics (CPU, memory, energy consumption)

### *Spheroid with diffusion*

**Motivation**: same as spheroid without diffusion but now with oxygen diffusion, decay and uptake by cells

**Description**:

**Initial conditions**:

* Same as use case 2 except for:
* Boundary conditions: 38 mmHg partial pressure ~ 5% O2 ~ physioxia
* Diffusion coefficient for oxygen: 2000 um^2/min
* decay rate for oxygen: 0.1
* cell uptake rate for oxygen: 20uM/min = 12044 substrates/min
* oxygen dependence: yes
* G0/G1 → S rate depends upon local O2. 
    * Use a simple linear relationship of slope = 1.
* O2_min = zero cycling below this level
* O2_max = saturated cycling above this level
* scale from 0 cycle entry rate to 1 / (duration G0/G1) at O2_max
*  apoptosis: small background rate
* necrosis: activated when O2 below a threshold (stochastic or deterministic?)
* O2_necrosis: necrosis below this O2 value
* movement: Brownian

**Data expected from the tools and metrics to be compared**:

* Compare population dynamics across tools at each 30 min and with respect to the experiment
* Compare how different models treat apoptotic cells, duration of that shrinkage/removal process
* Runtime metrics (CPU, memory, energy consumption)

**Experimental dataset**:

Fit the experimental data from Freyer and Sutherland (1986) also reported in Drasdo and Hoehme (2005) and (2010):

<table>
  <tr>
   <td><strong>Time (hours)</strong>
   </td>
   <td><strong>Number of cells</strong>
   </td>
   <td><strong>Diameter (um)</strong>
   </td>
  </tr>
  <tr>
   <td>101,69
   </td>
   <td>600
   </td>
   <td>154,47
   </td>
  </tr>
  <tr>
   <td>148,47
   </td>
   <td>1472
   </td>
   <td>272,36
   </td>
  </tr>
  <tr>
   <td>192,54
   </td>
   <td>4409
   </td>
   <td>369,92
   </td>
  </tr>
  <tr>
   <td>242,71
   </td>
   <td>14968
   </td>
   <td>461,38
   </td>
  </tr>
  <tr>
   <td>269,83
   </td>
   <td>30327
   </td>
   <td>558,94
   </td>
  </tr>
  <tr>
   <td>275,93
   </td>
   <td>16577
   </td>
   <td>575,20
   </td>
  </tr>
  <tr>
   <td>366,10
   </td>
   <td>62197
   </td>
   <td>821,14
   </td>
  </tr>
  <tr>
   <td>372,88
   </td>
   <td>81281
   </td>
   <td>867,89
   </td>
  </tr>
  <tr>
   <td>414,24
   </td>
   <td>121828
   </td>
   <td>916,67
   </td>
  </tr>
  <tr>
   <td>463,05
   </td>
   <td>202963
   </td>
   <td>1052,85
   </td>
  </tr>
  <tr>
   <td>561,36
   </td>
   <td>244836
   </td>
   <td>1207,32
   </td>
  </tr>
</table>

