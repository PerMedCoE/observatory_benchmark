import pandas as pd
import matplotlib.pyplot as plt

for i in range(4):
    data = pd.read_csv(f'results/cell-{i}.csv')

    data.columns = ['Time', 'Volume', 'Phase', 'Age']

    Time = data['Time']
    Volume = data['Volume']
    Phase = data['Phase']
    Age = data['Age']

    Volume_min = Volume[0]

    plt.figure()
    plt.plot(Time, Volume/Volume_min, '-r')
    plt.xlabel('time (hours)')
    plt.ylabel('cell volume (normalized to minimum value)')
    plt.grid(True)
    plt.savefig(f'results/VolumeVsTime-{i}.png')

    plt.figure()
    plt.plot(Time, Phase, '-b')
    plt.xlabel('time (hours)')
    plt.ylabel('cell phase (1:G0/G1; 2:S; 3:G2; 4:M)')
    plt.grid(True)
    plt.savefig(f'results/PhaseVsTime-{i}.png')