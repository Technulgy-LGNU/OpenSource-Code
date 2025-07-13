int readMuxIR(bool s1, bool s2, bool s3, bool s4) {  //Verkürzung Auslesen
  digitalWrite(MuxSig0, s1);
  digitalWrite(MuxSig1, s2);
  digitalWrite(MuxSig2, s3);
  digitalWrite(MuxSig3, s4);
  return analogRead(Sig_MUX5);
}

void IR_READ() {
  IR[0] = readMuxIR(0, 0, 0, 0);
  //IR[1] = readMuxIR(0, 0, 0, 1);
  IR[1] = 1023;
  IR[2] = readMuxIR(1, 0, 0, 1);
  IR[3] = readMuxIR(0, 1, 0, 1);
  IR[4] = readMuxIR(1, 1, 0, 1);
  IR[5] = readMuxIR(0, 0, 1, 1);
  IR[6] = readMuxIR(1, 0, 1, 1);
  IR[7] = readMuxIR(0, 1, 1, 1);
  IR[8] = readMuxIR(1, 1, 1, 0);
  IR[9] = readMuxIR(0, 1, 1, 0);
  IR[10] = readMuxIR(1, 1, 1, 1);
  IR[11] = readMuxIR(1, 0, 1, 0);
  IR[12] = readMuxIR(0, 0, 1, 0);
  IR[13] = readMuxIR(1, 1, 0, 0);
  IR[14] = readMuxIR(0, 1, 0, 0);
  IR[15] = readMuxIR(1, 0, 0, 0);
  //IR[15] = 1023;


  for (int i = 0; i < Both; i++) {
    if (RoboterNum == 0) {
      for (int x = 0; x < 16; x++) {
        mapped[x] = map(IR[x], lowestValue1[x], highestValue1[x], 200, 1023);
      }
    } else if (RoboterNum == 1) {
      for (int x = 0; x < 16; x++) {
        mapped[x] = map(IR[x], lowestValue2[x], highestValue2[x], 400, 1023);
      }
    }
  }

  SEbest = -1;
  IRbest = 1001;

  for (int i = 0; i < NumberofSensors; i++) {
    if (IR[i] < IRbest) {
      IRbest = IR[i];
      SEbest = i;
    }
  }
  if (SEbest == 0 || SEbest == 1 || SEbest == 15) {
    vorne = true;
  }
  else {
    vorne = false;
  }
  if (SEbest <= 14 && SEbest >= 10) {
    r = true;
  }
  else {
    r = false;
  }
  if (SEbest >= 2 && SEbest <= 6) {
    l = true;
  }
  else {
    l = false;
  }
  if (SEbest <= 9 && SEbest >= 7) {
    h = true;
  }
  else {
    h = false;
  }
}

