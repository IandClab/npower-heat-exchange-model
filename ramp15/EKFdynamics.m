function [xdot] = EKFdynamics(x,hotpar,coldpar,wallpar,pumppar,input)

% hot-leg parameters
rhoh  = hotpar(1);
Vh    = hotpar(2);
ch    = hotpar(3);
mdoth = hotpar(4);
hh    = hotpar(5);
Thi   = hotpar(6);

% cold-leg parameters
rhoc  = coldpar(1);
Vc    = coldpar(2);
cc    = coldpar(3);
hc    = coldpar(4);

% inputs
mdotc = input(1);
Tci   = input(2);

% wall parameters
rhow  = wallpar(1);
Vw    = wallpar(2);
cw    = wallpar(3);
A     = wallpar(4);

% pump and disturbance parameters
wp = pumppar(1);
wa = pumppar(2);
wb = pumppar(3);

%%%%% State equations
dx1 = -(x(4)*ch + hh*A)/(rhoh*Vh*ch)*x(1) + hh*A/(rhoh*Vh*ch)*x(3) + x(4)*ch/(rhoh*Vh*ch)*x(5);
dx2 = -(x(6)*cc + hc*A)/(rhoc*Vc*cc)*x(2) + hc*A/(rhoc*Vc*cc)*x(3) + x(6)*cc/(rhoc*Vc*cc)*Tci;
dx3 = hh*A/(rhow*Vw*cw)*x(1) + hc*A/(rhow*Vw*cw)*x(2) - (hh*A + hc*A)/(rhow*Vw*cw)*x(3);
dx4 = -wa*x(4);
dx5 = -wb*x(5);
dx6 = -wp*x(6) + wp*mdotc;

xdot = [dx1;dx2;dx3;dx4;dx5;dx6];