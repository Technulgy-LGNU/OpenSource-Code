void compassVorbereitung() {
  sensors_event_t orientationData;
  sensors_event_t angVelocityData;
  gyro.getEvent(&angVelocityData,  Adafruit_BNO055::VECTOR_GYROSCOPE);
  gyro.getEvent(&orientationData,  Adafruit_BNO055::VECTOR_EULER);
  winkel2 = orientationData.orientation.x;
  rotationspeed2 = angVelocityData.orientation.z;

  if (digitalRead(K2) == LOW) {
    minus = winkel2 ;
  }

  winkel2 = winkel2 - minus;
  //delay(10);


  if (winkel2 > 180) {
    winkel2 = winkel2 - 360;
  }
  if (winkel2 < -180) {
    winkel2 = winkel2 + 360;

  }
}

void compass() {
  double p = 0.75;//-0.6
  double d = 1.25;//-2.4
  drehung2 = (p * winkel2) - (d * rotationspeed2);

  if (drehung2 < 5 && drehung2 > -5) {
    drehung = 0;
  }
  else if (drehung2 > 5 || drehung2 < -5) {
    drehung = (p * winkel2) - (d * rotationspeed2);
  }
}

void com_cap_velo(){
  int a_w = abs(winkel2) / 2.4;
  int maxG = 80;
  geschw = maxG - a_w;
}
