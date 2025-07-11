/*
  main program setup and loop
*/

#include <Adafruit_BNO055.h>

bool onGoal = 0;  // 0=yellow, 1 =blue
bool RobotNB = 0; // 0 = JP5.1.4, taped as 1 => spielt hinten
// 1 = jp 6.2   taped as 2 => spielt vorne
const bool IS_TRANSMITTER = !RobotNB;  // true = Version A (Transmitter), false = Version B (Receiver)

constexpr bool STRIKER = 1, GOALIE = 0;
bool m = STRIKER;
int x_neutralPos[2] = { -20, 0};
int y_neutralPos[2] = { -5, -45};

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 8);  // CE, CSN
const byte addresses[][6] = { "00001", "00002" };

#include <Adafruit_NeoPixel.h>
namespace Neo {

extern const int PIN;
extern const int COUNT;
extern uint32_t nwhite;
extern uint32_t nblue;
extern uint32_t nyellow;
extern uint32_t npurple;
extern uint32_t ngreen;

// Enums - only define here, remove from neopixels_leds.ino
enum Mode { IDLE, FLASH, PULSE };

// Function declarations - remove default parameters here
void setup();
void update();
void flash(uint32_t c, unsigned long d = 1000);
void pulse(uint32_t c, unsigned long d = 1000);
void off();
}


namespace motor {
struct Anweisung {
  double dir;
  int velo;
  int dribble;
  bool schuss;
  bool chip;
  double exCenterRot;
  double rot;
};
void setup();
void drive(Anweisung);
Anweisung merge(Anweisung primary, Anweisung secondary);
}
namespace kompass {
double minus = 0;
double gyro_a;
struct Werte {
  double winkel;
  double upwards;
  double rotationSpeed;
};

extern Adafruit_BNO055 bno;

void setup();
Werte read();
motor::Anweisung control();
}

constexpr int resX = 816, resY = 616, middleX_Offset = 0, middleY_Offset = 0;  // Y bei H: -14
namespace jetson {
struct Msg {
  bool receivedMsg, isBall, isGoalY, isGoalB;
  uint16_t Xx, Yy, Ww, Hh, GoalYx, GoalYy, GoalYw, GoalYh, GoalBx, GoalBy, GoalBw, GoalBh;

  Msg(bool receivedMsg)
    : receivedMsg(receivedMsg) {}
  Msg(bool receivedMsg, bool isBall, uint16_t Xx, uint16_t Yy, uint16_t Ww, uint16_t Hh,
      bool isGoalY, uint16_t GoalYx, uint16_t GoalYy, uint16_t GoalYw, uint16_t GoalYh,
      bool isGoalB, uint16_t GoalBx, uint16_t GoalBy, uint16_t GoalBw, uint16_t GoalBh)
    : receivedMsg(receivedMsg), isBall(isBall), isGoalY(isGoalY), isGoalB(isGoalB),
      Xx(Xx), Yy(Yy), Ww(Ww), Hh(Hh),
      GoalYx(GoalYx), GoalYy(GoalYy), GoalYw(GoalYw), GoalYh(GoalYh),
      GoalBx(GoalBx), GoalBy(GoalBy), GoalBw(GoalBw), GoalBh(GoalBh) {}

  void print() {
    Serial.println("Msg:");
    Serial.print("\treceivedMsg: ");
    Serial.println(receivedMsg);
    if (receivedMsg) {
      Serial.print("\tisBall: ");
      Serial.println(isBall);
      Serial.print("\tXx: ");
      Serial.println(Xx);
      Serial.print("\tYy: ");
      Serial.println(Yy);
    }
    Serial.println("--------");
  }
};
Msg receive();
}

namespace ball {
struct Point {
  double x, y, dir, dist;
  Point(double x, double y)
    : x(x), y(y) {
    dir = ((atan2(-y, -x) * 180) / PI) + 180;
    while (dir < 0)
      dir += 360;
    while (dir > 360)
      dir -= 360;

    dist = sqrt((abs(x) * abs(x)) + (abs(y) * abs(y)));
  }
};

Point ball(0, 0);
Point balllast(0, 0);
byte ball_est(Point ball);
motor::Anweisung control(Point ball);
motor::Anweisung last;
void goalStuff(jetson::Msg msg);
motor::Anweisung dribble();
motor::Anweisung schuss();
}

