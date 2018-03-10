

int distances[180];


String doScan(int minAngle, int maxAngle) {
  moveHead(minAngle);
  delay(1500);
  int currentAngle = minAngle;

  while (currentAngle != -1) {
    moveHead(currentAngle);
    delay(10);
    distances[currentAngle] = measureDistanceInCm();
    currentAngle = nextAngle(currentAngle, maxAngle);
  }

  return concateData(minAngle, maxAngle);
}

int nextAngle(int currentAngle, int maxAngle) {
  return currentAngle <= maxAngle
      ? currentAngle + 1
      : -1;
}

String concateData(int minAngle, int maxAngle) {
  String concatedData = "";
  
  for(int i = minAngle; i <= maxAngle; i++) {
      concatedData += i;
      concatedData += "=";
      concatedData += distances[i];

      if (i != maxAngle) {
        concatedData += ", ";
      }
  }

  return concatedData;
}

