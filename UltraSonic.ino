#include <NewPing.h>

//init devices
const int LEFT_TRIGGER_PIN = 6;
const int LEFT_ECHO_PIN = 7;
const int RIGHT_TRIGGER_PIN = 5;
const int RIGHT_ECHO_PIN = 4;
const int MAX_DISTANCE_CM = 350;
NewPing leftSonar(LEFT_TRIGGER_PIN, LEFT_ECHO_PIN, MAX_DISTANCE_CM);
NewPing rightSonar(RIGHT_TRIGGER_PIN, RIGHT_ECHO_PIN, MAX_DISTANCE_CM);

void ultraSonicSetup() { 
} 

int leftMeasureDistanceInCm() {
  return leftSonar.convert_cm(leftSonar.ping_median());
}

int rightMeasureDistanceInCm() {
  return rightSonar.convert_cm(rightSonar.ping_median());
}
