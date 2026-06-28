void Knob() {
  // Wenn der Knopf GEDRÜCKT ist (LOW)
  while (digitalRead(K1) == LOW) {
    read_sens();
    // --- ERSTER MOMENT DES DRÜCKENS ---
    if (!k1WarGedrueckt) {
      for (int i = 0; i < numSensors; i++) {
        bestVL[i] = 0;       // Höchstwert extrem niedrig starten
        worstVL[i] = 1023;   // Tiefstwert extrem hoch starten (für analogRead Maximum)
      }
      k1WarGedrueckt = true;
      Serial.println("Kalibrierung läuft... Bitte über Linie UND Boden ziehen!");
    }

    // --- WÄHREND DES GEDRÜCKTHALTENS ---
    for (int i = 0; i < numSensors; i++) {
      // 1. Höchstwert (Maximum) suchen
      if (BodenSens[i] > bestVL[i]) {
        bestVL[i] = BodenSens[i];
      }
      
      // 2. Tiefstwert (Minimum) suchen
      if (BodenSens[i] < worstVL[i]) {
        worstVL[i] = BodenSens[i];
      }
      
      // 3. Mittelwert live berechnen
      // (Maximum + Minimum) geteilt durch 2
      sw2[i] = (bestVL[i] + worstVL[i]) / 2;
    }
  } 
  // Wenn der Knopf LOSGELASSEN wird (HIGH)
  if (digitalRead(K1) == HIGH) {
    if (k1WarGedrueckt) {
      Serial.println("Kalibrierung beendet! Mittelwerte sind gespeichert.");
      k1WarGedrueckt = false;
    }
  }

  if(digitalRead(K3) == LOW){
    schuss();
  }
}
