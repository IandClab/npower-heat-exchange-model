% Jason Pickel
% Heat Transfer comparison for the CT vs DT
% July 22 2016

clc; clear all; close all;

format compact
format shortg

% load data
load 'xkalsanity.mat'
load 'xorigsanity.mat'
load 'xsanity.mat'

%%%%%  Sanity check
% DT version (kalman filter)
tkal        = xkalsanity(1,:);  % time
Perror_kal  = xkalsanity(2,:);  % power error
cont_kal    = xkalsanity(3,:);  % control signal
Thi_kal     = xkalsanity(8,:);  % HL temp in
Tho_kal     = xkalsanity(4,:);  % HL temp out
mdoth_kal   = xkalsanity(7,:);  % HL mass flow rate

% CT version (use last received measurements
tnav        = xorigsanity(1,:);  % time
Perror_nav  = xorigsanity(2,:);  % power error
cont_nav    = xorigsanity(3,:);  % control signal
Thi_nav     = xorigsanity(4,:);   % HL temp in
Tho_nav     = xorigsanity(5,:); % HL temp out
mdoth_nav   = xorigsanity(6,:); % HL mass flow rate

% plant
tplant        = xsanity(1,:);
Perror_plant    = xsanity(2,:);  % power error
cont_plant      = xsanity(3,:);  % control signal
Tho_plant     = xsanity(5,:);
Thi_plant     = xsanity(4,:);
mdoth_plant   = xsanity(6,:);



figure
subplot(211), plot(tkal,Perror_kal,'k',tnav,Perror_nav,'--g')
xlabel('Time (sec)')
ylabel('Power error (MW)')
subplot(212), plot(tkal,cont_kal,'k',tnav,cont_nav,'--g')
xlabel('Time (sec)')
ylabel('CL mass flow rate (kg/s)')
legend('EKF','last value','Location','Best')

figure
subplot(311), plot(tkal,Tho_kal,'k',tnav,Tho_nav,'--g')
xlabel('Time (sec)')
ylabel('HL temp out (C)')
legend('EKF','last value','Location','Best')
subplot(312), plot(tkal,Thi_kal,'k',tnav,Thi_nav,'--g')
xlabel('Time (sec)')
ylabel('HL temp out (C)')
subplot(313), plot(tkal,mdoth_kal,'k',tnav,mdoth_nav,'--g')
xlabel('Time (sec)')
ylabel('HL mass flow rate (kg/s)')


