#ifndef LIB_AUTO_TEST_MATCHERS_IS_NOT_EQUAL_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_IS_NOT_EQUAL_MATCHER_HPP

#include "Matcher.hpp"
#include <auto_test/to_string.hpp>
#include <optional>

namespace auto_test::matchers
{
    template<class T>
    class isNotEqual: public Matcher<T>
    {
    private:
    public:
        isNotEqual(const T& actual)
        {

        }

        const std::optional<std::string> test(const std::string& actualIdentifier, const T& actual) const override
        {
            return std::make_optional(description("", actual));
        }

        const std::string description(const std::string& actualIdentifier, const T& actual) const override
        {
            return "It just isn't!";
        }
    };
}

#endif