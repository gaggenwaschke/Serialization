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
    template<class SerializeableT, class MemberT>
    constexpr static auto make(MemberT SerializeableT::*member, const char* const name);

    template<class SerializeableT, class MemberT, class... LeftArgTs>
    constexpr static auto make(MemberT SerializeableT::*member, const char* const name, LeftArgTs&&... leftArgs);
};
} // Serialization

// template class, include src
#include "Descriptor.cpp"
#endif //__DESCRIPTOR_H__