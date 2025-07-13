//Emanuel
bool RoboterNum = 1; // 1 für Schwarz 0 für weiß


//Lichtschranke
constexpr int Ls = A12;
bool ik;


//US
#include <SonarSRF.h>
#define GAIN 0x09
#define RANGE 0x8C

SonarSRF08 mySonar1(&Wire, 0xE0, GAIN, RANGE);
SonarSRF08 mySonar2(&Wire, 0xE2, GAIN, RANGE);
SonarSRF08 mySonar3(&Wire, 0xE4, GAIN, RANGE);
SonarSRF08 mySonar4(&Wire, 0xFE, GAIN, RANGE);

constexpr int AnzahlUS = 4;
int US_V[AnzahlUS];
int BreiteFeld = 180;
int HöheFeld = 240;
int sumX;
int sumY;
int XCord;
int YCord = 0;
int lastX;
bool sumx = false;
int dis;
bool simpel;

//Kompass
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
double rotationspeed2;
double winkel2;
double drehung2;
bool openmv_an;
int sizeofGoal;

Adafruit_BNO055 gyro = Adafruit_BNO055(55, 0x28, &Wire);
double minus;


//Funkmodul
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// nRF24L01 Pins
#define CE_PIN   9
#define CSN_PIN  27

// NODE_ID ändern: 1 für ersten Teensy, 2 für zweiten Teensy
#define NODE_ID 1

RF24 radio(CE_PIN, CSN_PIN);

// Adressen
const byte address1[] = "Node1";
const byte address2[] = "Node2";

// Deine Boolean-Variable
bool meinBoolWert = false;
bool letzterBoolWert = false;


//Boden
constexpr int numSensors = 64;  // Anzahl der Sensoren
int BodenSens[numSensors];      // Array für die Sensorwerte
int threshold = 500;            // Schwellenwert für die Linie
int firstActiveSensor = -1;     // Index des ersten aktivierten Sensors
bool AufLinie;
long ZeitAufLinie;
int xCord[numSensors];
int yCord[numSensors];
double test;
bool a[64];

// Array mit den Richtungen für jeden Sensor
const int KoordinatenSens[numSensors][2] = {
  { -550, 2650},
  { -250, 2700},
  {250, 2700},
  {550, 2650},
  {1000, 2800},
  {1600, 3300},
  {3950, 625},
  { -1000, 2800},
  {4000, -350},
  {4000, 350},
  { -1600, 3350},
  {3750, 225},
  {3375, 525},
  {2900, 700},
  {2500, 2000},
  {2000, 2500},

  {350, -4000},
  { -350, -4000},
  { -625, -3950},
  { -1275, -3800},
  { -1525, -3375},
  { -1650, -2850},
  {0, 0 },
  {0, 0 },
  {625, -3950},
  {1225, -3850},
  {1475, -3375},
  {1650, -2850},
  {2000, -2500},
  {2500, -2000},
  {2800, -1600},
  {3375, -1475},

  { -3950, 625},
  { -3800, 325},
  { -3375, 525},
  { -2900, 700},
  { -2500, 2000},
  { -2000, 2500},
  { -225, 550},
  { -225, 100},
  { -4000, 350},
  { -4000, -350},
  { -3900, -625},
  { -3750, -1225},
  { -3375, -1475},
  { -2800, -1600},
  { -2500, -2000},
  { -2000, -2500},

  {3950, -625},
  {3750, -1225},
  {2900, 350},
  {2450, 350},
  {1900, 350},
  {1450, 350},
  { -1450, 350},
  { -1900, 350},
  { -2450, 350},
  { -275, -1975},
  { -275, -1425},
  { -275, -975},
  { -2900, 350},
  { -275, -2425},
  {0, 0 },
  {0, 0 },
};


