void neo(){
if (showLeds) {
    // --- BLINK-CODE ---
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; 
      ledStatus = !ledStatus; 

      if (ledStatus) {
        for(int i = 0; i < NUMPIXELS; i++) {
          strip.setPixelColor(i, strip.Color(64, 224, 208));
        }
      } else {
        for(int i = 0; i < NUMPIXELS; i++) {
          strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
      }
      strip.show(); 
    }
  } 
  else {
    // --- AUSSCHALT-CODE ---
    // Wenn showLeds auf "false" steht, wird der Blink-Code ignoriert,
    // der Streifen wird geleert und komplett abgeschaltet.
    strip.clear(); 
    strip.show();  
  }
}
