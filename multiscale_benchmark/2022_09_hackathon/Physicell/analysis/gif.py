import glob,os,re
from PIL import Image

def get_key(fp):
    filename = os.path.splitext(os.path.basename(fp))[0]
    # int_part = filename.split("_")[1]
    int_part =  re.findall(r'\d+', filename)[0]
    return int(int_part)

def make_gif(frame_folder):
    frames = [Image.open(image) for image in sorted(glob.glob(f"{frame_folder}/*.png"),key=get_key)]

    frame_one = frames[0]
    frame_one.save("physicell_single_diffusion.gif", format="GIF", append_images=frames,
               save_all=True, duration=100, loop=0)
if __name__ == "__main__":
    make_gif("/home/thalia/BSC/NEW_BENCH/Physicell_template/out_single_diffusion/")