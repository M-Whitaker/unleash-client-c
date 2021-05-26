#include "utils/request.h"


void request_init() {
  // TODO: Not thread safe; call only once
  curl_global_init(CURL_GLOBAL_ALL);
}

void request_destroy() {
  curl_global_cleanup();
}

void request_get(const char *url, Response *response, ContentType contentType, HeaderNode *headers, bool debug) {
  CURL *curl;
  CURLcode res;

  response->text = malloc(1);
  response->statusCode = 0;
  response->size = 0;
  response->url = url;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    // set the callback function to send data to.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)response);

    // Set HTTP headers
    struct curl_slist* headerList = NULL;
    if (contentType == RESPONSE_TYPE_JSON) {
      headerList = curl_slist_append(headerList, "Content-Type: application/json");
    }
    HeaderNode *current = headers;
    while (current != NULL) {
      ulLogDebug("HEADER: %s\n", current->data);
      headerList = curl_slist_append(headerList, current->data);
      current = current->next;
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    if (debug)
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // Perform request
    res = curl_easy_perform(curl);
    if(res != CURLE_OK) {
      response->ok = false;
      ulLogError("Curl Request ERROR: %s\n",
                 curl_easy_strerror(res));
    } else {
      char *ct;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response->statusCode);
      curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);
      ulLogDebug("status code: %ld\n", response->statusCode);
      // TODO: Check 20x codes rather than just 200
      if(response->statusCode == 200) {
        response->ok = true;
      } else {
        response->ok = false;
      }
    }
    curl_easy_cleanup(curl);
  }
}

/**
 * @brief 
 * 
 * @param data Delivered data.
 * @param size Is always 1.
 * @param nmemb Size of delivered data.
 * @param userp 
 * @return size_t The number of bytes actually taken care of.
 */
static size_t write_data(void *data, size_t size, size_t nmemb, void *userp) {
  Response *mem = (Response *)userp;
  size_t bufferSize = size * nmemb;

  char *ptr = realloc(mem->text, mem->size + bufferSize + 1);
  if(!ptr) {
    ulLogError("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->text = ptr;
  memcpy(&(mem->text[mem->size]), data, bufferSize);
  mem->size += bufferSize;
  mem->text[mem->size] = 0;

  return bufferSize;
}
