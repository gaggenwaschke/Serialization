/**
 * @file ClassDescriptor.cpp
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief descriptor for classes in serialization
 * @version 1.0
 * @date 2020-07-22
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

//--------------------------------- INCLUDES ----------------------------------

#include "ClassDescriptor.h"
#include "MemberDescriptor.h"
#include <tuple>

//--------------------------- STRUCTS AND ENUMS -------------------------------

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

template <class... MemberDescriptorTs>
constexpr Serialization::ClassDescriptor<MemberDescriptorTs...>::
    ClassDescriptor(const char* const name, std::tuple<MemberDescriptorTs...>&& memberDescriptors) :
    name(name), memberDescriptors(memberDescriptors)
{
}

//--------------------------- EXPOSED FUNCTIONS -------------------------------

template <class... MemberDescriptorTs>
constexpr const char* const Serialization::ClassDescriptor<MemberDescriptorTs...>::getName() const
{
    return name;
}

template <class... MemberDescriptorTs>
constexpr const std::tuple<MemberDescriptorTs...>& Serialization::ClassDescriptor<MemberDescriptorTs...>::getMemberDescriptors() const
{
    return memberDescriptors;
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------