//
// Created by Matt Whitaker on 16/05/2021.
//

#ifndef UNLEASH_CLIENT_C_INCLUDE_UNLEASH_H_
#define UNLEASH_CLIENT_C_INCLUDE_UNLEASH_H_

#include "utils/request.h"
#include "utils/log.h"
#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

static bool debug = false;

typedef struct UlConfigInfo {
  ULChar apiUrl;
  ULChar appName;
  HeaderNode *headers;
} UlConfigInfo;

typedef struct UlHandle {
  UlConfigInfo info;
} UlHandle;

UlHandle* ulInit(UlConfigInfo *sInfo);
void ulDestroy(UlHandle *pUnleash);
void ulToggleDebug();
int ulCheckError();
bool ulGetEnabled(UlHandle *pUnleash, ULChar featureName, bool featureDefault);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // UNLEASH_CLIENT_C_INCLUDE_UNLEASH_H_
