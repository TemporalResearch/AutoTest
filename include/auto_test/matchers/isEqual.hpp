#ifndef LIB_AUTO_TEST_MATCHERS_IS_EQUAL_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_IS_EQUAL_MATCHER_HPP

#include "Matcher.hpp"
#include <auto_test/to_string.hpp>
#include <optional>

namespace auto_test::matchers
{
    template<class T>
    class isEqual: public Matcher<T>
    {
    private:
        const std::optional<std::string> _expectedIdentifier;
        const T& _expected;
    public:
        isEqual(const T& actual):
            _expectedIdentifier(std::nullopt),
            _expected(actual)
        {
            
        }
        
        isEqual(const std::string& actualIdentifier, const T& actual):
            _expectedIdentifier(std::make_optional(actualIdentifier)),
            _expected(actual)
        {

        }
        
        const std::optional<std::string> test(const std::string& actualIdentifier, const T& actual) const override
        {
            if (actual != _expected)
            {
                return std::make_optional(description(actualIdentifier, actual));
            }
            
            return std::nullopt;
        }
        
        const std::string description(const std::string& actualIdentifier, const T& actual) const override
        {
            if (_expectedIdentifier)
            {
                return actualIdentifier + " != " + _expectedIdentifier.value() + + "; " +
                    auto_test::to_string(actual) + " != " + auto_test::to_string(_expected);
            }
            else
            {
                std::string superDescription = Matcher<T>::description(actualIdentifier, actual);
                return superDescription + "; " + auto_test::to_string(actual) + " != " + auto_test::to_string(_expected);
            }
        }
    };
};

#endif