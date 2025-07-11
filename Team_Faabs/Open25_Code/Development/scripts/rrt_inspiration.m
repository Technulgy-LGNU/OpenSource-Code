clc; clear; close all;

% Belegungsraster erstellen (0 = frei, 1 = Hindernis)
map = binaryOccupancyMap(30, 30, 1);
setOccupancy(map, [7 7; 8 7; 6 8; 7 8; 8 8; 9 8], 1); % Hindernis setzen

% Zustandsraum für Dubins-Pfade (x, y, theta)
ss = stateSpaceDubins([0 30; 0 30; -pi pi]);
ss.MinTurningRadius = 1; % Krümmungsbegrenzung setzen

% Zustandsvalidierer für Kollisionsprüfung
sv = validatorOccupancyMap(ss);
sv.Map = map;
sv.ValidationDistance = 0.5; % Feinheit der Kollisionsprüfung

% RRT*-Planer mit Zustandsvalidierer
planner = plannerRRTStar(ss, sv);
planner.MaxIterations = 10000;
planner.GoalBias = 0.3; % Ziel-Bias für schnellere Konvergenz
possibleAngles = linspace(-pi, pi, 20); % 10 mögliche Startwinkel
bestPath = [];
shortestLength = Inf;
start = [10, 3, NaN]; % (x, y, Richtung)
goal  = [7, 6, pi/2]; % Endrichtung nach oben
for theta = possibleAngles
    tempStart = [start(1), start(2), theta];
    [pathObj, ~] = plan(planner, tempStart, goal);
    
    if ~isempty(pathObj.States)
        pathLength = sum(vecnorm(diff(pathObj.States(:,1:2)), 2, 2)); % Länge berechnen
        if pathLength < shortestLength
            shortestLength = pathLength;
            bestPath = pathObj;
        end
    end
end

% Start- und Zielpunkt mit Richtung


% Pfad berechnen
%rng(0); % Reproduzierbare Ergebnisse
%[pathObj, solnInfo] = plan(planner, start, goal);

% Ergebnisse visualisieren
figure; show(map); hold on;

plot(bestPath.States(:,1), bestPath.States(:,2), 'g-', 'LineWidth', 2);
plot(start(1), start(2), 'bo', 'MarkerSize', 10, 'MarkerFaceColor', 'b');
plot(goal(1), goal(2), 'ro', 'MarkerSize', 10, 'MarkerFaceColor', 'r');
title('RRT*-Pfad mit Krümmungsbegrenzung');
hold off;