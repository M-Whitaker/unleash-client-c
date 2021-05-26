//
// Created by Matt Whitaker on 21/05/2021.
//

#include "utils/log.h"

static void print(const char *string, const char *colourFmtString) {
  time_t t = time(NULL);
  char buffer[80];
  struct tm *timeInfo = localtime(&t);
  strftime(buffer, 80, timeFormat, timeInfo);

  if (logLevel >= LOGGING_LEVEL_ERROR)
    fprintf(stderr, "%s%s %s" CONSOLE_OUTPUT_RESET, colourFmtString, buffer, string);
  else
    fprintf(stdout, "%s%s %s" CONSOLE_OUTPUT_RESET, colourFmtString, buffer, string);
}
void ulLogDebug(const char *fmt, ...) {
  if (logLevel <= LOGGING_LEVEL_DEBUG) {
    va_list args;
    va_start(args, fmt);
    //TODO: alloc memory
    char buffer[4096];
    int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
    print(buffer, CONSOLE_OUTPUT_BLU);
    va_end(args);
  }
}
void ulLogInfo(const char *fmt, ...) {
  if (logLevel <= LOGGING_LEVEL_INFO) {
    va_list args;
    va_start(args, fmt);
    //TODO: alloc memory
    char buffer[4096];
    int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
    print(buffer, CONSOLE_OUTPUT_RESET);
    va_end(args);
  }
}
void ulLogWarn(const char *fmt, ...) {
  if (logLevel <= LOGGING_LEVEL_WARN) {
    va_list args;
    va_start(args, fmt);
    //TODO: alloc memory
    char buffer[4096];
    int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
    print(buffer, CONSOLE_OUTPUT_YEL);
    va_end(args);
  }
}
void ulLogError(const char *fmt, ...) {
  if (logLevel <= LOGGING_LEVEL_ERROR) {
    va_list args;
    va_start(args, fmt);
    //TODO: alloc memory
    char buffer[4096];
    int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
    print(buffer, CONSOLE_OUTPUT_RED);
    va_end(args);
  }
}
void ulLogCritical(const char *fmt, ...) {
  if (logLevel <= LOGGING_LEVEL_CRITICAL) {
    va_list args;
    va_start(args, fmt);
    //TODO: alloc memory
    char buffer[4096];
    int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
    print(buffer, CONSOLE_OUTPUT_RED);
    va_end(args);
  }
}
LogLevel ulLogSetLevel(LogLevel newLevel) {
  logLevel = newLevel;
  return newLevel;
}
