void rausdrehen() {
  sensors_event_t linearAccelData;
  gyro.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  double velocity = linearAccelData.acceleration.x;
  velo[A] = velocity;
  A++;
  if (A >= anzahlReadings) {
    double sum = 0;
    for (int i = 0; i < anzahlReadings; i++) {
      /*if(readings[i] > bestV){
        bestV = readings[i];
        }*/
      sum += velo[i];
    }
    avg = abs(sum / anzahlReadings);
    A = 0;
  }

  if (avg < 1) {
    if (!timerAktiv) {
      startZeitUnterSchwellwert = millis();
      timerAktiv = true;
    }


    if (millis() - startZeitUnterSchwellwert >= 500 && !amDrehen) {
      drehung = 150;
      turnOut = true;
      drehStartZeit = millis();
      amDrehen = true;
    }
  }
  else {
    timerAktiv = false;
  }

  if (amDrehen) {
    if (millis() - drehStartZeit >= 200) {
      drehung = 0;
      turnOut = false;
      amDrehen = false;
      timerAktiv = false;
    }
  }
  else if (!amDrehen && !timerAktiv) {
    turnOut = false;
  }
}