//Motoren
const int AnzahlBLMotoren = 4;
int M_DIR[AnzahlBLMotoren] = {32, 30, 1, 20};
int M_PWM[AnzahlBLMotoren] = {29, 28, 4, 22};
constexpr byte mVl = 1, mHl = 0, mVr = 3, mHr = 2;
double Motor_Wert[AnzahlBLMotoren];
double Schuss_M;
double richtung, drehung, geschw;
int gerundet[AnzahlBLMotoren];
int M_En = 31;
bool m_state;
int dribbler_fw = 7;
int dribbler_rw = 8;
int dribbler_pwm = 6;


//Knöpfe
int K1 = 3;
int K2 = 2;
int K3 = 0;


//IR
const int NumberofSensors = 16;
const int Both = 32;
int lowMap[Both];
int mapped[16];
int IR[NumberofSensors];
int SEbest;
int IRbest;
int Irbest[16];
int receivedIRbest = 0;
int slow;
int schnell;
int hinten;
int mid;
int useIRbest;
bool IR_an;
byte byteRead;
bool vorne;
bool h;
bool l;
bool r;

const int lowestValue1[16] = {424, 436, 439, 434, 435, 433, 432, 381, 433, 440, 458, 437, 438, 438, 446, 441};
const int lowestValue2[16] = {424, 436, 439, 434, 435, 433, 432, 381, 433, 440, 458, 437, 438, 438, 446, 441};

const int highestValue1[16] = {424, 436, 439, 434, 435, 433, 432, 381, 433, 440, 458, 437, 438, 438, 446, 441};
const int highestValue2[16] = {424, 436, 439, 434, 435, 433, 432, 381, 433, 440, 458, 437, 438, 438, 446, 441};


//Multiplexer
constexpr int MuxSig0 = 39;
constexpr int MuxSig1 = 38;
constexpr int MuxSig2 = 37;
constexpr int MuxSig3 = 36;
constexpr int Sig_MUX5 = 41; //IR
constexpr int Sig_MUX3 = 14;
constexpr int Sig_MUX2 = 15;
constexpr int Sig_MUX1 = 16;
constexpr int Sig_MUX0 = 17;


//OpenMV
int winkel;
bool torwarttor;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial8.begin(19200);
  analogWriteResolution(12);

  pinMode(M_DIR[0], OUTPUT);
  pinMode(M_DIR[1], OUTPUT);
  pinMode(M_DIR[2], OUTPUT);
  pinMode(M_DIR[3], OUTPUT);
  pinMode(M_En, OUTPUT);

  pinMode(K1, INPUT_PULLUP);
  pinMode(K2, INPUT_PULLUP);
  pinMode(K3, INPUT_PULLUP);

  pinMode(MuxSig0, OUTPUT);
  pinMode(MuxSig1, OUTPUT);
  pinMode(MuxSig2, OUTPUT);
  pinMode(MuxSig3, OUTPUT);

  pinMode(dribbler_fw, OUTPUT);
  pinMode(dribbler_rw, OUTPUT);

  m_state = false;
  openmv_an = true;
  gyro.begin(8);

  // nRF24L01 initialisieren
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(3);

  // Adressen setzen
  if (NODE_ID == 1) {
    radio.openWritingPipe(address2);     // Node1 sendet an Node2
    radio.openReadingPipe(1, address1);  // Node1 empfängt von Node1
  } else {
    radio.openWritingPipe(address1);     // Node2 sendet an Node1
    radio.openReadingPipe(1, address2);  // Node2 empfängt von Node2
  }

  radio.startListening();

  for (int i = 0; i < 16; i++) {
    Irbest[i] = 1001;
  }
}

void loop() {
  long timer = millis();
  //openmv_read();
  compassVorbereitung();
  compass();
  IR_READ();
  Bodenread2();
  bodenControl2();
  US();
  //velo_math();
  //LS();
  torwart();
  Motor();
  Print();
  /*Serial.print("Time: ");
    Serial.println(millis() - timer);*/
}
