import numpy as np
import matplotlib #as plt #(for ubuntu some python bug, thats why following lines are added)
matplotlib.use('gtk3agg') 
import matplotlib.pyplot as plt

# Initialisierung
num_steps = 50  # Anzahl der Zeitschritte
x_true = np.array([0, 0, 1, 0.5])  # Startzustand: Position (0,0), Geschwindigkeit (1, 0.5)
x_est = np.array([0, 0, 0, 0])  # Startschätzung: Position & Geschwindigkeit unbekannt
P = np.eye(4)  # Anfangs-Kovarianzmatrix (Unsicherheit)

# Messmatrix H (wir messen nur Position)
H = np.array([[1, 0, 0, 0], [0, 1, 0, 0]])

# Messrauschkovarianzmatrix R
sigma_x, sigma_y = 0.5, 0.5  # Messrauschen
R = np.array([[sigma_x ** 2, 0], [0, sigma_y ** 2]])

# Listen für Visualisierung
true_positions, measured_positions, estimated_positions = [], [], []
times = np.cumsum(np.random.uniform(0.5, 2.0, num_steps))  # Zufällige Zeitintervalle
prev_time = times[0]

for i in range(num_steps):
    dt = times[i] - prev_time  # Berechne Zeitschritt
    prev_time = times[i]

    # Dynamische Zustandsübergangsmatrix
    F = np.array([[1, 0, dt, 0],
                  [0, 1, 0, dt],
                  [0, 0, 1, 0],
                  [0, 0, 0, 1]])

    # Prozessrauschkovarianzmatrix Q
    sigma_w = 0.1
    Q = sigma_w ** 2 * np.array([[dt ** 4 / 4, 0, dt ** 3 / 2, 0],
                                 [0, dt ** 4 / 4, 0, dt ** 3 / 2],
                                 [dt ** 3 / 2, 0, dt ** 2, 0],
                                 [0, dt ** 3 / 2, 0, dt ** 2]])

    # Wahre Bewegung mit Prozessrauschen
    w = np.random.multivariate_normal([0, 0, 0, 0], Q)
    x_true = F @ x_true + w
    true_positions.append(x_true[:2])

    # Simulation einer verrauschten Messung
    v = np.random.multivariate_normal([0, 0], R)
    z = H @ x_true + v
    measured_positions.append(z)

    # **Kalman-Filter Vorhersage**
    x_pred = F @ x_est
    P_pred = F @ P @ F.T + Q

    # **Kalman-Filter Update**
    K = P_pred @ H.T @ np.linalg.inv(H @ P_pred @ H.T + R)
    x_est = x_pred + K @ (z - H @ x_pred)
    P = (np.eye(4) - K @ H) @ P_pred

    # Ergebnisse speichern
    estimated_positions.append(x_est[:2])

# Konvertiere Listen in Arrays für die Visualisierung
true_positions = np.array(true_positions)
measured_positions = np.array(measured_positions)
estimated_positions = np.array(estimated_positions)

# **Visualisierung**
plt.figure(figsize=(10, 6))
plt.plot(true_positions[:, 0], true_positions[:, 1], 'g-', label="Wahre Position")
plt.plot(measured_positions[:, 0], measured_positions[:, 1], 'rx', label="Messung (verrauscht)")
plt.plot(estimated_positions[:, 0], estimated_positions[:, 1], 'b-', label="Kalman-Schätzung")
plt.legend()
plt.xlabel("X-Position")
plt.ylabel("Y-Position")
plt.title("Kalman-Filter mit variabler Messrate")
plt.grid()
plt.show()
