//
// Created by Matt Whitaker on 16/05/2021.
//

#ifndef UNLEASH_CLIENT_C_INCLUDE_UTILS_REQUEST_H_
#define UNLEASH_CLIENT_C_INCLUDE_UTILS_REQUEST_H_


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#include <curl/curl.h>
#include <json-c/json_tokener.h>

#include "utils/log.h"
#include "types.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct HeaderNode {
  ULChar data;
  struct HeaderNode *next;
} HeaderNode;

typedef struct Response {
    ULChar url;
    bool ok;
    long statusCode;
    ULChar text;
    size_t size;
} Response;

typedef enum ContentType {
    RESPONSE_TYPE_JSON,
    RESPONSE_TYPE_TEXT
} ContentType;

void request_init();
void request_destroy();

void request_get(const char *url, Response *response, ContentType contentType, HeaderNode *headers, bool debug);
static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

#ifdef __cplusplus
} // extern "C"
#endif

#endif  // UNLEASH_CLIENT_C_INCLUDE_UTILS_REQUEST_H_
