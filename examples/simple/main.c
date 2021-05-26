#include "main.h"

#include <utils/log.h>

void help() {
  printf("OVERVIEW: An example application for the unleash-client in C\n"
         "USAGE: example [options] apiurl\n"
         "OPTIONS: \n"
         "\t --auth <bearer token> \t: The API authentication client token from unleash.\n"
         "\t --help \t: This help message.\n");
}

int main(int argc, const char** argv) {
  ulLogSetLevel(LOGGING_LEVEL_ERROR);
  ulLogDebug("Parsing Command Line Arguments...\n");
  CommandLineArguments cmdArgs = {0};
  for (int i = 1; i < argc - 1; i++) {
    if(strcmp(argv[i], "--auth") == 0) {
      i++;
      strcpy(cmdArgs.authToken, argv[i]);
    } else if (strcmp(argv[i], "--help") == 0) {
      help();
      exit(0);
    } else {
      printf("Invalid Argument %s\n", argv[i]);
    }
  }

  UlConfigInfo info = {};
  info.apiUrl = (ULChar) malloc(100 * sizeof(char));
  strcpy(info.apiUrl, argv[argc - 1]);
  info.appName = "cpp-example";
  HeaderNode *auth, *second = NULL;
  auth = (HeaderNode *) malloc(sizeof(HeaderNode));
  second = (HeaderNode *) malloc(sizeof(HeaderNode));
  auth->data = (ULChar) malloc((AUTH_TOKEN_LENGTH + 15) * sizeof(char));
  sprintf(auth->data, "Authorization: %s", cmdArgs.authToken);
  auth->next = second;
  second->data = "User-Agent: Mozilla/5.0 (<system-information>) <platform> (<platform-details>) <extensions>";
  second->next = NULL;
  info.headers = auth;

  UlHandle *ul = ulInit(&info);

  printf("Feature1 is %s\n", ulGetEnabled(ul, "DemoToggle", NULL) ? "true" : "false");
  printf("Feature2 is %s\n", ulGetEnabled(ul, "DemoToggle2", NULL) ? "true" : "false");
  ulDestroy(ul);
  free(info.apiUrl);
}
