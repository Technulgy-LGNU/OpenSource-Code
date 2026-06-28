void compassVorbereitung() {
  sensors_event_t orientationData;
  sensors_event_t angVelocityData;
  gyro.getEvent(&angVelocityData,  Adafruit_BNO055::VECTOR_GYROSCOPE);
  gyro.getEvent(&orientationData,  Adafruit_BNO055::VECTOR_EULER);
  angle = orientationData.orientation.x;
  rotationSpeed = angVelocityData.orientation.z;
  //Serial.println(angle);
  if (digitalRead(K4) == LOW) {
    ded = angle ;
  }

  angle = angle - ded;
  //delay(10);


  if (angle > 180) {
    angle = angle - 360;
  }
  if (angle < -180) {
    angle = angle + 360;

  }
  //Serial.println(angle);
}

void compass() {
  double p = 0.85;//-0.6
  double d = 0.5;//-2.4
  if (abs(angle) >= 3) {
    drehung = (p * angle) - (d * rotationSpeed);
  }
  else {
    drehung = 0;
  }
  //Serial.println("COMPASS");
}
