#ifndef LIB_AUTO_TEST_MATCHERS_VECTOR_SLIDING_WINDOW_VECTOR_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_VECTOR_SLIDING_WINDOW_VECTOR_MATCHER_HPP

#include <auto_test/matchers/Matcher.hpp>
#include <vector>
#include <string>
#include <optional>

namespace auto_test::matchers::vector
{
    /**
     * @brief Matches vectors against a sub-matcher by looking at a sliding window.
     * 
     * @tparam T Type of the vector's elements.
     */
    template<class T>
    class SlidingWindowVectorMatcher: public Matcher<std::vector<T>>
    {
    private:
        const unsigned int _windowSize;
        const auto_test::matchers::Matcher<std::vector<T>>& _windowMatcher;
    public:
        /**
         * @brief Construct a new Sliding Window Vector Matcher
         * 
         * @param windowSize The size of the window inside the vector to match against.
         * @param windowMatcher The matcher that the window should match against.
         */
        SlidingWindowVectorMatcher(const unsigned int& windowSize, const auto_test::matchers::Matcher<std::vector<T>>& windowMatcher):
            _windowSize(windowSize),
            _windowMatcher(windowMatcher)
        {
            
        }

        const std::optional<std::string> test(const std::string& actualIdentifier, const std::vector<T>& actual) const override
        {
            for (unsigned int windowStart = 0; windowStart < (actual.size() - _windowSize); windowStart++)
            {
                // FIXME: #7 this is a bit yuck, is there really no better way to match on vectors than this? Should not really have to allocate each window
                std::vector<T> subVector(actual.cbegin() + windowStart, actual.cbegin() + windowStart + _windowSize);
                
                std::optional<std::string> testResult = _windowMatcher.test(actualIdentifier, subVector);
                if(!testResult)
                {
                    return std::nullopt;
                }
            }
            
            return this->description(actualIdentifier, actual);
        }
    };
}

#endif