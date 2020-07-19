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

template <class SerializeableT>
void Serialization::Serializer::serialize(std::ostream& os, const SerializeableT& object)
{
    serializeObjectStart(os);
    std::apply([&os, &object, this](const auto& ...descriptor){
        bool firstMember = true;
        (this->serializeMember(os, descriptor, object, firstMember), ...);
    }, SerializeableT::descriptors);
    serializeObjectEnd(os);
}

template <class SerializeableT>
void Serialization::Serializer::serializeStructure(std::ostream& os)
{
    std::apply([&os, this](const auto& ...descriptor){
        (this->serializeDescriptor(os, descriptor), ...);
    }, SerializeableT::descriptors);
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------


//---------------------------- STATIC FUNCTIONS -------------------------------