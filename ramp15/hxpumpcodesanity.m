% Jason Pickel
% Kalman filter  for heat exchanger
% June 18 2016

% treating the hot-leg mass flow rate and the hot-leg temp in as
% disturbances
% both the hot-leg mass flow rate and the hot-leg temp in are additional
% states

clc; clear all; close all;

format compact
format shortg

delay = 0;

% simulation parameters
Ts = 1e-1;
h  = Ts;
Tfinal =300;
wref= 0.1;

% hot-leg parameters
rhoh  = 1940;
Vh    = 1.1508;
ch    = 2414;
mdoth = 350;
hh    = 3400*7;
Thi   = 700;

% cold-leg parameters
rhoc  = 2020;
Vc    = 1.5127;
cc    = 1901; 
mdotc = 247;
hc    = 3500*7;
Tci   = 550;

% wall parameters
rhow  = 8860;
Vw    = 0.4675;
cw    = 578;
A     = 292.2;

% pump parameters
wp = 0.1;
wa = 2e-3;
wb = 5e-3;

% noisePSD
Sw_tc  = 0.05;
Sw_mh  = 25;
Sw_th  = 25;
Sw = diag([Sw_tc Sw_mh Sw_th]);

Sv_thi = 5e-2;
Sv_tho = 0.1;
Sv_mh  = 0.05;
Sv = diag([Sv_thi Sv_tho Sv_mh]);

% initial states
x0=[650.29 638.4 644.3 mdoth Thi 250];

% covariance initial conditions are the steady-state values
% State Matrices in Continuous-Time
ACT = [-(mdoth*ch + hh*A)/(rhoh*Vh*ch) 0 hh*A/(rhoh*Vh*ch) ch*(Thi - x0(1))/(rhoh*Vh*ch) mdoth*ch/(rhoh*Vh*ch) 0;
       0 -(mdotc*cc + hc*A)/(rhoc*Vc*cc) hc*A/(rhoc*Vc*cc) 0 0 cc*(Tci-x0(2))/(rhoc*Vc*cc);
       hh*A/(rhow*Vw*cw) hc*A/(rhow*Vw*cw) -(hh*A + hc*A)/(rhow*Vw*cw) 0 0 0;
       0 0 0 -wa 0 0;
       0 0 0 0 -wb 0;
       0 0 0 0 0 -wp];
BwCT = [0 0 0  ; mdotc*cc/(rhoc*Vc*cc)*Tci 0 0 ; zeros(1,3); 0 1 0;0 0 1;0 0 0];
CCT  = [0 0 0 0 1 0; 1 0 0 0 0 0; 0 0 0 1 0 0];

% ACT = [-(xhatin(4)*ch + hh*A)/(rhoh*Vh*ch) 0 hh*A/(rhoh*Vh*ch) ch*(xhatin(5) - xhatin(1))/(rhoh*Vh*ch) xhatin(4)*ch/(rhoh*Vh*ch) 0;
%        0 -(mdotc*cc + hc*A)/(rhoc*Vc*cc) hc*A/(rhoc*Vc*cc) 0 0 cc*(Tci-xhatin(2))/(rhoc*Vc*cc);
%        hh*A/(rhow*Vw*cw) hc*A/(rhow*Vw*cw) -(hh*A + hc*A)/(rhow*Vw*cw) 0 0 0;
%        0 0 0 -wa 0 0;
%        0 0 0 0 -wb 0;
%        0 0 0 0 0 -wp];

% State Matrices in Discrete-Time
ADT = eye(6) + ACT*h+ACT^2*h^2/2+ACT^3*h^3/6+ACT^4*h^4/24;
BwDT = BwCT*h + ACT*BwCT*h^2/2 + 1/6*ACT^2*BwCT*h^3 + 1/24*ACT^3*BwCT*h^4;
CDT = CCT;
[LDT,PDT,EDT,eig_poles]  = dlqe(ADT,BwDT,CDT,Sw,Sv);

% control gains
kp = 4.995;
ki = 1.2;
% kp = 4.4495;
% ki = 1.5;


% reference signal
Pref= 37.8;  % megawatts

%% Simulation of the controller and heat exchanger
% note, no EKF or wireless network


