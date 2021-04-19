add_library(auto_test_src_module SHARED
        auto_test.hpp
        auto_test/MatcherRunner.hpp
        auto_test/to_string.hpp
        auto_test/matchers/isEqual.hpp
        auto_test/matchers/Matcher.hpp
        auto_test/matchers/noMatch.hpp
        auto_test/matchers/vector/SlidingWindowVectorMatcher.hpp

        ../src/auto_test.cpp
        ../src/auto_test/to_string.cpp
        )
target_include_directories(auto_test_src_module PRIVATE ./)
SET_TARGET_PROPERTIES(auto_test_src_module PROPERTIES LINKER_LANGUAGE CXX)
