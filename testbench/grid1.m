% Loading the mesh
cd ../Debug
teste
cd ../testbench

% Electrical field is defined as:
% E = (50*cos(-8x) âx) + (40*sin(-8x) ây)
%
% u vector corresponds to âx
% v vector corresponds to ây  

% Initializing u and v
u = zeros(size(x));
v = zeros(size(y));

% Calculating the values
for i=1:(size(x)(1))
	for j=1:(size(x)(2))
		u(i,j) = 5*cos(-8*x(i,j));
		v(i,j) = 4*cos(-8*x(i,j));
	endfor
endfor

% Plotting
quiver(x,y,u,v)
