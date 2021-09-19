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
type get_parent_class(member_type type::*member);

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

/**
 * Dummy base class for all descriptors. This is needed to be able to check for
 * the descriptor identity.
 */
struct descriptor_base {};

/**
 * Member descriptor describing a member pointer of any kind with a name.
 *
 * @tparam _member_pointer_type Type of the member pointer.
 */
template <typename _member_pointer_type>
requires(
    std::is_member_pointer_v<_member_pointer_type>) struct member_descriptor
    : public descriptor_base {
  /**
   * Class the member belongs to.
   */
  using described_type = typename parent<_member_pointer_type>::type;
  /**
   * Member pointer type.
   */
  using member_pointer_type = _member_pointer_type;

  const std::string_view name;
  const member_pointer_type member_pointer;

  member_descriptor() = delete;

  consteval member_descriptor(const member_descriptor &other) noexcept =
      default;
  consteval member_descriptor &
  operator=(const member_descriptor &other) noexcept = default;

  consteval member_descriptor(std::string_view name,
                              member_pointer_type member_ptr) noexcept
      : name{name}, member_pointer{member_ptr} {}
};

template <typename... DescriptorTypes>
concept are_descriptors =
    (std::is_base_of_v<descriptor_base, DescriptorTypes> && ...);

template <typename... DescriptorType>
consteval bool is_descriptor_collection(std::tuple<DescriptorType...>) {
  return are_descriptors<DescriptorType...>;
}

template <typename candidate_type>
concept reflective = requires {
  {struct_name<candidate_type>::value};
  is_descriptor_collection(descriptor<candidate_type>::value) == true;
};

/**
 * @brief Implementations to make descriptors them self reflective.
 *
 * @details This allows to serialize the information about the structure of
 * classes.
 *
 * @tparam member_pointer_type Member pointer type of the descriptor.
 */
template <typename member_pointer_type>
struct struct_name<member_descriptor<member_pointer_type>>
{
  constexpr static const_string value{"descriptor"};
};

/**
 * @brief Implementations to make descriptors them self reflective.
 *
 * @details This allows to serialize the information about the structure of
 * classes.
 *
 * @tparam member_pointer_type Member pointer type of the descriptor.
 */
template <typename member_pointer_type>
struct descriptor<member_descriptor<member_pointer_type>>
{
  constexpr static auto value = std::make_tuple(
      member_descriptor{"name", &member_descriptor<member_pointer_type>::name},
      member_descriptor{"member pointer", &member_descriptor<member_pointer_type>::member_pointer}
 );
};
}
