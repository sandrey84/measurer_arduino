void serialSetup() {
  Serial.begin(9600);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    onDataReceived(inChar);
  }
}
