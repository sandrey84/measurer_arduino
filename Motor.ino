
const int enA = 2;
const int in1 = 22;
const int in2 = 24;
const int in3 = 23;
const int in4 = 25;
const int enB = 3;

long turnedOnTime = 0;

void motorSetup() { 
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);  
    pinMode(in2, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);  
    pinMode(in4, OUTPUT);
} 

void moveChassis(int leftMs, int leftPower, int rightMs, int rightPower) {
  while(true) {
    if (turnedOnTime == 0) {
      setMotorsSpeed(leftPower, rightPower);
      turnedOnTime = millis();
      continue;
    }

    long now = millis();
    boolean timeToTurnOffLeft = (turnedOnTime + leftMs) < now;
    boolean timeToTurnOffRight = (turnedOnTime + rightMs) < now;

    if (timeToTurnOffLeft) {
      analogWrite(enB, 0);   
    }

    if (timeToTurnOffRight) {
      analogWrite(enA, 0);
    }

    if (timeToTurnOffLeft && timeToTurnOffRight) {
      turnedOnTime = 0;
      break;
    }

    delay(50);
  }
}

void setMotorsSpeed(int leftPower, int rightPower) {
   analogWrite(enB, abs(leftPower));
   digitalWrite(in1, leftPower > 0 ? HIGH : LOW);
   digitalWrite(in2, leftPower > 0 ? LOW : HIGH);

   analogWrite(enA, abs(rightPower));
   digitalWrite(in3, rightPower > 0 ? HIGH : LOW);
   digitalWrite(in4, rightPower > 0 ? LOW : HIGH);
}



