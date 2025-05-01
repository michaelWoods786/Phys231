#include <Arduino_APDS9960.h>
#include "Arduino_BMI270_BMM150.h"
#include <Arduino_LPS22HB.h>
#include <Arduino_HS300x.h>
int proximityMode = 0;
int positionMode = 0;
int gestureMode = 0;
int pressureMode = 0;
int temperatureMode = 0;
int accelerationMode = 0;




const float LOW_THRESHOLD = 1.2;
const float HIGH_THRESHOLD = 2.2;
















int ledState = LOW;




unsigned long previousMillis = 0;








const long intervalLong = 1000;




const long intervalMed = 500;




const long intervalShort = 100;
int Rlight = 2;
int Glight = 3;
int Blight = 4;
/*
int lastX[10];
int lastY[10];
int lastZ[10];




void AddArr(int arr[], int element) {
 int i = 0;
 while (i < 10 && arr[i] != 0) {  // avoid out-of-bounds
   i++;
 }
 if (i < 10) {
   arr[i] = element;
 }
}
*/




void TurnLightOn(int LED){
 digitalWrite(LED,HIGH);




}




void TurnLightOff(int LED){
 digitalWrite(LED,LOW);




}


void reset(){


       digitalWrite(LEDR, HIGH);
       digitalWrite(LEDG, HIGH);
       digitalWrite(LEDB, HIGH);

}





void proximity(){




unsigned long currentMillis = millis();








 if (APDS.proximityAvailable()) {




   int proximity = APDS.readProximity();


   if (proximity > 150) {




     if (currentMillis - previousMillis >= intervalLong) {




       previousMillis = currentMillis;



       if (ledState == LOW) {




         ledState = HIGH;




       } else {




         ledState = LOW;




       }




       digitalWrite(LEDB, ledState);




       digitalWrite(LEDR, HIGH);




       digitalWrite(LEDR, HIGH);




     }




   }








   else if(proximity > 50 && proximity <= 150){




     if (currentMillis - previousMillis >= intervalMed) {




       previousMillis = currentMillis;








       if (ledState == LOW) {




         ledState = HIGH;




       } else {




         ledState = LOW;




       }




       digitalWrite(LEDB, ledState);




       digitalWrite(LEDR, HIGH);




       digitalWrite(LEDG, HIGH);




     }




   }








   else {




     if (currentMillis - previousMillis >= intervalShort) {




       previousMillis = currentMillis;




       if (ledState == LOW) {




         ledState = HIGH;




       } else {




         ledState = LOW;




       }








       digitalWrite(LEDR, ledState);




       digitalWrite(LEDB, HIGH);




       digitalWrite(LEDG, HIGH);




     }




   }




   Serial.println(proximity);




 }
































}
void setup() {
 Serial.begin(9600);
 while (!Serial);




 if (!APDS.begin()) {
   Serial.println("Failed to initialize APDS9960 sensor!");
   while (1);
 }
 Serial.println("Proximity sensor ready!");
 // APDS.enableGesture(true);  // REMOVE this line because it doesn't exist on Rev2!




 if (!IMU.begin()) {
   Serial.println("Failed to initialize IMU!");
   while (1);
 }
 Serial.println("IMU ready!");




 if (!HS300x.begin()) {
   Serial.println("Failed to initialize HS300x sensor!");
   while (1);
 }
 Serial.println("HS300x sensor ready.");








 if (!BARO.begin()) {
 
   Serial.println("Failed to initialize pressure sensor!");
   while (1);
 }
   pinMode(Rlight, OUTPUT);
   pinMode(Glight, OUTPUT);
   pinMode(Blight, OUTPUT);
}




char checkAnalogValue(float val){








 if (val < 42.5){




   Serial.print("TEMPERATURE MODE");
   return 't';
 }








 if (val > 42.5  && val < 85){
   Serial.print("PRESSURE MODE");
   return 'p';
 }








 if (val > 85 && val < 127.5){
   Serial.print("GESTURE mode");
   return 'g';
 }








 if (val > 127.5 && val < 170){
   Serial.print("ACCELERATION mode");
   return 'a';
 }




 if (val > 170 && val < 212.5){
    Serial.print("POSITION mode");
   return 'q';
 }








 if (val > 212.5 && val < 255){




   Serial.print("Proximity MODE");
   return 'z';
 }












}








