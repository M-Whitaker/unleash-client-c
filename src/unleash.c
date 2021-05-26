#include "unleash.h"

UlHandle *ulInit(UlConfigInfo *sInfo) {
  // Construct the ulHandle for future calls.
  UlHandle *ulHandle = malloc(sizeof(UlHandle));
  ulHandle->info = *sInfo;
  request_init();
  return ulHandle;
}

void ulDestroy(UlHandle *pUnleash) {
  request_destroy();
  free(pUnleash->info.headers);
  free(pUnleash);
}

bool ulGetEnabled(UlHandle *pUnleash, ULChar featureName, bool featureDefault) {
  if ((void *) featureDefault == NULL)
    featureDefault = false;
  Response response;
  request_get(pUnleash->info.apiUrl, &response, RESPONSE_TYPE_JSON, pUnleash->info.headers, debug);
  if (response.ok) {
    ulLogDebug("data: %s\n"
           "size: %lu bytes\n", response.text, (unsigned long)response.size);
    struct json_object *root;
    root = json_tokener_parse(response.text);
    struct json_object *links = json_object_object_get(root, "links");
    struct json_object *client = json_object_object_get(links, "client");
    struct json_object *clientLinks = json_object_object_get(client, "links");
    struct json_object *featureToggles = json_object_object_get(clientLinks, "feature-toggles");
    const char *url = json_object_get_string(json_object_object_get(featureToggles, "uri"));
    ulLogDebug("FEATURE TOGGLES URI: %s\n", url);
    free(response.text);
    response = (const Response){ 0 };
    //TODO: Compute size based on url
    ULChar newUrl = (ULChar ) malloc(100 * sizeof(char));
    unsigned long apiUrlLength = strlen(pUnleash->info.apiUrl);
    ULChar baseUrl = (ULChar ) malloc((apiUrlLength - 4) * sizeof(char));
    strncpy(baseUrl, pUnleash->info.apiUrl, apiUrlLength - 4);
    baseUrl[apiUrlLength - 4] = 0;
    sprintf(newUrl, "%s%s", baseUrl, url);
    ulLogDebug("%s\n", newUrl);
    request_get(newUrl, &response, RESPONSE_TYPE_JSON, pUnleash->info.headers, debug);
    ulLogDebug("%s\n", response.text);
    root = json_tokener_parse(response.text);
    free(newUrl);
    free(response.text);
    // Get the feature flags to check.
    struct json_object *features = json_object_object_get(root, "features");
    size_t arrayLen = json_object_array_length(features);
    for (int i = 0; i < arrayLen; i++) {
      struct json_object *item = json_object_array_get_idx(features, i);
      const char *itemName = json_object_get_string(json_object_object_get(item, "name"));
      if (strcmp(featureName, itemName) == 0) {
        return json_object_get_boolean(json_object_object_get(item, "enabled"));
      } else {
        ulLogDebug("%s != %s\n", featureName, itemName);
      }
    }
    //TODO: Warn user feature not found.
    return featureDefault;
  }
  else {
    //TODO: Warn user bad request.
    return false;
  }
}
void ulToggleDebug() {
  debug = !debug;
}
