/**
 * @file MemberFunctionDescriptor.cpp
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief descriptor for member functions
 * @version 1.0
 * @date 2020-07-21
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

//--------------------------------- INCLUDES ----------------------------------

#include "MemberFunctionDescriptor.h"
#include <utility>

//--------------------------- STRUCTS AND ENUMS -------------------------------

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

template<class SerializeableT, class ReturnT, class... ArgTs>
constexpr Serialization::MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>::
    MemberFunctionDescriptor(
        const FunctionType function,
        const char* const name,
        const std::array<const char* const, sizeof...(ArgTs)>&& argumentNames) :
    function(function), name(name), argumentNames(std::move(argumentNames))
{
}

//--------------------------- EXPOSED FUNCTIONS -------------------------------

template<class SerializeableT, class ReturnT, class... ArgTs>
constexpr ReturnT Serialization::MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>::call(
    SerializeableT& object,
    ArgTs&&... arguments) const
{
    return (object.*function)(std::forward<ArgTs>(arguments)...);
}

template<class SerializeableT, class ReturnT, class... ArgTs>
constexpr const char* const Serialization::MemberFunctionDescriptor<SerializeableT, ReturnT, ArgTs...>::getName() const
{
    return name;
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------