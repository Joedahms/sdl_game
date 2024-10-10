#include <string>
#include <fstream>

#include "logger.h"

// Add a log to the log file
int Logger::add(int logLevel, string logMessage) {
  if (logLevel != this.logLevel) {    // If not the current log level
    return 0;
  }

  // Add the log message to the file
  ofstream logFile(this.logFileName);
  logFile << logMessage;
  logFile.close();

  return 0;
}
