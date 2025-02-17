
//MSB
int pinL0 = 4;
int pinL1 = 5;
int pinL2 = 6;

//this will be the LSB
int pinL3 = 7;


String Tobinary(int num){
  String s = "";
  int myNum = num;
  if (num == 0){
    return "0000";
  }

  if (num == 1){
    return "0001";
  }
  
  while (myNum > 0){
  s =  String(myNum % 2) + s;
  Serial.print("this is s now: " + s);
  myNum /= 2;
  }
  Serial.println("this is s:" + s);
  while (s.length() < 4) {
    s = "0" + s ;
  }


  return s;
}


void binaryLightUp(String num){
    digitalWrite(pinL0, LOW);
    digitalWrite(pinL1, LOW);
    digitalWrite(pinL2, LOW);
    digitalWrite(pinL3, LOW);
    if (num[0] == '1'){
      digitalWrite(pinL0, HIGH);
    }
    else {
       digitalWrite(pinL0, LOW);
    }
    if (num[1] == '1'){
      digitalWrite(pinL1, HIGH);
    }
    else{
      digitalWrite(pinL1, LOW);
    }
    if (num[2] == '1'){
      digitalWrite(pinL2, HIGH);
    }
    else{
       digitalWrite(pinL2, LOW);
    }
    
    if (num[3] == '1'){
      digitalWrite(pinL3, HIGH);
    }
    else{
       digitalWrite(pinL3, LOW);
    }

}



void setup() {
  pinMode(pinL0, OUTPUT);
  pinMode(pinL1, OUTPUT);
  pinMode(pinL2, OUTPUT);
  pinMode(pinL3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int i = 0;

  
  for (int i = 0; i <= 9; i +=1){
    Serial.print(i);
    Serial.print(":");
    String myBinary = (Tobinary(i));
    Serial.println(myBinary);


    binaryLightUp(Tobinary(i));
    delay(5000);
  }
  }
