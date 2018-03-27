const char END_OF_MESSAGE_MARKER = '\n';
String readData = "";

void onDataReceived(char dataChar) {
  if (dataChar == END_OF_MESSAGE_MARKER) {
     parseCommand(readData);
     readData = "";
  } else {
     readData += dataChar;
  }
}

void dataChannelWrite(String data) {
  Serial1.print(data + END_OF_MESSAGE_MARKER);
}

