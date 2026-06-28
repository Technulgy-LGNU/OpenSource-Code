void Goalie() {//-220-230
  if (noB) {
    if (yGd) {//positiv links
      int x_f = msg.GoalYx - 408;
      int y_f = msg. GoalYy - 308;
      Serial.println(angle);
      int winkelTorHinten = (atan2(y_f, x_f) * 180 / PI) + 90;
      
      if (winkelTorHinten > 180) {
        winkelTorHinten = winkelTorHinten - 360;
      }
      if (winkelTorHinten < -180) {
        winkelTorHinten = winkelTorHinten + 360;
      }
      float p = 0.8;
      float d = 0.5;
      drehung = (winkelTorHinten * p) - (rotationSpeed * d);
      int sizeG = msg.GoalYh * msg.GoalYw;
      if (sizeG < 14500 && abs(angle) < 60) {
        richtung = 270;
        geschw = 50;
        Serial.println("Normal");
      }
      else if(sizeG < 8800 && abs(angle) >= 60){
        richtung = 270;
        geschw = 50;
        Serial.println("ECKE");
      }
      else if((sizeG > 8800 && abs(angle) >= 60) || (sizeG > 14500 && abs(angle) < 60)){
        Serial.println("NAH");
        if (SBest == 6) {
          geschw = 0;
          richtung = 0;
        }
        else if ((SBest < 6 &&  SBest >= 0) || (SBest >= 18 && SBest <= 23)) {
          geschw = 45;
          richtung = 180;
        }
        else if (SBest > 6 && SBest < 18) {
          geschw = 45;
          richtung = 0;
        }
      }//18-23 und 1 bis 5
        Serial.println(msg.GoalYh * msg.GoalYw);
    }
    else {
      richtung = 270;
      geschw = 40;
      compass();
    }
  }
}
