# Unleash Client SDK for C

This is an unofficial Unleash Client SDK for C. 
It is compatible with the Unleash-hosted.com SaaS offering and Unleash Open-Source. 
It also works with GitLab Feature Flags.

The architecture specification for the client is detailed at 
https://github.com/Unleash/unleash/blob/master/docs/client-specification.md 
and conformance tests are written in line with the current checkout in the 
[/test/conformance/specification](/test/conformance/specification) folder 
which is a submodule of https://github.com/Unleash/client-specification.

## Building

### Requirements
- [LibCurl](https://curl.se/libcurl/)

```commandline
git clone --recursive https://github.com/M-Whitaker/unleash-client-c.git
cd build
cmake ../
make
```

## Linking

### Static
```cmake
add_subdirectory(vendor/unleash-client-c)
add_executable(${APPLICATION_NAME} ${APPLICATION_SOURCE} ${APPLICATION_HEADERS})
target_link_libraries(${APPLICATION_NAME} PRIVATE unleash-client-c)
```

### Dynamic
```cmake
add_subdirectory(vendor/unleash-client-c)
add_executable(${APPLICATION_NAME} ${APPLICATION_SOURCE} ${APPLICATION_HEADERS})
target_link_libraries(${APPLICATION_NAME} PRIVATE unleash-client-c)
```

## Getting Started

> You will need your `API URL` and your `API token` in order to connect the Client SDK to you Unleash instance. You can find this information in the “Admin” section Unleash management UI. [Read more](../user_guide/api-token)

```C
#include <unleash.h>

// Headers are added with a linked list
auth = (HeaderNode *) malloc(sizeof(HeaderNode));
auth->data = "<API token>";
auth->next = NULL;

UlConfigInfo info = {};
// Ensure there is no trailing backslash
info.apiUrl = "<API url>";
info.appName = "<Application Name>";
info.headers = auth;

UlHandle *ul = ulInit(&info);

ulGetEnabled(ul, "DemoToggle", NULL);

// Cleans up handle and headers linked list.
ulDestroy(ul);
```

### Checking if a feature is enabled

A check of a simple toggle:

```C
ulGetEnabled(ul, "DemoToggle", NULL);
```

Specifying a default value:

```C
ulGetEnabled(ul, "DemoToggle", true);
```

For more complete examples see the [/examples](/examples) folder.
