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

//--------------------------- STRUCTS AND ENUMS -------------------------------

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

//--------------------------- EXPOSED FUNCTIONS -------------------------------

template <class SerializeableT>
void Serialization::Serializer::serialize(std::ostream& os, const SerializeableT& object)
{
    std::apply([&os, &object, this](const auto& ...descriptor){
        (this->serializeMember(os, descriptor, object), ...);
    }, SerializeableT::descriptors);
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

template <class SerializeableT, class MemberT>
void Serialization::Serializer::serializeMember(
    std::ostream& os,
    const MemberDescriptor<SerializeableT, MemberT>& descriptor,
    const SerializeableT& object)
{
    os << descriptor.getName() << ": " << descriptor.getMemberValue(object) << std::endl;
}

//---------------------------- STATIC FUNCTIONS -------------------------------