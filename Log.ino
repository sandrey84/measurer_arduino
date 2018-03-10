
const String INFO_LOG_PREFIX = "INFO_LOG_";
const String ERROR_LOG_PREFIX = "ERROR_LOG_";
 
boolean infoLogEnabled = true;
boolean errorLogEnabled = true;
 
void logInfo(String toLog) {
  if(infoLogEnabled) {
    dataChannelWrite(INFO_LOG_PREFIX + toLog);
  }
}

void logError(String toLog) {
  if(errorLogEnabled) {
    dataChannelWrite(ERROR_LOG_PREFIX + toLog);
  }
}
