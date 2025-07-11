import numpy as np
import matplotlib #as plt #(for ubuntu some python bug, thats why following lines are added)
matplotlib.use('gtk3agg') 
import matplotlib.pyplot as plt

# Simulierte "wahre" Position
np.random.seed(42)
true_positions = np.linspace(0, 10, 50)  # Ein Objekt bewegt sich von 0 bis 10
measured_positions = true_positions + np.random.normal(0, 1, size=len(true_positions))  # Rauschen hinzufügen

# Kalman-Filter mit festem K
def simple_kalman_filter(measurements, K):
    x_filtered = [measurements[0]]  # Startwert mit erster Messung
    for i in range(1, len(measurements)):
        x_pred = x_filtered[-1]  # Einfache Vorhersage (Bewegung bleibt konstant)
        x_update = x_pred + K * (measurements[i] - x_pred)  # Kalman-Filter-Formel
        x_filtered.append(x_update)
    return x_filtered

# Verschiedene K-Werte testen
K_values = [0.1, 0.5, 0.9]
filtered_results = {K: simple_kalman_filter(measured_positions, K) for K in K_values}

# Plotten der Ergebnisse
plt.figure(figsize=(8, 6))
plt.plot(true_positions, label="Wahre Position", linestyle="dashed", color="black")
plt.scatter(range(len(measured_positions)), measured_positions, label="Messwerte (rauschig)", color="red", s=10)
for K, filtered in filtered_results.items():
    plt.plot(filtered, label=f"Kalman-Filter (K={K})")

plt.legend()
plt.xlabel("Zeitschritt")
plt.ylabel("Position")
plt.title("Einfluss des Kalman-Gains K auf die Filterung")
plt.show()
