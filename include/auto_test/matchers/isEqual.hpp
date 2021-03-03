#ifndef LIB_AUTO_TEST_MATCHERS_IS_EQUAL_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_IS_EQUAL_MATCHER_HPP

#include "Matcher.hpp"
#include <auto_test/to_string.hpp>
#include <optional>

namespace auto_test::matchers
{
    /**
     * @brief Matches values when they are equal.
     * 
     * @tparam T Type of the value to be matched.
     */
    template<class T>
    class isEqual: public Matcher<T>
    {
    private:
        const std::optional<std::string> _expectedIdentifier;
        const T& _expected;
    public:
        /**
         * @param expected The value that the tested value is supposed to match against.
         */
        isEqual(const T& expected):
            _expectedIdentifier(std::nullopt),
            _expected(expected)
        {
            
        }
        
        /**
         * @param expectedIdentifier The identifier for the expected value.
         * @param expected The value that the tested value is supposed to match against.
         */
        isEqual(const std::string& expectedIdentifier, const T& expected):
            _expectedIdentifier(std::make_optional(expectedIdentifier)),
            _expected(expected)
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