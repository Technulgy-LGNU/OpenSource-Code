clc; clear; close all;
% Parameter für das Meshgrid
[x_mesh, y_mesh] = meshgrid(-6:0.3:6, -6:0.3:6);
% Kreisparameter
x_c = 0; y_c = 0; r = 4;
arrow_length = 0.5; % Länge der Pfeile
% Erstelle den Plot
figure; hold on; axis equal;
thetaCircle = linspace(0, 2*pi, 100);
plot(x_c + r * cos(thetaCircle), y_c + r * sin(thetaCircle), 'b-', 'LineWidth', 2); % Kreis zeichnen
% Iteriere über das Meshgrid
for i = 1:numel(x_mesh)
x_p = x_mesh(i);
y_p = y_mesh(i);
d = hypot(x_p - x_c, y_p - y_c); % Abstand zum Kreismittelpunkt
if d > r
% Winkel der Tangenten
theta = atan2(y_p - y_c, x_p - x_c);
alpha = asin(r / d);
theta1 = pi + theta + alpha;
% Vektorpfeil in Tangentenrichtung
quiver(x_p, y_p, arrow_length * cos(theta1), arrow_length * sin(theta1), 'b', 'LineWidth', 1, 'MaxHeadSize', 0.5);
else
% Punkt innerhalb des Kreises → Spiegelung berechnen
theta = atan2(y_p - y_c, x_p - x_c);
i_c_t = [cos(theta) * d, sin(theta) * d]; % Punkt im Kreis
o_c_t = [cos(theta) * (2*r - d), sin(theta) * (2*r - d)]; % Spiegelpunkt
plot(i_c_t(1), i_c_t(2), '.g'); % Grüner Punkt (innen)
plot(o_c_t(1), o_c_t(2), '.r'); % Roter Punkt (außen)
% Berechnung der Spiegelung
theta3 = atan2(i_c_t(2) - y_c, i_c_t(1) - x_c);
S = [cos(2*theta3), sin(2*theta3); sin(2*theta3), -cos(2*theta3)];
% Gespiegelter Tangentenvektor
theta_sp = atan2(o_c_t(2) - y_c, o_c_t(1) - x_c);
alpha_sp = asin(r / hypot(o_c_t(1) - x_c, o_c_t(2) - y_c));
theta1_sp = pi + theta_sp + alpha_sp;
% Transformierter Vektor
pos_spiegel = -arrow_length * S * [cos(theta1_sp); sin(theta1_sp)];
quiver(x_p, y_p, pos_spiegel(1), pos_spiegel(2), 'b', 'LineWidth', 1, 'MaxHeadSize', 0.5);
end
end
hold off;
title('Vektorfeld der Winkel \theta zur x-Achse');
xlabel('x'); ylabel('y');