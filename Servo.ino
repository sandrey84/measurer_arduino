#include <Servo.h>

//init devices
Servo headServo;
const int HEAD_SERVO_PIN = 8;

//program variables
int headServoAngle;

void servoSetup() { 
  reattachHeadServo(510, 1380);
  headServoAngle = headServo.read();
} 

void moveHead(int angle) {
    if(angle < 0 || angle > 180) {
      logError("angle must be [0, 180]");
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
  Serial.print(message);
}
