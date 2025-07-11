#to be tested, because of chatgpt translation from matlab

import numpy as np
import matplotlib #as plt #(for ubuntu some python bug, thats why following lines are added)
matplotlib.use('gtk3agg') 
import matplotlib.pyplot as plt

# Parameter für das Meshgrid
x_mesh, y_mesh = np.meshgrid(np.arange(-6, 6.3, 1), np.arange(-6, 6.3, 1))

# Kreisparameter
x_c, y_c, r = 0, 0, 4
arrow_length = 1  # Länge der Pfeile

# Erstelle den Plot
fig, ax = plt.subplots()
ax.set_aspect('equal')

# Kreis zeichnen
theta_circle = np.linspace(0, 2 * np.pi, 100)
ax.plot(x_c + r * np.cos(theta_circle), y_c + r * np.sin(theta_circle), 'b-', linewidth=2)

# Iteriere über das Meshgrid
for i in range(x_mesh.shape[0]):
    for j in range(x_mesh.shape[1]):
        x_p = x_mesh[i, j]
        y_p = y_mesh[i, j]
        d = np.hypot(x_p - x_c, y_p - y_c)  # Abstand zum Kreismittelpunkt

        if d > r:
            # Winkel der Tangente
            theta = np.arctan2(y_p - y_c, x_p - x_c)
            alpha = np.arcsin(r / d)
            theta1 = np.pi + theta + alpha
            
            # Vektorpfeil in Tangentenrichtung
            ax.quiver(x_p, y_p, arrow_length * np.cos(theta1), arrow_length * np.sin(theta1),
                      color='b', angles='xy', scale_units='xy', scale=1, width=0.005)
        else:
            # Punkt innerhalb des Kreises → Spiegelung berechnen
            theta = np.arctan2(y_p - y_c, x_p - x_c)
            i_c_t = np.array([np.cos(theta) * d, np.sin(theta) * d])  # Punkt im Kreis
            o_c_t = np.array([np.cos(theta) * (2 * r - d), np.sin(theta) * (2 * r - d)])  # Spiegelpunkt

            ax.plot(i_c_t[0], i_c_t[1], '.g')  # Grüner Punkt (innen)
            ax.plot(o_c_t[0], o_c_t[1], '.r')  # Roter Punkt (außen)

            # Berechnung der Spiegelung
            theta3 = np.arctan2(i_c_t[1] - y_c, i_c_t[0] - x_c)
            S = np.array([[np.cos(2 * theta3), np.sin(2 * theta3)],
                          [np.sin(2 * theta3), -np.cos(2 * theta3)]])

            # Gespiegelter Tangentenvektor
            theta_sp = np.arctan2(o_c_t[1] - y_c, o_c_t[0] - x_c)
            alpha_sp = np.arcsin(r / np.hypot(o_c_t[0] - x_c, o_c_t[1] - y_c))
            theta1_sp = np.pi + theta_sp + alpha_sp

            # Transformierter Vektor
            pos_spiegel = -arrow_length * S @ np.array([np.cos(theta1_sp), np.sin(theta1_sp)])
            ax.quiver(x_p, y_p, pos_spiegel[0], pos_spiegel[1],
                      color='b', angles='xy', scale_units='xy', scale=1, width=0.005)

# Achsentitel
plt.title(r'Vektorfeld der Winkel $\theta$ zur x-Achse')
plt.xlabel('x')
plt.ylabel('y')
plt.grid()
plt.show()
