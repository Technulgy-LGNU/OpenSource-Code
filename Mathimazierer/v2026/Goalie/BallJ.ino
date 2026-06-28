void cam_V2() {
  Punkt Zielpunkt;
  ballV = true;
  //Serial.println(isB);
  //Serial.println(isB);
  //Einteilen der Zonen mithilfe der x-Koordinaten(muss noch am Roboter von uns ausgelesen werden)
  //Im folgenden Teil verwende ich Beispielwerte von Julius
  if ((isB && SBest == -1) || (isB && SBest != -1)) {
    //Serial.println("DA");
    int xKoordinaten = msg.Xx - (408 - 5);
    int yKoordinaten = msg.Yy - 308;
    yKoordinaten = -yKoordinaten;
    xKoordinaten = -xKoordinaten;
    /*int absIRCam = abs(richtung_b - richtungIR);
      if (absIRCam > 180) {
      absIRCam = 360 - absIRCam;
      }
      if (absIRCam <= 75) {
      ballV = true;
      }
      else {
      ballV = false;
      }*/
    if (ballV) {
      //Serial.println(yKoordinaten);
      noV = false;
      if (abs(xKoordinaten) < 35 &&  yKoordinaten > -20) {
        Zielpunkt = {0, 35};
      }
      else if (abs(xKoordinaten) >= 35 &&  yKoordinaten > -20) {
        Zielpunkt = {0, 130};
      }
      else if (xKoordinaten < 0 &&  yKoordinaten <= -20) {
        Zielpunkt = { -200, 0};
      }
      else if (xKoordinaten >= 0 &&  yKoordinaten <= -20) {
        Zielpunkt = {200, 0};
      }

      if (abs(xKoordinaten) < 85 && yKoordinaten > -20 && yKoordinaten <= 225) {
        geschw = 50;
        speedD = 1000;
      }
      else if (abs(xKoordinaten) < 85 && yKoordinaten > 225) {
        geschw = 72.5;
        speedD = 1000;

      }
      else {
        geschw = 95;
        speedD = 1000;
      }

      //Serial.println(yKoordinaten);
      double d = 0;
      double x_f = (xKoordinaten - Zielpunkt.x);
      double y_f =  (yKoordinaten - Zielpunkt.y);
      richtung = (atan2(y_f, x_f) * 180 / PI);
      if (richtung < 0) {
        richtung += 360;
      }
    }
    else {
      noV = true;
    }
  }
  else if (SBest == -1 && isB == false) {
    geschw = 0;
    noV = false;
  }
  else if (SBest != -1 && isB == false) {
    noV = true;
  }
}
