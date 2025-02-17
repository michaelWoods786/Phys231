


int buttonPin = 2;  // Pin for the built-in button
int ledPin = 5;
int AnalogPin = A5;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(AnalogPin, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up resistor
    Serial.begin(9600);

}

void loop() {

   
    
    int analogValue = analogRead(AnalogPin);
    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {  // Button is pressed
        Serial.println("PUSHED");
    } else {
        Serial.println("NOT PUSHED");
    }

    delay(200);

  



    Serial.print("This is the analogValue:");
    Serial.println(analogValue/4);
    if (buttonState == LOW && analogValue/4 > 127){
      digitalWrite(5,  HIGH);
    }
    else{
      digitalWrite(ledPin, LOW);
    }
    
    
    delay(200);  // Delay to avoid spamming the Serial Monitor
}