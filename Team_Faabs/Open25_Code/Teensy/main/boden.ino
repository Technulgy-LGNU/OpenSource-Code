bool SBod[AnzahlSensoren];
long ZeitpunktLinie;
int AnzahlGesehen = 0;

double x_Sum = 0;
double y_Sum = 0;
elapsedMillis onLine;
elapsedMillis offLine;

bool BodenSens[AnzahlSensoren];
bool MindestensEiner = false;

constexpr int sensorCoordinate[AnzahlSensoren][2] = {

  //innerst ring (8 Sensoren, SFH0X )
  { 205, 425 },    //SFH01, arrayNr0
  { -205, 425 },   //2
  { 425, 205 },    //3
  { 425, -205 },   //4
  { -205, -425 },  //5
  { 205, -425 },   //6
  { -425, 205 },   //7
  { -425, -205 },  //8

  //middle ring (24 Sensoren, SFH1X)
  { 1044, -205 },   //11
  { 1044, 205 },    //12
  { 1007, 345 },    //13
  { 802, 699 },     //14
  { 699, 802 },     //15
  { 345, 1007 },    //16
  { 205, 1044 },    //17
  { -205, 1044 },   //18
  { -345, 1007 },   //19
  { -699, 802 },    //110
  { -802, 699 },    //111
  { -1007, 345 },   //112
  { -1044, 205 },   //113
  { -1044, -205 },  //114
  { -1007, -345 },  //115
  { -802, -699 },   //116
  { -699, -802 },   //117
  { -345, -1007 },  //118
  { -205, -1044 },  //119
  { 205, -1044 },   //120
  { 345, -1007 },   //121
  { 699, -802 },    //122
  { 802, -699 },    //123
  { 1007, -345 },   //124


  //big outer ring (32 Sensoren, SFH2X)
  { 1663, -205 },    //21
  { 1663, 205 },     //22
  { 1615, 447 },     //23
  { 1458, 826 },     //24
  { 1321, 1031 },    //25
  { 1031, 1321 },    //26
  { 826, 1458 },     //27
  { 447, 1615 },     //28
  { 205, 1663 },     //29
  { -205, 1663 },    //210
  { -447, 1615 },    //211
  { -826, 1458 },    //212
  { -1031, 1321 },   //213
  { -1321, 1031 },   //214
  { -1458, 826 },    //215
  { -1615, 447 },    //216
  { -1663, 205 },    //217
  { -1663, -205 },   //218
  { -1615, -447 },   //219
  { -1458, -826 },   //220
  { -1321, -1031 },  //221
  { -1031, -1321 },  //222
  { -826, -1458 },   //223
  { -447, -1615 },   //224
  { -205, -1663 },   //225
  { 205, -1663 },    //226
  { 447, -1615 },    //227
  { 826, -1458 },    //228
  { 1031, -1321 },   //229
  { 1321, -1031 },   //230
  { 1458, -826 },    //231
  { 1615, -447 },    //232

  // outer sensorarrays (6 Sensoren, SFH3X)
  { 2234, -512 },   //31
  { 2288, -106 },   //32
  { -2288, -106 },  //33
  { -2234, -512 },  //34
  { -205, -2282 },  //35
  { 205, -2282 },   //36

  //second ring (12 Sensoren, SFH4X)
  { 742, 199 },    //41
  { 543, 543 },    //42
  { 199, 742 },    //43
  { -199, 742 },   //44
  { -543, 543 },   //45
  { -742, 199 },   //46
  { -742, -199 },  //47
  { -543, -543 },  //48
  { -199, -742 },  //49
  { 199, -742 },   //410
  { 543, -543 },   //411
  { 742, -199 },   //412

  //third ring (10 Sensoren, SFH5X)
  { 1354, 0 },      //51
  { 1172, 677 },    //52
  { 677, 1172 },    //53
  { 0, 1354 },      //54
  { -677, 1172 },   //55
  { -1172, 677 },   //56
  { -1354, 0 },     //57
  { -677, -1172 },  //59
  { 0, -1354 },     //510
  { 677, -1172 }    //511

};

