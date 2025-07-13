void Motor() {
  if (digitalRead(K1) == LOW) {
    m_state = !m_state;
    delay(350);
  }

  double phi = (richtung / 180) * PI;
  //Motoren zurücktauschen
  Motor_Wert[mHl] = sin(phi - 5 * PI / 4) * geschw + drehung;//mHL
  Motor_Wert[mVr] = sin(phi - 7 * PI / 4) * geschw + drehung;//mHR
  Motor_Wert[mHr] = sin(phi - PI / 4) * geschw + drehung;//mVR
  Motor_Wert[mVl] = sin(phi - 3 * PI / 4) * geschw + drehung;//mVL

  if (m_state == true) {
    for (int i = 0; i < AnzahlBLMotoren; i++) {
      if(Motor_Wert[i] > 255){
        Motor_Wert[i] = 255;
      }
      gerundet[i] = map(abs(Motor_Wert[i]), 0, 255, 500, 3680);

      if (Motor_Wert[i] < 0) {
        digitalWrite(M_En, HIGH);
        digitalWrite(M_DIR[i], HIGH);
        analogWrite(M_PWM[i], gerundet[i]);
      }
      if (Motor_Wert[i] > 0) {
        digitalWrite(M_En, HIGH);
        digitalWrite(M_DIR[i], LOW);
        analogWrite(M_PWM[i], gerundet[i]);
      }
      if (Motor_Wert[i] == 0) {
        digitalWrite(M_En, LOW);
        digitalWrite(M_DIR[i], LOW);
        analogWrite(M_PWM[i], gerundet[i]);
      }
    }
  }
  else {
    digitalWrite(M_En, LOW);
  }
}
