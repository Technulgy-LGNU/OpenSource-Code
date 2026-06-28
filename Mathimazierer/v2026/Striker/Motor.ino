void Motor() {
  if (digitalRead(K3) == LOW && Motor_an == false) {
    m_state = !m_state;
    zeitMotorKnopf = millis();
    Motor_an = true;
  }

  if ((millis() - zeitMotorKnopf) >= 350) {
    Motor_an = false;
  }
  else {
    Motor_an =  true;
  }
  
  double phi = (richtung / 180) * PI;
  //Motoren zurücktauschen
  Motor_Wert[mHl] = sin(phi - 5 * PI / 4) * geschw + drehung;//mHL
  Motor_Wert[mHr] = sin(phi - 7 * PI / 4) * geschw + drehung;//mHR
  Motor_Wert[mVr] = sin(phi - PI / 4) * geschw + drehung;//mVR
  Motor_Wert[mVl] = sin(phi - 3 * PI / 4) * geschw + drehung;//mVL

  if (m_state == true) {
    for (int i = 0; i < A_Motoren; i++) {
      if (Motor_Wert[i] > 255) {
        Motor_Wert[i] = 255;
      }
      else if (Motor_Wert[i] < -255) {
        Motor_Wert[i] = -255;
      }
      MWg[i] = map(abs(Motor_Wert[i]), 0, 255, 410, 3686);
      if (Motor_Wert[i] < 0) {
        digitalWrite(M_En, HIGH);
        digitalWrite(M_DIR[i], HIGH);
        analogWrite(M_PWM[i], MWg[i]);
      }
      if (Motor_Wert[i] > 0) {
        digitalWrite(M_En, HIGH);
        digitalWrite(M_DIR[i], LOW);
        analogWrite(M_PWM[i], MWg[i]);
      }
      if (Motor_Wert[i] == 0) {
        digitalWrite(M_En, LOW);
        digitalWrite(M_DIR[i], LOW);
        analogWrite(M_PWM[i], MWg [i]);
      }
    }
  }
  else {
    digitalWrite(M_En, LOW);
  }
  lastStateCom = digitalRead(41);
}
