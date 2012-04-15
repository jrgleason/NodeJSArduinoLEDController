bool toggle = false;

void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);     
  Serial.begin(9600);
  Serial.println("Starting....");
}

void loop() {
  byte brightness;
  // check if data has been sent from the computer:
  if (Serial.available()>0) {
    Serial.println("Serial Available....");
    if(toggle){
      Serial.println("Toggling On....");
      turnOnLight();
      toggle=false;
    }
    else{
      Serial.println("Toggling Off....");
      turnOffLight();
      toggle=true;
    }
    brightness = Serial.read();
  }
}



void turnOnLight(){
  digitalWrite(13, HIGH);   // set the LED on
}

void turnOffLight(){
  digitalWrite(13, LOW);   // set the LED on
}
