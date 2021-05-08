#ifndef LIB_AUTO_TEST_TO_STRING_HPP
#define LIB_AUTO_TEST_TO_STRING_HPP

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <type_traits>
#include <trlang/functional/optional.hpp>

namespace auto_test
{
    std::string to_string(bool v);
    std::string to_string(int v);
    std::string to_string(long int v);
    std::string to_string(long long v);
    std::string to_string(unsigned v);
    std::string to_string(unsigned long v);
    std::string to_string(unsigned long long v);
    std::string to_string(float v);
    std::string to_string(double v);
    std::string to_string(long double v);

#if __cplusplus >= 201704L
    template<class T>
        requires std::is_enum_v<T>
    std::string to_string(const T& t)
    {
        return std::to_string((int)t);
    }
#endif

    template<class T>
    std::string to_string(const trl::optional<T>& t)
    {
        if (t.has_value())
        {
            return std::string("trl::opt(") + to_string(t.value()) + ")";
        }
        else
        {
            return "trl::nullopt";
        }
    }

    template<class T>
    std::string to_string(const T& t)
    {
        return static_cast<std::string>(t);
    }

template<class T>
std::string to_string(const std::vector<T>& v_t)
    {
        if (v_t.empty())
        {
            return "[]";
        }

        std::string str = "[ ";

        for (unsigned int i = 0; i < v_t.size() - 1; i++)
        {
            str += auto_test::to_string(v_t.at(i)) + ", ";
        }

        str += auto_test::to_string(v_t.at(v_t.size() - 1)) + " ]";

        return str;
    }

    template<class T>
    std::string to_string(const std::set<T>& v_t)
    {
        std::string str = "{ ";

        std::for_each(
            v_t.cbegin(),
            v_t.cend(),
            [&str](const T& value) {
                str += auto_test::to_string(value) + ", ";
            });

        str += "}";

        return str;
    }
}

#endif