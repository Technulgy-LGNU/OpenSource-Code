/*
  ball calculation, to calculate the direction and action the robot has to take to achieve best game situation
*/

namespace ball {

double xeinsvorher = 0;
double xzweivorher = 0;
double yeinsvorher = 0;
double yzweivorher = 0;
long zeiteinsvorher = 0;
long zeitzweivorher = 0;

bool ballSeeing;
byte nichtMittig;                                      //0: mittig, 1: rechts 2: links //mit Kamera bestimmt
double yGoal, bGoal, GOALA, GOALOA;                    //winkel zu den Toren //GOALOA =other angel goal
double yDist, bDist, GOALDist, GOALODist;              // Abstände zu den Toren in Pixeln
double yGoalWitdh, bGoalWitdh, GOALWidth, GOALOWidth;  //Tor Breiten in Pixeln
double balAngl, balDist;
constexpr int seit = 25;
constexpr int ballkuhleY = 13;
const Point leftOf(-seit, 0), rightOf(seit, 0), goalie_point(0, -75), ballkuhle(0, ballkuhleY);
long lastNotIn = 0;

void goalStuff(jetson::Msg msg) {

  ballSeeing = true;

  int ball_X = (resY / 2) - msg.Yy + middleY_Offset;
  int ball_Y = (resX / 2) - msg.Xx + middleX_Offset;

  int goalB_X = (resY / 2) - msg.GoalBy + middleY_Offset;
  int goalB_Y = (resX / 2) - msg.GoalBx + middleX_Offset;

  int goalY_X = (resY / 2) - msg.GoalYy + middleY_Offset;
  int goalY_Y = (resX / 2) - msg.GoalYx + middleX_Offset;

  int bGoalDist = sqrt(goalB_X * goalB_X + goalB_Y * goalB_Y);
  int yGoalDist = sqrt(goalY_X * goalY_X + goalY_Y * goalY_Y);
  bGoalWitdh = msg.GoalBw;
  yGoalWitdh = msg.GoalYw;

  balAngl = atan2(ball_Y, -ball_X) * 180 / PI;
  if (balAngl < 0)
    balAngl += 360;
  if (balAngl > 360)
    balAngl -= 360;

  if (balAngl > 180) {
    balAngl = balAngl - 360;
  }
  if (balAngl < -180) {
    balAngl = balAngl + 360;
  }
  balDist = sqrt(ball_X * ball_X + ball_Y * ball_Y);


  double goalBAngl = atan2(goalB_Y, goalB_X) * 180 / PI;
  if (goalBAngl < 0) goalBAngl += 360;
  if (goalBAngl > 360) goalBAngl -= 360;
  bGoal = 90 - goalBAngl;

  double goalYAngl = atan2(goalY_Y, goalY_X) * 180 / PI;
  if (goalYAngl < 0) goalYAngl += 360;
  if (goalYAngl > 360) goalYAngl -= 360;
  yGoal = 90 - goalYAngl;

  //on which goal to play
  if (onGoal == 0) {
    GOALA = yGoal;
    GOALDist = yGoalDist;    // Abstände zu den Toren in Pixeln
    GOALWidth = yGoalWitdh;  //Tor Breiten in Pixeln

    GOALOA = bGoal;
    GOALODist = bGoalDist;    // Abstände zu den Toren in Pixeln
    GOALOWidth = bGoalWitdh;  //Tor Breiten in Pixeln
  }
  else {
    GOALA = bGoal;
    GOALDist = bGoalDist;    // Abstände zu den Toren in Pixeln
    GOALWidth = bGoalWitdh;  //Tor Breiten in Pixeln

    GOALOA = yGoal;
    GOALODist = yGoalDist;    // Abstände zu den Toren in Pixeln
    GOALOWidth = yGoalWitdh;  //Tor Breiten in Pixeln
  }

  if (GOALA > 180) GOALA = GOALA - 360;
  if (GOALA < -180) GOALA = GOALA + 360;

  if (GOALOA > 180) GOALOA = GOALOA - 360;
  if (GOALOA < -180) GOALOA = GOALOA + 360;
}

double realBallX = 0;
double realBallY = 0;
double realBallDist = 0;
double realBallAngle = 0;
double absBallAngl = 0;

float predicted_x = 0;
float predicted_y = 0;

unsigned long lastballKuhle = 0;
bool geschossen = 0;
bool reihenfolgenvariable = 0;

byte ball_est(Point ball) {
 
  if (Lightbarrier()) {
    return 255;
  }
  if (!ball_da) return 0;
  constexpr int frontAngle1 = 23;  // Toleranzbereich vorne (in Grad)
  if ((ball.dir > 90 - frontAngle1) && (ball.dir < 90 + frontAngle1) && ball.dist < 80) {
    return 255;
  }
  else {
    int v = abs(ball.dist - 70);
    double wh = ball.dir - 90;
    if (wh > 180) wh -= 360;
    wh = abs(wh);
    constexpr double tf = 1.80;
    double wf = 1 + ((wh / 180) * tf);

    byte est = map(v * wf, 0, 180 * (1 + tf), 253, 2); // best est. pos ist 253, schlechteste ist 2, für evt sondefälle
    return est;
  }
}

motor::Anweisung control(Point ball) {
  motor::Anweisung anw = { 0 };

  if (ball_da) {
    realBallDist = 0.000000229179 * pow(ball.dist, 4) - 0.000117986 * pow(ball.dist, 3) + 0.0224923 * pow(ball.dist, 2) - 1.70121 * ball.dist + 55.8438;
    realBallX = cos(ball.dir / 180 * PI) * realBallDist;
    realBallY = sin(ball.dir / 180 * PI) * realBallDist;
    realBallAngle = atan2(realBallY, realBallX) * 180 / PI;
  }

  double d_x = 15000 * ((realBallX - xeinsvorher) / (micros() - zeiteinsvorher) + (realBallX - xzweivorher) / (micros() - zeitzweivorher)) / 2;  //190000
  double d_y = 15000 * ((realBallY - yeinsvorher) / (micros() - zeiteinsvorher) + (realBallY - yzweivorher) / (micros() - zeitzweivorher)) / 2;  //190000

  realBallX += d_x;
  realBallY += d_y;

  if (realBallAngle < 0) realBallAngle += 360;
  if (realBallAngle > 360) realBallAngle -= 360;

  absBallAngl = realBallAngle;
  absBallAngl = 90 - absBallAngl;
  if (absBallAngl > 180) absBallAngl -= 360;
  if (absBallAngl < -180) absBallAngl += 360;

  constexpr int maxBall_v = 580; //500
  int minBall_v = 260;
  if (millis() - lastBodenSeen < 300)minBall_v = 180;

  constexpr int maxAdd_D = 220;
  constexpr int maxAdd_A = 160;

  double help_D_velo = min(pow(realBallDist, 4.2) / 70000, maxAdd_D);
  double help_A_velo = min(pow(abs(absBallAngl) * 0.15, 1.6), maxAdd_A);

  double target_v = minBall_v + help_D_velo + help_A_velo;

  target_v = max(target_v, minBall_v);
  target_v = min(target_v, maxBall_v);

  //double maped = mapfloat(target_v, minBall_v, maxBall_v, 13, 10);

  double computedDir = 0;
  double x_c = 12;//maped + 1; //here adjust cameraerror vor/zurück //=12
  constexpr int y_c = 0; //0
  double d = 12.5;//maped;
  //adjust d and x_c at the same time bc of position of the ball on the circle !!!
  //maybe add some value around 0.5 to 2 to one of those valuesto adjust

  //magic math
  if (realBallX < 0) {
    computedDir = computeVectorAngle(x_c, y_c, d, -realBallX, -realBallY) * 180 / PI;
  } else {
    computedDir = 180 - (computeVectorAngle(x_c, y_c, d, realBallX, -realBallY) * 180 / PI);
  }

  if (realBallX < 1.5 && realBallX > -1.5 && realBallY < 10 && realBallY > 0) {
    computedDir = 90;
  }

  target_v = min(lidar::lidar_cap_velo(computedDir), target_v);


  double correctionRot;

  constexpr double p_cRot = 0.032;
  constexpr double d_cRot = -0.1;
  kompass::Werte data = kompass::read();
  correctionRot = p_cRot * GOALA + d_cRot * data.rotationSpeed;

  double cR = clampValue(correctionRot, 2.5); //1.5 seems valid but slower

  anw = { .dir = computedDir, .velo = (int)target_v, .dribble = 0, .schuss = 0, .chip = 0, .exCenterRot = cR };

  if (Lightbarrier() && abs(GOALA) > 40) {
    anw = { .dir = lidar::fahren(0, 0).dir, .velo = 160, .dribble = 0, .schuss = 0, .chip = 0, .exCenterRot = 0};
  }

  if (Lightbarrier()) {
    if (anw.dir > 180 && anw.dir < 359) {
      anw.velo = anw.velo * 0.35;
    }
    else {
      anw.velo = anw.velo * 0.6;// + min((last_ls_not_in / 500) * 0.4 * anw.velo, 0.4 * anw.velo);
    }
  }
  xzweivorher = xeinsvorher;
  yzweivorher = yeinsvorher;
  zeitzweivorher = zeiteinsvorher;
  xeinsvorher = realBallX;
  yeinsvorher = realBallY;
  zeiteinsvorher = micros();

  return anw;
}

motor::Anweisung dribble() {
  if (ball::realBallDist < 30 && ((ball::ball.dir < 90 + 70) && (ball::ball.dir > 90 - 70))) {
    return { .dir = 0, .velo = 0, .dribble = 2000, .schuss = 0, .chip = 0 };
  } else return {};
}
motor::Anweisung schuss() {

  bool s = 0, c = 0;

  if (Lightbarrier() && realBallDist < 14) {
    s = 1;
  }

  if (abs(GOALA) < 9) { //maybe adjust to bigger goal
    return { .dir = 0, .velo = 0, .dribble = 2000, .schuss = s, .chip = c };
  } else return {};
}
}
