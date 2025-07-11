/*
  reads the measured values from the gyro/orientation sensor (BNO055) and translates it into an motorcomponent as rotation of the entire robot
*/


namespace kompass {

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup() {
  Wire.begin();
  bno.begin(OPERATION_MODE_IMUPLUS);
}

Werte read() {
  if (bno.getMode() == 0x10) {
    setup();
  }
  sensors_event_t gyroscopeEvent;
  sensors_event_t eulerEvent;
  bno.getEvent(&gyroscopeEvent, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&eulerEvent, Adafruit_BNO055::VECTOR_EULER);
  return { .winkel = eulerEvent.orientation.x, .upwards = eulerEvent.orientation.y, .rotationSpeed = gyroscopeEvent.gyro.z };
}

//PD controller
constexpr double p = -6;
constexpr double d = -10;
//double minus = 0;

double offset(double winkel, double minus) {
  winkel = winkel - minus;
  if (winkel > 180) {
    winkel = winkel - 360;
  }
  if (winkel < -180) {
    winkel = winkel + 360;
  }
  return winkel;
}


motor::Anweisung control() {
  auto kompass = read();

  gyro_a = kompass.winkel;

  if (digitalRead(btnKompass) == LOW) {
    minus = kompass.winkel;
    Neo::flash(Neo::npurple, 300);
  }

  double winkel = offset(kompass.winkel, minus);

  constexpr int maxDreh = 30;
  double drehung;
  /*if (ball::realBallDist < 24 && abs(ball::absBallAngl) < 90) drehung = (p * -0.30 * ball::absBallAngl) - (d * 1.5 * kompass.rotationSpeed);
    else */drehung = (p * winkel) - (d * kompass.rotationSpeed);

  double rot = drehung;
  return { .dir = 0, .velo = 0, .dribble = 0, .schuss = 0, .chip = 0, .exCenterRot = 0, .rot = rot };
}
}
