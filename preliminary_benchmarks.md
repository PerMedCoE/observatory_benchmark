# First technology observatory release and preliminary benchmarks

- [First technology observatory release and preliminary benchmarks](#first-technology-observatory-release-and-preliminary-benchmarks)
  - [**Executive Summary**](#executive-summary)
  - [**1. Introduction**](#1-introduction)
  - [**2. Tool observatory**](#2-tool-observatory)
    - [**2.1. Cell population modelling: PhysiCell and related tools**](#21-cell-population-modelling-physicell-and-related-tools)
    - [**2.2. Boolean modelling: MaBoSS and related tools**](#22-boolean-modelling-maboss-and-related-tools)
    - [**2.3. Constraint-based modelling: COBREXA.jl and COBRA toolboxes**](#23-constraint-based-modelling-cobrexajl-and-cobra-toolboxes)
    - [**2.4. CellNOpt/CARNIVAL benchmarks**](#24-cellnoptcarnival-benchmarks)
  - [**3. Benchmarking strategy**](#3-benchmarking-strategy)
    - [**3.1. Level A: Community benchmark**](#31-level-a-community-benchmark)
    - [**3.2. Level B: Preliminary benchmarks**](#32-level-b-preliminary-benchmarks)
    - [**3.3. Level C: Table descriptors**](#33-level-c-table-descriptors)
  - [**4. Status of the different community benchmarks**](#4-status-of-the-different-community-benchmarks)
  - [**5. Conclusions and future work**](#5-conclusions-and-future-work)
  - [**6. References**](#6-references)

## **Executive Summary**

PerMedCoE is a Centre of Excellence who, as one of its objectives, focuses on five different tools aimed at cell-based modelling: PhysiCell, MaBoSS, COBREXA, CellNOpt and CARNIVAL. Nevertheless, these tools, that we call “core tools” in the present document, are part of a scientific field that is changing regularly. Thus, one of the tasks of PerMedCoE was to establish an observatory of tools to remain aware of software, algorithms and standards developed around cell-based modelling. Further, PerMedCoE aimed to contact the tools’ developers responsible for these developments and to involve them to have community-driven benchmarks with their tools and the tools from PerMedCoE. Thus, Task 3.1 connects efforts directed towards having the observatory of tools and the efforts directed towards having benchmark activities among these tools and PerMedCoE’s own.

In PerMedCoE, we were active in contacting tools’ developers whose aims were similar to our own. Next, we set out to start community-driven benchmarks where all the developers agreed on the scope, metrics and use cases to benchmark their tools. Lastly, we have prepared the infrastructure that we are going to use to publish the results from these benchmarks.

All in all, the observatory and benchmarks give PerMedCoE project the ability to be aware of developments in the field and the presence to be a relevant partner for future endeavours in the field of cell-based modelling.

The observatory is publicly accessible here: [https://permedcoe.bio.tools/](https://permedcoe.bio.tools/); and the preliminary benchmarks are publicly accessible here: [https://dev-openebench.bsc.es/projects/OEBC009](https://dev-openebench.bsc.es/projects/OEBC009).


 ## **1. Introduction**

In the PerMedCoE project we focused on five pieces of software that we considered representatives of different aspects of cell-level simulations: a) PhysiCell for simulations of cell populations, b) COBREXA for simulations of metabolism, c) MaBoSS, d) CellNOpt and e) CARNIVAL for the simulation of signalling pathways. These “core tools” were neither built nor used devoid of any context or field. In the project proposal, we acknowledged the existence of other tools that have very similar aims as the above PerMedCoE core simulation tools. To keep up with a progressing, active field of cell-level simulation, we devised a tools’ observatory to gather information on tools being published that could complement and/or overlap the aims of our “core tools”. We have called these tools “external tools” in this document, as they are tools of interest, but external to our set of PerMedCoE simulation “core tools”.

As we describe in Section 2, we first mapped out the field and identified relevant "external tools" . Then, we set to compare these tools using controlled execution environment under controlled inputs that need to be agreed upon with the different tool developers in terms of metric, scope and use cases, as described in Section 3. This comparison is what we termed “community benchmark” and can be defined as the coordinated effort from a group of developers to compare their tools in a fair and transparent manner.

The main goal stated in the DoA was “to follow new developments and implementations, to compare and benchmark them against existing solutions in different realistic scenarios, and to offer the results to the user community, with the aim to assess the status of the field, defining the best applications to integrate in the CoE activities and engaging with the software users and developers.” This meant to get in contact with the tools’ developers to organise regular meetings until we could agree on a set of scenarios and metrics where to test the tools. Finally, as described in Section 4, these results should be offered to the community in a public website to ensure that other tool developers could join in in future releases and that users interested in these types of modelling could take advantage of these benchmarks to select a tool appropriate to their project.

In the present deliverable, we detail the current status of the tool observatory and benchmarks.

## **2. Tool observatory**

In this section, we describe the tools against which our “core tools” will be compared. We started the process of identification of interesting tools by identifying relevant keywords and performing exhaustive literature review. Additionally, some papers that introduced new tools cited and compared the performance of their tool with others. This provided a combination of newly developed tools as well as other tools that had been published years ago, but that were still under active maintenance. 

Next, we systematised the selection of tools by having feature-wise comparisons for each benchmark. This resulted with lists of candidate toolset that could be compared with the “core tools”. These feature-wise comparisons provided a descriptive top-level view of the benchmark and a systematic starting point for designing good performance benchmarks of the methods.

Finally, we sent letters of intent such as the one in Appendix 1 to the tool developers, contacting over 44 of them. We met with them and talked about the aim and motivation of the community benchmarks that we wanted to perform.

In the following, we list the tools that will be included in the different community benchmarks and show some of their characteristics in descriptive tables. All of the tools part of the observatory and listed in the table were also included in bio.tools database ([https://permedcoe.bio.tools/](https://permedcoe.bio.tools/)).

### **2.1. Cell population modelling: PhysiCell and related tools**

For this benchmark, we were particularly interested in overlapping spheres or centre-based models (CBM), where the agents are represented by overlapping spheres as it is a good trade-off between computation efficiency and close-to-reality simulations (Osborne *et al.*, 2017; Metzcar *et al.*, 2019). The core tool that performs cell population modelling in PerMedCoE is PhysiCell, an off-lattice, centre-based, agent-based simulation tool for cell populations (Ghaffarizadeh *et al.*, 2018). 

After exhaustive literature review and feature-wise comparison, we ended up with a list of 8 tools that simulate CBM and whose developers agreed to participate in the community benchmark. We built a list of different characteristics of these tools (Table 1) and each of them is hereby described.

**Table 1. Characteristics of tools for cell population modelling to benchmark. CBM stands for centre-based models. For entries represented by question marks, no evidence was found to the best of our efforts.**

|**Tool**|**PhysiCell**|**Chaste**|**BioCellion**|**FLAME GPU 2**|**BioDynaMo**|**CellSys**|**Timothy**|**PhysiCell-X**|
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|**Scope**|CBM|CBM, others|CBM|CBM|CBM|CBM|CBM|CBM|
|**Shared memory (OpenMP)**|Y|Y|Y|Y|Y|Y|Y|Y|
|**Distributed memory (MPI)**|N|Y|Y|Y|N|N|Y|Y|
|**Language**|C++|C++|C++|C++, CUDA, python|C++|C++|C|C++|
|**Open source**|Y|Y|Source-available software|Y|Y|Source-available software|Y|Y|
|**Format**|Executable|CTest Executable|Executable|Executable|Executable|Executable|Executable|Executable|
|**License**|BSD 3-clause|BSD 3-clause|Proprietary|MIT license|Apache 2.0|Proprietary|GPL 2.0|BSD 3-clause|
|**Dependencies**|1 (pugixml)|Many|?|Many (11)|Few (7)|Few|3 (MPI, Zoltan, Hypre)|2 (pugixml, MPI)|
|**Cell cycle models library**|Y|Y|?|N|N|?|N|Y|
|**Use case library**|Y|Y|Y|Y|Y|Y|N|Y|
|**Initial conditions from file**|Y|N|?|Y|Y|Y|Y|Y|
|**Repository**|<https://github.com/MathCancer/PhysiCell>|<https://github.com/Chaste/Chaste>|<https://biocellion.com/>|<https://github.com/FLAMEGPU/FLAMEGPU2/>|<https://github.com/BioDynaMo/biodynamo>|<https://www.hoehme.com/software/tisim>|<https://github.com/tissuemodelling/timothy>|[https://gitlab.bsc.es/gsaxena/PhysiCell_x](https://gitlab.bsc.es/gsaxena/physicell_x)|
|**Publication**|(Ghaffarizadeh *et al.*, 2018)|(Cooper *et al.*, 2020)|(Kang *et al.*, 2014)|(Richmond *et al.*, 2010)|(Breitwieser *et al.*, 2021)|(Hoehme and Drasdo, 2010)|(Cytowski and Szymanska, 2014)|NA|
|**Save and Load simulation**|N|Y|?|?|N|N|Y|N|
|**Compilation tool**|make|cmake|?|cmake|cmake|?|make|make|
|**Operative systems**|Linux, MacOS, Windows|Linux, Docker|Linux|Linux, Windows|Linux, macOS|Linux, Windows|Linux|Linux|

Chaste (Cooper *et al.*, 2020) is an open-source, general-purpose simulation package for modelling soft tissues and discrete cell populations that can be used with MPI. This tool allows using different modelling frameworks on a given problem, enabling users to select the most appropriate one for their research and to better understand the limitations of each one of them. Chaste has been used for a wide range of projects, such as intestinal (Dunn *et al.*, 2013) or colonic crypt (Dunn *et al.*, 2012) studies. 

Biocellion (Kang *et al.*, 2014) is a flexible, discrete agent-based simulation framework that has been used to model a wide range of multi-cellular biological models, such as a bacterial system in soil aggregate of over 26 million cells and cell sorting simulations of up to 1010 cells. Biocellion is freely available for academic use and its single-node version is open source.

FLAME (Coakley *et al.*, 2012) is an open-source, generic formal framework for agent-based modelling that allows parallelisation using MPI, and developers can use it to create models and tools. Implementing a Flame simulation is done by using finite-state automata with memory (Coakley *et al.*, 2006). This tool has been adapted to be used with distributed GPUs using the OpenCL standard (Richmond *et al.*, 2010). Examples of uses of FLAME range from bioreactor studies (Kaul *et al.*, 2013) to immunogenic studies (Kabiri Chimeh *et al.*, 2019) or also epidermis modelling (Lin *et al.*, 2013). 

BioDynaMo (Breitwieser *et al.*, 2021) is an open-source simulation tool fully parallelised, able to offload computation to hardware accelerators and load-balance agents and their environment on available nodes. Being general-purpose, it allows simulating models from various fields by being extensible and modular, showcasing its use in neurite growth, in tumour spheroid and in epidemiology examples.

CellSys (Hoehme and Drasdo, 2010) is a source-available software that has been used for multi-cellular biological models, such as liver regeneration (Hoehme *et al.*, 2010), introducing the deformability in centre-based models (Van Liedekerke *et al.*, 2015) and the inclusion of signalling pathways controlling the agents’ behaviours (Ramis-Conde and Drasdo, 2012).

Timothy (Cytowski and Szymanska, 2014, 2015) is an open-source, MPI-based tool that has proven to be able to simulate biological models of up to 0.3 billion cells in cancer projects (Cytowski *et al.*, 2017) as well as large-scale models with nuclear-cytoplasmic oscillations of NF-κB (Szymańska *et al.*, 2018). The developers of Timothy answered that they do not maintain the code anymore and that they could not be part of the benchmark. Nevertheless, we decided to include this tool as the method it uses to perform the dynamic and asymmetric domain decomposition using Peano-Hilbert space-filling curves has the potential to reach simulations of billions of cells and is very different from PhysiCell-X regular domain decomposition.

PhysiCell-X (Saxena *et al.*, in preparation) is BSC’s current effort to include MPI in PhysiCell, an open-source, flexible, and lattice-free agent-based framework for multi-scale simulation of multi-cellular systems that currently only support shared-memory parallelisation. The main advantage of PhysiCell is its lightweight, very efficient and self-contained framework. Additionally, PhysiCell can be expanded using add-ons, such as PhysiBoSS (Letort *et al.*, 2019), allowing the integration of individual Boolean models for the signalling networks embedded into each agent. PhysiCell-X expands our efforts to include distributed-memory in the solver that manages the chemicals' diffusion of PhysiCell: BioFVM-X (Saxena *et al.*, 2021). More information on PhysiCell-X’s development and benchmarking can be found in Deliverable 2.1.

### **2.2. Boolean modelling: MaBoSS and related tools**

For this benchmark, we were in tools that allow to simulate Boolean models. These tools can use synchronous or asynchronous updates to fins stable states and may have different functions available in their toolboxes, such as attractor reachability or have more probabilistic approaches (Abou-Jaoudé *et al.*, 2016; Chaouiya *et al.*, 2012). 

MaBoSS is a stochastic Boolean model simulator (Stoll *et al.*, 2012, 2017) that is able to simulate classic Boolean models using asynchronous updates. To do so it uses the Gillespie algorithm, which corresponds to using continuous time Markov chains to simulate transitions from one Boolean state to the next. MaBoSS also allows Boolean models with kinetic rates to represent activation and inactivation rates for each individual node. Developed at the Computational Systems Biology of Cancer's lab at Institut Curie since 2012, it was initially available as a command-line tool. MaBoSS is now available via its Python bindings, pyMaBoSS ([https://pymaboss.readthedocs.io/en/latest/](https://pymaboss.readthedocs.io/en/latest/)), via a web interface, WebMaBoSS (Noël *et al.*, 2021), and as a C++ library which is used in agent-based frameworks such as PhysiCell and CompuCell3D (Swat *et al.*, 2012).

In this benchmark, we are mainly interested in Boolean simulators using asynchronous updates and producing estimated trajectories of model dynamics. Below is a list of other tools which perform similar simulations (Table 2).

**Table 2. Characteristics of tools for stochastic Boolean simulator to benchmark. For entries represented by question marks, no evidence was found to the best of our efforts.**

|**Tool**|**MaBoSS**|**BoolNet**|**BooleanNet**|**AVATAR**|**ChemChain**|
| :-: | :-: | :-: | :-: | :-: | :-: |
|**Shared memory (OpenMP)**|Y|N|N|N|Y|
|**Distributed memory (MPI)**|Y|N|N|N|N|
|**Language**|C++|C|Python|Java|C++|
|**Open source**|Y|Y|Y|Y|Y|
|**Format**|Executable, Python package|R Package|Python package|Java package|Executable|
|**License**|BSD 3-clause|Artistic License 2.0|MIT license|GPLv3|GPLv2|
|**Dependencies**|libSBML (optional)|Many|?|bioLQM|?|
|**Repository**|<https://github.com/sysbio-curie/MaBoSS-env-2.0>|https://cran.r-project.org/package=BoolNet|https://github.com/ialbert/booleannet|http://ginsim.org/|http://www.bioinformatics.org/chemchains/wiki/|
|**Publication**|(Stoll *et al.*, 2017)|(Müssel *et al.*, 2010)|(Albert *et al.*, 2008)|(Mendes *et al.*, 2018)|(Helikar and Rogers, 2009)|
|**Operative systems**|Linux, MacOS, Windows|Linux, MacOS, Windows|Linux, MacOS, Windows|Linux, MacOS, Windows|Linux, Windows|

BoolNet (Müssel *et al.*, 2010) is an R package with efficient integration methods for synchronous, asynchronous and probabilistic Boolean networks. It allows one to perform multiple kinds of analyses, including perturbations, Markov chain simulations and identification/visualisation of attractors. Written by Hans Kestler's lab at Ulm University Hospital and published in 2010. It uses its own proprietary file format, Bnet, which is a simple and popular textual way of describing Boolean networks.

BooleanNet (Albert *et al.*, 2008) is a Python package for simulating various types of Boolean models (synchronous, asynchronous, ranked asynchronous, piecewise linear). It was developed by Réka Albert's lab at Pennsylvania State University in 2008. This software is now unmaintained, but community efforts recently helped produce a Python -compatible package.

GINsim (Gonzalez *et al.*, 2006) is a tool for building and analysing Boolean models developed in Claudine Chaouiya's lab at Université d'Aix-Marseille, released in 2005. It includes a graphical interface with a network editor, allowing it to easily build Boolean models. It also includes various tools for model conversion, as well as analyses and simulations of such models, using both formal and approximate methods. One of its simulators is a Monte Carlo method called AVATAR (Mendes *et al.*, 2018), which allows it to simulate large networks and detect dynamical behaviours such as limit cycles. One of the largest databases of Boolean models is also available on GINsim website: [http://ginsim.org/models_repository](http://ginsim.org/models_repository). 

CellCollective (Helikar *et al.*, 2012) is an online platform developed by Tomas Helikar's lab, at University of Nebraska. This platform contains one of the largest databases of Boolean networks, a graphical interface for its simulator, ChemChains (Helikar and Rogers, 2009), as well as tools focused on teaching. Its simulator is written is C++ and uses a precompiled version of the Boolean model to simulate. It produced trajectories of activation levels of visited states, using Markov chain methods.

### **2.3. Constraint-based modelling: COBREXA.jl and COBRA toolboxes**

COBREXA is a tool for the scalable construction and analysis of constraint-based metabolic models, belonging to a much wider and diverse category of Constraint Based Reconstruction and Analysis (COBRA) tools.

The landscape of available tools is shaped mainly by several main concerns: First, since the methodology is defined very vaguely, it encompasses a wide range of actual algorithms that differ in input types, purposes and output shapes. The possible algorithms include ones for assembling models from genomic information, combining the models, running basic analyses on the models represented as constrained optimization problems (this includes the most general and useful analyses such as flux balance and variability analysis), sampling of possible states of the metabolism, and inclusion of additional (sometimes non-linear) constraints into the model that may simulate protein crowding, satisfy laws of thermodynamics, ensure realistic reaction kinetics, etc. Second, only certain subsets of all problems are parallelizable and scalable, and many methods do not possess a scalable implementation either due to lack of interest that would drive the additional implementation effort, or because of technical impossibility (as is the case of linear optimization solver algorithms). Finally, because the individual algorithms are often quite simple and rarely useful as isolated tools, many toolboxes exist that combine multiple functionalities into a single software package. The toolboxes differ mainly by the chosen programming environment, and by the approach to systematic data representation (if present).

Notably, comparison of “precision” and generally “solution quality” metrics among the tools does not make as much sense for COBRA toolboxes as with other types of software, as most solutions are defined algebraically, not allowing any uncertainty. Benchmarking of specific aspects of the precision may be viable in special cases, such as with the MONGOOSE toolbox that aims to prevent floating-point computation imprecision, or by comparing the performance and precision of individual underlying constrained linear problem solvers, such as Gurobi ([https://www.gurobi.com/](https://www.gurobi.com/)), CPLEX ([https://www.ibm.com/analytics/cplex-optimizer](https://www.ibm.com/analytics/cplex-optimizer)), CLP ([https://github.com/coin-or/Clp](https://github.com/coin-or/Clp)), GLPK ([https://www.gnu.org/software/glpk/](https://www.gnu.org/software/glpk/)), Tulip (Anjos *et al.*, 2021), OSQP ([https://osqp.org/](https://osqp.org/)), and others.

To systematise the selection of tools to be benchmarked, we decided to start the preliminary benchmarking by feature-wise comparisons of whole toolboxes. The feature matrices would represent an already-valuable resource for users (allowing easier choice of a toolbox for a given task). At the same time, these would provide a way to contain the heterogeneity of the algorithm choice, creating a systematic starting point for designing good performance benchmarks of specific methods.

Thus, a preliminary feature-wise toolbox comparison was done internally for selecting several toolboxes to create an illustrative “starting point” for the benchmark structure. The toolboxes are listed in Table 3, together with several optimised algorithm implementations and a model management framework added to cover a broader scope of the tools. First preliminary performance benchmarks were also conducted to compare COBREXA with COBRApy and CobraToolbox, giving a possible view of the complexity and achievable results in quantitative benchmarking.

**Table 3. Characteristics of constraint-based modelling tools to benchmark.**

|**Software**|**Repository**|**Publication**|**Programming environment**|**Type**|
| :-: | :-: | :-: | :-: | :-: |
|**RAVEN Toolbox**|<https://github.com/SysBioChalmers/RAVEN>|(Wang *et al.*, 2018)|MATLAB|General toolbox|
|**COBRA.jl**|<https://github.com/opencobra/COBRA.jl>|(Heirendt *et al.*, 2017)|Julia|General toolbox|
|**The COBRA Toolbox**|<https://github.com/opencobra/cobratoolbox>|(Heirendt *et al.*, 2019)|MATLAB|General toolbox|
|**VFFVA**|<https://github.com/marouenbg/VFFVA>|(Guebila, 2020)|C, MATLAB, Python|Optimised algorithm|
|**FastCore**|<https://github.com/migp11/fastcore>|(Vlassis *et al.*, 2014)|Python|Optimised algorithm|
|**COBRApy**|<https://github.com/opencobra/cobrapy>|(Ebrahim *et al.*, 2013)|Python|General toolbox|
|**memote**|<https://github.com/opencobra/memote>|NA|Python|Model management|
|**MONGOOSE**|<http://cb.csail.mit.edu/cb/mongoose/>|(Chindelevitch *et al.*, 2014)|Python|General toolbox|
|**FastMM**|<https://github.com/GonghuaLi/FastMM>|(Li *et al.*, 2020)|MATLAB|General toolbox|
|**miom**|<https://github.com/MetExplore/miom>|NA|Python|General toolbox|
|**reFramed**|<https://github.com/cdanielmachado/reframed>|NA|Python|General toolbox|
|**COBREXA.jl**|<https://github.com/LCSB-BioCore/COBREXA.jl>|(Kratochvíl *et al.*, 2022)|Julia|General toolbox|

Appropriately, we contacted the tool authors about their potential participation in the community benchmark and received responses to 66\% of the calls, all of which were positive, offering possibilities to discuss and participate. Basic expectations about the benchmarks and presentation of the tools in OpenEBench interface were discussed at the preliminary meeting. We aim to prepare preliminary data for the OpenEBench site to provide a base for building more precise benchmarks and collecting better structured information and continue to involve the participants once the basic layout is decided and example data are available.

### **2.4. CellNOpt/CARNIVAL benchmarks**

CellNOpt and CARNIVAL are two similar tools for contextualization of signalling networks. CellNOpt uses (phospho)proteomics data from multiple conditions to infer a signalling network from a scaffold network that is able to explain the observed data, whereas CARNIVAL uses differential expression data to contextualise a scaffold network by selecting the subnetwork that explains the observed changes between conditions.

In terms of functionality, CellNOpt does both parameter fitting and simulation. Simulations are used to evaluate how well a network can reproduce a set of experiments, and this information is used by the stochastic optimizer to refine and improve the solution. Given this separation between parameter estimation and simulation, CellNOpt supports a variety of simulation methods, including MaBoSS. In this way, MaBoSS can be used as a simulation tool and CellNOpt as a parameter fitting tool. This particularity leads to a significant overlap between the two methods and therefore the available competing tools. During our analysis, we have not found tools that do exactly the same as CellNOpt (parameter fitting integrated with Boolean simulation), but only tools for Boolean simulations. These tools are the same as in the case of MaBoSS shown in Table 2 and thus already covered.

For CARNIVAL, following exhaustive literature review and a feature-wise matrix comparison as in the previous cases, we identified two tools that are similar in terms of inputs/outputs and functionality: CausalR and SigNet (Table 4).

**Table 4. Characteristics of tools for CARNIVAL to benchmark**

|**Tool**|**CausalR**|**SigNet**|
| :-: | :-: | :-: |
|**Inputs**|TF activities + PPI network|Gene expression / PPI + regulatory network|
|**Outputs**|Ranked list of nodes / Sub-network|Ranked list of nodes|
|**Language**|R|Unknown|
|**Open Source**|Y|No|
|**License**|GPL >= 2|Unknown|
|**Repository**|<https://bioconductor.org/packages/release/bioc/html/CausalR.html>|<https://clarivate.com/cortellis/cbdd>|
|**Publication**|(Bradley and Barrett, 2017)|(Jaeger *et al.*, 2014)|

## **3. Benchmarking strategy**

In PerMedCoE, we aim to benchmark the PerMedCoE simulation “core tools” to their corresponding relevant “external tools”. For this, we need to agree with the “external tools” developers the specificities of the controlled execution of the tools in terms of scope, metrics and use cases. This aim needs substantial efforts in terms of coordination of developers’ teams and reaching agreements. Thus, even though this community benchmark is the ultimate objective, we have devised two other types of benchmarks that can be done with less dependence on tool developers from outside the project. We briefly introduce them here and describe them in detail in the following sections:

- **Level A, Community benchmark**: A community benchmark is defined as the coordinated effort from a group of developers to compare their tools in a fair and transparent manner. For this, they need to agree on three sets of features: scope of the benchmark, which metrics will be used and which use cases or reference datasets will be considered.
- **Level B, Preliminary benchmark**: A preliminary benchmark is a comparison of tools that one developer performs on their own without any major input from other developers. The scope, metrics and use cases are defined by this developer.
- **Level C, Table descriptors**: We have gathered from the tools publications and website a set of descriptors such as operative system, coding language, etc. that can inform users of some characteristic of these tools to make a choice of which one is better for their problem or machine.

### **3.1. Level A: Community benchmark**

A community benchmark is defined as the coordinated effort from a group of developers to compare their tools in a fair and transparent manner. In this case, we define the term “community” as a group of people with diverse backgrounds and experiences working in the same field, who face similar problems and want to collaborate to find the best solutions to these problems.

Benchmarking efforts benefit the community, tool developers and end-users. Comparing tools against others encourages software developers to implement more efficient methods and develop new tools by focusing on challenging areas and methodological blind spots. In addition, users can access the benchmark results, which helps steer the user base towards the latest and better developments in the field.

To have a relevant and successful benchmark, it must reflect the existing challenges of the scientific community in terms of size, complexity and content. Thus, the community needs to agree on three features of the benchmark: scope, metrics and use cases.

- **Scope**: The relevant scientific questions that the benchmarked tools need to answer. These can be technical, focusing on the tool’s performance under specific conditions, or scientific, focusing on its performance and quality of the results within clearly defined scientific challenges.
- **Metrics**: A set of quantitative values used to measure the performance of the evaluated tools in the scope of the benchmark. The technical metrics could include e.g. memory use and run time; the scientific metrics may include accuracy and recall.
- **Use case definition**: Reference data sets and desired outcomes that can be used as ground truths and/or baselines for comparison. They need to be well defined, unbiased and their use should be agreed upon and supported by the community.

Once the community has agreed on these features, they need to run their tools on the defined use cases using the agreed metrics in a common computer architecture to normalise the technical metrics.

After the simulations are performed, the community needs to publish these efforts in technical papers and public websites so that they will be of maximal benefit to tool developers and end-users In our case, PerMedCoE collaborates with OpenEBench (Capella-Gutierrez *et al.*, 2017) to organise a platform with a public website, catalogue the tools in bio tools, host the benchmarks, and publish the benchmark results and methodologies, serving as panels for future simulation tools. 

In addition, we will actively disseminate these benchmarks, their results, methodology and organisation, and publish a community paper or white paper together with the benchmark participants to further consolidate the computational biology cell-level simulation community.

### **3.2. Level B: Preliminary benchmarks**

A preliminary benchmark is a comparison of tools that one developer performs on their own machine or cluster, without any major inputs from other developers. The scope and metrics of the benchmark are defined by this developer and, as use cases, they try to have templates from the diverse tools as close as possible.

In PerMedCoE, in parallel to the efforts devoted to gathering and organising the “external tools” developers, we started by preparing preliminary benchmarks of PhysiCell and two other tools, of COBREXA and another tool and of CARNIVAL and two other tools.

a)  Cell population preliminary benchmark

We focused on Timothy, PhysiCell and Chaste to complete a preliminary benchmark of the cell population simulations. This methodical comparison aimed to evaluate the different simulation software and their performance, while simultaneously minimising the amount of changes to the source code of each software as well as any input from the owners of the tools.

**Scope**:

All the experiments with the three tools were executed in MareNostrum4, a supercomputer based on Intel Xeon Platinum processors from the Skylake generation. It is a Lenovo system composed of SD530 Compute Racks, an Intel Omni-Path high performance network interconnect and running SuSE Linux Enterprise Server as the operating system. Its current Linpack Rmax Performance is 6.2272 Petaflops. 

This general-purpose block consists of 48 racks housing 3456 nodes with a grand total of 165,888 processor cores and 390 Terabytes of main memory. The compute nodes are equipped with 2 sockets Intel Xeon Platinum 8160 CPU with 24 cores each @ 2.10GHz for a total of 48 cores per node.

For each of our runs we sent jobs to the workload manager asking for the 48 cores and 2 hours of run time and in 3 replicates per tool.

**Use case to benchmark**:

Although these frameworks are used to model, among other things, cells growing and their surrounding microenvironment, they do not specialise in the same use cases. To perform this preliminary benchmarking, we intended to use computational configurations, use cases, and model specifications that were as similar as possible. 

The model that was implemented within each of the tools was to simulate the growth of a cell population in the shape of a spheroid and its response to the presence of oxygen. Cells would grow until reaching a threshold level were oxygen could not get in the middle of the spheroid, causing cell death.

Technically, the implementation of the benchmarking was carried out by letting each software run with a timeout of two hours of execution. We studied the different tools by comparing the amount of cells produced at the endpoint. For each of the 3 replicates, a single node with 48 cores was used.

In what follows, we briefly describe how we set each simulator and in particular which configurational parameters were modified to run the simulations. 

**Timothy**: We used the source code from (Cytowski and Szymanska, 2014, 2015) with no modifications. We performed different experiments by changing various values of the parameter file that is provided by the developers in which cells are responsive to the levels of oxygen.
The parameters we modified are:

- NHS, the number of cells needed to activate apoptosis by cells’ crowding
- OXYGEN, a binary variable to indicate that the simulation includes oxygen
- TGS, this binary variable sets the model to be run as a tumour growth simulation

**PhysiCell**: This tool provides the user with different templates that serve as guides for different types of simulations. In this case, we used an example that demonstrates a cell heterogeneity model. This model starts with a low amount of cells and the agents are able to change phenotypes, such as growth or death, depending on the physics as well as the secretion and uptake of oxygen.

**Chaste**: The cell-based implementation in Chaste is built with the use of CTest, which is an executable that comes with CMake and handles running tests for C++ based projects. That is, the user does not create a main source file, but rather they exploit the executables which are generated by CTest. The user can either use any of the tutorials provided by the developers of Chaste or extend them with desired functionality. For our benchmarking, we have modified several built-in tests to match the desired simulation.

Using Chaste, we have explored:

- Different microenvironment setups. Chaste provides mesh-based, node-based and vertex-based simulations.
- Initialisation of the microenvironment. According to the user manual, the simulations can be populated with cells in different ways, depending on if you need parallel execution, cells generated randomly or generated based on information stored in files.

Another characteristic that differentiates Chaste from the other simulators is that user parameters are set in the source code of the test files. If a user desires to read external files with parameters, they should have to add that parser part to the test files. Also, this implies that any modification needed to the model parameters requires recompilation.

**Metrics:**

Due to time constraints, we decided to focus on technical metrics that we could gather from the runs, such as average walltime, memory use and power consumption. We also studied scientific metrics such as final cell count. As this was a preliminary test, we did not considered further metrics such as precision or recall when comparing to a reference dataset.

To have a meaningful comparison, all simulations were sent to the cluster with the same number of cores (48) and run time (2 hours). Nevertheless, we considered one scientific metric, the total number of cells grown as it was a value readily available upon simulating the tools.

**Results:**

For each software, we started with the same number of cells (5). Furthermore, we performed a 2-hour execution time and in three replicates for each tool (Figures 1 and 2 and Table 5).

![Figure 1. Cell counts for the three cell populations tools after 120 minutes of simulation for Chaste (A), PhysiCell (B) and Timothy (C). Note that the x-axis in panels A and B are in minutes and in panel C is in hours and that y-axis have different ranges across panels.](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/prelim/Fig1.svg)

**Figure 1. Cell counts for the three cell populations tools after 120 minutes of simulation for Chaste (A), PhysiCell (B) and Timothy (C). Note that the x-axis in panels A and B are in minutes and in panel C is in hours and that y-axis have different ranges across panels.**

In terms of the final number of cells, one can observe that Chaste and PhysiCell produce similar cell populations, whereas Timothy outperforms the two latter in number of cells (15x, Figure 2, right panel) and in simulated time (60x, Timothy simulates hours while the other two simulate minutes). One potential explanation for this difference is that Timothy deals with the diffusion of chemical entities by considering a continuous field. 

**Table 5. Metrics gathered for the cell population preliminary benchmark. Three replicates were run for each of the three tools.**

|**Tool**|**Execution Time**|**Cores**|**Average CPU Usage (\%)**|**Average Memory Usage (\%)**|**Power Consumption (Watts)**|**Simulation Time (min)**|**Initial Cells**|**Total Cells**|
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|**Chaste**|1 h, 59 m, 3 s|48|3.876176471|5.001302521|148.5294118|14940|5|10081|
|**Chaste**|1 h, 59 m, 29 s|48|2.041589958|4.440962343|142.6778243|15000|5|9488|
|**Chaste**|1 h, 59 m, 28 s|48|5.597447699|4.158786611|132.0125523|14940|5|10081|
|**PhysiCell**|1 h, 59 m, 14 s|48|98.55794118|5.602226891|334.1470588|14400|5|5826|
|**PhysiCell**|1 h, 59 m, 27 s|48|69.98179487|4.732301255|331.4560669|14040|5|6016|
|**PhysiCell**|1 h, 58 m, 10 s|48|61.86947368|4.331764706|337.2605042|14040|5|5971|
|**Timothy**|1 h, 59 m, 23 s|48|104.142563|4.212983193|252.8487395|912000|5|190623|
|**Timothy**|1 h, 59 m, 7 s|48|103.81|4.999495798|260.3529|907800|5|188262|
|**Timothy**|1 h, 59 m, 26 s|48|76.00684211|20.29634454|263.2521008|892200|5|179541|

![Figure 2. Average CPU, memory, power and total cell counts](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/prelim/Fig2.svg)

**Figure 2. Average CPU, memory, power and total cell counts.** 

b)  COBRA toolboxes preliminary benchmark

A preliminary benchmark was conducted to compare COBREXA to other state-of-art COBRA toolboxes, originally for publication purposes (Kratochvíl *et al.*, 2022). The benchmark measures the performance and scalability of flux variability analysis (FVA) and production envelope computation, which are the most usual algorithms found in many toolboxes as well as standalone algorithm implementations, and their design makes them quite suitable for parallelization. 

An example output of the benchmarks can be seen in Figure 3, showing an aggregation of collected benchmark measurements for 2 implementations of the production envelope computation. We plan to provide similar scaling plots (comparing time, task size, available resources and energy efficiency) for all parallelizable algorithms and methods. These results are also discussed in detail in Deliverable 1.2.

We aim to re-use the prepared automated HPC-compatible benchmark tooling and scripts for the community benchmarking; probably using FVA, production envelopes and flux sampling algorithm as the cornerstones for “general” performance evaluation. The collected data of this preliminary benchmark will additionally serve as base material for discussions with other tool authors, providing better explanation and illustration of the purpose and scope of the benchmarks.

![Figure 3. Example benchmark output for COBRA methods](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/prelim/Fig3.svg)

**Figure 3. Example benchmark output for COBRA methods (performance and efficiency of production envelope computations).**

c)  CARNIVAL preliminary benchmark

Preliminary discussions were carried out to establish the common grounds for the evaluation of the different signalling network contextualization methods. We identified two different approaches: 1) *direct*, based on direct metrics from the outputs of the tools, and 2) *indirect*, based on predictive capabilities from extracted features of the outputs. In the first approach, metrics can be focused on aspects like measuring whether relevant perturbed nodes were detected in the results, in which case enrichment tests on the nodes of the extracted networks can be directly applied to the output results. In the second approach, metrics calculated from the output of the methods can be used for prediction of a secondary goal (e.g., mechanism of action).

During initial discussions around the first approach for benchmarking, a preprint comparing CARNIVAL, SigNet and CausalR was published (Hosseini-Gerami *et al.*, 2022). In this work, the authors compare CARNIVAL, SigNet and CausalR using the LINCS L1000 dataset to predict known direct drug targets and altered pathways from perturbational data (Table 6). 

![Table 6. Algorithm outputs and metrics, from Hosseini-Gerami *et al.*, 2022](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/prelim/Table6.png)

**Table 6. Algorithm outputs and metrics, from Hosseini-Gerami *et al.*, 2022.**

The benchmark was designed to consider different metrics that fall under the *direct* approach discussed above, from which two metrics are applicable for the three methods: 1) Target recovery and 2) Pathway recovery. Target recovery refers to the ability to recover known drug targets, and it is measured using the one-sided Fisher’s exact test. Pathway recovery was designed to measure the enrichment on the set of recovered nodes from the subnetwork, to test whether the perturbed pathway is detected (enriched) in the solution. 

Figure 4 shows the results of a post-hoc analysis of the Network:Algorithm interaction effect using ANOVA, that captures the ability of each algorithm to recover pathways containing direct perturbed targets. All methods show better performance than the use of differentially expressed genes alone (orange dashed line). The method that achieves the best performance is SigNet using the Omnipath network, being CausalR using top ranked compounds output produced by the method.

![Figure 4. Result for the ANOVA Post Hoc test on the network/algorithm interaction effect on performance for pathway recovery, using 4 different scaffold base networks](https://github.com/PerMedCoE/observatory_benchmark/raw/main/figures/prelim/Fig4.png)

**Figure 4. Result for the ANOVA test on the network/algorithm interaction effect on performance for pathway recovery, using 4 different scaffold base networks (*x* axis). The *y* axis shows the average estimated effect of the evaluated metric, in this case, larger values indicate more enrichment of the perturbed pathway for a given base network and method.**

### **3.3. Level C: Table descriptors**

As a result of the work done for our tool observatory, we have gathered sets of features and characteristics of each one of the tools that can inform users to make a choice of which one is better for their problem or machine. With this information, we built descriptive tables. The characteristics were chosen so that they could inform future users looking to perform any of these simulations with their different dependencies or operative systems needed.

Examples of these are provided in Tables 1, 2 and 3.

## **4. Status of the different community benchmarks**

To prepare for the actual community benchmarks, we needed to prepare a set of meeting to discuss the open question from the section 3.1: which scope, metrics and use case would the benchmarks have. In this section, we have detailed the meetings and workshops we had to organise the benchmark hackathon.

Together with CompBioMed3, PerMedCoE organised a workshop in February 2022 to study the possibilities to include agent-based models in digital twins of organ models. This was the first meeting we had with developers of cell population modelling tools. While this meeting was not exclusively focused on the benchmark, it provided a useful initial opportunity to discuss the limitations of the technologies and, thus, the limitations of the scope of the community benchmark.

In addition, we had a second meeting in March 2022 where we addressed the community benchmark in more detail. This meeting served to kickstart both the “cell population” and the “constraint-based or metabolic modelling” benchmarks.

Each tool owner presented briefly their tool and then we discussed on the scope, metrics and use cases. There was consensus with respect to what kind of scope and use cases to be used: the scope would be CBM, and the use cases should be a combination of simple and complex ones that should be already implemented in the tools to minimise overheads. There was more debate on which kind of metrics could be needed and wanted: they should be quantitative, but also qualitative.

The metabolic participants also talked about which features could be benchmarkable and which could not. In this benchmark, there was a drop of one participant due to conflict of interest, as he is in the evaluation committee of this project.

Additionally, we discussed organising a hackathon on these benchmarks for the end of September, before or after the ECCB 2022, located in Sitges, near Barcelona. This hackathon would consist of having a hybrid meeting so that we all discuss and send jobs to an HPC cluster, such as MN4, to obtain the results of the simulations that would be benchmarked.

No final agreements were obtained on which scope, metrics and use cases would be used and we decided to reconvene in May 2022 for a follow-up meeting.

Action points decided were that BSC would gather minutes and distribute them and that BSC would ask ECCB organisers and technical BSC staff for the possibility of a back-to-back hackathon to execute the benchmark in late September 2022.

## **5. Conclusions and future work**

In this deliverable, we present the PerMedCoE observatory of tools that allows us to remain aware of software, algorithms and standards developed around cell-level modelling. We also present how we are benchmarking these tools with PerMedCoE’s own with the aim to assess the status of the field, defining the best applications to integrate in the CoE activities and engaging with the software users and developers.

The PerMedCoE observatory and benchmark results are being offered to the community in public websites to ensure that other tool developers join in in future releases and that users interested in these types of modelling take advantage of these benchmarks to select a tool appropriate to their project. The observatory is publicly accessible in this link : [https://permedcoe.bio.tools/](https://permedcoe.bio.tools/) and the preliminary benchmarks are publicly accessible in this one: [https://dev-openebench.bsc.es/projects/OEBC009](https://dev-openebench.bsc.es/projects/OEBC009). 

For future work, we will continue the meetings for the metabolic and cell population benchmarks and we will kick-start the ones for Boolean and CARNIVAL with the target schedule of late September to gather together to perform the community benchmarks hackathon around ECCB 2022.


## **6. References**

Abou-Jaoudé,W. *et al.* (2016) Logical Modeling and Dynamical Analysis of Cellular Networks. *Front. Genet.*, **7**, 94.

Albert,I. *et al.* (2008) Boolean network simulations for life scientists. *Source Code Biol. Med.*, **3**, 16.

Anjos,M.F. *et al.* (2021) Design and implementation of a modular interior-point solver for linear optimization. *arXiv*, **13**, 509–551.

Bradley,G. and Barrett,S.J. (2017) CausalR: extracting mechanistic sense from genome scale data. *Bioinformatics*, **33**, 3670–3672.

Breitwieser,L. *et al.* (2021) BioDynaMo: a modular platform for high-performance agent-based simulation. *Bioinformatics*.

Capella-Gutierrez,S. *et al.* (2017) Lessons Learned: Recommendations for Establishing Critical Periodic Scientific Benchmarking. *bioRxiv*, 181677.

Chaouiya,C. *et al.* (2012) Logical Modelling of Gene Regulatory Networks with GINsim. In, Helden,J. van *et al.* (eds), *Bacterial Molecular Networks, Methods in Molecular Biology*. Springer New York, 463–479.

Chindelevitch,L. *et al.* (2014) An exact arithmetic toolbox for a consistent and reproducible structural analysis of metabolic network models. *Nat. Commun.*, **5**, 4893.

Coakley,S. *et al.* (2012) Exploitation of High Performance Computing in the FLAME Agent-Based Simulation Framework. In, *2012 IEEE 14th International Conference on High Performance Computing and Communication 2012 IEEE 9th International Conference on Embedded Software and Systems*., 538–545.

Coakley,S. *et al.* (2006) Using x-machines as a formal basis for describing agents in agent-based modelling. *Simul. Ser.*, **38**, 33.

Cooper,F. *et al.* (2020) Chaste: Cancer, Heart and Soft Tissue Environment. *J. Open Source Softw.*, **5**, 1848.

Cytowski,M. *et al.* (2017) Implementation of an Agent-Based Parallel Tissue Modelling Framework for the Intel MIC Architecture. *Sci. Program.*, **2017**, 1–11.

Cytowski,M. and Szymanska,Z. (2014) Large-Scale Parallel Simulations of 3D Cell Colony Dynamics. *Comput. Sci. Eng.*, **16**, 86–95.

Cytowski,M. and Szymanska,Z. (2015) Large-Scale Parallel Simulations of 3D Cell Colony Dynamics: The Cellular Environment. *Comput. Sci. Eng.*, **17**, 44–48.

Dunn,S.-J. *et al.* (2013) Computational Models Reveal a Passive Mechanism for Cell Migration in the Crypt. *PLOS ONE*, **8**, e80516.

Dunn,S.-J. *et al.* (2012) Modelling the role of the basement membrane beneath a growing epithelial monolayer. *J. Theor. Biol.*, **298**, 82–91.

Ebrahim,A. *et al.* (2013) COBRApy: COnstraints-Based Reconstruction and Analysis for Python. *BMC Syst. Biol.*, **7**, 74.

Ghaffarizadeh,A. *et al.* (2018) PhysiCell: An open source physics-based cell simulator for 3-D multicellular systems. *PLOS Comput. Biol.*, **14**, e1005991.

Gonzalez,A.G. *et al.* (2006) GINsim: a software suite for the qualitative modelling, simulation and analysis of regulatory networks. *Biosystems*, **84**, 91–100.

Guebila,M.B. (2020) VFFVA: dynamic load balancing enables large-scale flux variability analysis. *BMC Bioinformatics*, **21**, 424.

Heirendt,L. *et al.* (2019) Creation and analysis of biochemical constraint-based models using the COBRA Toolbox v.3.0. *Nat. Protoc.*, **14**, 639–702.

Heirendt,L. *et al.* (2017) DistributedFBA.jl: high-level, high-performance flux balance analysis in Julia. *Bioinformatics*, **33**, 1421–1423.

Helikar,T. *et al.* (2012) Bio-Logic Builder: A Non-Technical Tool for Building Dynamical, Qualitative Models. *PLoS ONE*, **7**, e46417.

Helikar,T. and Rogers,J.A. (2009) ChemChains: a platform for simulation and analysis of biochemical networks aimed to laboratory scientists. *BMC Syst. Biol.*, **3**, 58.

Hoehme,S. *et al.* (2010) Prediction and validation of cell alignment along microvessels as order principle to restore tissue architecture in liver regeneration. *Proc. Natl. Acad. Sci.*, **107**, 10371–10376.

Hoehme,S. and Drasdo,D. (2010) A cell-based simulation software for multi-cellular systems. *Bioinformatics*, **26**, 2641–2642.

Hosseini-Gerami,L. *et al.* (2022) Benchmarking causal reasoning algorithms for gene expression-based compound mechanism of action analysis.

Jaeger,S. *et al.* (2014) Causal Network Models for Predicting Compound Targets and Driving Pathways in Cancer. *J. Biomol. Screen.*, **19**, 791–802.

Kabiri Chimeh,M. *et al.* (2019) Parallelisation strategies for agent based simulation of immune systems. *BMC Bioinformatics*, **20**, 579.

Kang,S. *et al.* (2014) Biocellion: accelerating computer simulation of multicellular biological system models. *Bioinforma. Oxf. Engl.*, **30**, 3101–3108.

Kaul,H. *et al.* (2013) A Multi-Paradigm Modeling Framework to Simulate Dynamic Reciprocity in a Bioreactor. *PLOS ONE*, **8**, e59671.

Kratochvíl,M. *et al.* (2022) COBREXA.jl: constraint-based reconstruction and exascale analysis. *Bioinformatics*, **38**, 1171–1172.

Letort,G. *et al.* (2019) PhysiBoSS: a multi-scale agent-based modelling framework integrating physical dimension and cell signalling. *Bioinformatics*, bty766.

Li,G.-H. *et al.* (2020) FastMM: an efficient toolbox for personalized constraint-based metabolic modeling. *BMC Bioinformatics*, **21**, 67.

Lin,C.-L. *et al.* (2013) Multiscale image-based modeling and simulation of gas flow and particle transport in the human lungs. *Wiley Interdiscip. Rev. Syst. Biol. Med.*, **5**, 643–655.

Mendes,N.D. *et al.* (2018) Estimating Attractor Reachability in Asynchronous Logical Models. *Front. Physiol.*, **9**.

Metzcar,J. *et al.* (2019) A Review of Cell-Based Computational Modeling in Cancer Biology. *JCO Clin. Cancer Inform.*, 1–13.

Müssel,C. *et al.* (2010) BoolNet -- an R package for generation, reconstruction and analysis of Boolean networks. *Bioinformatics*, **26**, 1378–1380.

Noël,V. *et al.* (2021) WebMaBoSS: A Web Interface for Simulating Boolean Models Stochastically. *Front. Mol. Biosci.*, **8**.

Osborne,J.M. *et al.* (2017) Comparing individual-based approaches to modelling the self-organization of multicellular tissues. *PLOS Comput. Biol.*, **13**, e1005387.

Ramis-Conde,I. and Drasdo,D. (2012) From genotypes to phenotypes: classification of the tumour profiles for different variants of the cadherin adhesion pathway. *Phys. Biol.*, **9**, 036008.

Richmond,P. *et al.* (2010) High performance cellular level agent-based simulation with FLAME for the GPU. *Brief. Bioinform.*, **11**, 334–347.

Saxena,G. *et al.* (2021) BioFVM-X: An MPI+OpenMP 3-D Simulator for Biological Systems. In, Cinquemani,E. and Paulevé,L. (eds), *Computational Methods in Systems Biology*, Lecture Notes in Computer Science. Springer International Publishing, Cham, 266–279.

Stoll,G. *et al.* (2012) Continuous time Boolean modeling for biological signaling: application of Gillespie algorithm. *BMC Syst. Biol.*, **6**, 116.

Stoll,G. *et al.* (2017) MaBoSS 2.0: an environment for stochastic Boolean modeling. *Bioinformatics*, **33**, 2226–2228.

Swat,M.H. *et al.* (2012) Multi-Scale Modeling of Tissues Using CompuCell3D. In, *Methods in Cell Biology*. Elsevier, 325–366.

Szymańska,Z. *et al.* (2018) Computational Modelling of Cancer Development and Growth: Modelling at Multiple Scales and Multiscale Modelling. *Bull. Math. Biol.*, **80**, 1366–1403.

Van Liedekerke,P. *et al.* (2015) Simulating tissue mechanics with agent-based models: concepts, perspectives and some novel results. *Comput. Part. Mech.*, **2**, 401–444.

Vlassis,N. *et al.* (2014) Fast Reconstruction of Compact Context-Specific Metabolic Network Models. *PLOS Comput. Biol.*, **10**, e1003424.

Wang,H. *et al.* (2018) RAVEN 2.0: A versatile toolbox for metabolic network reconstruction and a case study on Streptomyces coelicolor. *PLOS Comput. Biol.*, **14**, e1006541.
