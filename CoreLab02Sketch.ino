/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
// the setup function runs once when you press reset or power the board
const int myLeds[] = {3,4,5,6,7};

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(2, INPUT_PULLUP);  // Button
}

void blink(int b1, int b2){

    //here, we are turning on LED 3, and turning off LED 4
    digitalWrite(b1, HIGH);
    digitalWrite(b2, LOW);  
    delay(1000);
    //Here, we are turning on LED 4, and turning off LED 3
    digitalWrite(b2, HIGH);
    digitalWrite(b1, LOW);
    delay(1000);

    
  }


void blinkFoo( int mode){
  //goes from l3 to l7
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
   digitalWrite(5, LOW);
   digitalWrite(6, LOW);



  if (mode == HIGH){
    Serial.print("mode is HIGH");
      while (digitalRead(2) == HIGH){
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      blink(3,4);  
      tone(8,294,250);

      }
  }

  if (mode == LOW){
    Serial.print("mode is LOW");
    while (digitalRead(2) == LOW){
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    blink(5,6);
    tone(8,330,250);
  }
  }
}



void loop() {
  blinkFoo(digitalRead(2));
}





