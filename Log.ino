
const String INFO_LOG_PREFIX = "INFO_LOG_";
const String ERROR_LOG_PREFIX = "ERROR_LOG_";
 
boolean infoLogEnabled = true;
boolean errorLogEnabled = true;
 
void logInfo(String toLog) {
  if(infoLogEnabled) {
    Serial.println(INFO_LOG_PREFIX + toLog);
  }
}

void logError(String toLog) {
  if(errorLogEnabled) {
    Serial.println(ERROR_LOG_PREFIX + toLog);
  }
}
