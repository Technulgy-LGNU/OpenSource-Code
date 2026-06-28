bool ausrichten = false;
int absoluterWinkelHinten;
int winkelTorHinten;
int anySeen;
double dirAktive;
bool limiter;
bool b_vorne;
int sizeG;
double lastDrehung;
int richtungFcA;
int richtungFcG;
int geschwA;
int geschwG;
double richtung_l;
#include <math.h>
bool k1WarGedrueckt = false;

//Boden woanders gespeichert
constexpr int numSensors = 64;
int BodenSens[numSensors];
int sw = 670;//725
int worstVL[numSensors]; // Speichert den jeweils niedrigsten Wert

int bestVL[numSensors];
int sw2[numSensors];
int xCord[numSensors];
int yCord[numSensors];
bool noB;

const double KoordinatenSens[numSensors][2] = {
  {31, 0.1},
  {40.25, 0},
  {46.355, 0},
  {55.575, 0},
  {71.1, 22.675},
  {72.9, 15.9},
  {74.55, 3.5},
  {74.55, -3.5},
  { 72.9, -15.9},
  { 71.1, -22.675},
  { 66.31, -34.2},
  { 62.8, -40.3},
  { 55.18, -50.24},
  { 50.24, -55.18},
  { 40.3, -62.8},
  { 34.24, -66.3},

  {0, -31},
  {0, -40.25},
  {0, -46.36},
  {0, -55.57},
  {22.67, -61.1},
  {15.9, -72.9},
  {3.5, -74.55},
  { -3.5, -74.55},
  { -40.3, -62.8},
  { -34.24, -66.31},
  { -22.67, -71.1},
  { -15.9, -72.9},
  { -50.2, -55.2},
  { -55.2, -50.2},
  { -62.8, -40.3},
  { -66.3, -34.24},

  { -0.1, 31},
  { 0, 40.25},
  { 0, 46.335},
  { 0, 55.6},
  { -22.67, 71.1},
  { -15.9, 72.9},
  { -3.5, 74.55},
  { 3.5, 74.55},
  { 40.3, 62.8},
  { 34.24, 66.3},
  { 22.67, 71.1},
  { 15.9, 72.9},
  { 50.23, 55.2},
  { 55.2, 50.23},
  { 62.8, 40.3},
  { 66.3, 34.24},

  { -31, 0},
  { -40.25, 0},
  { -46.335, 0},
  { -55.5752, 0},
  { -71.1, -22.67},
  { -72.9, -15.9},
  { -74.55, -3.5},
  { -74.55, 3.5},
  { -62.8, 40.3},
  { -66.31, 34.24},
  { -71.1, 22.67},
  { -72.9, 15.9},
  { -55.1, 50.24},
  { -50.23, 55.2},
  { -40.3, 62.8},
  { -34.24, 66.31},
};

//Buzzer
int buzzer = 32;

//Compass
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
Adafruit_BNO055 gyro = Adafruit_BNO055(55, 0x28, &Wire1);
double ded;
double angle;
double rotationSpeed;

//Com_Module
int comModule = 6;
bool lastCM;

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
constexpr int Anzahl_IR = 16;
int IR_V[Anzahl_IR];
int SBest;
int Vbest;
int richtungIR;
float durchschnitte[8];
int besteGruppe;

//Jetson
#include "JetsonMsg.h"
extern JetsonMsg msg;
double richtung_b;
bool isB;
int zeit_l;
unsigned long iD = 0;
struct Punkt {
  double x;
  double y;
};
double richtung_d;
double xBall, yBall;
char attackGoal = 'g';
bool attackGch = true;
bool defenseGoalch = true;
int xG, yG;
bool yGd, bGd;
bool vorG;
bool noV;
bool ballV;
int lastX;
int lastY;
bool schussWartet = false;
unsigned long schussZeitpunkt;

//Knöpfe
int K1 = 23;
int K2 = 22;
int K3 = 0;
int K4 = 1;
unsigned long letzteZeit_ball;

//Lichtschranke
int LS_Pin = A17;
bool b_kuhle;
constexpr int wertemenge = 5;
int readings[wertemenge];
int number = 0;
constexpr int wertemenge2 = 2;
int avg_r[wertemenge2];
int number_d = 0;
int bestV = 0;
bool letzteLS = 0;
int avgL;
constexpr int wm3 = 3;
int d_d[wm3];
int numberd_d = 0;
int avgd_d[wm3];
int avgLs;
unsigned long lastPulseTime = 0;
const unsigned long nachlaufZeit = 250;
const int schwellenwert = 140;
  // Diese Variablen müssen global (außerhalb der Funktion) definiert sein,
