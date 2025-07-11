/*
  GPIO controll, to read Buttons, Dipswitches and Lightsenors on the floor to detect the line
*/


constexpr byte mainMotorBtnPin = 17;

constexpr byte btnKompass = 32;


constexpr int IR_LED = 23;    // Output to MOSFET gate for IR LED (38kHz or 40kHz PWM)
constexpr int SchusstestBtnPin = 37;    // Ball_indicator
constexpr int OnGoalBtnPin = 10;    //
//add Neopixels


bool Lightbarrier() {
  analogWrite(IR_LED, 4096);
  //Serial.println(analogRead(A8));
  constexpr int lsw = 10;
  if (analogRead(A8) < lsw) {
    return true;
  }

  else {
    last_ls_not_in = millis();
    return false;
  }
}

bool Schusstest(){
  if(digitalRead(SchusstestBtnPin) == LOW) return true;
  else return false;
}

bool OnGoal(){
  if(digitalRead(OnGoalBtnPin) == LOW) return true;
  else return false;
}

void GPIOsetup() {

  //SET SCHWELLWERTE
  for (int i = 0; i < 92; i++) {
    Bodensens[i] = 0;
    sw[i] [RobotNB] = Schwellwert;
  }
  set_SW();

  //LIGHT BARRIER
  pinMode(IR_LED, OUTPUT);
  analogWriteFrequency(IR_LED, 40000);
  analogWrite(IR_LED, 255); //maybe 50% duty cycle and better method

  //BUTTONS
  pinMode(btnMuxPin, INPUT_PULLUP);
  pinMode(mainMotorBtnPin, INPUT_PULLUP);
  pinMode(btnKompass, INPUT_PULLUP);

  //DEBUG-LEDS
  pinMode(SchusstestBtnPin, INPUT_PULLUP);
  pinMode(OnGoalBtnPin,INPUT_PULLUP);
  //add Neopixels

  //MUXPINS
  for (int i = 0; i < 4; i++) {
    pinMode(muxPins[i], OUTPUT);
  }
}
