#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>
using namespace boost::assign;

#include <cucumber-cpp/internal/utils/Regex.hpp>
using namespace cucumber::internal;

TEST(RegexTest, matchesSimpleRegex) {
    Regex exact("^cde$");

    RegexMatch::pointer match(exact.find("cde"));
    EXPECT_TRUE(match->matches());
    EXPECT_TRUE(match->getSubmatches().empty());

    assign(match, exact.find("abcdefg"));
    EXPECT_FALSE(match->matches());
    EXPECT_TRUE(match->getSubmatches().empty());
}

TEST(RegexTest, matchesRegexWithoutSubmatches) {
    Regex variable("x\\d+x");

    RegexMatch::pointer match(variable.find("xxxx123xxx"));
    EXPECT_TRUE(match->matches());

    assign(match, variable.find("xxx"));
    EXPECT_FALSE(match->matches());
}

TEST(RegexTest, matchesRegexWithSubmatches) {
    Regex sum("^(\\d+)\\+\\d+=(\\d+)$");

    RegexMatch::pointer match(sum.find("1+2=3 "));
    EXPECT_FALSE(match->matches());
    EXPECT_TRUE(match->getSubmatches().empty());

    assign(match, sum.find("42+27=69"));
    EXPECT_TRUE(match->matches());
    ASSERT_EQ(2, match->getSubmatches().size());
    EXPECT_EQ("42", match->getSubmatches()[0].value);
    EXPECT_EQ("69", match->getSubmatches()[1].value);
}

TEST(RegexTest, findAllDoesNotMatchIfNoTokens) {
    Regex sum("([^,]+)(?:,|$)");
    RegexMatch::pointer match(sum.findAll(""));

    EXPECT_FALSE(match->matches());
    EXPECT_EQ(0, match->getSubmatches().size());
}

TEST(RegexTest, findAllExtractsTheFirstGroupOfEveryToken) {
    Regex sum("([^,]+)(?:,|$)");
    RegexMatch::pointer match(sum.findAll("a,b,cc"));

    EXPECT_TRUE(match->matches());
    EXPECT_EQ(3, match->getSubmatches().size());
    //EXPECT_THAT(match.getSubmatches(), ElementsAre("a", "b", "cc"));
}

/*
TEST(RegexTest, findAllHasToMatchTheEntireInput) {
    Regex sum("([^,]+)(?:,|$)");
    RegexMatch::pointer match(sum.findAll("1 a,b,cc"));

    EXPECT_FALSE(match->matches());
    EXPECT_EQ(0, match->getSubmatches().size());
}
*/
