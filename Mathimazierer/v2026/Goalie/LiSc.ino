float glatterWert = 0;
float alpha = 0.05;
bool lb;
void LS() {
  int LS_Wert = analogRead(LS_Pin);
  /*Serial.println(LS_Wert);
    readings[number] = LS_Wert;
    number++;
    if (number >= wertemenge) {
    long sum = 0;
    for (int i = 0; i < wertemenge; i++) {
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
      sum += avg_r[i];
    }
     avgL = sum / wertemenge2;
     avgd_d[numberd_d] = avgL;
    //Serial.println(avg);
    number_d = 0;
    bestV = 0;    numberd_d++;
    }
    if(numberd_d >=  wm3){
    long sum = 0;
    for (int i = 0; i < wm3; i++){
      sum += avgd_d[i];
    }
     avgLs = sum/wm3;
    numberd_d = 0;
    if(avgLs >= 30){
      b_kuhle = true;
    }
    else{
      b_kuhle = false;
    }
    }*/
  //Serial.println(b_kuhle);
  //glatterWert = (alpha * LS_Wert) + ((1.0 - alpha) * glatterWert);
  if(LS_Wert > schwellenwert){
    lastPulseTime = millis();
  }
  if(millis() - lastPulseTime < 150){
    b_kuhle = true;
  }
  else{
    b_kuhle = false;
  }
  if(lb != b_kuhle ){
  }
  lb = b_kuhle;
}
