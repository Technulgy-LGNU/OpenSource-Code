// RawHID packets are always 64 bytes
byte bytes[64];

JetsonMsg msg(false);

void updateJetson() {
  isB = getBallda(msg.isBall);
  if (isB) {
    int xKoordinaten = msg.Xx - 408;
    int yKoordinaten = msg.Yy - 308;
    richtung_b = (atan2(yKoordinaten, xKoordinaten) * 180 / PI);
    if (richtung_b < 0) {
      richtung_b += 360;
    }
  }
  yGd = getIsYellowGda(msg.isGoalY);
  bGd = getIsBlueGda(msg.isGoalB);
  if (RawHID.recv(bytes, 0)) {
    anzahlJetson++;
    bool ob = (((bytes[0] >> 0) & ((1 << 1) - 1)) << 0) != 0;
    uint16_t ox = ((bytes[0] >> 1) & ((1 << 6) - 1)) << 0 | ((bytes[1] >> 0) & ((1 << 4) - 1)) << 6;
    uint16_t oy = ((bytes[1] >> 4) & ((1 << 3) - 1)) << 0 | ((bytes[2] >> 0) & ((1 << 7) - 1)) << 3;
    uint16_t ow = ((bytes[3] >> 0) & ((1 << 7) - 1)) << 0 | ((bytes[4] >> 0) & ((1 << 3) - 1)) << 7;
    uint16_t oh = ((bytes[4] >> 3) & ((1 << 4) - 1)) << 0 | ((bytes[5] >> 0) & ((1 << 6) - 1)) << 4;
    bool yb = (((bytes[5] >> 6) & ((1 << 1) - 1)) << 0) != 0;
    uint16_t yx = ((bytes[6] >> 0) & ((1 << 7) - 1)) << 0 | ((bytes[7] >> 0) & ((1 << 3) - 1)) << 7;
    uint16_t yy = ((bytes[7] >> 3) & ((1 << 4) - 1)) << 0 | ((bytes[8] >> 0) & ((1 << 6) - 1)) << 4;
    uint16_t yw = ((bytes[8] >> 6) & ((1 << 1) - 1)) << 0 | ((bytes[9] >> 0) & ((1 << 7) - 1)) << 1 | ((bytes[10] >> 0) & ((1 << 2) - 1)) << 8;
    uint16_t yh = ((bytes[10] >> 2) & ((1 << 5) - 1)) << 0 | ((bytes[11] >> 0) & ((1 << 5) - 1)) << 5;
    bool bb = (((bytes[11] >> 5) & ((1 << 1) - 1)) << 0) != 0;
    uint16_t bx = ((bytes[11] >> 6) & ((1 << 1) - 1)) << 0 | ((bytes[12] >> 0) & ((1 << 7) - 1)) << 1 | ((bytes[13] >> 0) & ((1 << 2) - 1)) << 8;
    uint16_t by = ((bytes[13] >> 2) & ((1 << 5) - 1)) << 0 | ((bytes[14] >> 0) & ((1 << 5) - 1)) << 5;
    uint16_t bw = ((bytes[14] >> 5) & ((1 << 2) - 1)) << 0 | ((bytes[15] >> 0) & ((1 << 7) - 1)) << 2 | ((bytes[16] >> 0) & ((1 << 1) - 1)) << 9;
    uint16_t bh = ((bytes[16] >> 1) & ((1 << 6) - 1)) << 0 | ((bytes[17] >> 0) & ((1 << 4) - 1)) << 6;

    msg = {true, ob, ox, oy, ow, oh, yb, yx, yy, yw, yh, bb, bx, by, bw, bh};
  }
  else {
    msg =  {false};
  }
}
