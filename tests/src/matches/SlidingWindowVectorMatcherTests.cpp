#include <auto_test.hpp>
#include <vector>

using namespace auto_test::matchers;
using namespace auto_test::matchers::vector;

TEST_SUITE(SlidingWindowVectorMatcherTests)
{
    TEST(7, shouldMatchWhenPartOfSequenceMatchesSubMatcher)
    {
        std::vector<int> fullSequence {
            1, 2, 3, 4, 5, 6
        };

        ASSERT_MATCHES(fullSequence)(SlidingWindowVectorMatcher(2, isEqual(
            std::vector { 4, 5 }
        )));
    }
    
    TEST(7, shouldNotMatchWhenNoPartOfSequencesMatchesSubMatcher)
    {
        std::vector<int> fullSequence {
            1, 2, 3, 4, 5, 6
        };

        ASSERT_MATCHES(fullSequence)(noMatch(SlidingWindowVectorMatcher(2, isEqual(
            std::vector { 10, 11 }
        ))));
    }
    
    IGNORE_TEST(7, shouldMatchWhenSequenceFromNegativeMatcherDoesNotAppear)
    {
        std::vector<int> fullSequence {
            1, 2, 3, 4, 5, 6
        };

        ASSERT_MATCHES(fullSequence)(SlidingWindowVectorMatcher(2, noMatch(isEqual(
            std::vector { 10, 11 }
        ))));
    }

    IGNORE_TEST(7, shouldNotMatchWhenSequenceFromNegativeMatcherDoesAppear)
    {
        std::vector<int> fullSequence {
            1, 2, 3, 4, 5, 6
        };

        ASSERT_MATCHES(fullSequence)(noMatch(SlidingWindowVectorMatcher(2, noMatch(isEqual(
            std::vector { 4, 5 }
        )))));
    }
}