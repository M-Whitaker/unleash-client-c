//
// Created by Matt Whitaker on 17/05/2021.
//

#include <fstream>

#include "test.h"

#ifdef ULTEST_INTERNET

TEST(Unit_NetworkingTest, HTTPTextGetRequest) {
  Response response;
  request_get("http://neverssl.com", &response, RESPONSE_TYPE_TEXT, nullptr, true);
  std::ifstream t(TEST_FOLDER_PATH "/unit/resources/neverssldotcom.html");
  std::string genFile((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());
  ASSERT_EQ(response.text, genFile) << "Output should equal the file at in " TEST_FOLDER_PATH "/unit/resources/neverssldotcom.html";
}

TEST(Unit_NetworkingTest, HTTPResponseCodeGetRequest) {
  Response response;
  request_get("http://neverssl.com", &response, RESPONSE_TYPE_TEXT, nullptr, true);
  ASSERT_EQ(response.statusCode, 200);
  ASSERT_TRUE(response.ok);
}

TEST(Unit_NetworkingTest, HTTPSInvalidCertificateError) {
  Response response;
  request_get("https://neverssl.com", &response, RESPONSE_TYPE_TEXT, nullptr, true);
  ASSERT_FALSE(response.ok) << "Response.ok should be false because of invalid SSL Certificate";
}

#endif
