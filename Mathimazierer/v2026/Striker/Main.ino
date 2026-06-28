//Boden woanders gespeichesp
constexpr int numSensors = 64;
int richtung_Sens[numSensors];
bool Motor_WertDe;
int BodenSens[numSensors];
int sw = 725;
int winkelGc;
bool noB;
float last_drehung;
bool langsam = false;
double dir1;
bool seitlichL;
unsigned long letzteZeitonLine = 0;
bool beginMeasureTimeoL;
bool vorne;
bool BsameSpot;
bool bodenAn;
bool sensHinten;
int onLV;
bool turnOut;
bool overdriveL = false;
unsigned long startoverdrive = 0;
double lastBAngle;
int AnzahlaL = 0;
int richtung_S[numSensors];
bool aufLinie;
bool lastLineStat;
bool turntoB = false;
unsigned long startTurning = 0;
unsigned long a;
double KoordinatenSens[numSensors][2] = {
  {0, -1000},
  {0, -1500},
  {0, -1750},
  {0, -2250},
  {200, -2875},
  { -200, -2875},
  { -550.5, -2827.5},
  { -937, -2724},
  { -1263.5, -2589},
  { -1610, -2389},
  { -1890.5, -2173.5},
  { -2173.5, -1890.5},
  { -2389, -1610},
  { -2589, -1263.75},
  { -2724, -937},
  { -2827.75, -550.75},

  {0, 1000},
  {0, 1500},
  {0, 1750},
  {0, 2250},
  { -200, 2875},
  {200, -2875},
  {551, 2828},
  {937, 2724},
  {1264, 2589},
  {1610, 2389},
  {1891, 2173},
  {2173, 1890},
  {2389, 1610},
  {2589, 1263.7995},
  {2724, 937},
  {2827.75, 550.75},

  { -1000, 0},
  { -1500, 0},
  { -1750, 0},
  { -2250, 0},
  { -2875, -200},
  { -2875, 200},
  { -2827.75, 550.75},
  { -2724, 937},
  { -2589, 1263.75197},
  { -2389, 1610},
  { -2173.5, 1890.5},
  { -1890.5, 2173.5},
  { -1610, 2389},
  { -1263.75, 2589},
  { -937, 2724},
  { -550.75, 2827.5},

  {1000, 0},
  {1500, 0},
  {1750, 0},
  {2250, 0},
  {2875, 200},
  {2875, -200},
  {2827.75, -550.75},
  {2724, -937},
  {2589, -1263.75},
  {2389, -1610},
  {2173.5, -1890.5},
  {1890.5, -2173.5},
  {1610, -2389},
  {1263.75, -2589},
  {937, -2724},
  {550.75, -2827.75},
};

const double KoordinatenSensCopy[numSensors][2] = {
  {0, -1000},
  {0, -1500},
  {0, -1750},
  {0, -2250},
  {200, -2875},
  { -200, -2875},
  { -550.5, -2827.5},
  { -937, -2724},
  { -1263.5, -2589},
  { -1610, -2389},
  { -1890.5, -2173.5},
  { -2173.5, -1890.5},
  { -2389, -1610},
  { -2589, -1263.75},
  { -2724, -937},
  { -2827.75, -550.75},

  {0, 1000},
  {0, 1500},
  {0, 1750},
  {0, 2250},
  { -200, 2875},
  {200, -2875},
  {551, 2828},
  {937, 2724},
  {1264, 2589},
  {1610, 2389},
  {1891, 2173},
  {2173, 1890},
  {2389, 1610},
  {2589, 1263.7995},
  {2724, 937},
  {2827.75, 550.75},

  { -1000, 0},
  { -1500, 0},
  { -1750, 0},
  { -2250, 0},
  { -2875, -200},
  { -2875, 200},
  { -2827.75, 550.75},
  { -2724, 937},
  { -2589, 1263.75197},
  { -2389, 1610},
  { -2173.5, 1890.5},
  { -1890.5, 2173.5},
  { -1610, 2389},
  { -1263.75, 2589},
  { -937, 2724},
  { -550.75, 2827.5},

  {1000, 0},
  {1500, 0},
  {1750, 0},
  {2250, 0},
  {2875, 200},
  {2875, -200},
  {2827.75, -550.75},
  {2724, -937},
  {2589, -1263.75},
  {2389, -1610},
  {2173.5, -1890.5},
  {1890.5, -2173.5},
  {1610, -2389},
  {1263.75, -2589},
  {937, -2724},
  {550.75, -2827.75},
};

//Compass
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
Adafruit_BNO055 gyro = Adafruit_BNO055(55, 0x28, &Wire2);
double ded;
double angle;
double rotationSpeed;
constexpr int anzahlReadings = 8;
double velo[anzahlReadings];
int A;
bool turnOutB;
bool isRotating;
bool startTurnOut;
unsigned long TsTO;
bool lastTurnOut;
unsigned long rotationStartTime;
bool lastStateCom;
unsigned long startZeitUnterSchwellwert = 0; 
bool timerAktiv = false;
unsigned long drehStartZeit = 0;
bool amDrehen = false;
double avg;

