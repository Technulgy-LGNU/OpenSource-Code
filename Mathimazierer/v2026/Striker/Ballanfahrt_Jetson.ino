void cam_V2() {
  Punkt Zielpunkt;
  isB = getBallda(msg.isBall);
  if (isB) {
    int xKoordinaten = msg.Xx - 408;
    int yKoordinaten = msg.Yy - 308;
    richtung_b = (atan2(yKoordinaten, xKoordinaten) * 180 / PI) - 90;
    if (richtung_b > 180) {
      richtung_b = richtung_b - 360;
    }
    if (richtung_b < -180) {
      richtung_b = richtung_b + 360;
    }

  }
  //Serial.println(isB);
  //Einteilen der Zonen mithilfe der x-Koordinaten(muss noch am Roboter von uns ausgelesen werden)
  //Im folgenden Teil verwende ich Beispielwerte von Julius
  if ((isB && SBest == -1) || (isB && SBest != -1)) {
    //Serial.println("DA");
    int xKoordinaten = msg.Xx - 408;
    int yKoordinaten = (msg.Yy - 308) - 8;
    if (abs(xKoordinaten) < 32 &&  yKoordinaten > -30) {
      Zielpunkt = {0, 20};
    }
    else if (abs(xKoordinaten) >= 32 &&  yKoordinaten > -30) {
      Zielpunkt = {0, 190};
    }
    else if (xKoordinaten < 0 &&  yKoordinaten <= -30) {
      Zielpunkt = { -200, 0};
    }
    else if (xKoordinaten >= 0 &&  yKoordinaten <= -30) {
      Zielpunkt = {200, 0};
    }

    if (abs(xKoordinaten) < 85 && yKoordinaten > -20 && yKoordinaten <= 225) {
      geschw = 50;//50
      langsam = true;
    }
    else if (abs(xKoordinaten) < 85 && yKoordinaten > 225) {
      geschw = 80;//55
      langsam = false;
    }
    else {
      geschw = 90;//55
      langsam = false;
    }
    geschwX = (xKoordinaten - letzteX) / (millis() - letzteZeit_ball);
    geschwY = (yKoordinaten - letzteY) / (millis() - letzteZeit_ball);
    if (xKoordinaten == letzteX) {
      geschwX = 0;
    }
    if (yKoordinaten == letzteY) {
      geschwY = 0;
    }
    //Serial.println(yKoordinaten);
    double d = 0;
    double x_f = (xKoordinaten - Zielpunkt.x) + (d * geschwX);
    double y_f =  (yKoordinaten - Zielpunkt.y) + (d * geschwY);
    richtung = (atan2(y_f, x_f) * 180 / PI);
    if (richtung < 0) {
      richtung += 360;
    }
    Serial.println(richtung);
    //Serial.println(richtung);
    letzteZeit_ball = millis();
    letzteX = xKoordinaten;
    letzteY = yKoordinaten;
  }
  else if (SBest == -1 && isB == false) {
    geschw = 0;
  }
  else if (SBest != -1 && isB == false) {
    IrControl();
  }
}
