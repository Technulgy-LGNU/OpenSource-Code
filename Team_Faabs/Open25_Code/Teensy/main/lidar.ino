
namespace lidar {
void printPosition() {

  Serial.println("LIDAR Position");

  Serial.print("x:");
  Serial.println(dx);

  Serial.print("y:");
  Serial.println(dy);

  Serial.println("-----------");

  /*
    Serial.println("reference X");
    Serial.println(SumX);

    Serial.println("right side X");
    Serial.println(SumX1r);

    Serial.println("left side X");
    Serial.println(SumX1l);
  */
}

constexpr int FeldLaenge = 240, FeldBreite = 180, Torbreite = 60, Strafraum = 30;

bool xSum, ySum;
int dx = 0, dy = 0;

constexpr byte lidarLeft = 0, lidarRight = 18, lidarFront = 27, lidarBack = 9;

void lidar() {

  double dd[NUM_BINS];
  for (size_t i = 0; i < NUM_BINS; i++) {
    dd[i] = distances[i];
  }

  double phi = kompass::offset(kompass::gyro_a, kompass::minus); //angle from 0 to 360 for robot orientation to straight
  double phi_r = phi / 180 * PI;


  // === X DIRECTION ===
  double SumX = dd[lidar_rot_correction(lidarLeft, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(lidarLeft, phi)))))
                + dd[lidar_rot_correction(lidarRight, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(lidarRight, phi)))));

  double SumX1r = dd[lidar_rot_correction(lidarLeft + 1, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(lidarLeft + 1, phi)))))
                  + dd[lidar_rot_correction(lidarRight + 1, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(lidarLeft + 1, phi)))));

  double SumX1l = dd[lidar_rot_correction(lidarRight - 1, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(35, phi)))))
                  + dd[lidar_rot_correction(35, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(35, phi)))));

  double best_dx = (
                     dd[lidar_rot_correction(lidarLeft, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(lidarLeft, phi)))) -
                     dd[lidar_rot_correction(lidarRight, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(lidarLeft, phi))))
                   ) / 2.0;

  double best_distance_x = abs(SumX - FeldBreite);


  double dist_x1r = abs(SumX1r - FeldBreite);
  if (dist_x1r < best_distance_x) {
    best_dx = (
                dd[lidar_rot_correction(lidarLeft + 1, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(lidarLeft + 1, phi)))) -
                dd[lidar_rot_correction(lidarRight + 1, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(lidarLeft + 1, phi))))
              ) / 2.0;
    best_distance_x = dist_x1r;
  }

  double dist_x1l = abs(SumX1l - FeldBreite);
  if (dist_x1l < best_distance_x) {
    best_dx = (
                dd[lidar_rot_correction(35, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(35, phi)))) -
                dd[lidar_rot_correction(lidarRight - 1, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(35, phi))))
              ) / 2.0;
    best_distance_x = dist_x1l;
  }

  if (best_distance_x <= 25) {
    xSum = true;
    dx = best_dx;
  } else {
    xSum = false;
  }


  // === Y DIRECTION ===
  double SumY = dd[lidar_rot_correction(lidarFront, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(lidarLeft, phi)))))
                + dd[lidar_rot_correction(lidarBack, phi)]  * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(lidarLeft, phi)))));

  double SumY1r = dd[lidar_rot_correction(lidarFront + 1, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(lidarLeft + 1, phi)))))
                  + dd[lidar_rot_correction(lidarBack + 1, phi)]  * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(lidarLeft + 1, phi)))));

  double SumY1l = dd[lidar_rot_correction(lidarFront - 1, phi)]  * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(35, phi)))))
                  + dd[lidar_rot_correction(lidarBack - 1, phi)] * abs(cos(phi_r - (0.1745 * (36 - lidar_rot_correction(35, phi)))));


  double best_dy = (
                     dd[lidar_rot_correction(lidarBack, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(lidarLeft, phi)))) -
                     dd[lidar_rot_correction(lidarFront, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(lidarLeft, phi))))
                   ) / 2.0;

  double best_distance_y = abs(SumY - FeldLaenge);

  double dist_y1r = abs(SumY1r - FeldLaenge);
  if (dist_y1r < best_distance_y) {
    best_dy = (
                dd[lidar_rot_correction(lidarBack + 1, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(lidarLeft + 1, phi)))) -
                dd[lidar_rot_correction(lidarFront + 1, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(lidarLeft + 1, phi))))
              ) / 2.0;
    best_distance_y = dist_y1r;
  }

  double dist_y1l = abs(SumY1l - FeldLaenge);
  if (dist_y1l < best_distance_y) {
    best_dy = (
                dd[lidar_rot_correction(lidarBack - 1, phi)] * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(35, phi)))) -
                dd[lidar_rot_correction(lidarFront - 1, phi)]  * abs(cos(phi_r - 0.1745 * (36 - lidar_rot_correction(35, phi))))
              ) / 2.0;
    best_distance_y = dist_y1l;

  }

  constexpr int tolerance_lidar = 10;
  if (best_distance_y <= tolerance_lidar) {
    ySum = true;
    dy = best_dy;
  } else {
    ySum = false;
  }
  printPosition();

}

double lidar_cap_velo(double inputdir) {

  constexpr int r_max = 60; //cm as max radius
  constexpr int f_rg = 1;
  constexpr int f_ges = 4;

  int xv_l = -dx;
  int yv_l = -dy;

  double xv_r = cos(inputdir / 180 * PI) * r_max * f_rg;
  double yv_r = sin(inputdir / 180 * PI) * r_max * f_rg;

  double xv_v = xv_r + xv_l;
  double yv_v = yv_r + yv_l;

  double maxVelo = 180 + sqrt(xv_v * xv_v + yv_v * yv_v) * f_ges;
  if (sqrt(xv_l * xv_l + yv_l * yv_l) > r_max + 12) maxVelo = 180 + sqrt(xv_v * xv_v + yv_v * yv_v) * f_ges / 3;

  return maxVelo;
}


