clear
clc
%close all

data = table2array(readtable('cell-0-sim1.csv'));

Time = data(:,1);
Volume = data(:,2);
Phase = data(:,3);
Age = data(:,4);

Volume_min = Volume(1);

figure, hold on
plot(Time, Volume/Volume_min, '-r')
xlabel('time (hours)'), ylabel('cell volume (normalized to minimum value)')
grid on
hold off

figure, hold on
plot(Time, Phase, '-b')
xlabel('time (hours)'), ylabel('cell phase (1:G0/G1; 2:S; 3:G2; 4:M)')
grid on
hold off
