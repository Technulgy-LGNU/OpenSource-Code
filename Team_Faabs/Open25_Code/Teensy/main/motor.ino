/*
  motor and actuator section, to calculate and write motorvalues
*/
namespace motor {

//DRIVETRAIN AND DRIBBLER
constexpr int AnzahlMotoren = 5;                                                      //4 for drivetrain, one for the dribbler
constexpr int M_EN = 0;                                                               //Motor Enable Pin
constexpr int D_EN = 31;                                                              //Dribbler Enable Pin
constexpr int M_DIR[AnzahlMotoren] = { 28, 6, 5, 7, 30 };                             //Pins for Motor direction (LOW = CW, HIGH = CCW)
constexpr int M_PWM[AnzahlMotoren] = { 4, 2, 1, 3, 29 };                              //Pins for setting Motorspeed ( to 12bit resolution)
constexpr int MotorVR = 0, MotorVL = 1, MotorHR = 2, MotorHL = 3, MotorDribbler = 4;  //Motors
constexpr int motorBtnPin = 17;

//KICKERPINS AND KONSTANTS
constexpr int enableHV = 36, linear = 34, chipper = 35;  // updated for modified kickerboard

constexpr unsigned long SHOT_DURATION_US = 50000UL;
constexpr unsigned long CHIPPER_HIGH_TIME_US = 10000UL;  // for commented code
constexpr unsigned long CHIPPER_TOTAL_TIME_US = 50000UL;
constexpr unsigned long MICROSECONDS_MULTIPLIER = 1000UL;  // for multiplication with zeitChip

bool motorStatus = false;
long zeitSchuss = 0;
long zeitChip = 0;


void setup() {
  // MOTORSETUP
  pinMode(M_EN, OUTPUT);
  pinMode(D_EN, OUTPUT);
  pinMode(enableHV, OUTPUT);
  pinMode(linear, OUTPUT);
  pinMode(chipper, OUTPUT);

  analogWriteResolution(12);  // analogWrite() value 0 to 4095, or 4096 for higher resolution (12bit)

  for (int i = 0; i < AnzahlMotoren; i++) {
    pinMode(M_DIR[i], OUTPUT);
  }
  pinMode(motorBtnPin, INPUT_PULLUP);
}

void Schuss(bool schuss, bool chip) {
  if (schuss) {
    constexpr int schussTotzeit = 2500 * 1000;
    if ((micros() - zeitSchuss) > schussTotzeit) {
      zeitSchuss = micros();
    }
  }

  if (chip) {
    constexpr int chipTotzeit = 2500 * 1000;
    if ((micros() - zeitChip) > chipTotzeit) {
      zeitChip = micros();
    }
  }
}

Anweisung merge(Anweisung primary, Anweisung secondary) {
  return {
    .dir = primary.velo ? primary.dir : secondary.dir,
    .velo = primary.velo ? primary.velo : secondary.velo,
    .dribble = primary.dribble ? primary.dribble : secondary.dribble,
    .schuss = primary.schuss ? primary.schuss : secondary.schuss,
    .chip = primary.chip ? primary.chip : secondary.chip,
    .exCenterRot = primary.exCenterRot ? primary.exCenterRot : secondary.exCenterRot,
    .rot = primary.rot ? primary.rot : secondary.rot
  };
}

void drive(Anweisung motor_anw) {
  int Motor[AnzahlMotoren] = { 0, 0, 0, 0, 0 };
  double writeValPWM[AnzahlMotoren] = { 0, 0, 0, 0, 0 };

  // MOTOR ENABLING
  if (digitalRead(motorBtnPin) == LOW) {  //check motor button state
    motorStatus = !motorStatus;
    delay(300);
  }

  if (motorStatus && motor_anw.velo != 0) { //set enable Pins
    digitalWrite(M_EN, HIGH);
    digitalWrite(D_EN, HIGH);
  }
  else {
    digitalWrite(D_EN, LOW);
    digitalWrite(M_EN, LOW);
  }
  double richtung = motor_anw.dir ;

  if (richtung > 360)richtung -= 360;
  if (richtung < 0)richtung += 360;

  double phi = (richtung / 180) * PI;
  double m_v = motor_anw.velo;

  double m_rot = motor_anw.rot;
  double exCR = motor_anw.exCenterRot;

  if (ball::realBallY < 18 && ball::realBallY > 5 && abs(ball::realBallDist) < 13 && Lightbarrier()) {
    m_rot = 0;
    m_v = m_v;//motor_anw.velo * 0.8;
    exCR = exCR;
  }
  else {
    m_rot = m_rot;
    exCR = 0;
  }

  double vx = -cos(phi) * m_v;
  double vy = sin(phi) * m_v;

  constexpr double alpha = (32.5 / 180) * PI;
  constexpr double beta = (47.5 / 180) * PI;

  double m_eCR[4];
  m_eCR[MotorVR] = -22.76 * exCR;
  m_eCR[MotorVL] = -22.76 * exCR;
  m_eCR[MotorHR] = -99.24 * exCR;
  m_eCR[MotorHL] = -99.24 * exCR;

  Motor[MotorVR] = ((-sin(alpha) * vx) - (cos(alpha) * vy)) + m_rot + m_eCR[MotorVR];
  Motor[MotorVL] = ((-sin(alpha) * vx) + (cos(alpha) * vy)) + m_rot + m_eCR[MotorVL];
  Motor[MotorHL] = ((sin(beta) * vx) + (cos(beta) * vy)) + m_rot + m_eCR[MotorHL];
  Motor[MotorHR] = ((sin(beta) * vx) - (cos(beta) * vy)) + m_rot + m_eCR[MotorHR];

  // DRIBBLER
  Motor[MotorDribbler] = -motor_anw.dribble;

  // SCHUSS
  Schuss(motor_anw.schuss, motor_anw.chip);

  if (motorStatus || Schusstest()) {

    digitalWrite(enableHV, HIGH);

    if (RobotNB == 1) {  //sonderschuss
      if ((micros() - zeitSchuss) < 5000) { //1000 should be fine or so
        digitalWrite(linear, HIGH);
        digitalWrite(chipper, HIGH);
      } else {
        digitalWrite(linear, LOW);
        digitalWrite(chipper, LOW);
      }
    }

    else {
      if ((micros() - zeitSchuss) < 50000) {
        digitalWrite(linear, HIGH);
      } else {
        digitalWrite(linear, LOW);
      }
      if ((micros() - zeitChip) < 50000) {
        /*if ((micros() - zeitChip * 1000) < 10000 ) {
          digitalWrite(chipper, HIGH);
          }
          if ((micros() - zeitChip * 1000) > 1) {
          digitalWrite(linear, HIGH);
          }*/
        digitalWrite(chipper, HIGH);
      } else {
        digitalWrite(chipper, LOW);
        //digitalWrite(linear, LOW);
      }
    }
  }
  else {
    digitalWrite(enableHV, LOW);
  }


  //MOTORS
  for (int i = 0; i < AnzahlMotoren; i++) {

    if (Motor[i] > 0) writeValPWM[i] = Motor[i] + 409;  //401
    else if (Motor[i] < 0) writeValPWM[i] = Motor[i] - 409;
    else writeValPWM[i] = 0;

    if (writeValPWM[i] < -3000) writeValPWM[i] = -3000;
    if (writeValPWM[i] > 3000) writeValPWM[i] = 3000;

    if (writeValPWM[i] < 427 && writeValPWM[i] > -427) writeValPWM[i] = 0;

    //deciding in which direction to turn
    if (writeValPWM[i] < 0) {
      digitalWrite(M_DIR[i], LOW);
      analogWrite(M_PWM[i], abs(writeValPWM[i]));
    }

    else if (writeValPWM[i] > 0) {
      digitalWrite(M_DIR[i], HIGH);
      analogWrite(M_PWM[i], abs(writeValPWM[i]));
    }

    else if (writeValPWM[i] == 0) {
      analogWrite(M_PWM[i], 250);
    }
  }
}
}
