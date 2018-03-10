
//params constants
const String PARAMS_MARKER = "?";
const String NEXT_PARAM_MARKER = "&";

//commands
const String MOVE_HEAD = "MOVE_HEAD";
const String SCAN = "SCAN";
const String SCAN_SINGLE = "SCAN_SINGLE";
const String REATTACH_SERVO = "REATTACH_SERVO";

//command params
const String MIN_PARAM= "min";
const String MAX_PARAM = "max";
const String VALUE_PARAM = "value";

void commandServiceSetup() { 
} 

void parseAndExecute(String toParse) {
  logError("here_1");
  if (isCommand(toParse, MOVE_HEAD)) {
    logError("here_2");
    moveHead(getIntParamValue(toParse, VALUE_PARAM));
  } else if (isCommand(toParse, REATTACH_SERVO)) {
      reattachHeadServo(
          getIntParamValue(toParse, MIN_PARAM),
          getIntParamValue(toParse, MAX_PARAM));
  } else if (isCommand(toParse, SCAN_SINGLE)) {
    logError("here_3");
      String distanceAsString = "cm: ";
      distanceAsString += measureDistanceInCm();
      logInfo(distanceAsString);
  } else if (isCommand(toParse, SCAN)) {
    logError("here_4");
    logInfo("scan");
    logInfo(doScan(
      getIntParamValue(toParse, MIN_PARAM),
      getIntParamValue(toParse, MAX_PARAM)));
  }
  logError("here_5");
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
     logError("requested unexists int param");
     return 0;
  }
    
  String valueAsString = "";
      
  for(int i = valueStartPosition; i < nextParamPosition; i++) {
     valueAsString = valueAsString + toParse.charAt(i);
  }
  
  return valueAsString.toInt();
}
