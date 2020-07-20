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

//---------------------------- STATIC FUNCTIONS -------------------------------