% sim('HXpump_justplant',[0 Tfinal])
% 
% figure
% subplot(211), plot(tout,Perror)
% xlabel('Time (sec)')
% ylabel('Power Error (MW)')
% subplot(212), plot(tout,control)
% xlabel('Time (sec)')
% ylabel('mdot c (kg/s)')

%% Simulation of the heat exchanger, controller, and EKF
% note, no wireless network

sim('HXpump_whole_sanity',[0 Tfinal])


% hottemp = [xout(:,1) xhat(:,1)];
% coldtemp = [xout(:,2) xhat(:,2)];
% walltemp = [xout(:,3) xhat(:,3)];
% mdothstate = [mdoth*ones(length(tout),1) xhat(:,4)];
% Thistate = [Thi*ones(length(tout),1) xhat(:,5)];
   

% figure
% subplot(511), plot(tout,hottemp)
% xlabel('Time (sec)')
% ylabel('HL Temp out (C)')
% subplot(512), plot(tout,coldtemp)
% xlabel('Time (sec)')
% ylabel('CL Temp out (C)')
% subplot(513), plot(tout,walltemp)
% xlabel('Time (sec)')
% ylabel('Wall Temp (C)')
% subplot(514), plot(tout,mdothstate)
% xlabel('Time (sec)')
% ylabel('HL mass flow rate (kg/s)')
% subplot(515), plot(tout,Thistate)
% xlabel('Time (sec)')
% ylabel('HL temp in (C)')
% % 
% figure
% subplot(211), plot(tout,Perror), grid on
% xlabel('Time (sec)')
% ylabel('Power Error (MW)')
% subplot(212), plot(tout,control)
% xlabel('Time (sec)')
% ylabel('mdot c (kg/s)')

%% Simulation of the heat exchanger, controller, EKF, and wireless network
% everything
% 
% Delay = 0;
% ranD=[4 2 2 2 2]; %delayed time steps 
%  yin = [0 0 0];
%     ynd_tmp = [0 0 0];
%     
%     yin_d = [0 0 0]';
%     delay_v= [0 0 0]';
% count = 1;
%     i = 0;
%  structure.i = 0;
%     structure.count = count;
%     structure.sen_num=9;
%     structure.yin = yin;
%     structure.yin_d = yin_d;
%     structure.delay_v = delay_v;
%     structure.ynd_tmp = ynd_tmp;
%     %structure.sensor_value = sensor_value;
%     structure.ranD = ranD;

% sim('HXpump_whole',[0 Tfinal])
% 
% 
% hottemp = [xout(:,1) xhat(:,1)];
% coldtemp = [xout(:,2) xhat(:,2)];
% walltemp = [xout(:,3) xhat(:,3)];
% mdothstate = [mdoth*ones(length(tout),1) xhat(:,4)];
% Thistate = [Thi*ones(length(tout),1) xhat(:,5)];
%    
% 
% figure
% subplot(511), plot(tout,hottemp)
% xlabel('Time (sec)')
% ylabel('HL Temp out (C)')
% subplot(512), plot(tout,coldtemp)
% xlabel('Time (sec)')
% ylabel('CL Temp out (C)')
% subplot(513), plot(tout,walltemp)
% xlabel('Time (sec)')
% ylabel('Wall Temp (C)')
% subplot(514), plot(tout,mdothstate)
% xlabel('Time (sec)')
% ylabel('HL mass flow rate (kg/s)')
% subplot(515), plot(tout,Thistate)
% xlabel('Time (sec)')
% ylabel('HL temp in (C)')
% 
% figure
% subplot(211), plot(tout,Perror), grid on
% xlabel('Time (sec)')
% ylabel('Power Error (MW)')
% subplot(212), plot(tout,control)
% xlabel('Time (sec)')
% ylabel('mdot c (kg/s)')
% 
% figure
% subplot(311), plot(tout,hottemp)
% xlabel('Time (sec)')
% ylabel('HL Temp out (C)')
% subplot(312), plot(tout,mdothstate)
% xlabel('Time (sec)')
% ylabel('HL mass flow rate (kg/s)')
% subplot(313), plot(tout,Thistate)
% xlabel('Time (sec)')
% ylabel('HL temp in (C)')







