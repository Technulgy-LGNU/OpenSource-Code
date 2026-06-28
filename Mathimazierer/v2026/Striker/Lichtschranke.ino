void LS() {
  int LS_Wert = analogRead(LS_Pin);
  readings[number] = LS_Wert;
  number++;
  if (number >= wertemenge) {
    long sum = 0;
    for (int i = 0; i < wertemenge; i++) {
      /*if(readings[i] > bestV){
        bestV = readings[i];
        }*/
      sum += readings[i];
    }
    int avg = sum / wertemenge;
    avg_r[number_d] = avg;
    number_d++;
    number = 0;
  }
  if (number_d >= wertemenge2) {
    long sum = 0;
    for (int i = 0; i < wertemenge2; i++) {
      /*if(avg_r[i] > bestV){
        bestV = avg_r[i];
        }*/
      sum += avg_r[i];
    }
    int avg = sum / wertemenge2;
    if (avg >= 90) {//>=85
      b_kuhle = true;
    }
    else {
      b_kuhle = false;
    }
    number_d = 0;
    bestV = 0;
  } 
}
