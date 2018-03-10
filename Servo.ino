#include <Servo.h>

//init devices
Servo headServo;
const int HEAD_SERVO_PIN = 8;

void servoSetup() { 
  reattachHeadServo(510, 1250);
} 

void moveHead(int angle) {
    if(angle < 0 || angle > 180) {
      String error = "angle must be [0, 180], actual: ";
      error += angle;
      logError(error);
      return;
    }

    headServo.write(angle);
}

void reattachHeadServo(int minPwm, int maxPwm) {
  headServo.detach();
  headServo.attach(HEAD_SERVO_PIN, minPwm, maxPwm);

  String message = "reattached[";
  message += minPwm;
  message += ", ";
  message += maxPwm;
  message += "]";
  logInfo(message);
}
