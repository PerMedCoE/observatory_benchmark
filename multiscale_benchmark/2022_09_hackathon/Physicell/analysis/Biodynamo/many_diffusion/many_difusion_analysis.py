import matplotlib.pyplot as plt
import pandas as pd
from pathlib import Path
import glob
from PIL import Image
import os,re

biodynamo_output_folder = "/home/thalia/BSC/Benchmarks/Benchmarking/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_diffusion_1k/results/"
df = pd.read_csv("/home/thalia/BSC/Benchmarks/Benchmarking/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_diffusion_1k/results/concentration_all.csv",header=None,index_col=0)
x=[]
y=[]
z=[]
numbers =list(range(-110, 111, 20))
for xi in numbers:
    for yi in numbers:
        for zi in numbers:
            # print(x,y,z)
            x.append(xi)
            y.append(yi)
            z.append(zi)
print(len(x))
for index, row  in df.iterrows():
    if index%10==0:
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        # index = timestep
        # column = voxel id
        # # Add voxels to the plot
        ax.scatter(x, y, z, c=row, cmap='jet')


        # # Set the axis labels
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        # plt.show()
        # num_ite = index/100
        plt.title("Diffusion of molecules, 1k cells as sinks Biodynamo Timestep: "+f'{index:.2f}')
        # print(num_ite)
        plt.savefig(biodynamo_output_folder+"/diff_timepoint"+str(int(index))+".png")
        plt.close()

# now generate gif
def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    # int_part = filename.split("_")[1]
    int_part =  re.findall(r'\d+', filename)[0]
    return int(int_part)
frames = [Image.open(image) for image in sorted(glob.glob(f"{biodynamo_output_folder}/*.png"),key=get_key)]

frame_one = frames[0]
frame_one.save(biodynamo_output_folder+"many_diffusion.gif", format="GIF", append_images=frames,
            save_all=True, duration=100, loop=0)