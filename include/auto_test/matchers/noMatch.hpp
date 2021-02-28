#ifndef LIB_AUTO_TEST_MATCHERS_NOT_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_NOT_MATCHER_HPP

#include "Matcher.hpp"
#include <auto_test/to_string.hpp>
#include <optional>

namespace auto_test::matchers
{
    template<class T>
    class noMatch: public Matcher<T>
    {
    private:
        Matcher<T>& _matcher;
    public:
        noMatch(Matcher<T>&& matcher):
            _matcher(matcher)
        {
            
        }

        const std::optional<std::string> test(const std::string& actualIdentifier, const T& actual) const override
        {
            if (_matcher.test(actualIdentifier, actual))
            {
                return std::nullopt;
            }
            else
            {
                return std::make_optional(description(actualIdentifier, actual));
            }
        }
        
        const std::string description(const std::string& actualIdentifier, const T& actual) const override
        {
            auto matcherDescription = _matcher.description(actualIdentifier, actual);

            return std::string("Should have: '") + matcherDescription + "'";
        }
    };
}

#endif