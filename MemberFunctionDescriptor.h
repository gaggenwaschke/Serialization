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
    // delete default constructors
    MemberFunctionDescriptor() = delete;
    MemberFunctionDescriptor(const MemberFunctionDescriptor& other) = delete;
    MemberFunctionDescriptor& operator=(const MemberFunctionDescriptor& other) = delete;
public:
    using FunctionType = ReturnT (SerializeableT::*)(ArgTs...);

    constexpr MemberFunctionDescriptor(const FunctionType function, const char* const name);
    
    constexpr ReturnT call(SerializeableT& object, ArgTs... arguments) const;
    constexpr const char* const getName() const;

private:
    /** member function pointer */
    const FunctionType function;
    /** name of the function */
    const char* const name;  
};
} // Serialization

// template, include source from here
#include "MemberFunctionDescriptor.cpp"
#endif //__MEMBERFUNCTIONDESCRIPTOR_H__