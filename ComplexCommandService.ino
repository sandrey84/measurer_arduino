const String LEFT_SCAN_RESULT = "LEFT_SCAN_RESULT_";
const String RIGHT_SCAN_RESULT = "RIGHT_SCAN_RESULT_";
const String SCAN_RESULT = "SCAN_RESULT_";

int distances[360];

String doLeftScan() {
  String result = LEFT_SCAN_RESULT + leftMeasureDistanceInCm();  
  return result;
}

String doRightScan() {
  String result = RIGHT_SCAN_RESULT + rightMeasureDistanceInCm();  
  return result;
}


String doScan(int minAngle, int maxAngle) {
  selectHeadAndMove(minAngle);
  int currentAngle = minAngle;

  while (currentAngle != -1) {
    selectHeadAndMove(currentAngle);
    distances[currentAngle] = selectSonarAndMeasure(currentAngle);
    currentAngle = nextAngle(currentAngle, maxAngle);
  }

  return concateData(minAngle, maxAngle);
}

void selectHeadAndMove(int angle) {
  if(angle > 180) {
    moveRightHead(angle - 180);
    waitForServoPositioned(angle);
    return;
  }

  moveLeftHead(angle);
  waitForServoPositioned(angle);
}

void waitForServoPositioned(int angle) {
  if (angle == 0 || angle == 181) {
    delay(1000);
  }
}

int selectSonarAndMeasure(int angle) {
  return angle > 180 
     ? rightMeasureDistanceInCm()
     : leftMeasureDistanceInCm();
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

