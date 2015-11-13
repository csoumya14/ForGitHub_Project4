close all
clear all
clc

%Import data and define closed-form solution
%Data for ordered spins (up = 1) and T = 1.0
filename = 'DataForGraphsD.xlsx';
sheet = 1;
xlRange = 'A6:A990005';

[v,T,vT] = xlsread(filename, sheet, xlRange);
dataA_T_1=v(:,1); 

% Data for random spins and T = 2.4
filename = 'DataForGraphsD.xlsx';
sheet = 2;
xlRange = 'A6:A990005';

[v,T,vT] = xlsread(filename, sheet, xlRange);
dataB_T_24=v(:,1);

%Plot histograms
figure
%hist(dataA_T_1)
%xlim([-800 -797])
%nbins = 100;
%xbins = -800:-700;
xbins = -700:-200;
[f,x] = hist(dataB_T_24,xbins)
dx = diff(x(1:2))
bar(x,f/sum(f*dx))
legend('T=2.4','LineWidth',12)
xlabel('Mean in Energy','LineWidth',12)
ylabel('Probability','LineWidth',12)
%bar(x,f/trapz(x,f));



