
//params constants
const String PARAMS_MARKER = "?";
const String NEXT_PARAM_MARKER = "&";

//commands
const String MOVE_LEFT_HEAD = "MOVE_LEFT_HEAD";
const String MOVE_RIGHT_HEAD = "MOVE_RIGHT_HEAD";
const String SCAN = "SCAN";
const String LEFT_SCAN = "LEFT_SCAN";
const String RIGHT_SCAN = "RIGHT_SCAN";
const String REATTACH_SERVOS = "REATTACH_SERVOS";
const String MOVE = "MOVE";

//command params
const String MIN_PARAM= "min";
const String MAX_PARAM = "max";
const String VALUE_PARAM = "value";
const String LEFT_MS = "left_ms";
const String RIGHT_MS = "right_ms";
const String LEFT_POWER = "left_power";
const String RIGHT_POWER = "right_power";

void commandServiceSetup() { 
} 

void parseCommand(String toParse) {
  if (isCommand(toParse, MOVE_LEFT_HEAD)) {
    moveLeftHead(getIntParamValue(toParse, VALUE_PARAM));
  } else if(isCommand(toParse, MOVE_RIGHT_HEAD)) {
    moveRightHead(getIntParamValue(toParse, VALUE_PARAM));
  } else if (isCommand(toParse, REATTACH_SERVOS)) {
      reattachHeadServos(
          getIntParamValue(toParse, MIN_PARAM),
          getIntParamValue(toParse, MAX_PARAM));
  } else if (isCommand(toParse, LEFT_SCAN)) {
      dataChannelWrite(doLeftScan());
  } else if (isCommand(toParse, RIGHT_SCAN)) {
      dataChannelWrite(doRightScan());
  } else if (isCommand(toParse, SCAN)) {
      dataChannelWrite(doScan(
          getIntParamValue(toParse, MIN_PARAM),
          getIntParamValue(toParse, MAX_PARAM)));
  } else if (isCommand(toParse, MOVE)) {
     moveChassis(
          getIntParamValue(toParse, LEFT_MS),
          getIntParamValue(toParse, LEFT_POWER),
          getIntParamValue(toParse, RIGHT_MS),
          getIntParamValue(toParse, RIGHT_POWER)
      );
  } else {
    logError("unknown command: " + toParse);
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
     logError("requested unexists param: '" + paramName + "', command: " + toParse);
     return 0;
  }
    
  String valueAsString = "";
      
  for(int i = valueStartPosition; i < nextParamPosition; i++) {
     valueAsString = valueAsString + toParse.charAt(i);
  }
  
  return valueAsString.toInt();
}
