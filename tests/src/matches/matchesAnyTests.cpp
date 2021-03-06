#include <auto_test.hpp>

using namespace auto_test::matchers;

TEST_SUITE(matchesAnyTests)
{
    TEST(0, shouldMatchAnySubMatchesMatches)
    {
        ASSERT_MATCHES(true)(matchesAny {
            isEqual(true),
            isEqual(false)
        });
    }
}