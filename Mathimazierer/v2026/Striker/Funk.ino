void funk() {
}
/*bool anderer_bkuhle;
  bool success = radio_send.write(&b_kuhle, sizeof(b_kuhle));
  //Serial.println(success);
  if (radio_receive.available()) {
  radio_receive.read(&anderer_bkuhle, sizeof(anderer_bkuhle));
  //Serial.println(anderer_bkuhle);
  }
  if (anderer_bkuhle == 1 && b_kuhle == 0) {
  role = 0;
  }
  else if (anderer_bkuhle == 0 && b_kuhle == 1) {
  role = 1;
  }
  else if (anderer_bkuhle == b_kuhle) {
  role = role;
  }
  if(letzteLS != b_kuhle){
  radio_send.stopListening();
  radio_send.write(&b_kuhle, sizeof(b_kuhle));
  letzteLS = b_kuhle;
  radio_send.startListening();
  Serial.println("GESENDET");
  }
  else{
  Serial.println("AMLESEN");
  while(radio_send.available()){
    radio_send.read(&anderer_bkuhle, sizeof(anderer_bkuhle));
    Serial.println(anderer_bkuhle);
  }
  }
  Serial.println(b_kuhle);
  if (role == 1) {
  attacker();
  Serial.println("Attack");
  }
  else {
  goalie();
  Serial.println("DEFEMND");
  }
  }

  void attacker() {
  bV = true;
  }
  void goalie() {
  bV = false;
  }*/
