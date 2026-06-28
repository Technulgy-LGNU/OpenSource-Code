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
  if (iD > 15) {
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
