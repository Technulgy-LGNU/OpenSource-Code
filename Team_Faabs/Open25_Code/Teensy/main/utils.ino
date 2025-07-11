int lidar_rot_correction(int input, double phi) {
  return roundToNearest10(phi + (input * 10));
}

int roundToNearest10(double value) {
  int zwischenergenis = ((value + 5) / 10) ;

  zwischenergenis = 36 - zwischenergenis;
  if (zwischenergenis > 35)zwischenergenis =  zwischenergenis - 36;
  return zwischenergenis;
}

void controll_ongoal() {
  if (OnGoal()) {
    onGoal = !onGoal;
    if (onGoal)Neo::flash(Neo::nblue, 500);
    else Neo::flash(Neo::nyellow, 500);
    delay(300);
  }
}


bool isDirectionMatch(float dir1, float dir2, float toleranceDegrees) {
  // Normalize angles to the range [0, 360)
  dir1 = fmod(dir1, 360.0);
  if (dir1 < 0) dir1 += 360.0;

  dir2 = fmod(dir2, 360.0);
  if (dir2 < 0) dir2 += 360.0;

  // Calculate the smallest difference between the two directions
  float diff = fabs(dir1 - dir2);
  if (diff > 180.0) {
    diff = 360.0 - diff;
  }
  if (diff < -180) {
    diff += 360;
  }
  // Check if the difference is within the allowed tolerance
  return diff <= toleranceDegrees;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

double clampValue(double x, double g) {
  return max(-g, min(x, g));
}

float smoothAngle(float newAngle, float smoothedAngle, float smoothingFactor) {
  float x = (1 - smoothingFactor) * cos(radians(smoothedAngle)) + smoothingFactor * cos(radians(newAngle));
  float y = (1 - smoothingFactor) * sin(radians(smoothedAngle)) + smoothingFactor * sin(radians(newAngle));

  float result = degrees(atan2(y, x));
  return (result >= 0) ? result : (result + 360);  // Ensure 0-360° range
}

float smoothVelocity(float newVelocity, float smoothedVelocity, float smoothingFactor) {
  return (1 - smoothingFactor) * smoothedVelocity + smoothingFactor * newVelocity;
}

double computeVectorAngle(double x_c, double y_c, double r, double x, double y) {
  double d = hypot(x - x_c, y - y_c);  // Abstand zum Kreismittelpunkt

  // Verhindere Division durch 0
  if (isnan(d) || d == 0) d = 1e-6;

  double angle;

  if (d > r) {
    // Tangentenwinkel berechnen
    double theta = atan2(y - y_c, x - x_c);
    double alpha = asin(constrain(r / d, -1.0, 1.0));  // Schutz vor NaN
    angle = M_PI + theta + alpha;                      // Winkel der Tangente
  } else {
    // Spiegelung berechnen
    double theta = atan2(y - y_c, x - x_c);
    double i_c_x = cos(theta) * d, i_c_y = sin(theta) * d;                      // Punkt im Kreis
    double o_c_x = cos(theta) * (2 * r - d), o_c_y = sin(theta) * (2 * r - d);  // Spiegelpunkt

    // Falls Werte NaN sind, Abbruch und Default-Wert zurückgeben
    if (isnan(i_c_x) || isnan(i_c_y) || isnan(o_c_x) || isnan(o_c_y)) return 0.0;

    // Spiegelmatrix-Berechnung
    double theta3 = atan2(i_c_y - y_c, i_c_x - x_c);
    double S11 = cos(2 * theta3), S12 = sin(2 * theta3);
    double S21 = sin(2 * theta3), S22 = -cos(2 * theta3);

    // Gespiegelter Tangentenwinkel
    double theta_sp = atan2(o_c_y - y_c, o_c_x - x_c);
    double denom = hypot(o_c_x - x_c, o_c_y - y_c);

    // Verhindere NaN durch ungültige Werte in asin()
    if (isnan(denom) || denom == 0) denom = 1e-6;
    double alpha_sp = asin(constrain(r / denom, -1.0, 1.0));
    double theta1_sp = M_PI + theta_sp + alpha_sp;

    // Transformation des Winkels
    double new_x = -(S11 * cos(theta1_sp) + S12 * sin(theta1_sp));
    double new_y = -(S21 * cos(theta1_sp) + S22 * sin(theta1_sp));

    // Verhindere NaN in atan2()
    if (isnan(new_x) || isnan(new_y)) return 0.0;

    angle = atan2(new_y, new_x);
  }
  return angle;
}
