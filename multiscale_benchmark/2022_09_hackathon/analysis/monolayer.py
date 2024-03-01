import pandas as pd
from plotnine import *
import plotnine as p9
import re
import matplotlib.pyplot as plt
import argparse

def create_parser():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell ",
                        default="../Physicell/output/fixed_cell_cycle/cells_volumes.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo",
                    default="../Biodynamo/use_case_2Ddisk/results/monolayer_growth.json")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste cel",
                    default="../Chaste/use_case_2Ddisk/results/single-cell/tissuewidth.dat")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim cell",
                        default = "Tisim/use_case_2Ddisk/results/result_2d_10_8_3.9_50.txt")

    return parser
expe_dt = [336,386,408,481,506,646]
expe_dt = [x/24. for x in expe_dt]
expe_diam = [ 1140 , 1400 , 1590 , 2040 , 2250 , 3040 ]

biodynamo_dt = [14, 14.8333333333333, 15.6666666666667, 16.5, 17.3333333333333, 18.1666666666666, 18.9999999999999, 19.8333333333332, 20.6666666666665, 21.4999999999998, 22.333333333333, 23.1666666666663, 23.9999999999996, 24.8333333333329, 25.6666666666665, 26.5]
biodynamo_diam =  [1240, 1320, 1440, 1560, 1680, 1800, 1920, 2040, 2160, 2280, 2400, 2520, 2640, 2760, 2880, 3000]

df_tsim_pre = pd.read_csv('./tisim_result_2d_10_8_3.9_50_20221102.txt',sep='\t',engine='python')
tisim_diam = [2*x for x in df_tsim_pre['Radius of cell population [um]'].iloc[142:]]
tisim_dt = [x/86400 for x in df_tsim_pre['Time [s]'].iloc[142:]]

df_pc = pd.read_csv('./physicell1428.csv' ,sep=',',engine='python')
df_pc = df_pc.drop(columns=df_pc.columns[0])

df_exp = pd.DataFrame(data=zip(expe_dt,expe_diam),columns=['dt','diam'])
df_exp.insert(loc=2, column='Results', value='Experimental')
df_biod = pd.DataFrame(data=zip(biodynamo_dt,biodynamo_diam),columns=['dt','diam'])
df_biod.insert(loc=2, column='Results', value='BioDynaMo')
df_tisim = pd.DataFrame(data=zip(tisim_dt,tisim_diam),columns=['dt','diam'])
df_tisim.insert(loc=2, column='Results', value='TiSim')
df_pc.insert(loc=2, column='Results', value='PhysiCell')
frames = [df_pc, df_tisim, df_biod, df_exp]
df_all = pd.concat(frames)


# chaste
with open('tissuewidth.dat') as results_file:
    times = []
    tissue_widths = []
    num_cells = []
    for line in results_file:
        line = line.replace('\n', '')
        values = re.split('\t|,', line)
        if len(values) == 1:
            continue
        
        times.append(float(values[0]))
        tissue_widths.append(float(values[3]))
        num_cells.append(int(values[4]))

color = {
    'Experimental': 'black', 
    'BioDynaMo': 'red', 
    'TiSim': 'orange',
    'PhysiCell': 'green',
    'Chaste': 'blue'
    }

(
    ggplot (df_all) + 
    aes(x='dt',y='diam', colour='Results') + 
    geom_point(alpha = 0.7) +
    geom_point(data=df_all.query("Results == 'Experimental' "), shape="X", size=5)+
    scale_color_manual(values=color, name="Results")+
    scale_x_continuous(name="Time (days)", limits={14, 28}, breaks = range(14,30,2))+
    scale_y_continuous(name="Diameter (um)", limits={1000, 3500}, breaks = range(0,4000,500))+
    theme_bw()+
    theme(legend_position = "right")+
    guides(colour=guide_legend(override_aes={"shape": 'o'}))
)