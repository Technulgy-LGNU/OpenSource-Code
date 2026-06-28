void dribbler() {
 
  if(Motor_WertDe == true){
    Motor_WertD = Motor_WertD;
  }
  else{
    Motor_WertD = 2500;
  }
  if (m_state == true) {
    if (Motor_WertD < 0) {
      digitalWrite(D_FW, HIGH);
      digitalWrite(D_RV, LOW);
      analogWrite(D_PWM, abs(Motor_WertD));
    }
    if (Motor_WertD > 0) {
      digitalWrite(D_FW, LOW);
      digitalWrite(D_RV, HIGH);
      analogWrite(D_PWM, abs(Motor_WertD));
    }
    if (Motor_WertD == 0) {
      digitalWrite(D_FW, HIGH);
      digitalWrite(D_RV, HIGH);
      analogWrite(D_PWM, abs(Motor_WertD));
    }
  }
  else {
    analogWrite(D_PWM, 0);
  }
}

void schuss()
{
  constexpr int totzeit = 750;
  if (millis() > (totzeit + zeit_Schuss))
  {
    zeit_Schuss = millis();
  }
}

void schuss2()
{
  constexpr int totzeit2 = 950;
  if (millis() > (totzeit2 + zeit_Schuss2))
  {
    zeit_Schuss2 = millis();
  }
}
void SchussSetzen()
{
  if ((millis() >= zeit_Schuss ) && (millis() < (zeit_Schuss + 50)))
  {
    digitalWrite(Schuss_pin, HIGH);
  }
  else if ((millis() >= (zeit_Schuss + 50)) && (millis() <= (zeit_Schuss + 250))) {
    digitalWrite(Schuss_pin, HIGH);
  }
  else if ((millis() < zeit_Schuss) || (millis() > (zeit_Schuss + 250)))
  {
    digitalWrite(Schuss_pin, LOW);
  }
}

void SchussSetzen2()
{
  if ((millis() >= zeit_Schuss2 ) && (millis() < (zeit_Schuss2 + 50)))
  {
    digitalWrite(Schuss_pin, HIGH);
    Motor_WertD = 0;
  }
  else if ((millis() >= (zeit_Schuss2 + 50)) && (millis() <= (zeit_Schuss2 + 250))) {
    digitalWrite(Schuss_pin, HIGH);
    Motor_WertD = 0;
  }
  else if ((millis() < zeit_Schuss2) || (millis() > (zeit_Schuss2 + 250)))
  {
    digitalWrite(Schuss_pin, LOW);
    Motor_WertD = 2500;
  }
}