void Ir() {

  int Zone1 = 630;
  int Zone2 = 730;
  if (RoboterNum == 1) {  //Ballanfahrt 1
    //nahe Ballanfahrt
    if (SEbest == 1 && IRbest <= Zone1) {
      richtung = 125;  //112.5
      geschw = 40;
    }

    if (SEbest == 2 && IRbest <= Zone1) {
      richtung = 225;
      geschw = slow;
    }

    if (SEbest == 3 && IRbest <= Zone1) {
      richtung = 225;
      geschw = slow;
    }

    if (SEbest == 4 && IRbest <= Zone1) {
      richtung = 260;
      geschw = slow;
    }

    if (SEbest == 5 && IRbest <= Zone1) {
      richtung = 270;
      geschw = slow;
    }

    if (SEbest == 6 && IRbest <= Zone1) {
      richtung = 280;
      geschw = slow;
    }
    if (SEbest == 7 && IRbest <= Zone1) {
      richtung = 314;
      geschw = slow;
    }

    if (SEbest == 8 && IRbest <= Zone1) {
      richtung = 180;
      geschw = slow;
    }

    if (SEbest == 9 && IRbest <= Zone1) {
      richtung = 225;
      geschw = slow;
    }

    if (SEbest == 10 && IRbest <= Zone1) {
      richtung = 260;
      geschw = slow;
    }

    if (SEbest == 11 && IRbest <= Zone1) {
      richtung = 270;
      geschw = slow;
    }

    if (SEbest == 12 && IRbest <= Zone1) {
      richtung = 280;  //292.5
      geschw = slow;
    }

    if (SEbest == 13 && IRbest <= Zone1) {
      richtung = 314;  //314
      geschw = slow;
    }

    if (SEbest == 14 && IRbest <= Zone1) {
      richtung = 314;
      geschw = slow;
    }

    if (SEbest == 15 && IRbest <= Zone1) {
      richtung = 45;  //20
      geschw = 40;
    }

    if (SEbest == 0 && IRbest <= Zone1) {
      richtung = 90;
      geschw = 50;
    }

    if (IR[1] >=  490 && IR[1] <= 510 && IR[15] >=  490 && IR[15] <= 510) {
      richtung = 90;
      geschw = 50;
    }




    //Mittel
    if (SEbest == 1 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 135;  //112.5
      geschw = schnell;
    }
    if (SEbest == 2 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 157.5;  //115
      geschw = schnell;
    }
    if (SEbest == 3 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 180;
      geschw = schnell;
    }
    if (SEbest == 4 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 202.5;
      geschw = schnell;
    }
    if (SEbest == 5 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 225;
      geschw = hinten;
    }
    if (SEbest == 6 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 247.5;
      geschw = hinten;
    }
    if (SEbest == 7 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 270;
      geschw = hinten;
    }
    if (SEbest == 8 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 247.5;
      geschw = hinten;
    }
    if (SEbest == 9 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 270;
      geschw = hinten;
    }
    if (SEbest == 10 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 292.5;
      geschw = hinten;
    }
    if (SEbest == 11 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 314;  //337.5
      geschw = hinten;
    }
    if (SEbest == 12 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 337.5;  //0
      geschw = schnell;
    }
    if (SEbest == 13 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 0;
      geschw = schnell;
    }
    if (SEbest == 14 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 22.5;
      geschw = schnell;
    }
    if (SEbest == 15 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 45;
      geschw = schnell;
    }
    if (SEbest == 0 && IRbest < Zone2 && IRbest > Zone1) {
      richtung = 90;
      geschw = 50;
    }




    //Weite Ballanfahrt

    if (SEbest == 1 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 112.5;  //112.5
      geschw = schnell;
    }
    if (SEbest == 2 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 135;  //115
      geschw = schnell;
    }
    if (SEbest == 3 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 157.5;
      geschw = schnell;
    }
    if (SEbest == 4 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 180;
      geschw = schnell;
    }
    if (SEbest == 5 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 202.5;
      geschw = hinten;
    }
    if (SEbest == 6 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 225;
      geschw = hinten;
    }
    if (SEbest == 7 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 247.5;
      geschw = hinten;
    }
    if (SEbest == 8 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 270;
      geschw = hinten;
    }
    if (SEbest == 9 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 292.5;
      geschw = hinten;
    }
    if (SEbest == 10 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 314;
      geschw = hinten;
    }
    if (SEbest == 11 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 337.5;  //337.5
      geschw = hinten;
    }
    if (SEbest == 12 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 0;  //0
      geschw = schnell;
    }
    if (SEbest == 13 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 22.5;
      geschw = schnell;
    }
    if (SEbest == 14 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 45;
      geschw = schnell;
    }
    if (SEbest == 15 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 67.5;
      geschw = schnell;
    }
    if (SEbest == 0 && IRbest < 1000 && IRbest > Zone2) {
      richtung = 90;
      geschw = 70;
    }
    if (SEbest == -1) {
      geschw = 0;
      richtung = 0;
    }
  }
  else if (RoboterNum == 0) {  //Ballanfahrt 2

    //nahe Ballanfahrt
    if (SEbest == 1 && IRbest <= 620) {
      richtung = 130;  //112.5
      geschw = slow;
    }

    if (SEbest == 2 && IRbest <= 620) {
      richtung = 195;  //170
      geschw = slow;
    }

    if (SEbest == 3 && IRbest <= 620) {
      richtung = 230;  //230
      geschw = slow;
    }

    if (SEbest == 4 && IRbest <= 620) {
      richtung = 247.5;
      geschw = slow;
    }

    if (SEbest == 5 && IRbest <= 620) {
      richtung = 260;
      geschw = slow;
    }

    if (SEbest == 6 && IRbest <= 620) {
      richtung = 292.5;
      geschw = slow;
    }
    if (SEbest == 7 && IRbest <= 620) {
      richtung = 314;
      geschw = slow;
    }

    if (SEbest == 8 && IRbest <= 620) {
      richtung = 0;
      geschw = slow;
    }

    if (SEbest == 9 && IRbest <= 620) {
      richtung = 230;
      geschw = slow;
    }

    if (SEbest == 10 && IRbest <= 620) {
      richtung = 224.5;
      geschw = slow;
    }

    if (SEbest == 11 && IRbest <= 620) {
      richtung = 280;
      geschw = slow;
    }

    if (SEbest == 12 && IRbest <= 620) {
      richtung = 310.5;  //292.5
      geschw = slow;
    }

    if (SEbest == 13 && IRbest <= 620) {
      richtung = 314;  //314
      geschw = slow;
    }

    if (SEbest == 14 && IRbest <= 620) {
      richtung = 345;  //10
      geschw = slow;
    }

    if (SEbest == 15 && IRbest <= 620) {
      richtung = 30;  //20
      geschw = slow;
    }

    if (SEbest == 0 && IRbest <= 620) {
      richtung = 90;
      geschw = slow;
    }

    //weite Ballanfahrt
    if (SEbest == 1 && IRbest < 1000 && IRbest > 620) {
      richtung = 115;  //112.5
      geschw = schnell;
    }
    if (SEbest == 2 && IRbest < 1000 && IRbest > 620) {
      richtung = 115;  //115
      geschw = schnell;
    }
    if (SEbest == 3 && IRbest < 1000 && IRbest > 620) {
      richtung = 157.5;
      geschw = schnell;
    }
    if (SEbest == 4 && IRbest < 1000 && IRbest > 620) {
      richtung = 180;
      geschw = schnell;
    }
    if (SEbest == 5 && IRbest < 1000 && IRbest > 620) {
      richtung = 202.5;
      geschw = hinten;
    }
    if (SEbest == 6 && IRbest < 1000 && IRbest > 620) {
      richtung = 225;
      geschw = hinten;
    }
    if (SEbest == 7 && IRbest < 1000 && IRbest > 620) {
      richtung = 247.5;
      geschw = hinten;
    }
    if (SEbest == 8 && IRbest < 1000 && IRbest > 620) {
      richtung = 270;
      geschw = hinten;
    }
    if (SEbest == 9 && IRbest < 1000 && IRbest > 620) {
      richtung = 292.5;
      geschw = hinten;
    }
    if (SEbest == 10 && IRbest < 1000 && IRbest > 620) {
      richtung = 314;
      geschw = hinten;
    }
    if (SEbest == 11 && IRbest < 1000 && IRbest > 620) {
      richtung = 337.5;  //337.5
      geschw = hinten;
    }
    if (SEbest == 12 && IRbest < 1000 && IRbest > 620) {
      richtung = 20;  //0
      geschw = schnell;
    }
    if (SEbest == 13 && IRbest < 1000 && IRbest > 620) {
      richtung = 22.5;
      geschw = schnell;
    }
    if (SEbest == 14 && IRbest < 1000 && IRbest > 620) {
      richtung = 45;
      geschw = schnell;
    }
    if (SEbest == 15 && IRbest < 1000 && IRbest > 620) {
      richtung = 67.5;
      geschw = schnell;
    }
    if (SEbest == 0 && IRbest < 1000 && IRbest > 620) {
      richtung = 90;
      geschw = schnell;
    }
    if (SEbest == -1) {
      geschw = 0;
      richtung = 0;
    }
  }
  //int last_velo = geschw;
  /*if(velo_control(richtung) > geschw){
    geschw = last_velo;
    }
    else if(velo_control(richtung) < geschw){
    geschw = velo_control(richtung);
    }

    //US-Vorne
    if((vorne == true) && (US_V[0] < 60)){
    geschw = 50;
    }
    if((vorne == false) && (US_V[0] < 60)){
    geschw = last_velo;
    }
    else if((vorne == true) && (US_V[0] >= 60)){
    geschw = last_velo;
    }

    //US-Hinten
    if((h == true) && (US_V[2] < 60)){
    geschw = 50;
    }
    if((h == false) && (US_V[2] < 60)){
    geschw = last_velo;
    }
    else if((h == true) && (US_V[2] >= 60)){
    geschw = last_velo;
    }*/
  //Serial.println(geschw);
}
