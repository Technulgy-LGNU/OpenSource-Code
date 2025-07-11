/*
  jetson message interpretation, decodes the data which was send by the jetson via USB (RawHID)
*/

#define NUM_BINS 36 // see lidar/jetson program
uint8_t distances[NUM_BINS] = {0};

namespace jetson {
Msg receive() {
  // RawHID packets are always 64 bytes
  byte bytes[64];
  if (RawHID.recv(bytes, 0)) {

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

    for (int i = 0; i < NUM_BINS; i++) {
      distances[i] = bytes[18 + i];
    }

    /*Serial.print("distanz:");
      Serial.println(distances[9]);
    */
    return { true, ob, ox, oy, ow, oh, yb, yx, yy, yw, yh, bb, bx, by, bw, bh};
  }
  else {
    return { false };
  }
}
}
