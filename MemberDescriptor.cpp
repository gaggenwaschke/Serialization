/**
 * @file MemberDescriptor.cpp
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief describes a member of a class for serialization
 * @version 1,0
 * @date 2020-07-17
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

//--------------------------------- INCLUDES ----------------------------------

#include "MemberDescriptor.h"

//--------------------------- STRUCTS AND ENUMS -------------------------------

//-------------------------------- CONSTANTS ----------------------------------

template <class SerializeableT, class MemberT, MemberT SerializeableT::*member>
constexpr Serialization::MemberDescriptor<SerializeableT, MemberT, member>::MemberDescriptor(const char* const name) : name(name)
{
}

//------------------------------ CONSTRUCTOR ----------------------------------

//--------------------------- EXPOSED FUNCTIONS -------------------------------

template <class SerializeableT, class MemberT, MemberT SerializeableT::*member>
constexpr MemberT Serialization::MemberDescriptor<SerializeableT, MemberT, member>::getMemberValue(const SerializeableT& object) const
{
    return object.*member;
}

template <class SerializeableT, class MemberT, MemberT SerializeableT::*member>
constexpr void Serialization::MemberDescriptor<SerializeableT, MemberT, member>::setMemberValue(SerializeableT& object, MemberT value) const
{
    object.*member = value;
}

template <class SerializeableT, class MemberT, MemberT SerializeableT::*member>
constexpr const char* const Serialization::MemberDescriptor<SerializeableT, MemberT, member>::getName() const
{
    return name;
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------