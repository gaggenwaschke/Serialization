/**
* @file
* @author Joshua Lauterbach (gaggenwaschke@gmail.com)
* @brief Descriptor class for reflecting on class structure.
* @version 1.0
* @date 2021-09-19
* @license MIT
*/

#pragma once

#include "const_string.hpp"

namespace reflection {

template <typename type> struct struct_name {
  struct_name() { static_assert("No struct name available for this type."); }
};

template <typename types> struct descriptor {
  descriptor() { static_assert("No descriptor available for this type."); }
};

template <typename type, typename member_type>
auto get_parent_class(member_type type::*member) {
  return type{};
}

/**
 * Helper function to defer parent_type from member pointer.
 *
 * @tparam parent_type
 * @tparam member_type
 *
 * @param member_ptr
 *
 * @return
 */
template <typename member_pointer_type> struct parent {
  using type = decltype(get_parent_class(std::declval<member_pointer_type>()));
};

struct descriptor_base {};

template <typename _member_pointer_type>
requires(
    std::is_member_pointer_v<_member_pointer_type>) struct member_descriptor
    : public descriptor_base {
  using described_type = typename parent<_member_pointer_type>::type;
  using member_pointer_type = _member_pointer_type;

  std::string_view name;
  member_pointer_type member_ptr;

  member_descriptor() = delete;

  consteval member_descriptor(const member_descriptor &other) noexcept =
      default;
  consteval member_descriptor &
  operator=(const member_descriptor &other) noexcept = default;

  consteval member_descriptor(std::string_view name,
                              member_pointer_type member_ptr) noexcept
      : name{name}, member_ptr{member_ptr} {}
};

template <typename... DescriptorTypes>
concept are_descriptors =
    (std::is_base_of_v<descriptor_base, DescriptorTypes> && ...);

template <typename... DescriptorType>
consteval bool is_descriptor_collection(std::tuple<DescriptorType...>) {
  return are_descriptors<DescriptorType...>;
}

template <typename CandidateType>
concept reflective = requires {
  std::is_same_v<decltype(struct_name<CandidateType>::value), std::string_view>;
  is_descriptor_collection(descriptor<CandidateType>::value) == true;

};
}
