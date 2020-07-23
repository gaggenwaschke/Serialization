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
template <class Supplier>
template <class SerializeableT,
        typename std::enable_if_t<
            !(std::is_same_v<char, SerializeableT> ||
            std::is_same_v<int, SerializeableT> ||
            std::is_same_v<const char*, SerializeableT> ||
            std::is_same_v<bool, SerializeableT>), int> Dummy>
void Serialization::Serializer<Supplier>::serialize(std::ostream& os, const SerializeableT& object)
{
    os << Supplier::ObjectStart;
    std::apply([&os, &object](const auto& ...descriptor){
        bool firstMember = true;
        (serializeMember(os, descriptor, object, firstMember), ...);
    }, SerializeableT::descriptor.getMemberDescriptors());
    os << Supplier::ObjectEnd;
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
template <class Supplier>
template <class SerializeableT,
    typename std::enable_if_t<
    (
        std::is_same_v<char, SerializeableT> ||
        std::is_same_v<int, SerializeableT> ||
        std::is_same_v<const char*, SerializeableT> ||
        std::is_same_v<bool, SerializeableT>
    ), int>>
void Serialization::Serializer<Supplier>::serialize(std::ostream& os, const SerializeableT& value)
{
    Supplier::serializeValue(os, value);
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
template <class Supplier>
template <class SerializeableT>
void Serialization::Serializer<Supplier>::serializeStructure(std::ostream& os)
{
    os << Supplier::ObjectStart;

    // serialize name
    os << Supplier::BeforeName << Supplier::FieldNameClass << Supplier::AfterName;
    Supplier::serializeValue(os, SerializeableT::descriptor.getName());
    os << Supplier::Seperator;

    // serialize members
    os << Supplier::BeforeName << Supplier::FieldNameMembers << Supplier::AfterName;
    os << Supplier::ObjectStart;
    std::apply([&os](const auto& ...descriptor){
        bool firstDescriptor = true;
        (serializeMemberDescriptors(os, descriptor, firstDescriptor), ...);
    }, SerializeableT::descriptor.getMemberDescriptors());
    os << Supplier::ObjectEnd << Supplier::Seperator;

    // serialize functions
    os << Supplier::BeforeName << Supplier::FieldNameFunctions << Supplier::AfterName;
    os << Supplier::ObjectStart;
    std::apply([&os](const auto& ...descriptor){
        bool firstDescriptor = true;
        (serializeFunctionDescriptors(os, descriptor, firstDescriptor), ...);
    }, SerializeableT::descriptor.getMemberDescriptors());
    os << Supplier::ObjectEnd << Supplier::ObjectEnd;
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
template <class Supplier>
template <class SerializeableT, class MemberT>
void Serialization::Serializer<Supplier>::serializeMember(
    std::ostream& os,
    const MemberDescriptor<SerializeableT, MemberT>& descriptor,
    const SerializeableT& object,
    bool& firstMember)
{
    // forward to virtual function that does member seperators
    if (!firstMember) {
        os << Supplier::Seperator;
    } else {
        firstMember = false;
    }

    os << Supplier::BeforeName << descriptor.getName() << Supplier::AfterName;
    // forward to virtual functions for value output
    serialize(os, descriptor.getMemberValue(object));
}

/**
 * @brief ignore member function descriptors.
 * 
 * @details this overload of the function does nothing
 * 
 * @tparam SerializeableT 
 * @tparam ReturnT 
 * @tparam ArgTs 
 * @param os 
 * @param descriptor 
 * @param object 
 * @param firstMember 
 */
template <class Supplier>
template <class SerializeableT, class ReturnT, class... ArgTs>
void Serialization::Serializer<Supplier>::serializeMember(
    std::ostream& os,
    const MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>& descriptor,
    const SerializeableT& object,
    bool& firstMember)
{
    // do nothing
}

/**
 * @brief recurses to serialize encapsulated serializeable types.
 * 
 * @tparam MemberT serializeable type.
 * @param os stream to serialize to
 */
template <class Supplier>
template <class MemberT,
    typename std::enable_if_t<
        !std::is_same_v<char, MemberT> &&
        !std::is_same_v<int, MemberT> &&
        !std::is_same_v<const char*, MemberT> &&
        !std::is_same_v<bool, MemberT>, int>>
void Serialization::Serializer<Supplier>::serializeType(std::ostream& os)
{
    serializeStructure<MemberT>(os);
}

/**
 * @brief forwards writing of char to overwriteable function
 * 
 * @tparam MemberT char
 * @param os out stream
 */
template <class Supplier>
template <class MemberT,
    typename std::enable_if_t<std::is_same_v<char, MemberT>, int>>
void Serialization::Serializer<Supplier>::serializeType(std::ostream& os)
{
    os << Supplier::TypeChar;
}

/**
 * @brief forwards writing of int to overwriteable function
 * 
 * @tparam MemberT int
 * @param os out stream
 */
template <class Supplier>
template <class MemberT,
    typename std::enable_if_t<std::is_same_v<int, MemberT>, int>>
void Serialization::Serializer<Supplier>::serializeType(std::ostream& os)
{
    os << Supplier::TypeInt;
}

/**
 * @brief forwards writing of string to overwriteable function
 * 
 * @tparam MemberT string
 * @param os out stream
 */
template <class Supplier>
template <class MemberT,
    typename std::enable_if_t<std::is_same_v<const char*, MemberT>, int>>
void Serialization::Serializer<Supplier>::serializeType(std::ostream& os)
{
    os << Supplier::TypeString;
}

/**
 * @brief forwards writing of bool to overwriteable function
 * 
 * @tparam MemberT bool
 * @param os out stream
 */
template <class Supplier>
template <class MemberT,
    typename std::enable_if_t<std::is_same_v<bool, MemberT>, int>>
void Serialization::Serializer<Supplier>::serializeType(std::ostream& os)
{
    os << Supplier::TypeBool;
}

/**
 * @brief serializes a member descriptor of a serializeable class
 * 
 * @tparam SerializeableT 
 * @tparam MemberT 
 * @param os 
 * @param descriptor 
 */
template <class Supplier>
template <class SerializeableT, class MemberT>
void Serialization::Serializer<Supplier>::serializeMemberDescriptors(
    std::ostream& os,
    const MemberDescriptor<SerializeableT, MemberT>& descriptor,
    bool& firstDescriptor)
{
    // forward seperator serialization
    if (!firstDescriptor) {
        os << Supplier::Seperator;
    } else {
        firstDescriptor = false;
    }

    // forward member name serialization
    os << Supplier::BeforeName << descriptor.getName() << Supplier::AfterName;

    // forward serialization of type info
    serializeType<MemberT>(os);
}

/**
 * @brief overload for ignoring memberFunctionDescriptors
 * 
 * @tparam SerializeableT 
 * @tparam ReturnT 
 * @tparam ArgTs 
 * @param os 
 * @param descriptor 
 * @param firstDescriptor 
 */
template <class Supplier>
template <class SerializeableT, class ReturnT, class... ArgTs>
constexpr void Serialization::Serializer<Supplier>::serializeMemberDescriptors(
    std::ostream& os,
    const MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>& descriptor,
    bool& firstDescriptor)
{
    // do nothing
}

/**
 * @brief this overload of the function ignores MEmberDescriptors
 * 
 * @tparam SerializeableT 
 * @tparam MemberT 
 * @param os 
 * @param descriptor 
 * @param firstDescriptor 
 */
template <class Supplier>
template <class SerializeableT, class MemberT>
constexpr void Serialization::Serializer<Supplier>::serializeFunctionDescriptors(
    std::ostream& os,
    const MemberDescriptor<SerializeableT, MemberT>& descriptor,
    bool& firstDescriptor)
{
    // do nothing
}


/**
 * @brief serialize function descriptors to a stream
 * 
 * @tparam SerializeableT 
 * @tparam ReturnT 
 * @tparam ArgTs 
 * @param os 
 * @param descriptor 
 * @param firstDescriptor 
 */
template <class Supplier>
template <class SerializeableT, class ReturnT, class... ArgTs>
void Serialization::Serializer<Supplier>::serializeFunctionDescriptors(
    std::ostream& os,
    const MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>& descriptor,
    bool& firstDescriptor)
{
    // forward seperator serialization
    if (!firstDescriptor) {
        os << Supplier::Seperator;
    } else {
        firstDescriptor = false;
    }

    // forward member name serialization
    os << Supplier::BeforeName << descriptor.getName() << Supplier::AfterName;

    // serialize arguments
    os << Supplier::BeforeName << Supplier::FieldNameArguments << Supplier::AfterName << Supplier::ObjectStart;

    int ii = 0;
    bool firstElement = true;
    (serializeFunctionArgument<ArgTs>(os, descriptor.getArgumentName(ii++), firstElement), ...);

    os << Supplier::ObjectEnd;
}

template <class Supplier>
template <class ArgT>
void Serialization::Serializer<Supplier>::serializeFunctionArgument(std::ostream& os, const char* const name, bool& firstElement)
{
    // forward seperator serialization
    if (!firstElement) {
        os << Supplier::Seperator;
    } else {
        firstElement = false;
    }

    os << Supplier::BeforeName << name << Supplier::AfterName;
    serializeType<ArgT>(os);
}

//---------------------------- STATIC FUNCTIONS -------------------------------