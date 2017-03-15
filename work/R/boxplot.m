% MS: 1.21951
% AS: 0.183704
% AO: 1.50095
% AWO: 0.191092
% LOR: 0.974578
% AL: 0.178276
% EO: 2.7027
% EWO: 0.121507
% MLC: 5.71655
% MPOL1: 5.71606
% MPOL2: 0.971038
% ES: 0.0445238
% AL2: 1e-005
% AWS: 0.0867783
% EWS: 0.034608
% MAXS: 1
% AWS2: 1.43193
clc;
clear;
close all
% maindir1 = 'uniform_data';
% maindir2 = 'non-uniform_data';
maindir1 = 'Funnel/funnel_800_42/result';
% maindir2 = 'non-uniform_data_metric';
uniform=false;

subdir1 =  dir(fullfile([maindir1,'/'],'*.csv'));   % 先确定子文件夹
disp(subdir1(1).name);
% subdir2 =  dir( [maindir2,'/'] );   % 先确定子文件夹
dstdir = 'result/';
countdir=0;
x=1;
funcv = [];
num1=1;
num2=1;


color=[102,166,30 %AL
        139,0,255 %AS
        30,144,255 %AWO
        231,41,138 %MS
        217,95,2 %RV
        230,171,2 %L1L
        12,0,212 %LOR
        251,154,153 %AO
        ]/255;

matsaves=zeros(length( subdir1 ),1);
for i = 1 : length( subdir1 )
%     if( isequal( subdir1( i ).name, '.' ) || ...
%         isequal( subdir1( i ).name, '..' ) || ...
%         ~subdir1( i ).isdir )   % 如果不是目录跳过
%         continue;
%     end
      
    funcPath = [maindir1,'/',subdir1(i).name];
    disp(funcPath);
    tmp=dlmread(funcPath,',','B2..B2');
    
    matsaves(i,1)=tmp;
    
end

% -----------------------------
% matsaves=matsaves(:,1:7);

figure('NumberTitle', 'off', 'Name', 'Clumpy')
boxplot((matsaves(:,1)),'Widths',0.4,'FactorSeparator',1, 'Color','rrrrrr');
ylim([0 1]);
set(gcf,'Position',[70 70 140 140]);
% set(gca,'xtickLabel',{'Clumpy'});
% daspect([2 1 1]);
% axis off
% saveas(gcf,'boxp1d0126.pdf');
