#include <Servo.h>
#include <NewPing.h>

//params constants
const String PARAMS_MARKER = "?";
const String NEXT_PARAM_MARKER = "&";

//commands
const String MOVE_HEAD = "MOVE_HEAD";
const String SCAN_SINGLE = "SCAN_SINGLE";
const String REATTACH_SERVO = "REATTACH_SERVO";

//command params
const String MIN_PARAM= "min";
const String MAX_PARAM = "max";
const String VALUE_PARAM = "value";

//init devides
Servo myservo;
const int SERVO_PIN = 8;


const int TRIGGER_PIN = 6;
const int ECHO_PIN = 7;
const int MAX_DISTANCE_CM = 600;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_CM);

//program variables
int position;

String inputString = "";
boolean stringComplete = false;


void setup() {
  Serial.begin(9600);
//  inputString.reserve(200);

  reattachServo(520, 1310);
  position = myservo.read();
}

void loop() {
  delay(10); 
  verifyIncomeCommand();
}

void verifyIncomeCommand() {
  if (stringComplete) {
    executeCommand(inputString);
    inputString = "";
    stringComplete = false;
  }
}

void executeCommand(String toParse) {
  if (isCommand(toParse, MOVE_HEAD)) {
    moveHead(getIntParamValue(toParse, VALUE_PARAM));
  } else if (isCommand(toParse, REATTACH_SERVO)) {
    reattachServo(
       getIntParamValue(toParse, MIN_PARAM),
       getIntParamValue(toParse, MAX_PARAM));
  } else if (isCommand(toParse, SCAN_SINGLE)) {
    Serial.print("cm: ");
    Serial.println(doScan());
  }
}

boolean isCommand(String commandWithParams, String command) {
  return commandWithParams.indexOf(PARAMS_MARKER) == -1
      ? commandWithParams.equals(command)
      : commandWithParams.startsWith(command + PARAMS_MARKER);
}

int getIntParamValue(String toParse, String paramName) {
  String fullParamName = paramName + "=";
  int paramsMarkerPosition = toParse.indexOf(PARAMS_MARKER);
  int paramStartPosition = toParse.indexOf(fullParamName, paramsMarkerPosition);
  int valueStartPosition = paramStartPosition + fullParamName.length();
  int nextParamPosition = toParse.indexOf(NEXT_PARAM_MARKER, valueStartPosition + 1);

  if (nextParamPosition == -1) {//end of string
      nextParamPosition = toParse.length();
  }

  if(paramStartPosition == -1) {
     Serial.println("requested unexists int param");
     return 0;
  }
    
  String valueAsString = "";
      
  for(int i = valueStartPosition; i < nextParamPosition; i++) {
     valueAsString = valueAsString + toParse.charAt(i);
  }
  
  return valueAsString.toInt();
}

void moveHead(int angle) {
    if(angle < 0 || angle > 180) {
      Serial.print("angle must be [0, 180]");
      return;
    }

    myservo.write(angle);
}

void reattachServo(int min, int max) {
  myservo.detach();
  myservo.attach(SERVO_PIN, min, max);

  String message = "reattached[";
  message += min;
  message += ", ";
  message += max;
  message += "]";
  Serial.print(message);
}

int doScan() {
  return sonar.convert_cm(sonar.ping_median());
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      inputString += inChar;
    }
  }
}
