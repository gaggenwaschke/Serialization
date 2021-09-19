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
