//
// Created by Matt Whitaker on 16/05/2021.
//

#ifndef UNLEASH_CLIENT_C_INCLUDE_UTILS_LOG_H_
#define UNLEASH_CLIENT_C_INCLUDE_UTILS_LOG_H_

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define CONSOLE_OUTPUT_RED "\x1B[31m"
#define CONSOLE_OUTPUT_GRN "\x1B[32m"
#define CONSOLE_OUTPUT_YEL "\x1B[33m"
#define CONSOLE_OUTPUT_BLU "\x1B[34m"
#define CONSOLE_OUTPUT_MAG "\x1B[35m"
#define CONSOLE_OUTPUT_CYN "\x1B[36m"
#define CONSOLE_OUTPUT_WHT "\x1B[37m"
#define CONSOLE_OUTPUT_RESET "\x1B[0m"

#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#define PRINTFLIKE(fmtarg,firstvararg) __attribute__((format(printf,fmtarg,firstvararg)))
#define NORETURN()      __attribute__((noreturn))
#elif __clang__
#define PRINTFLIKE(fmtarg,firstvararg) __printflike(fmtarg, firstvararg)
#define NORETURN()      /* If only */
#else
#define PRINTFLIKE(n,m) /* If only */
#define NORETURN()      /* If only */
#endif /* __GNUC__ */

typedef enum LogLevel {
  LOGGING_LEVEL_DEBUG = 10,
  LOGGING_LEVEL_INFO = 20,
  LOGGING_LEVEL_WARN = 30,
  LOGGING_LEVEL_ERROR = 40,
  LOGGING_LEVEL_CRITICAL = 50
} LogLevel;

static const char *timeFormat = "%FT%TZ";
static LogLevel logLevel = LOGGING_LEVEL_ERROR;

static void print(const char *string, const char *colourFmtString);

LogLevel ulLogSetLevel(LogLevel newLevel);
void ulLogDebug(const char* fmt, ...) __attribute__((format(printf,1,2)));
void ulLogInfo(const char* fmt, ...) PRINTFLIKE(1, 2);
void ulLogWarn(const char* fmt, ...) PRINTFLIKE(1, 2);
void ulLogError(const char* fmt, ...) PRINTFLIKE(1, 2);
void ulLogCritical(const char* fmt, ...) PRINTFLIKE(1, 2);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UNLEASH_CLIENT_C_INCLUDE_UTILS_LOG_H_