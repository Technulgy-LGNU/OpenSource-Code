void wechsel() {
  isB = getBallda(msg.isBall);
  int x_Bewe = abs(msg.Xx - lastX);
  int y_Bewe = abs(msg.Yy - lastY);
  if (!isB) {
    x_Bewe = 20;
    y_Bewe = 20;
  }
  if (besteGruppe != -1 || isB || b_kuhle) {
    unsigned long aktuelleZeit = millis();
    /*for (int i = 0; i < A_Motoren; i++) {
      if (abs(Motor_Wert[i]) <= 10) {
        Mot_Stop[i] = true;
      }
      else {
        Mot_Stop[i] = false;
      }
      }*/
    /*if (Mot_Stop[0] && Mot_Stop[1] && Mot_Stop[2] && Mot_Stop[3]) {
      if (stillstandStartZeit == 0) {
        stillstandStartZeit = aktuelleZeit;
      }
      }*/
    if (!bV) {
      //Serial.println(aktuelleZeit - angriffStartZeit);
      if (x_Bewe <= 6 && y_Bewe <= 4) {
        if (stillstandStartZeit == 0) {
          stillstandStartZeit = aktuelleZeit;
        }
      }
      else {
        stillstandStartZeit = 0;
      }
      if ((stillstandStartZeit > 0 && (aktuelleZeit - stillstandStartZeit) >= 1500 && !isImAngriff) || (stillstandStartZeit > 0 && (aktuelleZeit - stillstandStartZeit) > 500 && !isImAngriff && msg.Yy > 150 && msg.Yy > 300)) {
        bV = true;
        angriffStartZeit = aktuelleZeit;
        isImAngriff = true;
        stillstandStartZeit = 0;
      }
    }

    if (isImAngriff && (aktuelleZeit - angriffStartZeit) >= 6000) {
      bV = false;
      isImAngriff = false;
    }
    //Serial.println(bV);
  }
  else {
    speedD = 1000;
    bV = false;
    isImAngriff = false;
    stillstandStartZeit = 0;
  }
  lastX = msg.Xx;
  lastY = msg.Yy;
}
