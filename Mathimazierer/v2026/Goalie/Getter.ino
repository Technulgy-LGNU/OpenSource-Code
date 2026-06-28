float mittelwertWinkel(float winkel1, float winkel2) {
  // Winkel im Bogenmaß (Rad) umrechnen
  float rad1 = winkel1 * DEG_TO_RAD;
  float rad2 = winkel2 * DEG_TO_RAD;
  
  // X- und Y-Komponenten der Vektoren addieren
  float x = cos(rad1) + cos(rad2);
  float y = sin(rad1) + sin(rad2);
  
  // Wenn beide Winkel exakt entgegengesetzt sind (z.B. 0° und 180°),
  // ist das Ergebnis mathematisch nicht definiert.
  if (x == 0 && y == 0) {
    return 0; // Standard-Rückgabewert für den Sonderfall
  }
  
  // Winkel aus den summierten Komponenten berechnen
  float mittelwertRad = atan2(y, x);
  
  // Zurück in Grad umrechnen
  float mittelwertGrad = mittelwertRad * RAD_TO_DEG;
  
  // Ergebnis auf den Bereich 0 bis 360 Grad normieren
  if (mittelwertGrad < 0) {
    mittelwertGrad += 360.0;
  }
  
  return mittelwertGrad;
}

double getDriveDir(double x) {
  double y;

  if (x < -10) {
    y = (-1.3368 * x) + 126.82;
  }
  else if (x >= -10 && x <= 10) {
    y = 90;
  }
  else if (x > 10 && x <= 40) {
    y = 0.045 * sq(x) - 3.45 * x + 76;
  }
  else if (x > 40) {
    y = -1.2538 * x + 404.55;
  }
  return y;
}

bool getBallda(bool Bd) {
  bool isballl;
  if (Bd == false) {
    unsigned long aktuelleZeit = millis();
    Dauer_nb = aktuelleZeit - letzteZeit;
    iD += Dauer_nb;
  }
  else {
    iD = 0;
  }
  if (iD > 7.5) {
    isballl = false;
  }
  else {
    isballl = true;
  }
  letzteZeit = millis();
  return isballl;
}

bool getIsYellowGda(bool Gd) {
  bool YGda;
  if (Gd == false) {
    unsigned long aktueZ = millis();
    Dauer = aktueZ - lastT;
    insD += Dauer;
  }
  else {
    insD = 0;
  }
  if (insD > 15) {
    YGda = false;
  }
  else {
    YGda = true;
  }
  lastT = millis();
  return YGda;

}
bool getIsBlueGda(bool Gd) {
  bool BGda;
  if (Gd == false) {
    unsigned long aktueZ = millis();
    Dauer_noB = aktueZ - lastT_B;
    insD_noB += Dauer;
  }
  else {
    insD_noB = 0;
  }
  if (insD > 15) {
    BGda = false;
  }
  else {
    BGda = true;
  }
  lastT_B = millis();
  return BGda;

}
