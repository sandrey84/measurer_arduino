const String SINGLE_SCAN_RESULT = "SINGLE_SCAN_RESULT_";
const String SCAN_RESULT = "SCAN_RESULT_";

int distances[180];

String doSingleScan() {
  String result = SINGLE_SCAN_RESULT + measureDistanceInCm();  
  return result;
}

String doScan(int minAngle, int maxAngle) {
  moveHead(minAngle);
  delay(1500);
  int currentAngle = minAngle;

  while (currentAngle != -1) {
    moveHead(currentAngle);
    distances[currentAngle] = measureDistanceInCm();
    currentAngle = nextAngle(currentAngle, maxAngle);
  }

  return concateData(minAngle, maxAngle);
}

int nextAngle(int currentAngle, int maxAngle) {
  return currentAngle < maxAngle
      ? currentAngle + 1
      : -1;
}

String concateData(int minAngle, int maxAngle) {
  String concatedData = SCAN_RESULT;
  
  for(int i = minAngle; i <= maxAngle; i++) {
      concatedData += i;
      concatedData += "=";
      concatedData += distances[i];

      if (i != maxAngle) {
        concatedData += ",";
      }
  }

  return concatedData;
}

