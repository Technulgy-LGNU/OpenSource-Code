void Motor() {
  if (digitalRead(comModule) != lastCM && Motor_an == false) {
    m_state = !m_state;
    startKnopf = millis();
    Motor_an = true;
  }

  if((millis() - startKnopf) >= 350){
    Motor_an = false;
  }
  else{
    Motor_an =  true;
  }
  float drehFV;
  float drehFH;
  
    drehFV = 1;
    drehFH = 1;
 
  double phi = (richtung / 180) * PI;
  //Motoren zurücktauschen
  Motor_Wert[mHl] = sin(phi - 5 * PI / 4) * geschw + (drehung * drehFH);//mHL
  Motor_Wert[mHr] = sin(phi - 7 * PI / 4) * geschw + (drehung * drehFH);//mHR
  Motor_Wert[mVr] = sin(phi - PI / 4) * geschw + (drehung * drehFV);//mVR
  Motor_Wert[mVl] = sin(phi - 3 * PI / 4) * geschw + (drehung * drehFV);//mVL

  if (m_state == true) {
    for (int i = 0; i < A_Motoren; i++) {
      if (Motor_Wert[i] > 255) {
        Motor_Wert[i] = 255;
      }
      if (Motor_Wert[i] < -255) {
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
}
