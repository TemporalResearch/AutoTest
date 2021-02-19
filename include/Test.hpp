#ifndef VIRTUAL_CANVAS_TESTS_TEST_H
#define VIRTUAL_CANVAS_TESTS_TEST_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

#include "matchers.hpp"
#include "to_string.hpp"
#include "MatcherRunner.hpp"

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


#define IGNORE_TEST(test_number, test_name) int test_name() // test ignored

#define TEST(test_number, test_name) void test_name(); \
    inline static const int test_name ## _auto_adder = test_push_back(TestInfo(#test_name, test_number, &test_name)); \
    void test_name()

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

#define ASSERT_EQUALS(expected, actual) { \
        auto expVal = expected; \
        auto actVal = actual; \
        auto matcher_runner = auto_test::MatcherRunner(#expected, expVal); \
        matcher_runner.test( \
            auto_test::matchers::isEqual(#actual, actVal) \
        ); }

#define ASSERT_TRUE(expected) { \
    bool expVal = expected; \
    auto matcher_runner = auto_test::MatcherRunner(#expected, expVal); \
    matcher_runner.test( \
        auto_test::matchers::isEqual("true", true) \
    ); }

#define ASSERT_FALSE(expected) { \
    bool expVal = expected; \
    auto matcher_runner = auto_test::MatcherRunner(#expected, expVal); \
    matcher_runner.test( \
        auto_test::matchers::isEqual("false", false) \
    ); }


namespace auto_test
{
    inline std::map<std::string, std::vector<TestInfo>*> _testSuites;

    int add_test_suite(const TestSuiteInfo& testSuite);
    int run_test_suite(const std::string& suite_name);
    int run_tests();
}

#endif
