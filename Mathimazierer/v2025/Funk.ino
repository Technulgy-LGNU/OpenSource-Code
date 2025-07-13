void Communication() {
  if (meinBoolWert != letzterBoolWert) {
    // Senden
    radio.stopListening();
    bool result = radio.write(&meinBoolWert, sizeof(meinBoolWert));
    radio.startListening();
    
    if (result) {
      Serial.print("Gesendet: ");
      Serial.println(meinBoolWert);
    } else {
      Serial.println("Senden fehlgeschlagen");
    }
    
    letzterBoolWert = meinBoolWert;
  }
  
  // Empfangen
  if (radio.available()) {
    bool empfangenerWert;
    radio.read(&empfangenerWert, sizeof(empfangenerWert));
    Serial.print("Empfangen: ");
    Serial.println(empfangenerWert);
  }
  
  // Test: Boolean alle 3 Sekunden ändern
  static unsigned long lastChange = 0;
  if (millis() - lastChange > 5000) {
    meinBoolWert = !meinBoolWert;
    lastChange = millis();
    Serial.print("Boolean geändert: ");
    Serial.println(meinBoolWert);
  }
}
