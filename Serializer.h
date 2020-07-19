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
    void serializeMember(std::ostream& os, const MemberDescriptor<SerializeableT, MemberT>& descriptor, const SerializeableT& object);
    
};
} // Serial

// template functions
#include "Serializer.cpp"
#endif //__SERIALIZER_H__