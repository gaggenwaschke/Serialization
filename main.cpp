/**
 * @file
 * @author Joshua Lauterbach (gaggenwaschke@gmail.com)
 * @brief test file for Serialization
 * @version 1.0
 * @date 2021-09-14
 * @license MIT
 */

#include <tuple>
#include <concepts>
#include <iostream>
#include <array>

/*----------------------*/
/* --- Const string --- */
/*----------------------*/

template <typename RangeType, typename CharType>
concept compile_time_input_for =
std::ranges::input_range<RangeType> &&
requires
{
    std::is_convertible_v<std::ranges::range_value_t<RangeType>, CharType>;
    typename std::tuple_size<RangeType>;
};

template <std::size_t Size, typename CharType>
class basic_const_string
{
private:
    std::array<CharType, Size> data;

public:
    using char_type = CharType;
    constexpr static std::size_t string_size{Size};

    constexpr std::size_t size() const noexcept
    {
        return string_size;
    }

    // CTORs

    basic_const_string() = delete;
    constexpr basic_const_string(basic_const_string&& other) : data{std::move(other.data)}
    {}
    constexpr basic_const_string& operator=(const basic_const_string& other) = default;
    constexpr basic_const_string(const basic_const_string& other) : data{other.data}
    {}

    template <std::size_t OtherSize>
    requires (OtherSize <= Size)
    constexpr basic_const_string(const basic_const_string<OtherSize, CharType>& other)
    {
        std::copy(std::ranges::cbegin(other), std::ranges::cend(other), std::ranges::begin(data));
    }

    template <typename RangeType>
    requires compile_time_input_for<RangeType, CharType>
    constexpr basic_const_string(const RangeType& range)
    {
        std::copy(std::ranges::cbegin(range), std::ranges::cend(range), std::begin(data));
    }

    template <typename RangeType>
    constexpr basic_const_string(const CharType (&c_array)[Size])
    {
        std::copy(std::ranges::cbegin(c_array), std::ranges::cend(c_array), std::begin(data));
    }

    // Range functions

    constexpr auto begin() const
    {
        return std::ranges::cbegin(data);
    }

    constexpr auto end() const
    {
        return std::ranges::cend(data);
    }

    constexpr auto& operator[] (std::size_t index)
    {
        return data[index];
    }

    // Friends

    template <typename OutStreamType>
    friend OutStreamType& operator<<( OutStreamType& stream, const basic_const_string& string)
    {
        for (auto& element : string)
        {
            stream << element;
        }
        return stream;
    }
};

template <std::size_t Size, typename CharType>
basic_const_string(basic_const_string<Size, CharType>) -> basic_const_string<Size, CharType>;

template <typename RangeType>
requires requires{ typename std::tuple_size<RangeType>; }
basic_const_string(RangeType) -> basic_const_string<std::tuple_size_v<RangeType>, std::ranges::range_value_t<RangeType>>;

template <std::size_t Size, typename CharType>
basic_const_string(const CharType (&c_array)[Size]) -> basic_const_string<Size, CharType>;

template <std::size_t Size>
using const_string = basic_const_string<Size, char>;

template <std::size_t SizeFirst, std::size_t SizeSecond, typename CharType>
constexpr auto operator+(
        const basic_const_string<SizeFirst, CharType>& first,
        const basic_const_string<SizeSecond, CharType>& second)
{
    basic_const_string<SizeFirst + SizeSecond, CharType> new_string{first};
    std::copy(std::ranges::cbegin(second), std::ranges::cend(second), new_string[SizeFirst]);
    return new_string;
}

/*--------------------*/
/* --- Reflection --- */
/*--------------------*/

struct descriptor_dummy{};

template <typename MemberPointerType>
requires
        (
                std::is_member_pointer_v<MemberPointerType>
        )
struct member_descriptor : public descriptor_dummy
{
    using member_ptr_type = MemberPointerType;

    const std::string_view name;
    const member_ptr_type member_ptr;

    member_descriptor() = delete;

    consteval member_descriptor(const member_descriptor& other) noexcept = default;
    consteval member_descriptor& operator=(const member_descriptor& other) noexcept = default;

    consteval member_descriptor(std::string_view name, member_ptr_type member_ptr) noexcept :
            name{name},
            member_ptr{member_ptr}
    {
    }
};

template <typename... DescriptorTypes>
concept are_descriptors = (std::is_base_of_v<descriptor_dummy, DescriptorTypes> && ...);

template <typename... DescriptorType>
consteval bool is_descriptor_collection(std::tuple<DescriptorType...>)
{
    return are_descriptors<DescriptorType...>;
}

template <typename CandidateType>
concept reflective = requires
{
    std::is_same_v<decltype(CandidateType::class_name), std::string_view>;
    is_descriptor_collection(CandidateType::descriptors) == true;
};

/*---------------*/
/* --- Tests --- */
/*---------------*/

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
    constexpr std::array<char, 7> a1{'H', 'e', 'l', 'l', 'o', ' ', 0};
    constexpr char a2[7]{'H', 'e', 'y', ' '};

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