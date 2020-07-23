/**
 * @file Serializer.h
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief generic serializer for C++ classes
 * @version 1.0
 * @date 2020-07-17
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

#ifndef __SERIALIZER_H__
#define __SERIALIZER_H__

//-------------------------------- PROTOTYPES ---------------------------------

namespace Serialization
{
template <class Supplier>
class Serializer;
}

//--------------------------------- INCLUDES ----------------------------------

#include <iostream>
#include "MemberFunctionDescriptor.h"
#include "MemberDescriptor.h"

namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief generic serializer for C++ classes
 */
template <class Supplier>
class Serializer
{
    // delete default constructors
    Serializer() = delete;
    Serializer(const Serializer& other) = delete;
    Serializer& operator=(const Serializer& other) = delete;
public:
    template <class SerializeableT,
        typename std::enable_if_t<
            !(std::is_same_v<char, SerializeableT> ||
            std::is_same_v<int, SerializeableT> ||
            std::is_same_v<const char*, SerializeableT> ||
            std::is_same_v<bool, SerializeableT>), int>  = 0>
    static void serialize(std::ostream& os, const SerializeableT& object);

    template <class SerializeableT,
        typename std::enable_if_t<
        (
            std::is_same_v<char, SerializeableT> ||
            std::is_same_v<int, SerializeableT> ||
            std::is_same_v<const char*, SerializeableT> ||
            std::is_same_v<bool, SerializeableT>
        ), int>  = 0>
    static void serialize(std::ostream& os, const SerializeableT& value);


    template <class SerialzeableT>
    static void serializeStructure(std::ostream& os);

private:
    template <class SerializeableT, class MemberT>
    static void serializeMember(
        std::ostream& os,
        const MemberDescriptor<SerializeableT, MemberT>& descriptor,
        const SerializeableT& object,
        bool& firstMember);

    template <class SerializeableT, class ReturnT, class... ArgTs>
    static void serializeMember(
        std::ostream& os,
        const MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>& descriptor,
        const SerializeableT& object,
        bool& firstMember);

    template <class MemberT,
        typename std::enable_if_t<
            !std::is_same_v<char, MemberT> &&
            !std::is_same_v<int, MemberT> &&
            !std::is_same_v<const char*, MemberT> &&
            !std::is_same_v<bool, MemberT>, int>  = 0>
    static void serializeType(std::ostream& os);

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<char, MemberT>, int> = 0>
    static void serializeType(std::ostream& os);

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<int, MemberT>, int> = 0>
    static void serializeType(std::ostream& os);

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<const char*, MemberT>, int> = 0>
    static void serializeType(std::ostream& os);

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<bool, MemberT>, int> = 0>
    static void serializeType(std::ostream& os);

    template <class SerializeableT, class MemberT>
    static void serializeMemberDescriptors(
        std::ostream& os,
        const MemberDescriptor<SerializeableT, MemberT>& descriptor,
        bool& firstDescriptor);

    template <class SerializeableT, class ReturnT, class... ArgTs>
    constexpr static void serializeMemberDescriptors(
        std::ostream& os,
        const MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>& descriptor,
        bool& firstDescriptor);

    template <class SerializeableT, class MemberT>
    constexpr static void serializeFunctionDescriptors(
        std::ostream& os,
        const MemberDescriptor<SerializeableT, MemberT>& descriptor,
        bool& firstDescriptor);

    template <class SerializeableT, class ReturnT, class... ArgTs>
    static void serializeFunctionDescriptors(
        std::ostream& os,
        const MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>& descriptor,
        bool& firstDescriptor);

    template <class ArgT>
    static void serializeFunctionArgument(std::ostream& os, const char* const name, bool& firstElement);
};
} // Serial

// template functions
#include "Serializer.cpp"
#endif //__SERIALIZER_H__