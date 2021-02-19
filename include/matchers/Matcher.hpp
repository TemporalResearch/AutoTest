#ifndef LIB_AUTO_TEST_MATCHERS_MATCHER_HPP
#define LIB_AUTO_TEST_MATCHERS_MATCHER_HPP

#include <optional>
#include <string>

namespace auto_test::matchers
{
    template<class T>
    class Matcher
    {
    public:
        virtual ~Matcher() { }
        virtual const std::optional<std::string> test(const std::string& expectedIdentifier, const T& expected) const = 0;

        virtual const std::string description(const std::string& expectedIdentifier, const T& expected) const
        {
            return expectedIdentifier + " does not match";
        }
    };
};

#endif