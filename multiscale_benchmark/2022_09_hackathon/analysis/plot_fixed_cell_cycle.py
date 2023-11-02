import argparse
import pandas as pd


def create_parser():
    parser = argparse.ArgumentParser(description="Create folders from input paths.")

    # Specify at least 3 folder paths as arguments
    parser.add_argument("--pc-csv", action="store", dest = "pc_csv",help="Path to the PhysiCell position over time csv",
                        default="../Physicell/output/mechanics_pushing/cells_position_time.csv")
    parser.add_argument("--bd-csv",action="store", dest = "bd_csv" ,help="Path to BioDynaMo position over time csv",
                    default="../Biodynamo/unit_test_mechanics_pushing/results/positions.csv")
    parser.add_argument("--ch-csv",action="store", dest = "ch_csv", help="Path to Chaste position over time csv",
                    default="../Chaste/unit_test_mechanics_pushing/results/results.viznodelocations")
    parser.add_argument("--ts-csv",action="store", dest = "ts_csv", help="Path to TiSim concentration over time csv")

    return parser

def get_physicell_df(file):
    df = pd.read_csv(file,index_col=0,float_precision='round_trip').sort_values(by=['dt']).reset_index(drop=True)

    return df

def get_biodynamo_df(file):
    df = pd.read_csv(file,index_col=0,header = None,sep='\t|,',engine='python').rename(columns={1: "x1", 4: "x2"})

    return df
def get_tisim_df(file):
    # df= pd.read_csv(file,delimiter="\t",names = ['timestep','diff'],header=0)
    df = pd.read_csv(file,names=[x for x in range(0,28)],skiprows=[0],index_col=0,sep='\t|,',engine='python')
    return df

def get_chaste_df(file):
    df = pd.read_csv(file,header = None,sep='\t| ',index_col=0,engine='python')
    with open(file, "r") as f:
        df = pd.DataFrame(columns=["dt","id","x","y","z","g1_duration","s_duration","g2_duration","m_duration","current_phase","target_area","volume"])
        for line in f.read().splitlines():
            data = line.split()
            data = [float(x) if x.replace('.', '', 1).isdigit() else x for x in data]
            dt = data[0]
            for i in range(0,len(data)//11):
                row = {'dt': dt, 'id': data[1+11*i], 'x': data[2+11*i], 'y': data[3+11*i], 'z': data[4+11*i], 'g1_duration': data[5+11*i], 's_duration': data[6+11*i], 'g2_duration': data[7+11*i], 'm_duration': data[8+11*i], 'current_phase': data[9+11*i], 'target_area': data[10+11*i], 'volume': data[11+11*i]}
                row = pd.Series(row)
                df2 = pd.DataFrame(row).transpose()

                df =pd.concat([df,df2],ignore_index=True)
        return df


def main():



    return

if __name__ == "__main__":
    main()