namespace lidar {
extern int dx, dy;
void lidar();

double lidar_cap_velo(double inputdir);
motor::Anweisung wand();
motor::Anweisung fahren(int x1, int y1);
}

// Communication state variables
int analogValue_Send = 0;
int receivedAnalogValue = 0;
unsigned long lastSendTime = 0;
unsigned long lastReceiveTime = 0;
const unsigned long sendInterval = 20;    // Send every 20ms
const unsigned long receiveTimeout = 40;  // 40ms timeout for receive
bool waitingForResponse = false;
bool listenMode = false;
bool hasNewData = false;
// Statistics for tracking nrf
unsigned long totalSent = 0;
unsigned long totalReceived = 0;
unsigned long timeouts = 0;

constexpr byte AnzahlSensoren = 92;
int Bodensens[AnzahlSensoren];
long lastBodenSeen;
bool buttonsState[5];

constexpr int Buzzer = 33;
constexpr int LED1 = 37;
constexpr int communicationmod = 21;

long last_ls_not_in = 0;

bool ball_da = 0;
double gyro_a;

void setup() {

  Serial.begin(115200);
  nrf_setup();

  //Beep at startup
  if (!RobotNB) {
    tone(Buzzer, 500);
    delay(300);
  }
  else {
    tone(Buzzer, 500);
    delay(300);
    tone(Buzzer, 800);
    delay(200);
    tone(Buzzer, 500);
    delay(300);
  }
  noTone(Buzzer);

  motor::setup();
  kompass::setup();
  GPIOsetup();
  Neo::setup();
}

unsigned long now;
unsigned long ball_da_last;

int ball_X = 0;
int ball_Y = 0;

int lastball_X = 0;
int lastball_Y = 0;

bool ball_nichtmehrda_sicher = 0;

void loop() {
  now = millis();
  jetson::Msg msg = jetson::receive();
  lidar::lidar();

  if (msg.receivedMsg && msg.isBall) {

    ball_da = true;
    ball_da_last = millis();
    ball::goalStuff(msg);

    ball_X = (resY / 2) - msg.Yy + middleY_Offset;
    ball_Y = (resX / 2) - msg.Xx + middleX_Offset;

    lastball_X = ball_X;
    lastball_Y = ball_Y;

    ball::ball = ball::Point(-ball_X, ball_Y);
    //Serial.println()

    if (m == STRIKER) {
      ball::last = ball::control(ball::ball);
    } else if (m == GOALIE) {
    } else {
      ball::last = ball::control(ball::ball);
    }
  }
  else if (msg.receivedMsg) {
    ball_da = false;
  }

  if (millis() - ball_da_last > 500)
  {
    ball::last = lidar::fahren(x_neutralPos[RobotNB], y_neutralPos[RobotNB]); //comment out for fluent
  }

  if (m == GOALIE)
  {
    ball::last = lidar::fahren(0, -45);//comment out for fluent
  }

  motor::Anweisung motor = ball::last;


  motor::Anweisung boden = bodenControlMain(motor.dir, motor.velo);
  if (boden.velo > 90) {
    motor = boden;
  }

  motor::Anweisung lidar_wand =  lidar::wand();
  if (lidar_wand.velo > 0) {
    motor = lidar_wand;
  }

  motor = motor::merge(motor, kompass::control());
  motor = motor::merge(motor, ball::dribble());
  motor = motor::merge(motor, ball::schuss());


  if (Schusstest()) {
    motor.schuss = 1;
  }

  controll_ongoal();
/*
  updateAnalogValue();
  processIncomingData();

  if (IS_TRANSMITTER) {
    attemptSend();
  } else {
    if (hasNewData) {
      attemptSend();
    }
  }

  
    //only for communication purpose debugging
    static unsigned long lastPrintTime = 0;
    if (millis() - lastPrintTime >= 100) {
      Serial.print("Mode (0 GOALIE and 1 STRIKER): ");
      Serial.print(m);

      Serial.print(" | Local: ");
      Serial.print(analogValue_Send);
      Serial.print(" | Received: ");
      Serial.println(receivedAnalogValue);

      lastPrintTime = millis();
    }*/

  motor::drive(motor);
  Neo::update();

}
