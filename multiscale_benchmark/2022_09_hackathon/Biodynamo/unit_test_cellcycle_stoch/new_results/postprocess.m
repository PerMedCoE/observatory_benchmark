clear
clc
close all

%%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%%
%%% loading up some 9 pre-run simulations of a single cell and plotting
%%% out the "cell volume" and "cell phase" with respect to time
%%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%%

figure, hold on
for I = 1 : 9
    fname = sprintf('output%d/cell-0.csv',I);
    data = table2array(readtable(fname));

    Time = data(:,1);
    Volume = data(:,2);
    Phase = data(:,3);
    Age = data(:,4);
    
    Volume_min = Volume(1);

    plot(Time, Volume/Volume_min, '-')
end
xlabel('time (hours)'), ylabel('cell volume (normalized to minimum value)')
grid on
hold off

figure, hold on
for I = 1 : 9
    fname = sprintf('output%d/cell-0.csv',I);
    data = table2array(readtable(fname));

    Time = data(:,1);
    Volume = data(:,2);
    Phase = data(:,3);
    Age = data(:,4);

    plot(Time, Phase, '-')
end
xlabel('time (hours)'), ylabel('cell phase (1:G0/G1; 2:S; 3:G2; 4:M)')
grid on
hold off

%%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%%
%%% loading up some 1 pre-run simulation of a four cells and plotting
%%% out the "cell volume" and "cell phase" with respect to time
%%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%% %%%

figure, hold on
CellIndex = [0,2,3,4];
for I = 1 : 4
    fname = sprintf('output/cell-%d.csv',CellIndex(I));
    data = table2array(readtable(fname));

    Time = data(:,1);
    Volume = data(:,2);
    Phase = data(:,3);
    Age = data(:,4);
    
    Volume_min = Volume(1);

    plot(Time, Volume/Volume_min, '-')
end
xlabel('time (hours)'), ylabel('cell volume (normalized to minimum value)')
grid on
hold off
