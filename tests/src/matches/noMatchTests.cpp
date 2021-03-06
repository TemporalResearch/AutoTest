#include <auto_test.hpp>

using namespace auto_test::matchers;

TEST_SUITE(noMatchTests)
{
    TEST(0, shouldNotMatchWhenSubMatcherMatches)
    {
        ASSERT_MATCHES(true)(isEqual(true));
        ASSERT_MATCHES(false)(noMatch(isEqual(true)));
    }
}