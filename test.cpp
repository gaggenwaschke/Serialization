/**
 * @file
 * @author Joshua Lauterbach (gaggenwaschke@gmail.com)
 * @brief test file for Serialization
 * @version 1.0
 * @date 2021-09-14
 * @license MIT
 */

#include "const_string.hpp"
#include "descriptor.hpp"
#include <iostream>

struct A
{
    int member_1;
    int member_2;

    void func_1() {std::cout << "func_1" << std::endl;}

    constexpr static std::string_view class_name{"A"};
    constexpr static auto descriptors = std::make_tuple(
            member_descriptor{"member_1", &A::member_1},
            member_descriptor{"member_2", &A::member_2},
            member_descriptor{"func_1", &A::func_1}
    );
};

void test_string()
{
    constexpr std::array<char, 6> a1{'H', 'e', 'l', 'l', 'o', ' '};
    constexpr char a2[]{'H', 'e', 'y', ' '};

    constexpr basic_const_string s1{a1};
    constexpr const_string s2{a2};
    constexpr const_string s3{"Dude!"};

    std::cout << (std::ranges::range<decltype(s1)> ? "const_string is range." : "const_string is not range.") << std::endl;

    constexpr const_string s4{s3};

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    std::cout << s4 << std::endl;

    constexpr const_string s5{std::move(s1)};

    std::cout << s1 << std::endl;
    std::cout << s5 << std::endl;

    constexpr auto s6 = s2 + s3;
    std::cout << s6 << std::endl;
}

void test_reflective()
{
    std::cout << (reflective<A> ? "A is reflective." : "A is not reflective.") << std::endl;

}

int main()
{
    test_string();
    test_reflective();

    return 0;
}