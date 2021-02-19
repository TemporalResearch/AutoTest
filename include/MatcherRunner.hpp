#ifndef LIB_AUTO_TEST_MATCHER_RUNNER_HPP
#define LIB_AUTO_TEST_MATCHER_RUNNER_HPP

#include <string>

namespace auto_test
{
    template<class T>
    class MatcherRunner
    {
    private:
        const std::string _expectedIdentifier;
        const T& _expected;
    public:
        MatcherRunner(const std::string& expectedIdentifier, const T& expected):
            _expectedIdentifier(expectedIdentifier),
            _expected(expected)
        {

        }
        
        void test(const auto_test::matchers::Matcher<T>& matcher)
        {
            std::optional result = matcher.test(_expectedIdentifier, _expected);
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