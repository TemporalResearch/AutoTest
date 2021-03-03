#ifndef VIRTUAL_CANVAS_TESTS_TEST_H
#define VIRTUAL_CANVAS_TESTS_TEST_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

#include "auto_test/matchers.hpp"
#include "auto_test/to_string.hpp"
#include "auto_test/MatcherRunner.hpp"

struct TestInfo
{
    const char* _test_name;
    int _issue_number;
    void (*_testFunction)();

    TestInfo(const char* test_name, const int& issue_number, void (*testFunction)()):
        _test_name(test_name),
        _issue_number(issue_number),
        _testFunction(testFunction)
    {

    }
};

struct TestSuiteInfo
{
    std::string _suite_name;
    std::vector<TestInfo>* _suite_tests;

    TestSuiteInfo(const TestSuiteInfo& otherInfo):
        _suite_name(otherInfo._suite_name),
        _suite_tests(otherInfo._suite_tests)
    {
        
    }

    TestSuiteInfo(const std::string& suite_name, std::vector<TestInfo>* suite_tests):
        _suite_name(suite_name),
        _suite_tests(suite_tests)
    {

    }
};

/**
 *@defgroup test_macros Macros for adding tests
 */

/**
 * @ingroup test_macros
 * @def IGNORE_TEST(test_number, test_name)
 * @brief Defines a test that should be ignored.
 *  
 * @param test_number Issue number of the test
 * @param test_name Test name.
 */
#define IGNORE_TEST(test_number, test_name) void test_name() // test ignored

/**
 * @ingroup test_macros
 * @def DONT_COMPILE_TEST(test_number, test_name, content...)
 * @brief Defines a test that does not compile.
 * 
 * @param test_number Issue number of the test
 * @param test_name Test name.
 * @param content Contents of the test.
 */
#define DONT_COMPILE_TEST(test_number, test_name, content...) void test_name() {}

/**
 * @ingroup test_macros
 * @def TEST(test_number, test_name)
 * @brief Defines a test.
 * 
 * @param test_number Issue number of the test.
 * @param test_name Test name.
 */
#define TEST(test_number, test_name) void test_name(); \
    inline static const int test_name ## _auto_adder = test_push_back(TestInfo(#test_name, test_number, &test_name)); \
    void test_name()

/**
 * @ingroup test_macros
 * @def TEST_SUITE(suite_name)
 * @brief Defines a test suite, containing a set of tests.
 * 
 * @param suite_name Test suite name.
 */
#define TEST_SUITE(suite_name) namespace suite_name { \
        inline static std::vector<TestInfo> _testInfo;\
        int test_push_back(TestInfo testInfo) \
        { \
            _testInfo.push_back(testInfo); \
            return 0; \
        } \
        inline int _add_suite = auto_test::add_test_suite(TestSuiteInfo(#suite_name, &_testInfo)); \
    }; \
    namespace suite_name

/**
 * @defgroup assertion_macros Macros for adding assertions to be used in tests.
 */

/**
 * @ingroup assertion_macros
 * @def ASSERT_MATCHES(actual)(matcher)
 * @brief Asserts that a value matches against a set of matchers.
 * 
 * Usage:
 * ```
 * ASSERT_MATCHES(actual)(matcher)
 * ```
 * 
 * @param actual The value to match against. 
 * @param matcher The matcher which defines a successful match.
 */
#define ASSERT_MATCHES(actual) auto_test::MatcherRunner(#actual, actual).test

/**
 * @ingroup assertion_macros
 * @def ASSERT_EQUALS(actual, expected)
 * @brief Asserts that two values are equal using the `==` operator.
 * 
 * @param actual Actual value.
 * @param expected Expected value.
 */
#define ASSERT_EQUALS(actual, expected) { \
        auto actVal = actual; \
        decltype(actVal) expVal = expected; \
        auto matcher_runner = auto_test::MatcherRunner(#actual, actVal); \
        matcher_runner.test( \
            auto_test::matchers::isEqual(#expected, expVal) \
        ); }

/**
 * @ingroup assertion_macros
 * @def ASSERT_TRUE(actual)
 * @brief Asserts that a value is true.
 * 
 * @param actual Actual value.
 */
#define ASSERT_TRUE(actual) { \
    bool actVal = actual; \
    auto matcher_runner = auto_test::MatcherRunner(#actual, actVal); \
    matcher_runner.test( \
        auto_test::matchers::isEqual("true", true) \
    ); }

/**
 * @ingroup assertion_macros
 * @def ASSERT_FALSE(actual)
 * @brief Asserts that a value is true.
 * 
 * @param actual Actual value.
 */
#define ASSERT_FALSE(actual) { \
    bool actVal = actual; \
    auto matcher_runner = auto_test::MatcherRunner(#actual, actVal); \
    matcher_runner.test( \
        auto_test::matchers::isEqual("false", false) \
    ); }


/**
 * @brief Main namespace for the auto_test framework.
 * 
 */
namespace auto_test
{
    inline std::map<std::string, std::vector<TestInfo>*> _testSuites;

    int add_test_suite(const TestSuiteInfo& testSuite);
    
    /**
     * @brief Run a single test suite.
     * 
     * @param suite_name The name of the suite to be run.
     *
     * @return 0 is successful.
     * @return 1 is unsuccessful.
     */
    int run_test_suite(const std::string& suite_name);
    
    /**
     * @brief To be run in the main program to automatically fun all test suites.
     * 
     * @return 0 is successful.
     * @return 1 is unsuccessful.
     */
    int run_tests();
}

#endif
