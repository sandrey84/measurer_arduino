#include <NewPing.h>

//init devices
const int TRIGGER_PIN = 6;
const int ECHO_PIN = 7;
const int MAX_DISTANCE_CM = 600;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_CM);

void ultraSonicSetup() { 
} 

int measureDistanceInCm() {
  return sonar.convert_cm(sonar.ping_median());
}
