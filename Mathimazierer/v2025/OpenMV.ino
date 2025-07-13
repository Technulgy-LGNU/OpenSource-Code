int lv1;
int lv2;
int16_t val1;
int16_t val2;
int w_g_t;
void openmv_read() {
  // Anfrage senden (1 Byte)
  Wire.beginTransmission(0x12);
  Wire.write(1);  // Anfragebefehl
  Wire.endTransmission();

  //delayMicroseconds(10); //Wichtiger kleiner Delay!
  // Jetzt 4 Byte lesen
  Wire.requestFrom(0x12, 4);
  if (Wire.available() == 4) {
    val1 = Wire.read() | (Wire.read() << 8);
    val2 = Wire.read() | (Wire.read() << 8);
    lv1 = val1;
    lv2 = val2;
  } else {
    val1 = lv1;
    val2 = lv2;
  }

  //delayMicroseconds(1);
  //Serial.println(millis()-timer);
  /*Serial.print("Blau: ");
    Serial.print(val1);
    Serial.print(" | Gelb: ");
    Serial.println(w_g_t);*/
  if (val2 <= -180 && val2 >= -270) {
    w_g_t = map(val2, -180, -270, 180, 90);
  }
  else if (val2 > -180 && val2 <= 90) {
    w_g_t = val2;
  }
  if (val2 == -300) {
    w_g_t = -300;
  }
}


void openmvattack() {
  if (w_g_t != -300) {
    attacker();
    if (abs(w_g_t) <= 5) {
      drehung = 0;
      //Serial.println("T");
    }
    else {
      double p = 0.75;
      double d = 0.25;
      drehung = (p * w_g_t) - (d * rotationspeed2);
    }
  }
  else {
    compass();
    US();
    velo_math();
  }
  //Serial.println(w_g_t);
}

void openmvgoalie() {
}
