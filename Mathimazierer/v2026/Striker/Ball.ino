int readMux1IR(bool s1, bool s2, bool s3, bool s4) {  //Verkürzung Auslesen
  digitalWrite(MuxSig0_IR, s1);
  digitalWrite(MuxSig1_IR, s2);
  digitalWrite(MuxSig2_IR, s3);
  digitalWrite(MuxSig3_IR, s4);
  return analogRead(SigMux1_IR);
}
int readMux2IR(bool s1, bool s2, bool s3, bool s4) {
  digitalWrite(MuxSig0_IR, s1);
  digitalWrite(MuxSig1_IR, s2);
  digitalWrite(MuxSig2_IR, s3);
  digitalWrite(MuxSig3_IR, s4);
  return analogRead(SigMux2_IR);
}

void IrRead() {
  IR_V[0] = readMux1IR(1, 0, 0, 0);
  IR_V[1] = readMux1IR(0, 1, 0, 0);
  IR_V[2] = readMux1IR(1, 1, 0, 0);
  IR_V[3] = readMux1IR(0, 0, 1, 0);
  IR_V[4] = readMux1IR(1, 0, 1, 0);
  IR_V[5] = readMux1IR(0, 1, 1, 0);
  IR_V[6] = readMux1IR(1, 1, 1, 0);
  IR_V[7] = readMux1IR(0, 1, 0, 1);
  IR_V[8] = readMux1IR(1, 1, 0, 1);
  IR_V[9] = readMux1IR(0, 0, 1, 1);
  IR_V[10] = readMux1IR(1, 0, 1, 1);
  IR_V[11] = readMux1IR(0, 1, 1, 1);
  IR_V[12] = readMux1IR(1, 1, 1, 1);

  IR_V[13] = readMux2IR(0, 1, 0, 0);
  IR_V[14] = readMux2IR(1, 1, 0, 0);
  IR_V[15] = readMux2IR(0, 0, 1, 0);
  IR_V[16] = readMux2IR(1, 0, 1, 0);
  IR_V[17] = readMux2IR(0, 1, 1, 0);
  IR_V[18] = readMux2IR(1, 1, 1, 0);
  IR_V[19] = readMux2IR(1, 1, 0, 1);
  IR_V[20] = readMux2IR(0, 0, 1, 1);
  IR_V[21] = readMux2IR(1, 0, 1, 1);
  IR_V[22] = readMux2IR(0, 1, 1, 1);
  IR_V[23] = readMux2IR(1, 1, 1, 1);

  SBest = -1;
  Vbest = 1001;

  for (int i = 0; i < Anzahl_IR; i++) {
    if (IR_V[i] < Vbest) {
      Vbest = IR_V[i];
      SBest = i;
    }
  }
  durchschnitte[0] = (IR_V[23] + IR_V[0] + IR_V[1]) / 3.0;
  int gruppenIndex = 1;
  for (int i = 2; i < 23; i += 3) {
    durchschnitte[gruppenIndex] = (IR_V[i] + IR_V[i + 1] + IR_V[i + 2]) / 3.0;
    gruppenIndex++;
  }
  int besteGruppeV = 1001;
  besteGruppe = -1;
  for (int i = 0; i < 8; i++) {
    if (durchschnitte[i] < besteGruppeV) {
      besteGruppeV = durchschnitte[i];
      besteGruppe = i;
    }
  }
  //Serial.println(besteGruppe);
}
void IrControl() {
  if (besteGruppe == 0) {
    richtung = 180;
    geschw = 105;//70
    langsam = false;
  }
  if (besteGruppe == 1) {
    richtung = 135;
    geschw = 105;
    langsam = false;
  }
  if (besteGruppe == 2) {
    richtung = 90;
    geschw = 105;
    langsam = false;
  }
  if (besteGruppe == 3) {
    richtung = 45;
    geschw = 105;
    langsam = false;
  }
  if (besteGruppe == 4) {
    richtung = 0;
    geschw = 105;
    langsam = false;
  }
  if (besteGruppe == 5) {
    richtung = 315;
    geschw = 105;
    langsam = false;
  }
  if (besteGruppe == 6) {
    richtung = 270;
    geschw = 105;
    langsam = false;
  }
  if (besteGruppe == 7) {
    richtung = 225;
    geschw = 105;
    langsam = false;
  }
  /*if (SBest == 0) {
    geschw = 100;
    richtung = 180;
    }
    if (SBest == 1) {
    geschw = 100;
    richtung = 165;
    }
    if (SBest == 2) {
    geschw = 100;
    richtung = 150;
    }
    if (SBest == 3) {
    geschw = 100;
    richtung = 135;
    }
    if (SBest == 4) {
    geschw = 100;
    richtung = 120;
    }
    if (SBest == 5) {
    geschw = 60;
    richtung = 105;
    }
    if (SBest == 6) {
    geschw = 60;
    richtung = 90;
    }
    if (SBest == 7) {
    geschw = 60;
    richtung = 75;
    }
    if (SBest == 8) {
    geschw = 100;
    richtung = 60;
    }
    if (SBest == 9) {
    geschw = 100;
    richtung = 45;
    }
    if (SBest == 10) {
    geschw = 100;
    richtung = 30;
    }
    if (SBest == 11) {
    geschw = 100;
    richtung = 15;
    }
    if (SBest == 12) {
    geschw = 100;
    richtung = 0;
    }
    if (SBest == 13) {
    geschw = 100;
    richtung = 345;
    }
    if (SBest == 14) {
    geschw = 100;
    richtung = 330;
    }
    if (SBest == 15) {
    geschw = 100;
    richtung = 315;
    }
    if (SBest == 16) {
    geschw = 100;
    richtung = 300;
    }
    if (SBest == 17) {
    geschw = 100;
    richtung = 285;
    }
    if (SBest == 18) {
    geschw = 100;
    richtung = 270;
    }
    if (SBest == 19) {
    geschw = 100;
    richtung = 255;
    }
    if (SBest == 20) {
    geschw = 100;
    richtung = 240;
    }
    if (SBest == 21) {
    geschw = 100;
    richtung = 225;
    }
    if (SBest == 22) {
    geschw = 100;
    richtung = 210;
    }
    if (SBest == 23) {
    geschw = 100;
    richtung = 195;
    }*/
}
