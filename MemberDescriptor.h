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
template <class SerializeableT, class MemberT, MemberT SerializeableT::*member>
class MemberDescriptor;
}

//--------------------------------- INCLUDES ----------------------------------


namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief describes a member of a class for serialization
 */
template <class SerializeableT, class MemberT, MemberT SerializeableT::*member>
class MemberDescriptor
{
    // delete default constructors
    MemberDescriptor() = delete;
    MemberDescriptor(const MemberDescriptor& other) = delete;
    MemberDescriptor& operator=(const MemberDescriptor& other) = delete;
public:
    constexpr MemberDescriptor(const char* const name);    

    MemberT getMemberValue(const SerializeableT& object);
    void setMemberValue(SerializeableT& object, MemberT value);

private:
    /** name of the field */
    const char* const name;
};
} // Serialization

// template class, include src from here
#include "MemberDescriptor.cpp"
#endif //__MEMBERDESCRIPTOR_H__