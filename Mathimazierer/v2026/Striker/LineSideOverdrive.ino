void LSD() {
  int x_g;
  int y_g;
  int winkelG;
  if (attackGch == false) {
    x_g = msg.GoalYx;
    y_g = msg.GoalYy;
  }
  else {
    x_g = msg.GoalBx;
    y_g = msg.GoalBy;
  }
  int x_f = x_g - 408;
  int y_f = y_g - 308;
  winkelG = (atan2(y_f, x_f) * 180 / PI) - 90;
  Serial.println(winkelG);
  if (langsam || (b_kuhle && abs(winkelG) > 20)) {
    specialReadSens();
  }
  else {
    read_sens();
  }

}

bool istSensorRechts(int id) {
  // Hier alle Sensor-IDs eintragen, die sich auf der LINKEN Seite befinden
  if ((id >= 26 && id <= 31) || (id >= 50 && id <= 59)) {
    return true;
  }
  return false;
}

bool istSensorLinks(int id) {
  // Hier alle Sensor-IDs eintragen, die sich auf der RECHTEN Seite befinden
  if ((id >= 34 && id <= 42) || (id >= 10 && id <= 15)) {
    return true;
  }
  return false;
}

void specialReadSens() {
  Serial.print("PENIS:");
  Serial.println(BodenSens[45]);

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


  int x_g;
  int y_g;
  int winkelG;
  if (attackGch == false) {
    x_g = msg.GoalYx;
    y_g = msg.GoalYy;
  }
  else {
    x_g = msg.GoalBx;
    y_g = msg.GoalBy;
  }
  int x_f = x_g - 408;
  int y_f = y_g - 308;
  winkelG = (atan2(y_f, x_f) * 180 / PI) - 90;

  for (int i = 0; i < numSensors; i++) {
    double x_koordinate = KoordinatenSens[i][0];
    if (winkelG < 0) {
      // Roboter ist RECHTS vom Tor -> Alle LINKEN Sensoren ignorieren (X < 0)
      if (x_koordinate < 0) {
        BodenSens[i] = 0;
      }
      else {
        KoordinatenSens[i][0] = -abs(KoordinatenSens[i][0]);
      }
    }
    else {
      // Roboter ist LINKS vom Tor -> Alle RECHTEN Sensoren ignorieren (X > 0)
      if (x_koordinate > 0) {
        BodenSens[i] = 0;
      }
      else {
        KoordinatenSens[i][0] = -abs(KoordinatenSens[i][0]);
      }
    }
  }
}