// damit sie ihren Wert zwischen den Durchläufen nicht verlieren:
bool last_state = false;
int last_speed = 0;

//Motoren
#include "ESC.h"
const int A_Motoren = 4;
int M_DIR[A_Motoren] = {40, 38, 4, 2};
int M_PWM[A_Motoren] = {37, 36, 5, 3};
int M_En = 39;
constexpr byte mVl = 1, mHl = 0, mVr = 3, mHr = 2;
int D_PWM = 33;
#define SPEED_MIN (1000)         // Minimale Geschwindigkeit in Mikrosekunden
#define SPEED_MAX (1900)   

ESC myESC (33, SPEED_MIN, SPEED_MAX, 500); // ESC Konfiguration
int speedD = SPEED_MIN;      
int speedAktuell;
double Motor_Wert[A_Motoren];
double Motor_WertD;
double richtung, drehung, geschw;
int MWg[A_Motoren];
bool m_state;
bool Mot_Stop[4];
bool switchRole = false;
unsigned long zeitSwitch = 8001;
unsigned long zeitMotorenaus;
bool timerrunning;
unsigned long attackStart;
unsigned long MotorAus;
bool Motor_an = false;
unsigned long startKnopf;

//Multiplexer
int MuxSig0_B = 28;
int MuxSig1_B = 29;
int MuxSig2_B = 30;
int MuxSig3_B = 31;
int MuxSig0_IR = 14;
int MuxSig1_IR = 15;
int MuxSig2_IR = 18;
int MuxSig3_IR = 19;
int SigMux0_B = A10;
int SigMux1_B = A11;
int SigMux2_B = A12;
int SigMux3_B = A13;
int SigMux_IR = A6;
bool bV;

bool bSens[numSensors];

//Neopixels
#include <Adafruit_NeoPixel.h>

#define PIN        21  // Der Pin, an dem DIN angeschlossen ist
#define NUMPIXELS 4   // Deine LED-Anzahl

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 40;         // Blinz-Geschwindigkeit in ms (kleiner = schneller)
bool ledStatus = false;           // Merkt sich, ob die LEDs an oder aus sind
bool showLeds = true;

//Schuss
int Schuss_pin = 35;
unsigned long zeit_Schuss;
long vorwaerts;
int absoluterWinkel;
long vergangen;

int x_ga;
int y_ga;
int x_gg;
int y_gg;
int sizeGa;
unsigned long anzahlJetson = 0;
unsigned long stillstandStartZeit;
bool isImAngriff;
unsigned long angriffStartZeit;
void setup() {
  Wire1.begin();
  Serial.begin(115200);
  //For ESP
  Serial2.begin(115200);
  analogWriteResolution(12);
  gyro.begin();//8
  myESC.arm();
  digitalWrite(13, HIGH);
  myESC.speed(1000);
  //delay(5000);
  m_state = false;

  for (int i = 0; i < numSensors; i++) {
    sw2[i] = 500;
    bestVL[i] = 20;
  }

  bV = false;
  //Pinmodes
  for (int i = 0; i < A_Motoren; i++) {
    pinMode(M_DIR[i], OUTPUT);
  }
  pinMode(M_En, OUTPUT);
  pinMode(33, OUTPUT);
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
  pinMode(K4, INPUT_PULLUP);
  pinMode(SigMux0_B, INPUT);
  pinMode(SigMux1_B, INPUT);
  pinMode(SigMux2_B, INPUT);
  pinMode(SigMux3_B, INPUT);
  pinMode(Schuss_pin, OUTPUT);
  memset(readings, 0, sizeof(readings));
  memset(avg_r, 0, sizeof(avg_r));
  memset(d_d, 0, sizeof(d_d));
  strip.begin();
  strip.show();
}

void loop() {
  if(anzahlJetson > 15 && anzahlJetson < 50){
      for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));
  }
  strip.show();
  strip.clear();
  }
  updateJetson();
  neo();
  read_sens();
  IRRead();
  bodenControl();
  Knob();
  wechsel();
  compassVorbereitung();
  Motor();
  SchussSetzen();
  LS();
  dribbler();
  x_ga = msg.GoalYx;
  y_ga = msg.GoalYy;
   if (digitalRead(K2) == LOW) {
     defenseGoalch = !defenseGoalch;
     attackGch = !attackGch;
     delay(350);
    }
    if (defenseGoalch == false) {
     x_gg = msg.GoalBx;
     y_gg = msg.GoalBy;
    }
    else {
     x_gg = msg.GoalYx;
     y_gg = msg.GoalYy;
    }
    //Serial.println(msg.GoalBw * msg.GoalBh);
  // Serial.println(bV);
  speedAktuell = speedD;
  lastDrehung = drehung;
  lastCM = digitalRead(comModule);
}
