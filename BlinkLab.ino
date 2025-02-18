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
  for (int i = 0; i < 5; i+=1 ){
    pinMode(myLeds[i], OUTPUT);
  }
  pinMode(LED_BUILTIN, OUTPUT);
}

void TurnOnOffSameTime(){
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
int x = 1;
while (x == 1){

digitalWrite(6, HIGH);
//console.log("printing 6 high, 7 off");
delay(40);
digitalWrite(6, LOW);
digitalWrite(7, HIGH);
delay(40);
digitalWrite(7, LOW);
}
}

void blinkFoo( int mode){
  //goes from l3 to l7
  if (mode == 0){
    for (int i = 0; i < 5; i+=1){
      digitalWrite(myLeds[i], HIGH);
      delay(40);
      digitalWrite(myLeds[i], LOW);
      }
  }

  if (mode == 1){
    for (int i = 4; i >= 0; i-=1){
      digitalWrite(myLeds[i],  HIGH);
      delay(40);
      digitalWrite(myLeds[i], LOW);
    }
  }
}


void loop() {
TurnOnOffSameTime();
}
