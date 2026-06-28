/*void aG() {
  if(richtung > 0 && richtung < 180){
    speedD = 1175;
  }
  else if (avgLs >= 13){
    speedD = 1175;
  }
  else if (richtung <= 360 && richtung >= 180 && avgLs < 13){
    speedD = 1175;
  }
  int x_g;
  int y_g;
  //Serial.println(b_kuhle);
  int winkelG;
  if (b_kuhle) {
    geschw = 105;
    richtung = 90;

    //Serial.println("HAVEBALL");
    if ((attackGch == false && msg.isGoalY) || (attackGch == true && msg.isGoalB)) {
      ausrichten = true;
      int x_f = x_ga - 408;
      int y_f = y_ga - 308;
      x_f = -x_f;
      y_f = -y_f;
      winkelG = (atan2(y_f, x_f) * 180 / PI) - 90;
      if (attackGch == false) {
        sizeGa = msg.GoalYh * msg.GoalYw;
      }
      else {
        sizeGa = msg.GoalBh * msg.GoalBw;
      }
      if (winkelG > 180) {
        winkelG = winkelG - 360;
      }
      if (winkelG < -180) {
        winkelG = winkelG + 360;
      }
      float p = 1.2;//0.67
      float d = 0.75;//0.45
      drehung = (p * winkelG) - (d * rotationSpeed);
      if (abs(winkelG) <= 7.5 && sizeGa > 3200) {
        schuss();
      }
    }
    else {
      ausrichten = false;
      compass();
      digitalWrite(Schuss_pin, LOW);
    }
  }
  else {
    ausrichten = false;
    compass();
    digitalWrite(Schuss_pin, LOW);
  }
  }*/




void aG() {
  int winkelG;
  int x_g;
  int y_g;
  if (attackGch == false) {
    x_g = msg.GoalYx;
    y_g = msg.GoalYy;
  }
  else {
    x_g = msg.GoalBx;
    y_g = msg.GoalBy;
  }
  //Serial.println(b_kuhle);
  if (msg.isGoalB) {
    int x_f = x_g - 408;
    int y_f = y_g - 308;
    x_f = -x_f;
    y_f = -y_f;
    winkelG = (atan2(y_f, x_f) * 180 / PI) - 90;
    if (winkelG > 180) {
      winkelG = winkelG - 360;
    }
    if (winkelG < -180) {
      winkelG = winkelG + 360;
    }
    absoluterWinkel = abs(angle) + abs(winkelG);

  }
  if (noB) {
    if (b_kuhle == true) {
      geschw = 105;
      richtung = 90;
      /*if (LS_Wert >= 75 && LS_Wert <= 120) {
        compass();
        // Serial.println("NOBALL");
        }
        else {*/
      //Serial.println("HAVEBALL");
      if ((attackGch == false && yGd) || (attackGch == true && msg.isGoalB)) {
        float p = 0.95;//1
        float d = 0.55;//0.65
        drehung = (p * winkelG) - (d * rotationSpeed);
        if (abs(winkelG) <= 10 && (msg.GoalYw * msg.GoalYh) > 2500) {
          schuss();
        }
      }
      else {
        compass();
        //}
      }
    }
    else {
      compass();
    }
    /*else if (b_kuhle && absoluterWinkel > 55) {
      if ((attackGch == false && yGd) || (attackGch == true && bGd)) {
        geschw = 0;
          float p = 0.2;//0.67
          float d = 0.1;//0.45
          drehung = (p * winkelG) - (d * rotationSpeed);
          if (abs(winkelG) <= 7.5) {
          geschw = 20;
          richtung = 300;
          Motor_WertD = 0;
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
          speedD = 1200;
        }
        else if (vergangen >= 600 && abs(winkelG) > 10) {
          geschw = 0;
          speedD = 1450;
          float p = 0.25;//0.67
          float d = 0.125;//0.45
          drehung = (p * winkelG) - (d * rotationSpeed);
          vorwaerts = 0;
        }
        else if (vergangen >= 600 && abs(winkelG) <= 10) {
          if (vorwaerts == 0) {
            vorwaerts = millis();
          }
          geschw = 90;
          richtung = 90;
          speedD = 1200;
          if ((millis() - vorwaerts) >= 135) {
            speedD = 1000;
            schuss();
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
      }*/
  }
}
