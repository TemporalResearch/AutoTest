#ifndef LIB_AUTO_TEST_MATCHERS_NOT_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_NOT_MATCHER_HPP

#include "Matcher.hpp"
#include <auto_test/to_string.hpp>
#include <optional>

namespace auto_test::matchers
{
    /**
     * @brief Satisfied if the internal matcher is not satisfied.
     * 
     * @tparam T The type of the value to be matched.
     */
    template<class T>
    class noMatch: public Matcher<T>
    {
    private:
        const Matcher<T>& _matcher;
    public:
        /**
         * @brief Negate the matcher provided.
         * 
         * @param matcher The matcher to be negated.
         */
        noMatch(const Matcher<T>&& matcher):
            _matcher(matcher)
        {
            
        }

        /**
         * @brief Negate the matcher provided.
         * 
         * @param matcher The matcher to be negated.
         */
        noMatch(const Matcher<T>& matcher):
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