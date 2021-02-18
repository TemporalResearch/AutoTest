#include "Test.hpp"

#include <algorithm>
#include <string>


int AutoTest::add_test_suite(const TestSuiteInfo& testSuite)
{
    _testSuites[testSuite._suite_name] = testSuite._suite_tests;
    return 0;
}

int AutoTest::run_test_suite(const std::string& suite_name)
{
    unsigned int testFailures = 0;
    
    std::vector<TestInfo>* suite = AutoTest::_testSuites[suite_name];
    
    std::cout << "Running suite '" << suite_name << "'" << std::endl;
    std::for_each(
        suite->cbegin(),
        suite->cend(),
        [&testFailures](TestInfo testInfo)
        {
            try
            {
                std::cout << "    #" << testInfo._issue_number << ": ";
                testInfo._testFunction();
                std::cout << testInfo._test_name << " passed" << std::endl;
            }
            catch (std::logic_error err)
            {
                std::cout << testInfo._test_name << " failed with: " << err.what() << std::endl;
                testFailures++;
            }
        }
    );

    if (testFailures > 0)
    {
        std::cout << testFailures << " tests failed in suite '" << suite_name << "'" << std::endl;
    }
    else
    {
        std::cout << "All tests passed in suite '" << suite_name << "'" << std::endl;
    } 
    
    return testFailures;
}


int AutoTest::run_tests()
{
    unsigned int totalTestFailures = 0;

    std::cout << "Running test suites" << std::endl;

    std::for_each(
        AutoTest::_testSuites.cbegin(),
        AutoTest::_testSuites.cend(),
        [&totalTestFailures](auto suite) {
            unsigned int testFailures = AutoTest::run_test_suite(suite.first);
            totalTestFailures += testFailures;
        }
    );

    if (totalTestFailures > 0)
    {
        std::cout << "Total test failures from all suites: " << totalTestFailures << std::endl;
        return 1;
    }
    else
    {
        std::cout << "All suites passed" << std::endl;
        return 0;
    }

}

std::string AutoTest::to_string(int v)
{
    return std::to_string(v);
}
std::string AutoTest::to_string(long int v)
{
    return std::to_string(v);
}
std::string AutoTest::to_string(long long v)
{
    return std::to_string(v);
}
std::string AutoTest::to_string(unsigned v)
{
    return std::to_string(v);
}
std::string AutoTest::to_string(unsigned long v)
{
    return std::to_string(v);
}
std::string AutoTest::to_string(unsigned long long v)
{
    return std::to_string(v);
}
std::string AutoTest::to_string(float v)
{
    return std::to_string(v);
}
std::string AutoTest::to_string(double v)
{
    return std::to_string(v);
}
std::string AutoTest::to_string(long double v)
{
    return std::to_string(v);
}
