int readMux1Boden(bool s1, bool s2, bool s3, bool s4) {
  digitalWrite(MuxSig0_B, s1);
  digitalWrite(MuxSig1_B, s2);
  digitalWrite(MuxSig2_B, s3);
  digitalWrite(MuxSig3_B, s4);
  return analogRead(SigMux0_B);
}

int readMux2Boden(bool s1, bool s2, bool s3, bool s4) {
  digitalWrite(MuxSig0_B, s1);
  digitalWrite(MuxSig1_B, s2);
  digitalWrite(MuxSig2_B, s3);
  digitalWrite(MuxSig3_B, s4);
  return analogRead(SigMux1_B);
}

int readMux3Boden(bool s1, bool s2, bool s3, bool s4) {
  digitalWrite(MuxSig0_B, s1);
  digitalWrite(MuxSig1_B, s2);
  digitalWrite(MuxSig2_B, s3);
  digitalWrite(MuxSig3_B, s4);
  return analogRead(SigMux2_B);
}

int readMux4Boden(bool s1, bool s2, bool s3, bool s4) {
  digitalWrite(MuxSig0_B, s1);
  digitalWrite(MuxSig1_B, s2);
  digitalWrite(MuxSig2_B, s3);
  digitalWrite(MuxSig3_B, s4);
  return analogRead(SigMux3_B);
}

void read_sens() {

  BodenSens[0] = readMux1Boden(0, 0, 0, 0);//3
  BodenSens[1] = readMux1Boden(1, 0, 0, 0);//4
  BodenSens[2] = readMux1Boden(0, 1, 0, 0);//5
  BodenSens[3] = readMux1Boden(1, 1, 0, 0);//6
  BodenSens[4] = readMux1Boden(0, 0, 1, 0);//7
  BodenSens[5] = readMux1Boden(1, 0, 1, 0);//8
  BodenSens[6] = readMux1Boden(0, 1, 1, 0);//14
  BodenSens[7] = readMux1Boden(1, 1, 1, 0);//2
  BodenSens[8] = readMux1Boden(0, 0, 0, 1);//16
  BodenSens[9] = readMux1Boden(1, 0, 0, 1);//15
  BodenSens[10] = readMux1Boden(0, 1, 0, 1);//1
  BodenSens[11] = readMux1Boden(1, 1, 0, 1);//13
  BodenSens[12] = readMux1Boden(0, 0, 1, 1);//12
  BodenSens[13] = readMux1Boden(1, 0, 1, 1);//11
  BodenSens[14] = readMux1Boden(0, 1, 1, 1);//10
  BodenSens[15] = readMux1Boden(1, 1, 1, 1);//9

  BodenSens[16] = readMux2Boden(0, 0, 0, 0);//27
  BodenSens[17] = readMux2Boden(1, 0, 0, 0);//28
  BodenSens[18] = readMux2Boden(0, 1, 0, 0);//29
  BodenSens[19] = readMux2Boden(1, 1, 0, 0);//30
  BodenSens[20] = readMux2Boden(0, 0, 1, 0);//31
  BodenSens[21] = readMux2Boden(1, 0, 1, 0);//32
  BodenSens[22] = readMux2Boden(0, 1, 1, 0);
  BodenSens[23] = readMux2Boden(1, 1, 1, 0);
  BodenSens[24] = readMux2Boden(0, 0, 0, 1);//26
  BodenSens[25] = readMux2Boden(1, 0, 0, 1);//25
  BodenSens[26] = readMux2Boden(0, 1, 0, 1);//24
  BodenSens[27] = readMux2Boden(1, 1, 0, 1);//23
  BodenSens[28] = readMux2Boden(0, 0, 1, 1);//22
  BodenSens[29] = readMux2Boden(1, 0, 1, 1);//21
  BodenSens[30] = readMux2Boden(0, 1, 1, 1);//20
  BodenSens[31] = readMux2Boden(1, 1, 1, 1);//19

  BodenSens[32] = readMux3Boden(0, 0, 0, 0);//41
  BodenSens[33] = readMux3Boden(1, 0, 0, 0);//42
  BodenSens[34] = readMux3Boden(0, 1, 0, 0);//43
  BodenSens[35] = readMux3Boden(1, 1, 0, 0);//44
  BodenSens[36] = readMux3Boden(0, 0, 1, 0);//45
  BodenSens[37] = readMux3Boden(1, 0, 1, 0);//46
  BodenSens[38] = readMux3Boden(0, 1, 1, 0);//47
  BodenSens[39] = readMux3Boden(1, 1, 1, 0);//48
  BodenSens[40] = readMux3Boden(0, 0, 0, 1);//40
  BodenSens[41] = readMux3Boden(1, 0, 0, 1);//39
  BodenSens[42] = readMux3Boden(0, 1, 0, 1);//38
  BodenSens[43] = readMux3Boden(1, 1, 0, 1);//37
  BodenSens[44] = readMux3Boden(0, 0, 1, 1);//36
  BodenSens[45] = readMux3Boden(1, 0, 1, 1);//35
  BodenSens[46] = readMux3Boden(0, 1, 1, 1);//34
  BodenSens[47] = readMux3Boden(1, 1, 1, 1);//33

  BodenSens[48] = readMux4Boden(0, 0, 0, 0);//17
  BodenSens[49] = readMux4Boden(1, 0, 0, 0);//18
  BodenSens[50] = readMux4Boden(0, 1, 0, 0);//56
  BodenSens[51] = readMux4Boden(1, 1, 0, 0);//55
  BodenSens[52] = readMux4Boden(0, 0, 1, 0);//54
  BodenSens[53] = readMux4Boden(1, 0, 1, 0);//53
  BodenSens[54] = readMux4Boden(0, 1, 1, 0);//52
  BodenSens[55] = readMux4Boden(1, 1, 1, 0);//51
  BodenSens[56] = readMux4Boden(0, 0, 0, 1);//50
  BodenSens[57] = readMux4Boden(1, 0, 0, 1);//58
  BodenSens[58] = readMux4Boden(0, 1, 0, 1);//59
  BodenSens[59] = readMux4Boden(1, 1, 0, 1);//60
  BodenSens[60] = readMux4Boden(0, 0, 1, 1);//49
  BodenSens[61] = readMux4Boden(1, 0, 1, 1);//57
  BodenSens[62] = readMux4Boden(0, 1, 1, 1);
  BodenSens[63] = readMux4Boden(1, 1, 1, 1);

}

