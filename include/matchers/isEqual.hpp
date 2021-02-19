#ifndef LIB_AUTO_TEST_MATCHERS_IS_EQUAL_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_IS_EQUAL_MATCHER_HPP

#include "Matcher.hpp"
#include <to_string.hpp>
#include <stdexcept>
#include <optional>

namespace auto_test::matchers
{
    template<class T>
    class isEqual: public Matcher<T>
    {
    private:
        const std::optional<std::string> _actualIdentifier;
        const T& _actual;
    public:
        isEqual(const T& actual):
            _actualIdentifier(std::nullopt),
            _actual(actual)
        {
            
        }
        
        isEqual(const std::string& actualIdentifier, const T& actual):
            _actualIdentifier(std::make_optional(actualIdentifier)),
            _actual(actual)
        {

        }
        
        const std::optional<std::string> test(const std::string& expectedIdentifier, const T& expected) const override
        {
            if (expected != _actual)
            {
                return std::make_optional(description(expectedIdentifier, expected));
            }
            
            return std::nullopt;
        }
        
        const std::string description(const std::string& expectedIdentifier, const T& expected) const override
        {
            if (_actualIdentifier)
            {
                return expectedIdentifier + " != " + _actualIdentifier.value() + + "; " +
                    auto_test::to_string(expected) + " != " + auto_test::to_string(_actual);
            }
            else
            {
                std::string superDescription = Matcher<T>::description(expectedIdentifier, expected);
                return superDescription + "; " + auto_test::to_string(expected) + " != " + auto_test::to_string(_actual);
            }
        }
    };
};

#endif