//Getter
unsigned long insD = 0;
unsigned long Dauer = 0;
unsigned long Dauer_noB = 0;
unsigned long insD_noB = 0;
unsigned long lastT;
unsigned long lastT_B;
unsigned long Dauer_nb;
unsigned long letzteZeit;

//IR
constexpr int Anzahl_IR = 24;
int IR_V[Anzahl_IR];
int SBest;
int Vbest;
float durchschnitte[8];
int besteGruppe;

//Jetson
#include "JetsonMsg.h"
extern JetsonMsg msg;
double richtung_b;
bool isB;
unsigned long iD = 0;
struct Punkt {
  double x;
  double y;
};
unsigned long schussZeitpunkt = 0;
bool schussWartet = false;
double richtung_d;
double xBall, yBall;
double letzteX, letzteY;
double geschwX;
double geschwY;
bool attackGch = false;
bool yGd, bGd;
int absoluterWinkel;
unsigned long vergangen;
unsigned long vorwaerts;

//Knöpfe
int K1 = 14;
int K2 = 17;
int K3 = 32;
unsigned long letzteZeit_ball;

//Lichtschranke
int LS_Pin = A12;
bool b_kuhle;
constexpr int wertemenge = 5;
int readings[wertemenge];
int number = 0;
constexpr int wertemenge2 = 4;
int avg_r[wertemenge2];
int number_d = 0;
int bestV = 0;
bool letzteLS = 0;

//Motoren
const int A_Motoren = 4;
int M_DIR[A_Motoren] = {30, 27, 34, 35};
int M_PWM[A_Motoren] = {29, 28, 33, 36};
int M_En = 31;
int D_FW = 38;
int D_RV = 39;
int D_PWM = 37;
constexpr byte mVl = 0, mHl = 2, mVr = 1, mHr = 3;
double Motor_Wert[A_Motoren];
int MWg[A_Motoren];
double Motor_WertD;
double richtung, drehung, geschw;
bool m_state;
bool Motor_an;
unsigned long zeitMotorKnopf;

//Multiplexer
int MuxSig0_B = 3;
int MuxSig1_B = 1;
int MuxSig2_B = 2;
int MuxSig3_B = 0;
int MuxSig0_IR = 10;
int MuxSig1_IR = 9;
int MuxSig2_IR = 7;
int MuxSig3_IR = 8;
int SigMux0_B = A6;
int SigMux1_B = A8;
int SigMux2_B = A9;
int SigMux3_B = A7;
int SigMux1_IR = A4;
int SigMux2_IR = A5;

//NRF24L01
bool bV;

//Schuss
int Schuss_pin = 40;
unsigned long zeit_Schuss;
unsigned long zeit_Schuss2;

void setup() {
  Wire2.begin();
  Serial.begin(115200);
  analogWriteResolution(12);
  gyro.begin();//8
  m_state = false;

  //Pinmodes
  for (int i = 0; i < A_Motoren; i++) {
    pinMode(M_DIR[i], OUTPUT);
  }
  pinMode(D_FW, OUTPUT);
  pinMode(D_RV, OUTPUT);
  pinMode(M_En, OUTPUT);
  pinMode(MuxSig0_B, OUTPUT);
  pinMode(MuxSig1_B, OUTPUT);
  pinMode(MuxSig2_B, OUTPUT);
  pinMode(MuxSig3_B, OUTPUT);
  pinMode(MuxSig0_IR, OUTPUT);
  pinMode(MuxSig1_IR, OUTPUT);
  pinMode(MuxSig2_IR, OUTPUT);
  pinMode(MuxSig3_IR, OUTPUT);
  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K3, INPUT_PULLUP);
  pinMode(Schuss_pin, OUTPUT);
  memset(readings, 0, sizeof(readings));
  memset(avg_r, 0, sizeof(avg_r));
  memset(velo, 0, sizeof(velo));
  bV = true;
}

void loop() {
  //rausdrehen();
  turnOut = false;
  updateJetson();
  IrRead();
  read_sens();
  //LSD();
  compassVorbereitung();
  Print();
  LS();
  dribbler();
  SchussSetzen();
  SchussSetzen2();
  Motor();
  cam_V2();
  bodenControl();
  bV = true;
  /*Serial.println(digitalRead(41));
  if (digitalRead(41) == 1) {
    bV = true;
    //Goalie();
  }
  else if (digitalRead(41) == 0){
    for(int i = 0; i < A_Motoren; i++){
      Motor_Wert[i] = 0;
    }
    Motor_WertD = 0;
    digitalWrite(Schuss_pin, LOW);
  }*/
  last_drehung = drehung;
}