bool MindestensEiner = false;

void SensorAuswerten() {
  MindestensEiner = false;
  for (int i = 0; i < numSensors; i++)
  {

    if (BodenSens[i] > sw2[i])
    {
      bSens[i] = true;
      MindestensEiner = true;
    } else {
      bSens[i] = false;
    }
  }
}

bool SBod[numSensors];
unsigned long ZeitpunktLinie;
int AnzahlGesehen = 0;

void bodenControl() {
  SensorAuswerten();
  if (MindestensEiner) {
    ZeitpunktLinie = millis();
    for (int i = 0; i < numSensors; i++) {
      if (bSens[i] && AnzahlGesehen < 40 && !SBod[i]) { //mit wie vielen Sensoren maximal dazugezählz werden müssen max 40
        SBod[i] = true;
        AnzahlGesehen++;
      }
    }
  } else {
    if ((millis() - ZeitpunktLinie) > 20 && AnzahlGesehen) { //Zeit anpassen, wie lang er zurückfahren soll
      AnzahlGesehen = 0;
      for (int i = 0; i < numSensors; i++) {
        SBod[i] = false;
      }
    }
  }
  double x_sumAktive = 0;
  double y_sumAktive = 0;
  dirAktive = 0;
  for (int i = 0; i < numSensors; i++) {
    if (bSens[i]) {
      x_sumAktive += KoordinatenSens[i][0];
      y_sumAktive += KoordinatenSens[i][1];
      dirAktive = atan2(-y_sumAktive, x_sumAktive) * 180 / PI + 180;
    }
  }
  if (AnzahlGesehen > 0) {
    if(!bV){
      drehung = lastDrehung;
    }
    compass();
    double x_Sum = 0;
    double y_Sum = 0;
    for (int i = 0; i < numSensors; i++) {
      if (SBod[i]) {
        x_Sum += KoordinatenSens[i][0];
        y_Sum += KoordinatenSens[i][1];
      }
    }
    //experimenteles feature: if(AnzahlGesehen>5{
    double dir1 = atan2(-y_Sum, x_Sum) * 180 / PI + 180;
    richtung = dir1;
    geschw = 95;  //anpassen//auskommentieren
    noB = false;
    //}
  }

  else if (AnzahlGesehen == 0)  {
    if (bV) {
      cam_V2();
      aG();
      IRControl();
    }
    else {
      goalie();
    }
    //IrControl();
    noB = true;
  }
}
