#ifndef LIB_AUTO_TEST_MATCHERS_MATCHES_ANY_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_MATCHES_ANY_MATCHER_HPP

#include "Matcher.hpp"
#include <auto_test/to_string.hpp>
#include <optional>
#include <numeric>
#include <functional>

namespace auto_test::matchers
{
    /**
     * @brief Matches values when they match any of the internal matchers.
     * 
     * @tparam U Type of the value to be matched.
     */
    template<class U>
    class matchesAny: public Matcher<U>
    {
    private:
        std::vector<Matcher<U>*> _matchers;
        
        void pushBackMatchers() { }

        template<template <class T> class SubMatcher, template<class T> class... OtherSubMatchers>
#if __cplusplus >= 201704L
            requires std::derived_from<SubMatcher<U>, Matcher<U>>
#endif
        void pushBackMatchers(SubMatcher<U>& matcher, OtherSubMatchers<U>&... rest)
        {
            _matchers.push_back(&matcher);
            pushBackMatchers(rest...);
        }

    public:
        matchesAny():
            _matchers()
        {

        }
        
        /**
         * @brief Creates a matcher which is satisfied if any of the sub-matchers are satisfied.
         * 
         * @tparam SubMatcher Must be of type Matcher<U>.
         * @tparam OtherSubMatchers Must all be of type Matcher<U>.
         * @param matcher First sub-matcher.
         * @param rest Additional sub-matchers.
         */
        template<template<class T> class SubMatcher, template<class T> class... OtherSubMatchers>
#if __cplusplus >= 201704L
            requires std::derived_from<SubMatcher<U>, Matcher<U>>
#endif
        matchesAny(SubMatcher<U>&& matcher, OtherSubMatchers<U>&&... rest):
            _matchers()
        {
            pushBackMatchers(matcher, rest...);
        }

        
        const std::optional<std::string> test(const std::string& actualIdentifier, const U& actual) const override
        {
            std::vector<std::string> matchErrors;
            for (unsigned int i = 0; i < _matchers.size(); i++)
            {
                auto matcherResult = _matchers[i]->test(actualIdentifier, actual);
                if (matcherResult)
                {
                    matchErrors.push_back(matcherResult.value());
                }
                else
                {
                    return std::nullopt;
                }
            }
            
            return std::reduce(
                matchErrors.cbegin(),
                matchErrors.cend(),
                std::string("\nNo match found:\n"),
                [](const std::string current, const std::string next) {
                    return current + next + ";\n";
                });
        }
    };
}

#endif