int sw[AnzahlSensoren] [2] = {0};
void set_SW() {

  sw[7] [0] = 915;
  sw[15][0] = 885;
  sw[16] [0] = 885;
  sw[19] [0] = 1100;
  sw[20] [0] = 975;
  sw[21] [0] = 975;
  sw[22] [0] = 950;
  sw[23] [0] = 980;
  sw[24] [0] = 1100;
  sw[25] [0] = 935;
  sw[26] [0] = 1100;
  sw[44] [0] = 880;
  sw[45] [0] = 880;
  sw[46] [0] = 1100;
  sw[47] [0] = 1100;
  sw[48] [0] = 1100;
  sw[73] [0] = 920;
  sw[75] [0] = 1100;
  sw[76] [0] = 1100;
  sw[77] [0] = 980;
  sw[85] [0] = 880;
  sw[88] [0] = 1100;

  sw[17][1] = 1100;
  sw[73][1] = 1100;
  sw[86][1] = 1100;
  sw[89][1] = 1100;
  sw[41][1] = 1100;
  sw[87][1] = 1100;
  sw[20][1] = 1100;
  sw[19][1] = 1100;
  sw[75][1] = 1100;
  sw[76][1] = 1100;
  sw[39][1] = 1100;
  sw[44][1] = 1100;
  sw[48][1] = 1100;
  sw[51][1] = 1100;
}

motor::Anweisung bodenControlMain(double ball_follow_dir, double ball_follow_velo) {
  readMux();
  SensorAuswerten();

  if (MindestensEiner) {
    ZeitpunktLinie = millis();
    for (int i = 0; i < AnzahlSensoren; i++) {
      if (BodenSens[i] && AnzahlGesehen < 40 && !SBod[i]) {//65
        SBod[i] = true;
        AnzahlGesehen++;
      }
    }
  } else {
    if ((millis() - ZeitpunktLinie) > 20 && AnzahlGesehen) {
      AnzahlGesehen = 0;
      for (int i = 0; i < AnzahlSensoren; i++) {
        SBod[i] = false;
      }
    }
  }

  if (AnzahlGesehen > 0) {
    double x_Sum = 0;
    double y_Sum = 0;
    for (int i = 0; i < AnzahlSensoren; i++) {
      if (SBod[i]) {
        x_Sum += sensorCoordinate[i][0];
        y_Sum += sensorCoordinate[i][1];
      }
    }
    double dir1 = atan2(y_Sum, x_Sum) * 180 / PI + 180;
    double ve = 150;
    return { .dir = dir1, .velo = (int)ve, .dribble = 0, .schuss = 0 };

  }
  else {
    return {};
  }

  /*
    if (AnzahlGesehen) {
    constexpr double ok = 0.2;
    constexpr int bmax = 150;
    double y_k_Ball = min(ok * ball::ball.y, bmax);
    double x_k_Ball = min(ok * ball::ball.x, bmax);
    double v_k_Ball = sqrt(x_k_Ball * x_k_Ball + y_k_Ball * y_k_Ball);

    double kp = v_k_Ball / 60; //15;
    constexpr double kd = 0.008;//0.0027;

    constexpr double ki = 0; //2000;
    double p = AnzahlGesehen;

    double d = (AnzahlGesehen * 1.) / onLine;
    if (AnzahlGesehen < 20) d = 0;
    if (AnzahlGesehen > 80) d = 0;
    double i = AnzahlGesehen * (onLine / 1000000.);

    Serial.printf("p:%d,", p * kp);
    Serial.printf("d:%d,", d * kd);
    Serial.printf("i:%d\n", i * ki);

    double dir1 = atan2(y_Sum, x_Sum) * 180 / PI - 270;
    double ve1 = ki * i + kp * p + kd * d;

    double y_k_Bod = sin(dir1 / 180 * PI) * ve1;
    double x_k_Bod = cos(dir1 / 180 * PI) * ve1;

    double x_v = x_k_Ball + x_k_Bod;
    double y_v = y_k_Ball + y_k_Bod;

    double dir = atan2(y_v, x_v) * 180 / PI;
    while (dir < 0)
      dir += 360;
    while (dir > 360)
      dir -= 360;

    double ve = sqrt(x_v * x_v + y_v * y_v) * 3 ;
    Serial.println(ve); //debug here.........................................................
    ve = min(ve, 320); //oder =215, dann fixert wert... wie vorher
    //if (AnzahlGesehen > 41) ve = 200; // Strafraum
    //if(noRisk)ve = 215;

    if (isDirectionMatch(dir, ball_follow_dir, 90))
      {
      return { .dir = dir , .velo = ve, .dribble = 0, .schuss = 0 };
      /}
      else {
      return {};
      }
    return { .dir = dir , .velo = ve, .dribble = 0, .schuss = 0 };

    } else {
    return {};
    }*/
}

