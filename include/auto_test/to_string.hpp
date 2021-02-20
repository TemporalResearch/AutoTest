#ifndef LIB_AUTO_TEST_TO_STRING_HPP
#define LIB_AUTO_TEST_TO_STRING_HPP

#include <string>

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
            str += auto_test::to_string(v_t[i]) + ", ";
        }

        str += auto_test::to_string(v_t[v_t.size() - 1]) + " ]";

        return str;
    }
}

#endif