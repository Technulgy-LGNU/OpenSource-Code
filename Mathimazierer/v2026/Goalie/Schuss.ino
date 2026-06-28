void schuss()
{
  constexpr int totzeit = 750;
  if (millis() > (totzeit + zeit_Schuss))
  {
    zeit_Schuss = millis();
  }
}


void SchussSetzen()
{
  if ((millis() >= zeit_Schuss ) && (millis() < (zeit_Schuss + 50)))
  {
    speedD = 1000;
    digitalWrite(Schuss_pin, HIGH);
    showLeds = true;
  }
  else if ((millis() >= (zeit_Schuss + 50)) && (millis() <= (zeit_Schuss + 250))) {
    speedD = 1000;
    digitalWrite(Schuss_pin, HIGH);
    showLeds = true;
  }
  else if ((millis() < zeit_Schuss) || (millis() > (zeit_Schuss + 250)))
  {
    digitalWrite(Schuss_pin, LOW);
    showLeds = false;
  }
}
void dribbler() {

  if (m_state) {
    // Wenn er laufen soll, senden wir NUR, wenn er vorher aus war
    // ODER wenn sich die Geschwindigkeit geändert hat
    if (!last_state || speedD != last_speed) {
      myESC.speed(speedD);
      last_state = true;
      last_speed = speedD; // Neue Geschwindigkeit merken
    }
  }
  else {
    // Wenn er stoppen soll, senden wir den Stopp-Befehl NUR,
    // wenn er im vorherigen Durchlauf noch lief
    if (last_state) {
      myESC.speed(1000);
      last_state = false;
    }
  }
}
