int grnLEDPin = 12;
int estcontactcount = 0;
int commandCount = 0;


void setup() {
  pinMode(grnLEDPin, OUTPUT);
  digitalWrite(grnLEDPin, LOW);
  Serial.begin(9600);
  establishContact(); // wait for commands
}

void establishContact() {
  while (Serial.available() <= 0) {         // do nothing unless serial buffer has data
    Serial.print("waiting for command:");
    Serial.println(++commandCount);       
    //Serial.print("waiting for command: ");  // starting message
  //Serial.println(++estcontactcount);
    digitalWrite(grnLEDPin, HIGH);
    delay(1000);
    digitalWrite(grnLEDPin, LOW);
    delay(1000);
  }
}

void loop() {

  /*
  commandCount = 0;
  while (Serial.available() > 0){
    char cmd =  Serial.read();
    if (cmd == 'g'){
      Serial.print("\t");
      Serial.print(" _data from Arduino: ");
      Serial.println(commandCount);
      commandCount+=1;
    }
   
  }
  
*/
  
  if (Serial.available() > 0) {             // do something only if bytes in buffer
    char cmd = Serial.read();   
    
      // read one byte only (removes byte from buffer)
    if (cmd == 'g') {                       // execute only if a "g" is rec'd

      Serial.print("\t");
      Serial.print(" _data from Arduino: ");
      Serial.print(random(1,10));

      Serial.println();       // write code to send byte with random value between 1 and 10
                              // send CRLF to indicate end of line/data
    }
  }
  
  establishContact();     // return to wait for more cmds
}
