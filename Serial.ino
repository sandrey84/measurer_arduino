
const char END_OF_COMMAND = '\n';
String serialInputString = "";

void serialSetup() {
  Serial.begin(9600);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    
    if (inChar == END_OF_COMMAND) {
      parseAndExecute(serialInputString);
      serialInputString = "";
    } else {
      serialInputString += inChar;
    }
  }
}
