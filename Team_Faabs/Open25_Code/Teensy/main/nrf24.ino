long last_available;

void nrf_setup() {

  // Initialize radio
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
  }

  // Enhanced radio configuration
  radio.setRetries(15, 15);
  radio.setAutoAck(true);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(76);

  // Configure radio pipes based on device role
  if (IS_TRANSMITTER) {
    radio.openWritingPipe(addresses[1]);     // Write to "00002"
    radio.openReadingPipe(1, addresses[0]);  // Read from "00001"
    listenMode = false;
    Serial.println("Configured as Transmitter (Version A)");
  } else {
    radio.openWritingPipe(addresses[0]);     // Write to "00001"
    radio.openReadingPipe(1, addresses[1]);  // Read from "00002"
    listenMode = true;
    radio.startListening();
    Serial.println("Configured as Receiver (Version B)");
  }

  Serial.println("nrf Setup complete");
}
void updateAnalogValue() {
  analogValue_Send = ball::ball_est(ball::ball);
}

void processIncomingData() {
  byte receivedByte = communicate_receive();
  if (receivedByte != 255) {
    last_available = millis();  // Update timing
    byte rea = receivedByte;    // Use received byte directly
    
    if (rea == 0) {
      m = 1;
    }
    else if (rea < ball::ball_est(ball::ball)) {
      m = 1;
    }
    else {
      m = 0;
    }
  }
  
  constexpr int blootot = 300;
  if (millis() - last_available > blootot) {
    m = 1;
  }
  
  Serial.print("Mode (0 GOALIE and 1 STRIKER): ");
  Serial.println(m);
}

bool communicate_send(byte input) {
  // Internal timing logic - decide if we should send
  bool shouldSend = false;

  if (IS_TRANSMITTER) {
    shouldSend = !waitingForResponse && (millis() - lastSendTime >= sendInterval);
  } else {
    shouldSend = !waitingForResponse && hasNewData && (millis() - lastSendTime >= sendInterval);
  }

  if (shouldSend) {
    radio.stopListening();
    listenMode = false;

    bool result = radio.write(&input, sizeof(input));
    totalSent++;

    lastSendTime = millis();
    lastReceiveTime = millis();
    waitingForResponse = true;
    hasNewData = false;

    radio.startListening();
    listenMode = true;

    return true;
  }

  return false;
}

byte communicate_receive() {

  static byte lastReceivedValue = 0;

  if (IS_TRANSMITTER) {

    if (waitingForResponse && listenMode) {
      if (radio.available()) {
        byte receivedValue;
        radio.read(&receivedValue, sizeof(receivedValue));
        lastReceivedValue = receivedValue;
        totalReceived++;
        waitingForResponse = false;

        return receivedValue;
      } else if (millis() - lastReceiveTime >= receiveTimeout) {
        waitingForResponse = false;
        timeouts++;
        return 255;  // Return 255 as error code
      }
    }
  } else {
    if (listenMode && !waitingForResponse) {
      if (radio.available()) {
        byte receivedValue;
        radio.read(&receivedValue, sizeof(receivedValue));
        lastReceivedValue = receivedValue;
        totalReceived++;
        hasNewData = true;

        return receivedValue;
      }
    }

    if (waitingForResponse && (millis() - lastReceiveTime >= receiveTimeout)) {
      waitingForResponse = false;
    }
  }

  return lastReceivedValue;  // Return last known value
}
void attemptSend() {
  communicate_send(analogValue_Send);  // ← Send directly, no mapping needed
}
