

void setup() {
  serialSetup();
  commandServiceSetup();
  servoSetup();
  ultraSonicSetup();
}


//keep in mind that there is serial listener that actually start command execution
void loop() {
  delay(10); 
}
