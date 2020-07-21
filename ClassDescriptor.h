/**
 * @file ClassDescriptor.h
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief describes a class for serialization
 * @version 1.0
 * @date 2020-07-21
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

#ifndef __CLASSDESCRIPTOR_H__
#define __CLASSDESCRIPTOR_H__

//-------------------------------- PROTOTYPES ---------------------------------

namespace Serialization
{
template<class... MemberDescriptorTs>
class ClassDescriptor;
}

//--------------------------------- INCLUDES ----------------------------------

#include <tuple>

namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief describes a class for serialization
 */
template<class... MemberDescriptorTs>
class ClassDescriptor
{
    friend class Descriptor;
    friend class Serializer;

    // delete default constructors
    ClassDescriptor() = delete;
    ClassDescriptor(const ClassDescriptor& other) = delete;
    ClassDescriptor& operator=(const ClassDescriptor& other) = delete;

private:
    constexpr ClassDescriptor(const char* const name, MemberDescriptorTs&&... memberDescriptorArgs);

    /** class name */
    const char* const name;
    /** descriptors for the member variables */
    const std::tuple<MemberDescriptorTs...> memberDescriptors;
};
} // Serialization

// template class needs to include source file here
#include "ClassDescriptor.cpp"
#endif //__CLASSDESCRIPTOR_H__