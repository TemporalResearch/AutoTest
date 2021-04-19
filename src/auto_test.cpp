#include <auto_test.hpp>

#include <algorithm>
#include <string>
#include <iostream>


int auto_test::add_test_suite(const TestSuiteInfo& testSuite)
{
    _testSuites[testSuite._suite_name] = testSuite._suite_tests;
    return 0;
}

int auto_test::run_test_suite(const std::string& suite_name)
{
    unsigned int testFailures = 0;

    std::vector<TestInfo>* suite = auto_test::_testSuites[suite_name];
    
    std::for_each(
        suite->cbegin(),
        suite->cend(),
        [&testFailures](TestInfo testInfo)
        {
            try
            {
                testInfo._testFunction();
            }
            catch (const std::logic_error& err)
            {
                std::cout << "    #" << testInfo._issue_number << ": ";
                std::cout << testInfo._test_name << " failed with: " << err.what() << std::endl;
                testFailures++;
            }
            catch(const std::exception& err)
            {
                std::cout << "    #" << testInfo._issue_number << ": ";
                std::cout << testInfo._test_name << " failed with non-assertion exception: " << err.what() << std::endl;
            }
        }
    );

    if (testFailures > 0)
    {
        std::cout << testFailures << " tests failed in suite '" << suite_name << "'" << std::endl;
    } 
    return testFailures;
}


int auto_test::run_tests()
{
    unsigned int totalTestFailures = 0;

    std::cout << "Running test suites" << std::endl;

    std::for_each(
        auto_test::_testSuites.cbegin(),
        auto_test::_testSuites.cend(),
        [&totalTestFailures](auto suite) {
            unsigned int testFailures = auto_test::run_test_suite(suite.first);
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