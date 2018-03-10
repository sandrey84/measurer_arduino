#include <Servo.h>

//init devices
Servo myservo;
const int SERVO_PIN = 8;

//program variables
int headServoAngle;

void servoSetup() { 
  reattachHeadServo(510, 1380);
  headServoAngle = myservo.read();
} 

void moveHead(int angle) {
    if(angle < 0 || angle > 180) {
      Serial.print("angle must be [0, 180]");
      return;
    }

    myservo.write(angle);
}

void reattachHeadServo(int minPwm, int maxPwm) {
  myservo.detach();
  myservo.attach(SERVO_PIN, minPwm, maxPwm);

  String message = "reattached[";
  message += minPwm;
  message += ", ";
  message += maxPwm;
  message += "]";
  Serial.print(message);
}
