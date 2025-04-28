#include <Arduino_APDS9960.h>
#include "Arduino_BMI270_BMM150.h"
#include <Arduino_LPS22HB.h>


int proximityMode = 0;
int positionMode = 0;
int gestureMode = 1;
int derivMode =  0;
int pressureMode = 1;

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


  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
}

void loop() {
  Serial.println("HERE, I AM IN THE LOOP");

  float x, y, z;

  if (positionMode == 1) {
    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(x, y, z);
      Serial.print(x);
      Serial.print('\t');
      Serial.print(y);
      Serial.print('\t');
      Serial.println(z);

      AddArr(lastX, (int)x);
      AddArr(lastY, (int)y);
      AddArr(lastZ, (int)z);
    }
  }

  if (proximityMode == 1) {
    if (APDS.proximityAvailable()) {
      int proximity = APDS.readProximity();
      Serial.print("Proximity: ");
      Serial.println(proximity);
    }
  }

  if (derivMode == 1) {
    int lastXSum = 0;
    int lastYSum = 0;
    int lastZSum = 0;

    for (int i = 0; i < 10; i++) {
      lastXSum += lastX[i];
      lastYSum += lastY[i];
      lastZSum += lastZ[i];
    }

    int XDeriv = (lastXSum - lastX[0]) / 20;
    int YDeriv = (lastYSum - lastY[0]) / 20;
    int ZDeriv = (lastZSum - lastZ[0]) / 20;

    if (XDeriv > 0 && YDeriv > 0) {
      Serial.println("Swipe Up Right");
    }
    else if (XDeriv < 0 && YDeriv < 0) {
      Serial.println("Swipe Down Left");
    }
    else if (XDeriv < 0) {
      Serial.println("Swipe Left");
    }
    else if (XDeriv > 0) {
      Serial.println("Swipe Right");
    }
    else if (YDeriv < 0) {
      Serial.println("Swipe Down");
    }
    else if (YDeriv > 0) {
      Serial.println("Swipe Up");
    }
  }

  if (gestureMode == 1){
    if (APDS.gestureAvailable()) {
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

  }


  if (pressureMode == 1){
  float pressure = BARO.readPressure();
  Serial.print("Pressure (hPa): ");
  Serial.println(pressure);
  delay(500);
  }

  delay(200);
}