void SensorAuswerten() {
  
  MindestensEiner = false;

  for (int i = 0; i < AnzahlSensoren; i++)
  {
    if (sw[i] [RobotNB] < Bodensens[i])
    {
      BodenSens[i] = true;
      MindestensEiner = true;
      lastBodenSeen = millis();
      /*      Serial.print(i);
            Serial.print(" :");
            Serial.println(Bodensens[i]);*/
    } else {
      BodenSens[i] = false;
    }
  }
}



constexpr byte muxPins[4] = { 16, 15, 14, 38 };
constexpr byte btnMuxPin = 31;
constexpr int muxBodenAnalogPins[6] = { A10, A11, A12, A13, A17, A16 };

bool dipSwitchState[8];
constexpr int Schwellwert = 890;

void setMuxChannel(int channel) {
  digitalWrite(muxPins[0], channel & 0x01);
  digitalWrite(muxPins[1], channel >> 1 & 0x01);
  digitalWrite(muxPins[2], channel >> 2 & 0x01);
  digitalWrite(muxPins[3], channel >> 3 & 0x01);
}


void readMux() {
  // Function to set the multiplexer channel

  setMuxChannel(0);
  Bodensens[17] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[35] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[4] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[81] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[1] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[59] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(1);
  Bodensens[43] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[34] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[78] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[70] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[73] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[60] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(2);
  Bodensens[86] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[33] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[74] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[10] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[90] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[61] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(3);
  Bodensens[42] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[82] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[6] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[9] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[89] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[62] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(4);
  Bodensens[16] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[36] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[7] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[8] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[56] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[63] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(5);
  Bodensens[15] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[83] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[77] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[31] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[68] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[32] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(6);
  Bodensens[41] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[37] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[25] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[30] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[55] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[65] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(7);
  Bodensens[85] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[11] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[26] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[29] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[67] = analogRead(muxBodenAnalogPins[4]);
  // (IR)  Bodensens[] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(8);
  Bodensens[18] = 0;  //analogRead(muxBodenAnalogPins[0]);
  // (IR)  Bodensens[] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[24] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[27] = analogRead(muxBodenAnalogPins[3]);
  // (IR)  Bodensens[] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[64] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(9);
  Bodensens[44] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[40] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[23] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[28] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[66] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[58] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(10);
  Bodensens[87] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[14] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[22] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[80] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[49] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[69] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(11);
  Bodensens[45] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[13] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[21] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[3] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[50] = analogRead(muxBodenAnalogPins[4]);
  // (IR)  Bodensens[] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(12);
  Bodensens[88] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[39] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[20] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[2] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[51] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[57] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(13);
  Bodensens[48] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[84] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[19] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[71] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[52] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[91] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(14);
  Bodensens[47] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[38] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[75] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[79] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[53] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[72] = analogRead(muxBodenAnalogPins[5]);

  setMuxChannel(15);
  Bodensens[46] = analogRead(muxBodenAnalogPins[0]);
  Bodensens[12] = analogRead(muxBodenAnalogPins[1]);
  Bodensens[76] = analogRead(muxBodenAnalogPins[2]);
  Bodensens[5] = analogRead(muxBodenAnalogPins[3]);
  Bodensens[54] = analogRead(muxBodenAnalogPins[4]);
  Bodensens[0] = analogRead(muxBodenAnalogPins[5]);
}
