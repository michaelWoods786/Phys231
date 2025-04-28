#include <Arduino_APDS9960.h>



/*
  Arduino BMI270 - Simple Gyroscope


  This example reads the gyroscope values from the BMI270
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.


  The circuit:
  - Arduino Nano 33 BLE Sense Rev2


  created 10 Jul 2019
  by Riccardo Rizzo


  This example code is in the public domain.
*/


#include "Arduino_BMI270_BMM150.h"


int proximityMode = 1;
int positionMode = 0;
int gestureMode = 0;





void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
    while (1);
  }


  Serial.println("Proximity sensor ready!");
}

void loop() {
  if (proximityMode == 1){

  float myProx = APDS.readProximity();


  if (myProx != 255 && myProx > 0){
  
  Serial.print("PROXUP:");
  Serial.println(myProx);
  }

  }


  float x, y, z;

  if (positionMode == 1){
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);


    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);


  }
  }


  Serial.print(APDS.gestureAvailable());
  if (gestureMode == 1 && APDS.gestureAvailable()) {
    Serial.println("SEEING IF THERE ARE GESTURES");
    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        break;

      default:
        // ignore
        break;
    }
  }



  delay(20); // read every 200 ms
  }




