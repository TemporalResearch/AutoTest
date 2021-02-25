#ifndef LIB_AUTO_TEST_MATCHERS_MATCHES_ANY_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_MATCHES_ANY_MATCHER_HPP

#include "Matcher.hpp"
#include <auto_test/to_string.hpp>
#include <optional>
#include <numeric>

namespace auto_test::matchers
{
    template<
        template<class T> class SubMatcher,
        class U
    >
    class matchesAny: public Matcher<U>
    {
    private:
        const std::vector<SubMatcher<U>> _matchers;
    public:
        matchesAny(std::initializer_list<SubMatcher<U>> matchers):
            _matchers(matchers)
        {

        }
        
        const std::optional<std::string> test(const std::string& actualIdentifier, const U& actual) const override
        {
            std::vector<std::string> matchErrors;
            for (int i = 0; i < _matchers.size(); i++)
            {
                auto matcherResult = _matchers[i].test(actualIdentifier, actual);
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
                std::string("No match found:\n"),
                [](const std::string current, const std::string next) {
                    return current + ";\n" + next;
                });
        }
    };
}

#endif