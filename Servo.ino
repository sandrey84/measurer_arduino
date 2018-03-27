#include <Servo.h>

//init devices
Servo leftHeadServo;
Servo rightHeadServo;
const int LEFT_HEAD_SERVO_PIN = 8;
const int RIGHT_HEAD_SERVO_PIN = 9;

void servoSetup() { 
  reattachHeadServos(495, 1300);
} 

void moveLeftHead(int angle) {
    if (!isAngleCorrect(angle, false)) {
      return;
    }

    leftHeadServo.write(angle);
}

boolean isAngleCorrect(int angle, boolean rightHead) {
    if (angle < 0 || angle > 180) {
       String error = rightHead ? "right" : "left";
       error += " head angle must be [0, 180], actual: ";
       error += angle;
       logError(error);
       return false;
    }

    return true;
}    

void moveRightHead(int angle) {
    if (!isAngleCorrect(angle, true)) {
      return;
    }

    rightHeadServo.write(angle);
}

void reattachHeadServos(int minPwm, int maxPwm) {
  leftHeadServo.detach();
  rightHeadServo.detach();
  leftHeadServo.attach(LEFT_HEAD_SERVO_PIN, minPwm, maxPwm);
  rightHeadServo.attach(RIGHT_HEAD_SERVO_PIN, minPwm, maxPwm);

  String message = "reattached[";
  message += minPwm;
  message += ", ";
  message += maxPwm;
  message += "]";
  logInfo(message);
}
