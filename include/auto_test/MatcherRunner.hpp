#ifndef LIB_AUTO_TEST_MATCHER_RUNNER_HPP
#define LIB_AUTO_TEST_MATCHER_RUNNER_HPP

#include <string>
#include <auto_test/matchers/Matcher.hpp>

namespace auto_test
{
    template<class T>
    class MatcherRunner
    {
    private:
        const std::string _actualIdentifier;
        const T& _actual;
    public:
        MatcherRunner(const std::string& actualIdentifier, const T& actual):
            _actualIdentifier(actualIdentifier),
            _actual(actual)
        {

        }
        
        void test(const auto_test::matchers::Matcher<T>& matcher)
        {
            std::optional result = matcher.test(_actualIdentifier, _actual);
            if (result)
            {
                throw std::logic_error(
                    result.value()
                );
            }
        }
    };
};

#endif