void loop() {

       

      delay(2000);

 //TurnLightOn(3);








 //TurnLightOn(4);
 int sensorValue = analogRead(A0)/4; // Read from analog pin A0
 Serial.print("this is sensorVal:");
 Serial.println(sensorValue);
 char a = checkAnalogValue(sensorValue);
 Serial.print("this is a:");
 Serial.println(a);
 if (a == 't'){
   temperatureMode = 1;
 }




 if (a == 'q'){
   positionMode = 1;
 }




 if (a == 'p'){
   pressureMode = 1;
 }
  if (a == 'a'){
   accelerationMode = 1;
 }




 if (a == 'g'){
   gestureMode = 1;
 }




 if (a == 'z'){
   proximityMode = 1;
 }








 float x, y, z;




 if (temperatureMode == 1){








   float temperature = HS300x.readTemperature();
   Serial.print("Temperature (°C): ");
   Serial.println(temperature);
   delay(1000);




   if (temperature < 18.0) {
    reset();
   Serial.println("Low temperature range");




 
       digitalWrite(LEDR, LOW);




       digitalWrite(LEDG, HIGH);




       digitalWrite(LEDB, HIGH);








 }
  else if (temperature >= 18.0 && temperature <= 25.0) {


      reset();
   Serial.println("Medium temperature range");




 
       digitalWrite(LEDR, HIGH);
       digitalWrite(LEDG, LOW);
       digitalWrite(LEDB, HIGH);








 } else {  
    reset();











       Serial.println("High temperature range");
       digitalWrite(LEDR, HIGH);
       digitalWrite(LEDG, HIGH);
       digitalWrite(LEDB, LOW);
 }











   temperatureMode = 0;
}




 if (proximityMode == 1){
   
   reset();
   
   
   proximity();
 }












 if (positionMode == 1) {
   if (IMU.gyroscopeAvailable()) {
     IMU.readGyroscope(x, y, z);




     Serial.print("POSIITION:");
     Serial.print(x);
     Serial.print('\t');
     Serial.print(y);
     Serial.print('\t');
     Serial.println(z);








     positionMode = 0;




     /*
     AddArr(lastX, (int)x);
     AddArr(lastY, (int)y);
     AddArr(lastZ, (int)z);
     */
   }
 }
















 if (gestureMode == 1){
  reset();
    if (APDS.gestureAvailable()) {
   // a gesture was detected, read and print to Serial Monitor
 int gesture = APDS.readGesture();




   switch (gesture) {




     case GESTURE_UP:




       Serial.println("Detected UP gesture");




       digitalWrite(LEDG, LOW);




       digitalWrite(LEDR, HIGH);




       digitalWrite(LEDB, HIGH);








       break;




     case GESTURE_DOWN:




       Serial.println("Detected DOWN gesture");




     
       digitalWrite(LEDG, HIGH);




       digitalWrite(LEDR, LOW);




       digitalWrite(LEDB, HIGH);




       break;




     case GESTURE_LEFT:




       Serial.println("Detected LEFT gesture");












       digitalWrite(LEDG, HIGH);




       digitalWrite(LEDR, HIGH);




       digitalWrite(LEDB, LOW);












       break;




     case GESTURE_RIGHT:




       Serial.println("Detected RIGHT gesture");
     
       digitalWrite(LEDG, HIGH);




       digitalWrite(LEDR, LOW);




       digitalWrite(LEDB, HIGH);












       break;




     default:




       break;




   }
 
 
 }




 }








 if (pressureMode == 1){
  reset();
 float pressure = BARO.readPressure();
 Serial.print("Pressure (hPa): ");
 Serial.println(pressure);

 if (pressure >= 95){
      digitalWrite(LEDG, LOW);
       digitalWrite(LEDR, HIGH);
       digitalWrite(LEDB, HIGH);


 }




 if (pressure < 95){


   digitalWrite(LEDG, HIGH);
       digitalWrite(LEDR, LOW);
       digitalWrite(LEDB, HIGH);
 }
pressureMode = 0;
  }


if (accelerationMode == 1){
  reset();
float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    float magnitude = sqrt(x * x + y * y + z * z); // Acceleration vector magnitude

    Serial.print("Accel magnitude: ");
    Serial.println(magnitude);

    if (magnitude < LOW_THRESHOLD) {
      digitalWrite(LEDR, LOW);   // RED ON
      digitalWrite(LEDB, HIGH);  // BLUE OFF
    } else if (magnitude > 1) {
      digitalWrite(LEDR, HIGH);  // RED OFF
      digitalWrite(LEDB, LOW);   // BLUE ON
    } else {
      digitalWrite(LEDR, HIGH);  // Both OFF
      digitalWrite(LEDB, HIGH);
    }

    delay(100);
  }
  
}


 delay(20);
}
























