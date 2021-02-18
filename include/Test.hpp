#ifndef VIRTUAL_CANVAS_TESTS_TEST_H
#define VIRTUAL_CANVAS_TESTS_TEST_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

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

// #define TEST(test_number, test_name, test_code...) int test_name() { test_code; return 0; } \
    // inline static const int test_name ## _auto_adder = test_push_back(TestInfo(#test_name, test_number, &test_name));
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
        inline int _add_suite = AutoTest::add_test_suite(TestSuiteInfo(#suite_name, &_testInfo)); \
    }; \
    namespace suite_name


#define ASSERT_EQUALS(a, b) { \
        auto aVal = a; \
        auto bVal = b; \
        if (aVal != bVal) throw std::logic_error( \
        std::string("Assertion failed:") + #a + " != " + #b + \
        "; " + AutoTest::to_string(aVal) + " != " + AutoTest::to_string(bVal)); }
#define ASSERT_TRUE(expected) { if (!(expected)) throw std::logic_error(std::string("Assertion failed:") + #expected + " was false"); }
#define ASSERT_FALSE(unexpected) { if (expected) throw std::logic_error(std::string("Assertion failed:") + #unexpected + " was true"); }

namespace AutoTest
{
    inline std::map<std::string, std::vector<TestInfo>*> _testSuites;

    int add_test_suite(const TestSuiteInfo& testSuite);
    int run_test_suite(const std::string& suite_name);
    int run_tests();

    std::string to_string(int v);
    std::string to_string(long int v);
    std::string to_string(long long v);
    std::string to_string(unsigned v);
    std::string to_string(unsigned long v);
    std::string to_string(unsigned long long v);
    std::string to_string(float v);
    std::string to_string(double v);
    std::string to_string(long double v);

    template<class T>
    std::string to_string(const T& t)
    {
        return (std::string)t;
    }

    template<class T>
    std::string to_string(const std::vector<T>& v_t)
    {
        std::string str = "[ ";

        for (unsigned int i = 0; i < v_t.size() - 1; i++)
        {
            str += AutoTest::to_string(v_t[i]) + ", ";
        }

        str += AutoTest::to_string(v_t[v_t.size() - 1]) + " ]";

        return str;
    }
}

#endif
