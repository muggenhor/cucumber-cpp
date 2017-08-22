#include <gtest/gtest.h>
#include <cucumber-cpp/autodetect.hpp>

GIVEN("some step with a docstring")
{
  REGEX_PARAM(std::string, docstring);
  EXPECT_EQ("doc string goes here", docstring);
}
