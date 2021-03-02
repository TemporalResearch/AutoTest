#ifndef LIB_AUTO_TEST_MATCHERS_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_MATCHER_HPP

#include <optional>
#include <string>

namespace auto_test::matchers
{
    /**
     * @brief The base class for a Matcher against a value of type T
     * 
     * @tparam T Type of the value to match against.
     */
    template<class T>
    class Matcher
    {
    public:
        virtual ~Matcher() { }
        
        /**
         * @brief Tests a value to see if it satisfies the matcher.
         * 
         * @param actualIdentifier The string to identify the value being provided.
         * @param actual The value being provided to match against.
         * @return const std::optional<std::string> Returns an error string if the value did not match.
         */
        virtual const std::optional<std::string> test(const std::string& actualIdentifier, const T& actual) const = 0;

        /**
         * @brief A description of how the value provided does not match.
         * 
         * @param actualIdentifier The string to identify the value being provided.
         * @param actual The value being provided to match against.
         * @return const std::string 
         */
        virtual const std::string description(const std::string& actualIdentifier, const T& actual) const
        {
            return actualIdentifier + " does not match";
        }
    };
};

#endif