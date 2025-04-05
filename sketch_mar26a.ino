void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  // -------- LED01 --------
  pinMode(8, OUTPUT);   // P1
  pinMode(9, OUTPUT);   // P2
  pinMode(10, INPUT);   // P3
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
  delay(1000);

  // -------- LED02 --------
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delay(1000);

  // -------- LED03 --------
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, INPUT);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  delay(1000);


  //led4

  // -------- LED03 --------
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(8, INPUT);
  digitalWrite(10, HIGH);
  digitalWrite(9, LOW);
  delay(1000);




  // -------- LED05 --------
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, INPUT);
  digitalWrite(8, HIGH);
  digitalWrite(10, LOW);
  delay(1000);

  // -------- LED06 --------
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, INPUT);
  
  digitalWrite(10, HIGH);
  digitalWrite(8, LOW);

  delay(1000);
}
