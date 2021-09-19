/**
* @file
* @author Joshua Lauterbach (gaggenwaschke@gmail.com)
* @brief Const run time computable string class.
* @version 1.0
* @date 2021-09-19
* @license MIT
*/

#pragma once

#include <array>
#include <concepts>
#include <ranges>

template <typename range_type, typename char_type>
concept compile_time_input_for =
    std::ranges::input_range<range_type> &&
    requires()
{
  std::is_convertible_v<std::ranges::range_value_t<range_type>, char_type>;
  typename std::tuple_size<range_type>;
};

template <std::size_t _size, typename _char_type>
class basic_const_string
{
private:
  std::array<_char_type, _size> data;

public:
  using char_type = _char_type;
  constexpr static std::size_t Size{_size};

  constexpr std::size_t size() const noexcept
  {
    return Size;
  }

  // CTORs

  basic_const_string() = delete;
  constexpr basic_const_string(basic_const_string&& other) : data{std::move(other.data)}
  {}
  constexpr basic_const_string& operator=(const basic_const_string& other) = default;
  constexpr basic_const_string(const basic_const_string& other) : data{other.data}
  {}

  template <std::size_t other_size>
  requires (other_size <= _size)
      constexpr basic_const_string(const basic_const_string<other_size, _char_type>& other)
  {
    std::copy(std::ranges::cbegin(other), std::ranges::cend(other), std::ranges::begin(data));
  }

  template <typename range_type>
  requires compile_time_input_for<range_type, _char_type>
  constexpr basic_const_string(const range_type & range)
  {
    std::copy(std::ranges::cbegin(range), std::ranges::cend(range), std::begin(data));
  }

  template <std::size_t array_size>
  constexpr basic_const_string(const _char_type (&c_array)[array_size])
  {
    std::copy_n(std::ranges::cbegin(c_array), _size, std::begin(data));
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

template <std::size_t size, typename char_type>
basic_const_string(basic_const_string<size, char_type>) -> basic_const_string<size, char_type>;

template <typename range_type>
requires requires{ typename std::tuple_size<range_type>; }
basic_const_string(range_type) -> basic_const_string<std::tuple_size_v<range_type>, std::ranges::range_value_t<range_type>>;

template <std::size_t size, typename char_type>
basic_const_string(const char_type (&c_array)[size]) -> basic_const_string<size, char_type>;

template <std::size_t size>
using const_string = basic_const_string<size, char>;

template <std::size_t size_first, std::size_t size_second, typename CharType>
constexpr auto operator+(
    const basic_const_string<size_first, CharType>& first,
    const basic_const_string<size_second, CharType>& second)
{
  basic_const_string<size_first + size_second, CharType> new_string{first};
  std::copy(std::ranges::cbegin(second), std::ranges::cend(second), &(new_string[size_first]));
  return new_string;
}