motor::Anweisung wand() {
  constexpr int ge = 280;  // geschwindigkeit in der Ecke
  constexpr int gs = 200;  // geschwindigkeit an der Seite

  int Linie_Wand = 30;  //(veli > 50) ? 13 + 7 : 13;
  Linie_Wand = 10;
  if (xSum && ySum) {
    // ECKEN
    //
    //  rechts-vorne Ecke (1.Quadrant)
    if ((dx > ((FeldBreite / 2) - Linie_Wand)) && (dy > ((FeldLaenge / 2) - Linie_Wand))) {
      return { .dir = 225, .velo = ge, .dribble = 0, .schuss = 0 };
    }
    // links-vorne Ecke (2.Quadrant)
    else if ((dx < ((-1 * (FeldBreite / 2)) + Linie_Wand)) && (dy > ((FeldLaenge / 2) - Linie_Wand))) {
      return { .dir = 315, .velo = ge, .dribble = 0, .schuss = 0 };
    }
    // links-hinten Ecke (3.Quadrant)
    else if ((dx < ((-1 * (FeldBreite / 2)) + Linie_Wand)) && (dy < ((-1 * (FeldLaenge / 2)) + Linie_Wand))) {
      return { .dir = 45, .velo = ge, .dribble = 0, .schuss = 0 };
    }
    // rechts-hinten Ecke (4.Quadrant)
    else if ((dx > ((FeldBreite / 2) - Linie_Wand)) && (dy < ((-1 * (FeldLaenge / 2)) + Linie_Wand))) {
      return { .dir = 135, .velo = ge, .dribble = 0, .schuss = 0 };
    }

    // SEITEN
    //
    // rechts
    else if (dx > ((FeldBreite / 2) - Linie_Wand)) {
      return { .dir = 180, .velo = gs, .dribble = 0, .schuss = 0 };
    }
    // links
    else if (dx < ((-1 * (FeldBreite / 2)) + Linie_Wand)) {
      return { .dir = 0, .velo = gs, .dribble = 0, .schuss = 0 };
    }
    // hinten
    else if (dy < ((-1 * (FeldLaenge / 2)) + Linie_Wand)) {
      return { .dir = 90, .velo = gs, .dribble = 0, .schuss = 0 };
    }
    // vorne
    else if (dy > ((FeldLaenge / 2) - Linie_Wand + 5)) {
      return { .dir = 270, .velo = gs, .dribble = 0, .schuss = 0 };
    } else {
      return { .dir = 0, .velo = 0, .dribble = 0, .schuss = 0 };
    }
  } else if (xSum && !ySum) {
    // SEITEN
    //
    // rechts
    if (dx > ((FeldBreite / 2) - Linie_Wand)) {
      return { .dir = 180, .velo = gs, .dribble = 0, .schuss = 0 };
    }
    // links
    else if (dx < ((-1 * (FeldBreite / 2)) + Linie_Wand)) {
      return { .dir = 0, .velo = gs, .dribble = 0, .schuss = 0 };
    }
  } else if (!xSum && ySum) {
    // SEITEN
    //
    //  hinten
    if (dy < ((-1 * (FeldLaenge / 2)) + Linie_Wand)) {
      return { .dir = 90, .velo = gs, .dribble = 0, .schuss = 0 };
    }
    // vorne
    else if (dy > ((FeldLaenge / 2) - Linie_Wand + 5)) {
      return { .dir = 270, .velo = gs, .dribble = 0, .schuss = 0 };
    } else {
      return { .dir = 0, .velo = 0, .dribble = 0, .schuss = 0 };
    }
  } else {
    return { .dir = 0, .velo = 0, .dribble = 0, .schuss = 0 };
  }
  return { .dir = 0, .velo = 0, .dribble = 0, .schuss = 0 };
  /*
    int Linie_Wand = 10;
    if ((FeldBreite / 2) - abs(dx) < Linie_Wand || (FeldLaenge / 2) - abs(dy) < Linie_Wand) {
      return fahren(0, 0);
    }
    else return {};*/
}


double sv = 0;
double sdire = 0;

motor::Anweisung fahren(int x1, int y1) {

  double diff_x = x1 - (dx);
  double diff_y = y1 - (dy);

  double p = 10;
  double dire = 0;
  double dista = 0;
  int v = 0;
  if (xSum && ySum) {
    dire = (atan2(diff_y, diff_x) * 180 / PI) * 1;
    dista = sqrt(diff_x * diff_x + diff_y * diff_y);
    v = p * dista;
  }

  else if (xSum && (!ySum)) {
    diff_y = 0;
    dire = (atan2(diff_y, diff_x) * 180 / PI) * 1;
    dista = sqrt(diff_x * diff_x + diff_y * diff_y);
    v = p * dista;
  }

  else if (ySum && (!xSum)) {
    diff_x = 0;
    dire = (atan2(diff_y, diff_x) * 180 / PI) * 1;
    dista = sqrt(diff_x * diff_x + diff_y * diff_y);
    v = p * dista;
  }
  if (v < 80) return {};
  if (v > 420) v = 420;

  sv = smoothVelocity(v, sv, 12);
  sdire = smoothAngle(dire, sdire, 3);
  return { .dir = dire, .velo = v, .dribble = 0, .schuss = 0 };
  //return { .dir = dire, .velo = 150, .dribble = 0, .schuss = 0 };
}

}
