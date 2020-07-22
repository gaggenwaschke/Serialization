/**
 * @file MemberFunctionDescriptor.h
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief descriptor for member functions
 * @version 1.0
 * @date 2020-07-21
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

#ifndef __MEMBERFUNCTIONDESCRIPTOR_H__
#define __MEMBERFUNCTIONDESCRIPTOR_H__

//-------------------------------- PROTOTYPES ---------------------------------

namespace Serialization
{
template<class SerializeableT, class ReturnT, class... ArgTs>
class MemberFunctionDescriptor;
}

//--------------------------------- INCLUDES ----------------------------------

#include <iostream>

namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief descriptor for member functions
 */
template<class SerializeableT, class ReturnT, class... ArgTs>
class MemberFunctionDescriptor
{
    friend class Descriptor;

    // delete default constructors
    MemberFunctionDescriptor() = delete;
    
public:
    using FunctionType = ReturnT (SerializeableT::*)(ArgTs...);

public:
    constexpr MemberFunctionDescriptor(const MemberFunctionDescriptor& other) = default;
    constexpr MemberFunctionDescriptor& operator=(const MemberFunctionDescriptor& other) = default;
    constexpr MemberFunctionDescriptor(
        const FunctionType function,
        const char* const name,
        const std::array<const char* const, sizeof...(ArgTs)>&& argumentNames);

public:    
    constexpr ReturnT call(SerializeableT& object, ArgTs&&... arguments) const;
    constexpr const char* const getName() const;

private:
    /** member function pointer */
    const FunctionType function;
    /** name of the function */
    const char* const name;
    /** names of the function arguments */
    const std::array<const char* const, sizeof...(ArgTs)> argumentNames;
};
} // Serialization

// template, include source from here
#include "MemberFunctionDescriptor.cpp"
#endif //__MEMBERFUNCTIONDESCRIPTOR_H__