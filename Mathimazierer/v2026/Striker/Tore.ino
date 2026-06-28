void aG() {
  int winkelG;
  int x_g;
  int y_g;
  int sizeGa;
  if (digitalRead(K2) == LOW) {
    attackGch = !attackGch;
    delay(350);
  }
  if (attackGch == false) {
    x_g = msg.GoalYx;
    y_g = msg.GoalYy;
  }
  else {
    x_g = msg.GoalBx;
    y_g = msg.GoalBy;
  }
  if (!attackGch) {
    sizeGa = msg.GoalYh * msg.GoalYw;
  }
  else {
    sizeGa = msg.GoalBh * msg.GoalBw;
  }
  //Serial.println(msg.GoalYw * msg.GoalYh);
  //Serial.println(b_kuhle);
  if (yGd) {
    int x_f = x_g - 408;
    int y_f = y_g - 308;
    int x_gf;
    winkelG = (atan2(y_f, x_f) * 180 / PI) - 90;
    if (winkelG > 180) {
      winkelG = winkelG - 360;
    }
    if (winkelG < -180) {
      winkelG = winkelG + 360;
    }
    absoluterWinkel = abs(angle) + abs(winkelG);
    if (absoluterWinkel >= 50 && richtung < 165 && richtung > 15) {
      Motor_WertD = 2500;
      geschw = 30;
      }
      else {
      Motor_WertD = 0;
      }
  }
 if (noB) {
    if (b_kuhle && absoluterWinkel <= 55) {
      geschw = 105;
      richtung = 90;
      /*if (LS_Wert >= 75 && LS_Wert <= 120) {
        compass();
        // Serial.println("NOBALL");
        }
        else {*/
      //Serial.println("HAVEBALL");
      if ((attackGch == false && yGd) || (attackGch == true && bGd)) {
        float p = 1.2;//0.67
        float d = 0.75;//0.45
        drehung = (p * winkelG) - (d * rotationSpeed);
        if (abs(winkelG) <= 7.5 && (msg.GoalYw * msg.GoalYh) > 1250) {
          schuss2();
        }
      }
      else {
        compass();
        //}
      }
    }
    else if (b_kuhle && absoluterWinkel > 55) {
      if ((attackGch == false && yGd) || (attackGch == true && bGd)) {
        /*geschw = 0;
          float p = 0.2;//0.67
          float d = 0.1;//0.45
          drehung = (p * winkelG) - (d * rotationSpeed);
          if (abs(winkelG) <= 7.5) {
          geschw = 20;
          richtung = 300;
          Motor_WertD = 0;*/
        if (!schussWartet) {
          schussZeitpunkt = millis();
          schussWartet = true;
          vorwaerts = 0;
        }
        vergangen = millis() - schussZeitpunkt;
        if (vergangen < 600) {
          geschw = 20;
          richtung = 270;
          compass();
          Motor_WertD = 2500;
        }
        else if (vergangen >= 600 && abs(winkelG) > 10) {
          geschw = 0;
          Motor_WertD = 3600;
          float p = 0.25;//0.67
          float d = 0.125;//0.45
          drehung = (p * winkelG) - (d * rotationSpeed);
          vorwaerts = 0;
        }
        else if (vergangen >= 600 && abs(winkelG) <= 10) {
          if (vorwaerts == 0) {
            vorwaerts = millis();
          }
          Motor_WertD = 0;
          if ((millis() - vorwaerts) >= 135) {
            Motor_WertD = 0;
            geschw = 20;
            richtung = 90;
            schuss2();
            schussWartet = false;
          }
        }
      }
      else {
        compass();
        schussWartet = false;
      }

    }
    else if (b_kuhle == false) {
      compass();
      schussWartet = false;
    }
  }
 
}
