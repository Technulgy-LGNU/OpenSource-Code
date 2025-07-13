void US() {
  US_V[0] = mySonar1.distanceContinuous();
  US_V[1] = mySonar2.distanceContinuous();
  US_V[2] = mySonar3.distanceContinuous();
  US_V[3] = mySonar4.distanceContinuous();

  /*for (int i = 0; i < AnzahlUS; i++) {
    if (US_V[i] > 100) {
      US_V[i] = 100;
    }
    else if (US_V[i] <= 100) {
      US_V[i] = US_V[i];
    }
  }*/

  if ((US_V[0] > 50) && (US_V[2] > 55)) {
    simpel = false;
    if (US_V[1] < US_V[3]) {
      dis = US_V[1];
    }
    else if (US_V[1] > US_V[3]) {
      dis = US_V[3];
    }
  }
  else if (US_V[2] <= 55 || US_V[0] <= 50) {
    simpel = true;
    //Serial.println("L");
  }
}
/*sumX = US_V[1] + US_V[3];
  sumY = US_V[0] + US_V[2];

  if((sumX < BreiteFeld + 15) && (sumX > BreiteFeld - 15)){
  sumx = true;
  }
  else{
  sumx = false;
  }
  if(sumx == false){
  XCord = lastX;
  }
  else if (sumx == true){
  uptadeX();
  }
  Serial.println(velo_control(richtung));
  }

  void uptadeX(){
  XCord = (US_V[1] - US_V[3]) / 2;
  lastX = XCord;
  }

  double velo_control(double inputdir) {

  constexpr int r_max = 50; //cm as max radius
  constexpr int f_rg = 1;
  constexpr int f_ges = 1.25;

  int xv_l = -XCord;
  int yv_l = -YCord;

  double xv_r = cos(inputdir / 180 * PI) * r_max * f_rg;
  double yv_r = sin(inputdir / 180 * PI) * r_max * f_rg;

  double xv_v = xv_r + xv_l;
  double yv_v = yv_r + yv_l;

  double maxVelo = 10 + sqrt(xv_v * xv_v + yv_v * yv_v) * f_ges;
  if (sqrt(xv_l * xv_l + yv_l * yv_l) > r_max + 12) maxVelo = 10 + sqrt(xv_v * xv_v + yv_v * yv_v) * f_ges / 3;

  return maxVelo;*/
void velo_math() {
  if (IR_an == true) {
    if (SEbest != -1) {
      if (simpel == false) {
        int ap = 86;
        int maxG = 110;
        int ag = ap - dis;
        geschw = maxG - ag;
      }
      else {
        geschw = 50;
      }
    }
    else {
      geschw = 0;
    }
  }
  else {
    geschw = geschw;
    richtung = richtung;
  }
}
