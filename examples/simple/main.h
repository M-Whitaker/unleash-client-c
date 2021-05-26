#include <stdlib.h>

#include <unleash.h>

#define AUTH_TOKEN_LENGTH 100

typedef struct CommandLineArguments {
  char authToken[AUTH_TOKEN_LENGTH];
} CommandLineArguments;
