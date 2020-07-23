/**
 * @file Descriptor.cpp
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief general descriptor functions and types
 * @version 1.0
 * @date 2020-07-21
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

//--------------------------------- INCLUDES ----------------------------------

#include "Descriptor.h"
#include "MemberDescriptor.h"
#include <tuple>

//--------------------------- STRUCTS AND ENUMS -------------------------------

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

//--------------------------- EXPOSED FUNCTIONS -------------------------------

template <class... MemberDescriptorArgTs>
constexpr auto Serialization::Descriptor::makeClassDescriptor(
    const char* const name,
    MemberDescriptorArgTs&&... memberDescriptorArgs
)
{
    return ClassDescriptor(name, make(std::forward<MemberDescriptorArgTs>(memberDescriptorArgs)...));
}

/**
 * @brief Makes a tuple of descriptors.
 * 
 * @details creates a tuple of descriptors for any member pointer
 * name pair it gets passed. Automatically determines the right type
 * of descriptor.
 * 
 * @tparam SerializeableT class that the descriptors are created for
 * @tparam MemberT member type that the descriptor is created for
 * @param member member that the descriptor is created for
 * @param name name of the member shown to Serializers
 * @return constexpr auto tuple of descriptors
 */
template<class SerializeableT, class MemberT,
    typename std::enable_if_t<std::is_object_v<MemberT>, int> = 0>
constexpr auto Serialization::Descriptor::make(MemberT SerializeableT::*member, const char* const name)
{
    return std::make_tuple(MemberDescriptor(member, name));
}

/**
 * @brief Makes a tuple of descriptors.
 * 
 * @details creates a tuple of descriptors for any member pointer
 * name pair it gets passed. Automatically determines the right type
 * of descriptor.
 * 
 * @tparam SerializeableT class that the descriptors are created for
 * @tparam MemberT member type that the descriptor is created for
 * @tparam LeftArgsT type of leftover arguments used to create more descriptors
 * @param member member that the descriptor is created for
 * @param name name of the member shown to Serializers
 * @param leftArgs arguements to create next descriptors from
 * @return constexpr auto tuple of descriptors
 */
template<class SerializeableT, class MemberT, class... LeftArgTs,
    typename std::enable_if_t<std::is_object_v<MemberT>, int> = 0>
constexpr auto Serialization::Descriptor::make(MemberT SerializeableT::*member, const char* const name, LeftArgTs&&... leftArgs)
{
    return std::tuple_cat(std::make_tuple(MemberDescriptor(member, name)), make(std::forward<LeftArgTs>(leftArgs)...));
}

template <class SerializeableT, class ReturnT, class... ArgTs>
constexpr auto Serialization::Descriptor::make(
    ReturnT (SerializeableT::*function)(ArgTs...),
    const char* const name,
    const std::array<const char* const, sizeof...(ArgTs)>&& argumentNames)
{
    return std::make_tuple(
        MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>(function, name, std::move(argumentNames))
    );
}

template <class SerializeableT, class ReturnT, class... ArgTs, class... LeftArgTs>
constexpr auto Serialization::Descriptor::make(
    ReturnT (SerializeableT::*function)(ArgTs...),
    const char* const name,
    const std::array<const char* const, sizeof...(ArgTs)>&& argumentNames,
    LeftArgTs&&... leftArgs)
{
    return std::tuple_cat(
        std::make_tuple(
            MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>(function, name, std::move(argumentNames))
        ),
        make(std::forward<LeftArgTs>(leftArgs)...)
    );
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------