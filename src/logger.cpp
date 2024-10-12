#include <string>
#include <fstream>

#include "logger.h"

void clearLogFile(std::string logFileName) {
  std::ofstream logFile(logFileName, std::ios_base::trunc);
  logFile.close();
}

void writeToLogFile(std::string logFileName, std::string logMessage) {
  std::ofstream logFile(logFileName, std::ios_base::app); // Open log file for appending
  logFile << logMessage + '\n';                           // Add the message
  logFile.close();                                        // Close the file
}
