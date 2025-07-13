bool readLS() {
  if (analogRead(Ls) > 2) {
    ik = false;
  }
  else if (analogRead(Ls) <= 2) {
    ik = true;
  }
  return ik;
}
void LS() {
  if (readLS() == true) {
    openmv_read();
    openmvattack();
  }

  else {
    compass();
    //bodenControl2();
    US();
    velo_math();
  }
}
