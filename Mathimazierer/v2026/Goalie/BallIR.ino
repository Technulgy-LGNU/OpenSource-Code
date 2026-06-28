int readMux1IR_V(bool s1, bool s2, bool s3, bool s4) {  //Verkürzung Auslesen
  digitalWrite(MuxSig0_IR, s1);
  digitalWrite(MuxSig1_IR, s2);
  digitalWrite(MuxSig2_IR, s3);
  digitalWrite(MuxSig3_IR, s4);
  return analogRead(SigMux_IR);
}

void IRRead() {
  IR_V[15] = readMux1IR_V(0, 0, 0, 0);//3
  IR_V[14] = readMux1IR_V(1, 0, 0, 0);//4
  IR_V[13] = readMux1IR_V(0, 1, 0, 0);//5
  IR_V[12] = readMux1IR_V(1, 1, 0, 0);//6
  IR_V[11] = readMux1IR_V(0, 0, 1, 0);//7
  //IR_V[10] = readMux1IR_V(1, 0, 1, 0);//8
  IR_V[10] = 1023;
  //IR_V[9] = readMux1IR_V(0, 1, 1, 0);//14
  IR_V[9] = 1023;
  IR_V[8] = readMux1IR_V(1, 1, 1, 0);//2
  IR_V[7] = readMux1IR_V(0, 0, 0, 1);//16
  IR_V[6] = readMux1IR_V(1, 0, 0, 1);//15
  IR_V[5] = readMux1IR_V(0, 1, 0, 1);//11
  IR_V[4] = readMux1IR_V(1, 1, 0, 1);//13
  //IR_V[4] = 1023;
  IR_V[3] = readMux1IR_V(0, 0, 1, 1);//12
  //IR_V[3] = 1023;
  IR_V[2] = readMux1IR_V(1, 0, 1, 1);//11
  //IR_V[2] = 1023;
  IR_V[1] = readMux1IR_V(0, 1, 1, 1);//10
  //IR_V[1] = 1023;
  IR_V[0] = readMux1IR_V(1, 1, 1, 1);//9
  //IR_V[0] = 1023;
  SBest = -1;
  Vbest = 980;
  for (int i = 0; i < Anzahl_IR; i++) {
    if (IR_V[i] < Vbest) {
      Vbest = IR_V[i];
      SBest = i;
    }
    /*Serial.print(i);
    Serial.print(": ");
    Serial.println(IR_V[i]);*/
  }
  /*Serial.print("IR: ");
    Serial.println(SBest);
    Serial.println(Vbest);*/
}
void IRControl() {
  /* if (besteGruppe == 0) {
     richtungIR = 180;
    }
    if (besteGruppe == 1) {
     richtungIR = 135;
    }
    if (besteGruppe == 2) {
     richtungIR = 90;
    }
    if (besteGruppe == 3) {
     richtungIR = 45;
    }
    if (besteGruppe == 4) {
     richtungIR = 0;
    }
    if (besteGruppe == 5) {
     richtungIR = 315;
    }
    if (besteGruppe == 6) {
     richtungIR = 270;
    }
    if (besteGruppe == 7) {
     richtungIR = 225;
    }*/
  /*if (SBest == 0) {
    richtungIR_V = 180;
    }
    if (SBest == 1) {
    richtungIR_V = 165;
    }
    if (SBest == 2) {
    richtungIR_V = 150;
    }
    if (SBest == 3) {

    richtungIR_V = 135;
    }
    if (SBest == 4) {

    richtungIR_V = 120;
    }
    if (SBest == 5) {
    richtungIR_V = 105;
    }
    if (SBest == 6) {

    richtungIR_V = 90;
    }
    if (SBest == 7) {

    richtungIR_V = 75;
    }
    if (SBest == 8) {

    richtungIR_V = 60;
    }
    if (SBest == 9) {

    richtungIR_V = 45;
    }
    if (SBest == 10) {

    richtungIR_V = 30;
    }
    if (SBest == 11) {

    richtungIR_V = 15;
    }
    if (SBest == 12) {

    richtungIR_V = 0;
    }
    if (SBest == 13) {

    richtungIR_V = 345;
    }
    if (SBest == 14) {

    richtungIR_V = 330;
    }
    if (SBest == 15) {

    richtungIR_V = 315;
    }
    if (SBest == 16) {

    richtungIR_V = 300;
    }
    if (SBest == 17) {

    richtungIR_V = 285;
    }
    if (SBest == 18) {

    richtungIR_V = 270;
    }
    if (SBest == 19) {

    richtungIR_V = 255;
    }
    if (SBest == 20) {

    richtungIR_V = 240;
    }
    if (SBest == 21) {

    richtungIR_V = 225;
    }
    if (SBest == 22) {

    richtungIR_V = 210;
    }
    if (SBest == 23) {

    richtungIR_V = 195;
    }*/
  if (noV) {
    if (SBest >= 3 && SBest <= 5) {
      richtung = 90;
      geschw = 65;
      speedD = 1100;
    }
    else {
      richtung = SBest * 22.5;
      geschw = 100;
      speedD = 1000;
    }
  }
}
