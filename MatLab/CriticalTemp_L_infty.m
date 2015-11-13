close all
clear all
clc

%Import data 
%Data for L=10, MC=e6, ramdon spin-config
filename = 'DataCriticalTemp.xlsx';
sheet = 5;
xlRange = 'A3:B6';
[v,T,vT] = xlsread(filename, sheet, xlRange);
L_invers=v(:,1); 
T_c=v(:,2); 

X = [ones(length(L_invers),1) L_invers];

b = X\T_c

x = 0:0.001:0.1;
y = b(1)+b(2)*x;

%Plot data
%ylim([20 300000])
%xlim([0 10000])

figure
plot(L_invers, T_c, 'ko', x, y, '--b', 'LineWidth',2)
legend('data','T_c (L^{-1} ) = 2.2865+0.6469*L^{-1}','FontSize',12,'Location','northwest')
 
xlabel('L^{-1}','FontSize',12)
ylabel('Critical temperature','FontSize',12)
% ylim([-1.8 -1.2])

