

void setup() {
//  Serial.begin(115200);//arduino debug port
  serialSetup();
  commandServiceSetup();
  servoSetup();
  ultraSonicSetup();
  motorSetup();
  logInfo("setup completed");
}

void loop() {
  serialLoop();
  delay(10);
}
