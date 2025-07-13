void torwart() {
  driveback();
}
void driveback() {
  int Abs_h = US_V[2];
  richtung = 270;
  int max_velo = 100;
  int ap = 130;
  int ag = ap - Abs_h;
  geschw = max_velo - ag;
  int last_velo = geschw;
  if (geschw < -5) {
    geschw = abs(geschw);
    richtung = 90;
  }
  if (geschw > 3) {
    geschw = last_velo;
    richtung = 270;
  }
  if (geschw >= -5 && geschw <= 3) {
    ballausrichten();
    Serial.println("B");
  }
}
void ballausrichten() {
  if (dis >= 40) {
    if (h == true || vorne == true) {
      geschw = 0;
      Serial.println("S");
    }
    if (l == true) {
      geschw = 45;
      richtung = 180;
      Serial.println("L");
    }
    if (r == true) {
      geschw = 45;
      richtung = 0;
      Serial.println("R");
    }
  }
  if (US_V[3] < 40 && richtung == 0) {
    geschw = 0;
  }
  else if(US_V[3] < 40 && richtung != 0){
    geschw = geschw;
    richtung = richtung;
  }
    if (US_V[1] < 40 && richtung == 180) {
    geschw = 0;
  }
  else if(US_V[1] < 40 && richtung != 180){
    geschw = geschw;
    richtung = richtung;
  }
  
}
