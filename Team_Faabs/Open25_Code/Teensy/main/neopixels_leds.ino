namespace Neo {
  const int PIN = 39;
  const int COUNT = 5;
  
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(COUNT, PIN, NEO_GRB + NEO_KHZ800);
  
  // Define the color variables (not constants since they're initialized at runtime)
  uint32_t nwhite, nblue, nyellow, npurple, ngreen;
  
  // Remove enum definition from here - it's already in main.ino
  
  Mode mode = IDLE;
  unsigned long lastUpdate = 0, startTime = 0, duration = 0;
  uint32_t color = 0;
  int pulseDir = 1, pulseBright = 0;
  
  void setup() {
    pixels.begin();
    pixels.clear();
    pixels.show();
    
    // Initialize colors after pixels.begin()
    nwhite = pixels.Color(255, 255, 255);
    nblue = pixels.Color(0, 0, 255);
    nyellow = pixels.Color(255, 255, 0);
    npurple = pixels.Color(255, 0, 255);
    ngreen = pixels.Color(0, 255, 0);
  }
  
  void update() {
    unsigned long now = millis();
    
    if (mode != IDLE && now - startTime >= duration) {
      mode = IDLE;
      pixels.clear();
      pixels.show();
      return;
    }
    
    if (now - lastUpdate < 50) return;
    lastUpdate = now;
    
    switch (mode) {
      case IDLE:
        // Do nothing for idle mode
        break;
        
      case FLASH:
        if ((now - startTime) % 200 < 100) {
          pixels.fill(color);
        } else {
          pixels.clear();
        }
        pixels.show();
        break;
        
      case PULSE:
        pulseBright += pulseDir * 8;
        if (pulseBright >= 255) { pulseBright = 255; pulseDir = -1; }
        else if (pulseBright <= 0) { pulseBright = 0; pulseDir = 1; }
        
        uint8_t r = ((color >> 16) & 0xFF) * pulseBright / 255;
        uint8_t g = ((color >> 8) & 0xFF) * pulseBright / 255;
        uint8_t b = (color & 0xFF) * pulseBright / 255;
        
        pixels.fill(pixels.Color(r, g, b));
        pixels.show();
        break;
    }
  }
  
  // Remove default parameters from function definitions
  void flash(uint32_t c, unsigned long d) {
    mode = FLASH; color = c; startTime = millis(); duration = d;
  }
  
  void pulse(uint32_t c, unsigned long d) {
    mode = PULSE; color = c; startTime = millis(); duration = d;
    pulseBright = 0; pulseDir = 1;
  }
  
  void off() {
    mode = IDLE;
    pixels.clear();
    pixels.show();
  }
}
/*
  void setup() {
  Neopixels_setup();
  pinMode(btnKompass, INPUT_PULLUP);
  }


  void loop() {
  // Call this in your main loop - it's non-blocking
  updateNeoPixels();
  if (digitalRead(btnKompass) == 0) {
    flash(YELLOW);
  }
  }*/
