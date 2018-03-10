
//params constants
const String PARAMS_MARKER = "?";
const String NEXT_PARAM_MARKER = "&";

//commands
const String MOVE_HEAD = "MOVE_HEAD";
const String SCAN = "SCAN";
const String SCAN_SINGLE = "SINGLE_SCAN";
const String REATTACH_SERVO = "REATTACH_SERVO";

//command params
const String MIN_PARAM= "min";
const String MAX_PARAM = "max";
const String VALUE_PARAM = "value";

void commandServiceSetup() { 
} 

void parseCommand(String toParse) {
  if (isCommand(toParse, MOVE_HEAD)) {
    moveHead(getIntParamValue(toParse, VALUE_PARAM));
  } else if (isCommand(toParse, REATTACH_SERVO)) {
      reattachHeadServo(
          getIntParamValue(toParse, MIN_PARAM),
          getIntParamValue(toParse, MAX_PARAM));
  } else if (isCommand(toParse, SCAN_SINGLE)) {
      dataChannelWrite(doSingleScan());
  } else if (isCommand(toParse, SCAN)) {
      dataChannelWrite(doScan(
          getIntParamValue(toParse, MIN_PARAM),
          getIntParamValue(toParse, MAX_PARAM)));
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
