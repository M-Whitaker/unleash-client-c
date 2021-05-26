//
// Created by Matt Whitaker on 17/05/2021.
//

#include "test.h"

TEST(DISABLED_Conformance_01simpleExamples, FeatureAShouldBeEnabled) {
  ulLogSetLevel(LOGGING_LEVEL_DEBUG);
  UlConfigInfo info = {};
  info.apiUrl = "https://unleash.herokuapp.com/api";
  info.appName = "cpp-example";
  HeaderNode *auth;
  auth = (HeaderNode *) malloc(sizeof(HeaderNode));
  auth->data = "Authorization: 3bd74da5b341d868443134377ba5d802ea1e6fa2d2a948276ade1f092bec8d92";
  auth->next = nullptr;
  info.headers = auth;

  UlHandle *ul = ulInit(&info);
  ulToggleDebug();
  EXPECT_TRUE(ulGetEnabled(ul, "123", static_cast<bool>(nullptr)));
  ulDestroy(ul);
  FAIL() << "Test is not implemented";
}

TEST(DISABLED_Conformance_01simpleExamples, FeatureBShouldBeDisabled) {
  FAIL() << "Test is not implemented";
}
