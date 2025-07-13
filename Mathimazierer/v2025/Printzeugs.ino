void Print() {
  //Motoren
  Serial.print("Richtung: ");
  Serial.println(richtung);
  Serial.print("Geschwindigkeit: ");
  Serial.println(geschw);
  Serial.print("Drehung: ");
  Serial.println(drehung);
  /*Serial.print("An: ");
    Serial.println(m_state);*/

  /*for (int i = 0; i < AnzahlBLMotoren; i++) {
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(gerundet[i]);
    }*/

  //Kompass
  /*Serial.print("Winkel: ");
    Serial.println(winkel2);*/

  //OpenMV
  /*Serial.print("WinkelO: ");
    Serial.println(winkel);*/

  //Knöpfe
  /*Serial.print("K1: ");
    Serial.println(digitalRead(K1));
    Serial.print("K2: ");
    Serial.println(digitalRead(K2));
    Serial.print("K3: ");
    Serial.println(digitalRead(K3));*/

  //IR
  /*Serial.print("IRbest: ");
    Serial.println(IRbest);
    Serial.print("SEbest: ");
    Serial.println(SEbest);
    for (int i = 0; i < NumberofSensors; i++) {
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(IR[i]);
    }*/

  //Boden
  /*for (int i = 0; i < numSensors; i++) {
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(SBod[i]);
    }*/
  /*for(int i = 0; i<numSensors; i++){
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(BodenSens[i]);
    }*/

  //Funk
  /*Serial.print("Empfangen: ");
    Serial.println(receivedIRbest);
    Serial.print("Eigener: ");
    Serial.println(IRbest);*/

  //Schuss
  /*Serial.print("Wert: ");
    Serial.println(Schuss_M);*/

  //US
  /*Serial.print("Vorne: ");
    Serial.println(US_V[0]);
    Serial.print("Links: ");
    Serial.println(US_V[1]);
    Serial.print("Hinten: ");
    Serial.println(US_V[2]);
    Serial.print("Rechts: ");
    Serial.println(US_V[3]);
    Serial.print("Dis: ");
    Serial.println(dis);*/

  //OpenMV
  /*Serial.print("wGelb: ");
    Serial.println(w_g_t);*/

  //Lichtschranke
  /*Serial.print("HabBall: ");
    Serial.println(ik);*/
}
