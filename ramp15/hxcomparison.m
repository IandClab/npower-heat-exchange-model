% Jason Pickel
% Heat Transfer comparison for the CT vs DT
% July 22 2016

clc; clear all; close all;

format compact
format shortg

% load data
load 'xkalman.mat'
load 'xnaive.mat'

% DT version (kalman filter)
tkal        = xkalman(1,:);  % time
Perror_kal  = xkalman(2,:); % Power error
control_kal = xkalman(3,:); % control CL mass flow rate)
Tho_kal     = xkalman(4,:); % HL temp out
mdoth_kal   = xkalman(7,:); % HL mass flow rate
Thi_kal     = xkalman(8,:);   % HL temp in

% CT version (use last received measurements
tnav        = xnaive(1,:);  % time
Perror_nav  = xnaive(2,:); % Power error
control_nav = xnaive(3,:); % control CL mass flow rate)
Tho_nav     = xnaive(5,:); % HL temp out
mdoth_nav   = xnaive(6,:); % HL mass flow rate
Thi_nav     = xnaive(4,:);   % HL temp in

figure
subplot(211), plot(tkal,Perror_kal,tnav,Perror_nav)
xlabel('Time (sec)')
ylabel('Power error (MW)')
subplot(212), plot(tkal,control_kal,tnav,control_nav)
xlabel('Time (sec)')
ylabel('CL mass flow rate (kg/s)')

figure
subplot(311), plot(tkal,Tho_kal,tnav,Tho_nav)
xlabel('Time (sec)')
ylabel('HL temp out (C)')
subplot(312), plot(tkal,Thi_kal,tnav,Thi_nav)
xlabel('Time (sec)')
ylabel('HL temp out (C)')
subplot(313), plot(tkal,mdoth_kal,tnav,mdoth_nav)
xlabel('Time (sec)')
ylabel('HL mass flow rate (kg/s)')


