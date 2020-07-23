/**
 * @file Descriptor.h
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief general descriptor functions and types
 * @version 1.0
 * @date 2020-07-21
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

#ifndef __DESCRIPTOR_H__
#define __DESCRIPTOR_H__

//-------------------------------- PROTOTYPES ---------------------------------

namespace Serialization
{
class Descriptor;
}

//--------------------------------- INCLUDES ----------------------------------

#include "ClassDescriptor.h"
#include "MemberFunctionDescriptor.h"
#include <array>
#include <tuple>

namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief general descriptor functions and types
 */
class Descriptor
{
    // delete default constructors
    Descriptor() = delete;
    Descriptor(const Descriptor& other) = delete;
    Descriptor& operator=(const Descriptor& other) = delete;
public:
    template <class... MemberDescriptorArgTs>
    constexpr static auto makeClassDescriptor(
        const char* const name,
        MemberDescriptorArgTs&&... memberDescriptorArgs
    );
private:
    template<class SerializeableT, class MemberT,
        typename std::enable_if_t<std::is_object_v<MemberT>, int> = 0>
    constexpr static auto make(MemberT SerializeableT::*member, const char* const name);

    template<class SerializeableT, class MemberT, class... LeftArgTs,
        typename std::enable_if_t<std::is_object_v<MemberT>, int> = 0>
    constexpr static auto make(MemberT SerializeableT::*member, const char* const name, LeftArgTs&&... leftArgs);

    template <class SerializeableT, class ReturnT, class... ArgTs>
    constexpr static auto make(
        ReturnT (SerializeableT::*function)(ArgTs...),
        const char* const name,
        const std::array<const char* const, sizeof...(ArgTs)>&& argumentNames);

    template <class SerializeableT, class ReturnT, class... ArgTs, class... LeftArgTs>
    constexpr static auto make(
        ReturnT (SerializeableT::*function)(ArgTs...),
        const char* const name,
        const std::array<const char* const, sizeof...(ArgTs)>&& argumentNames,
        LeftArgTs&&... leftArgs);
};
} // Serialization

// template class, include src
#include "Descriptor.cpp"
#endif //__DESCRIPTOR_H__