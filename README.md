# AutoTest

A C++ testing framework providing automatic testing and matchers.


## Example

```C++
#include <auto_test.hpp>

TEST_SUITE(ExampleTests)
{
    TEST(0, shouldRunThisTestAutomatically)
    {
        ASSERT_TRUE(1 == 1);
    }
}

int main()
{
    auto_test::run_tests();
}
```

### Output:
```
Running test suites
Running suite 'ExampleTests'
    #0: shouldRunThisTestAutomatically passed
All tests passed in suite 'ExampleTests'
All suites passed
```

## Issue Tracking
Main issue tracking available at https://git.supermarinesoftware.com/TemporalResearch/AutoTest/issues

Documentation available at https://docs.temporalresearch.co.uk/autotest.git/