function [xdot] = heatexchanger(x,hotpar,coldpar,wallpar,input,noise)

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

% input
mdotc = input(1);
Tci   = input(2);

% wall parameters
rhow  = wallpar(1);
Vw    = wallpar(2);
cw    = wallpar(3);
A     = wallpar(4);

% process noise
wt = noise(1);

%%%%% State equations
dx1 = -(mdoth*ch + hh*A)/(rhoh*Vh*ch)*x(1) + hh*A/(rhoh*Vh*ch)*x(3)...
    + mdoth*ch/(rhoh*Vh*ch)*Thi;
dx2 = -(mdotc*cc + hc*A)/(rhoc*Vc*cc)*x(2) + hc*A/(rhoc*Vc*cc)*x(3)...
    + mdotc*cc/(rhoc*Vc*cc)*Tci*(1+wt);
dx3 = hh*A/(rhow*Vw*cw)*x(1) + hc*A/(rhow*Vw*cw)*x(2)...
    - (hh*A + hc*A)/(rhow*Vw*cw)*x(3);

xdot = [dx1;dx2;dx3];