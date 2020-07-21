/**
 * @file MemberDescriptor.h
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief describes a member of a class for serialization
 * @version 1.0
 * @date 2020-07-17
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

#ifndef __MEMBERDESCRIPTOR_H__
#define __MEMBERDESCRIPTOR_H__

//-------------------------------- PROTOTYPES ---------------------------------

namespace Serialization
{
template <class SerializeableT, class MemberT>
class MemberDescriptor;
}

//--------------------------------- INCLUDES ----------------------------------

#include <tuple>

namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief describes a member of a class for serialization
 */
template <class SerializeableT, class MemberT>
class MemberDescriptor
{
    // delete default constructors
    MemberDescriptor() = delete;

public:
    constexpr MemberDescriptor(const MemberT SerializeableT::*member, const char* const name);    

    constexpr MemberT getMemberValue(const SerializeableT& object) const;
    constexpr void setMemberValue(SerializeableT& object, MemberT value) const;

    constexpr const char* const getName() const;

private:
    /** class member */
    const MemberT SerializeableT::*member;
    /** name of the field */
    const char* const name;
};
} // Serialization

// template class, include src from here
#include "MemberDescriptor.cpp"
#endif //__MEMBERDESCRIPTOR_H__