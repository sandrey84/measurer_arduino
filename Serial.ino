void serialSetup() {
  Serial1.begin(9600);
}

void serialLoop() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    onDataReceived(inChar);
  }
}
