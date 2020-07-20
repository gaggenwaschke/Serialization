/**
 * @file Serializer.cpp
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief generic serializer for C++ classes
 * @version 1.0
 * @date 2020-07-17
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

//--------------------------------- INCLUDES ----------------------------------

#include "Serializer.h"

#include <tuple>
#include <type_traits>

//--------------------------- STRUCTS AND ENUMS -------------------------------

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

Serialization::Serializer::Serializer()
{
    // do nothing
}

//--------------------------- EXPOSED FUNCTIONS -------------------------------

/**
 * @brief Serializes any object of a serializeable class.
 * 
 * @details A class is serializeable, if it has a static descriptors field
 * which contains an tuple of MemberDescriptors.
 * Every member described in that tuple will be serialized.
 * 
 * @tparam SerializeableT any class with static descriptors tuple.
 * @param os out stream to write to
 * @param object object to serialize
 */
template <class SerializeableT,
        typename std::enable_if_t<
            !(std::is_same_v<char, SerializeableT> ||
            std::is_same_v<int, SerializeableT> ||
            std::is_same_v<const char*, SerializeableT> ||
            std::is_same_v<bool, SerializeableT>), int>  = 0>
void Serialization::Serializer::serialize(std::ostream& os, const SerializeableT& object)
{
    serializeObjectStart(os);
    std::apply([&os, &object, this](const auto& ...descriptor){
        bool firstMember = true;
        (this->serializeMember(os, descriptor, object, firstMember), ...);
    }, SerializeableT::descriptors);
    serializeObjectEnd(os);
}

/**
 * @brief Serializes any primitive types.
 * 
 * @details primitive types are defined by the is_primitive function.
 * The serialization of these needs to be hardcoded in any
 * Serializer by overriding the serializeValue(...) functions.
 * 
 * @tparam SerializeableT SerializeableT any class with static descriptors tuple.
 * @param os out stream to write to
 * @param object object to serialize
 */
template <class SerializeableT,
    typename std::enable_if_t<
    (
        std::is_same_v<char, SerializeableT> ||
        std::is_same_v<int, SerializeableT> ||
        std::is_same_v<const char*, SerializeableT> ||
        std::is_same_v<bool, SerializeableT>
    ), int>  = 0>
void Serialization::Serializer::serialize(std::ostream& os, const SerializeableT& value)
{
    serializeValue(os, value);
}

/**
 * @brief Serializes the structure of an object.
 * 
 * @details Will serialize type and name for each descriptor.
 * How each type iis serialized is determined by overriding the
 * serializeType...(...) functions.
 * 
 * @tparam SerializeableT type to write descriptor of
 * @param os stream to write the descriptor to
 */
template <class SerializeableT>
void Serialization::Serializer::serializeStructure(std::ostream& os)
{
    serializeObjectStart(os);
    std::apply([&os, this](const auto& ...descriptor){
        bool firstDescriptor = true;
        (this->serializeDescriptor(os, descriptor, firstDescriptor), ...);
    }, SerializeableT::descriptors);
    serializeObjectEnd(os);
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

/**
 * @brief channels the serialization of a member to the right functions.
 * 
 * @tparam SerializeableT 
 * @tparam MemberT 
 * @param os 
 * @param descriptor 
 * @param object 
 * @param firstMember 
 */
template <class SerializeableT, class MemberT>
void Serialization::Serializer::serializeMember(
    std::ostream& os,
    const MemberDescriptor<SerializeableT, MemberT>& descriptor,
    const SerializeableT& object,
    bool& firstMember)
{
    // forward to virtual function that does member seperators
    if (!firstMember) {
        serializeSeperator(os);
    } else {
        firstMember = false;
    }

    serializeName(os, descriptor.getName());
    // forward to virtual functions for value output
    serialize(os, descriptor.getMemberValue(object));
}

/**
 * @brief recurses to serialize encapsulated serializeable types.
 * 
 * @tparam MemberT serializeable type.
 * @param os stream to serialize to
 */
template <class MemberT,
    typename std::enable_if_t<
        !std::is_same_v<char, MemberT> &&
        !std::is_same_v<int, MemberT> &&
        !std::is_same_v<const char*, MemberT> &&
        !std::is_same_v<bool, MemberT>, int>  = 0>
void Serialization::Serializer::serializeType(std::ostream& os)
{
    serializeStructure<MemberT>(os);
}

/**
 * @brief forwards writing of char to overwriteable function
 * 
 * @tparam MemberT char
 * @param os out stream
 */
template <class MemberT,
    typename std::enable_if_t<std::is_same_v<char, MemberT>, int> = 0>
void Serialization::Serializer::serializeType(std::ostream& os)
{
    serializeTypeChar(os);
}

/**
 * @brief forwards writing of int to overwriteable function
 * 
 * @tparam MemberT int
 * @param os out stream
 */
template <class MemberT,
    typename std::enable_if_t<std::is_same_v<int, MemberT>, int> = 0>
void Serialization::Serializer::serializeType(std::ostream& os)
{
    serializeTypeInt(os);
}

/**
 * @brief forwards writing of string to overwriteable function
 * 
 * @tparam MemberT string
 * @param os out stream
 */
template <class MemberT,
    typename std::enable_if_t<std::is_same_v<const char*, MemberT>, int> = 0>
void Serialization::Serializer::serializeType(std::ostream& os)
{
    serializeTypeString(os);
}

/**
 * @brief forwards writing of bool to overwriteable function
 * 
 * @tparam MemberT bool
 * @param os out stream
 */
template <class MemberT,
    typename std::enable_if_t<std::is_same_v<bool, MemberT>, int> = 0>
void Serialization::Serializer::serializeType(std::ostream& os)
{
    serializeTypeBool(os);
}

/**
 * @brief serializes a member descriptor of a serializeable class
 * 
 * @tparam SerializeableT 
 * @tparam MemberT 
 * @param os 
 * @param descriptor 
 */
template <class SerializeableT, class MemberT>
void Serialization::Serializer::serializeDescriptor(
    std::ostream& os,
    const MemberDescriptor<SerializeableT, MemberT>& descriptor,
    bool& firstDescriptor)
{
    // forward seperator serialization
    if (!firstDescriptor) {
        serializeSeperator(os);
    } else {
        firstDescriptor = false;
    }

    // forward member name serialization
    serializeName(os, descriptor.getName());

    // forward serialization of type info
    serializeType<MemberT>(os);
}

//---------------------------- STATIC FUNCTIONS -------------------------------