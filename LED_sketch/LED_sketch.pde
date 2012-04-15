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
    brightness = Serial.read();
    Serial.println('this is what I am');
  }
}



void turnOnLight(){
  digitalWrite(13, HIGH);   // set the LED on
}

void turnOffLight(){
  digitalWrite(13, LOW);   // set the LED on
}
