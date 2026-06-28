void nd(){
   if (noB) {
    if (b_kuhle && absoluterWinkel <= 40) {
      Motor_WertD = 0;
      geschw = 105;
      richtung = 90;
      /*if (LS_Wert >= 75 && LS_Wert <= 120) {
        compass();
        // Serial.println("NOBALL");
        }
        else {*/
      //Serial.println("HAVEBALL");
      if ((attackGch == false && msg.isGoalY) || (attackGch == true && msg.isGoalB)) {
        float p = 1.2;//1
        float d = 0.75;//0.65
        //drehung = (p * winkelG) - (d * rotationSpeed);
        /*if (abs(winkelG) <= 5 && sizeGa > 1250) {
          schuss2();
        }*/
      }
      else {
        Motor_WertD = 0;
        compass();
        //}
      }
    }
    else if (absoluterWinkel <= 40 && !b_kuhle) {
      compass();
      Motor_WertD = 0;
    }
    else if (absoluterWinkel >= 40 && absoluterWinkel < 67) {
      geschw = 65;
      Motor_WertD = 0;
      if ((attackGch == false && msg.isGoalY) || (attackGch == true && msg.isGoalB)) {
        float p = 0.7;//1
        float d = 0.35;//0.65
        //drehung = (p * winkelG) - (d * rotationSpeed);
        //if (abs(winkelG) <= 5 && b_kuhle) {
          //schuss2();
       //1 }
        /*geschw = 0;
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
              schuss2();
              schussWartet = false;
            }
          }*/
      }
      else {
        compass();
        schussWartet = false;
      }
    }
    else if (absoluterWinkel >= 67) {
      if (!b_kuhle) {
        if ((attackGch == false && msg.isGoalY && isB) || (attackGch == true && msg.isGoalB && isB)) {
          float p = 0.4;
          float d = 0.2;
          drehung = (richtung_b * p) - (rotationSpeed * d);
          richtung = 90;
          geschw = 20;
          Motor_WertD = 3600;
        }
        else {
          compass();
          Motor_WertD = 0;
        }
      }
      else {
        geschw = 0;
        Motor_WertD = 3600;
        if ((attackGch == false && msg.isGoalY && isB) || (attackGch == true && msg.isGoalB && isB)) {
          float p = 0.2;
          float d = 0.1;
         /* drehung = (winkelG * p) - (rotationSpeed * d);
          if (abs(winkelG) <= 3) {
            schuss2();
          }*/
        }
        else{
          compass();
          Motor_WertD = 0;
        }
      }
    }
  }
}
