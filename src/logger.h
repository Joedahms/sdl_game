#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
  public:
    int add(int, string); // Add to the log file

  private:
    string logFileName;   // Name of the log file
    int logLevel;         // Current log level
}

#endif
