void goalie() {
  //Angle-Calculation
  if ((defenseGoalch && msg.isGoalY) || (!defenseGoalch && bGd)) {
    int x_f = x_gg - 408;//Knöpfe in loop einkommentieren
    int y_f = y_gg - 308;
    x_f = -x_f;
    y_f = -y_f;
    //Serial.println(angle);
    winkelTorHinten = (atan2(y_f, x_f) * 180 / PI) + 90;
    if (winkelTorHinten > 180) {
      winkelTorHinten = winkelTorHinten - 360;
    }
    if (winkelTorHinten < -180) {
      winkelTorHinten = winkelTorHinten + 360;
    }
    absoluterWinkelHinten = winkelTorHinten - angle;
    if(absoluterWinkelHinten > 180){
      absoluterWinkelHinten -= 360;
    }
    if (absoluterWinkelHinten < -180){
      absoluterWinkelHinten += 360;
    }
    absoluterWinkelHinten = abs(absoluterWinkelHinten);
    Serial.println(absoluterWinkelHinten);
    Serial.println(msg.GoalYh);
    if (!defenseGoalch) {
      sizeG = msg.GoalBh * msg.GoalBw;
    }
    else {
      sizeG = msg.GoalYh * msg.GoalYw;
    }
    float p = 0.75;
    float d = 0.375;

    drehung = (winkelTorHinten * p) - (rotationSpeed * d);
  }
  else {
    compass();
  }
  int xKoordinaten = msg.Xx - (408 - 5);
  int yKoordinaten = msg.Yy - 308;
  yKoordinaten = -yKoordinaten;
  xKoordinaten = -xKoordinaten;


  //Limiting
  int limiter;
  if (absoluterWinkelHinten < -65 && richtung > 90 && richtung < 270) {
    limiter = true;
  }
  else if ((absoluterWinkelHinten > 65 && richtung <= 90 && richtung >= 0) || (absoluterWinkelHinten < -75 && richtung <= 360 && richtung >= 270)) {
    limiter = true;
  }
  else {
    limiter = false;
  }
  limiter = false;
  //Actual Goalie
  if (!limiter) {
    if (isB) {
      if (abs(xKoordinaten) <= 40) {
        geschwA = 0;
        richtungFcA = -1;
      }
      else if (xKoordinaten > 40 && xKoordinaten <= 130) {
        richtungFcA = 0;
        geschwA = 30;
      }
      else if (xKoordinaten < -40 && xKoordinaten >= -130) {
        richtungFcA = 180;
        geschwA = 30;
      }
      else if (xKoordinaten > 130) {
        richtungFcA = 0;
        geschwA = 80;
      }
      else if (xKoordinaten < -130) {
        richtungFcA = 180;
        geschwA = 80;
      }
      /*if (xKoordinaten > 55) {
        richtungFcA = 0;
        geschwA = xKoordinaten / 3;
        }
        else if (xKoordinaten < -55) {
        richtungFcA = 180;
        geschwA = (xKoordinaten / 3) * -1;
        }
        else if (xKoordinaten <= 55 && xKoordinaten >= -55) {
        geschwA = 0;
        richtungFcA = -1;
        }*/
    }
    else if (!isB && SBest != -1) {
      if (SBest >= 3 && SBest <= 5) {
        geschwA = 0;
        richtungFcA = -1;
      }
      else if ((SBest >= 13 && SBest <= 15) || (SBest < 3 && SBest >= 0)) {
        geschwA = 50;
        richtungFcA = 0;
      }
      else if (SBest <= 11 && SBest > 5 ) {
        geschwA = 50;
        richtungFcA = 180;
      }
    }
    else if (!isB && SBest == -1) {
     /* Serial.println("NOBIR");
      if (absoluterWinkelHinten > 15) {
        richtungFcA = 0;
        geschwA = 50;
      }
      else if (absoluterWinkelHinten < -15) {
        richtungFcA = 180;
        geschwA = 50;
      }
      else if (absoluterWinkelHinten <= 15 && absoluterWinkelHinten >= -15) {
        geschwA = 0;
        richtungFcA = -1;
      }*/
      geschwA = 0;
    }
  }
  else { 
    geschwA = 0;
  }

  //Holding Distance
  /*if ((absoluterWinkelHinten < 45 && sizeG > 13500) || (absoluterWinkelHinten >= 45 && absoluterWinkelHinten < 75 && sizeG > 4000) || (absoluterWinkelHinten >= 75 && sizeG > 400)) {
    geschwG = 0;
    richtungFcG = -1;
    }
    else {
    richtungFcG = 270;
    geschwG = 70;
    }*/
  if ((msg.GoalYh > 70 && absoluterWinkelHinten >= 60) || (msg.GoalYh > 56 && absoluterWinkelHinten < 60)) {
    geschwG = 0;
    richtungFcG = -1;
  }
  else {
    geschwG = 70;
    richtungFcG = 270;
    compass();
  }

  //richtung und geschwindigkeit berechnung
  if (richtungFcG == -1 && richtungFcA != -1) {
    richtung = richtungFcA;
  }
  else if (richtungFcG != -1 && richtungFcA == -1) {
    richtung = richtungFcG;
  }
  else {
    richtung = mittelwertWinkel(richtungFcG, richtungFcA);
  }
  if (geschwA == 0 && geschwG != 0) {
    geschw = geschwG;
  }
  else if (geschwA != 0 && geschwG == 0) {
    geschw = geschwA;
  }
  else {
    geschw = (geschwA + geschwG) / 2;
  }
}
