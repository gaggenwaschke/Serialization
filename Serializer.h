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
class Serializer;
}

//--------------------------------- INCLUDES ----------------------------------

#include <iostream>

namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief generic serializer for C++ classes
 */
class Serializer
{
    // delete default constructors
    //Serializer() = delete;
    Serializer(const Serializer& other) = delete;
    Serializer& operator=(const Serializer& other) = delete;
public:
    Serializer() {}

    template <class SerializeableT>
    void serialize(std::ostream& os, const SerializeableT& object);

private:
    template <class SerializeableT, class MemberT>
    void serializeMember(
        std::ostream& os,
        const MemberDescriptor<SerializeableT, MemberT>& descriptor,
        const SerializeableT& object,
        typename std::enable_if_t<!std::is_member_pointer<MemberT>::value>* = 0)
        {
            os << descriptor.getName() << ": " << descriptor.getMemberValue(object) << std::endl;
        }

    /** used to convert member ptr to the type of the member */
    template <class SerializeableT, class MemberT>
    MemberT member_ptr_to_type(MemberT SerializeableT::*);
    
    template <class SerializeableT, class MemberT>
    void serializeMember(
        std::ostream& os,
        const MemberDescriptor<SerializeableT, MemberT>& descriptor,
        const SerializeableT& object,
        typename std::enable_if_t<std::is_member_pointer<MemberT>::value>* = 0)
        {
            using memberT = decltype(member_ptr_to_type(descriptor.getMemberValue(object)));
            os << "type of \"" << descriptor.getName() << "\": " << typeid(memberT).name() << std::endl;
        }
    
};
} // Serial

// template functions
#include "Serializer.cpp"
#endif //__SERIALIZER_H__