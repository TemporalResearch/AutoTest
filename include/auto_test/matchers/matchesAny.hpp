#ifndef LIB_AUTO_TEST_MATCHERS_MATCHES_ANY_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_MATCHES_ANY_MATCHER_HPP

#include "Matcher.hpp"
#include <auto_test/to_string.hpp>
#include <optional>
#include <numeric>
#include <functional>
#include <concepts>

namespace auto_test::matchers
{
    template<class U>
    class matchesAny: public Matcher<U>
    {
    private:
        std::vector<Matcher<U>*> _matchers;
        
        void pushBackMatchers() { }

        template<template <class T> class SubMatcher, template<class T> class... OtherSubMatchers>
            requires std::derived_from<SubMatcher<U>, Matcher<U>>
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
        
        template<template<class T> class SubMatcher, template<class T> class... OtherSubMatchers>
            requires std::derived_from<SubMatcher<U>, Matcher<U>>
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