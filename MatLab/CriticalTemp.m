close all
clear all
clc

%Import data 
%Data for L=10, MC=e6, ramdon spin-config
filename = 'DataCriticalTemp.xlsx';
sheet = 2;
xlRange = 'A5:E13';
[v,T,vT] = xlsread(filename, sheet, xlRange);
Temperature=v(:,1); 
E_10=v(:,2); M_10=v(:,3); Cv_10=v(:,4); X_10=v(:,5);

%Data for L=20, MC=e6, ramdon spin-config
filename = 'DataCriticalTemp.xlsx';
sheet = 1;
xlRange = 'A5:E13';
[v,T,vT] = xlsread(filename, sheet, xlRange);
E_20=v(:,2); M_20=v(:,3); Cv_20=v(:,4); X_20=v(:,5);

%Data for L=40, MC=e6, ramdon spin-config
filename = 'DataCriticalTemp.xlsx';
sheet = 3;
xlRange = 'A5:E13';
[v,T,vT] = xlsread(filename, sheet, xlRange);
E_40=v(:,2); M_40=v(:,3); Cv_40=v(:,4); X_40=v(:,5);

%Data for L=60, MC=e6, ramton spin-config
filename = 'DataCriticalTemp.xlsx';
sheet = 4;
xlRange = 'A5:E13';
[v,T,vT] = xlsread(filename, sheet, xlRange);
E_60=v(:,2); M_60=v(:,3); Cv_60=v(:,4); X_60=v(:,5);

%Plot data
%ylim([20 300000])
%xlim([0 10000])
%Energy
figure
plot(Temperature,E_10/(10*10),'m',Temperature,E_20/(20*20),'-.b',Temperature,E_40/(40*40),'--r',Temperature,E_60/(60*60),':k','LineWidth',2)
legend('N=10','N=20','N=40','N=60','FontSize',12,'Location','northwest')

xlabel('Temperature','FontSize',12)
ylabel('Mean of Energy','FontSize',12)
ylim([-1.8 -1.2])

%Magnetization
figure
plot(Temperature,M_10/(10*10),'m',Temperature,M_20/(20*20),'-.b',Temperature,M_40/(40*40),'--r',Temperature,M_60/(60*60),':k','LineWidth',2)
legend('N=10','N=20','N=40','N=60','FontSize',12,'Location','northwest')

xlabel('Temperature','FontSize',12)
ylabel('Mean of Magnetization','FontSize',12)

%Specific heat
figure
plot(Temperature,Cv_10/(10*10),'m',Temperature,Cv_20/(20*20),'-.b',Temperature,Cv_40/(40*40),'--r',Temperature,Cv_60/(60*60),':k','LineWidth',2)
legend('N=10','N=20','N=40','N=60','FontSize',12,'Location','northwest')

xlabel('Temperature','FontSize',12)
ylabel('Specific heat','FontSize',12)

%Susceptibility
figure
plot(Temperature,X_10/(10*10),'m',Temperature,X_20/(20*20),'-.b',Temperature,X_40/(40*40),'--r',Temperature,X_60/(60*60),':k','LineWidth',2)
legend('N=10','N=20','N=40','N=60','FontSize',12,'Location','northwest')

xlabel('Temperature','FontSize',12)
ylabel('Susceptibility','FontSize',12)





