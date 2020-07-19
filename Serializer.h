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

    template <class SerialzeableT>
    void serializeStructure(std::ostream& os);

protected:
    virtual void serializeObjectStart(std::ostream& os) = 0;
    virtual void serializeObjectEnd(std::ostream& os) = 0;
    virtual void serializeMember(std::ostream& os, const char* const memberName, int value) = 0;
    virtual void serializeMember(std::ostream& os, const char* const memberName, char value) = 0;
    virtual void serializeMember(std::ostream& os, const char* const memberName, bool value) = 0;
    virtual void serializeMember(std::ostream& os, const char* const memberName, const char* const value) = 0;
    virtual void serializeMemberSeperator(std::ostream& os) = 0;
    virtual void serializeDescriptorsStart(std::ostream& os) {serializeObjectStart(os);}
    virtual void serializeDescriptorsEnd(std::ostream& os) {serializeObjectEnd(os);}
    virtual void serializeDescriptorSeperator(std::ostream& os) {serializeMemberSeperator(os);}
    virtual void serializeDescriptorInnerClassName(std::ostream& os, const char* const name) = 0;
    virtual void serializeDescriptorChar(std::ostream& os, const char* const name) = 0;
    virtual void serializeDescriptorInt(std::ostream& os, const char* const name) = 0;
    virtual void serializeDescriptorString(std::ostream& os, const char* const name) = 0;
    virtual void serializeDescriptorBool(std::ostream& os, const char* const name) = 0;

private:
    /**
     * @brief serializes data field member
     * 
     * @tparam SerializeableT 
     * @tparam MemberT 
     * @param os 
     * @param descriptor 
     * @param object 
     * @param firstMember used for seperator control
     */
    template <class SerializeableT, class MemberT>
    void serializeMember(
        std::ostream& os,
        const MemberDescriptor<SerializeableT, MemberT>& descriptor,
        const SerializeableT& object,
        bool& firstMember)
        {
            // forward to virtual function that does member seperators
            if (!firstMember) {
                serializeMemberSeperator(os);
            } else {
                firstMember = false;
            }

            // forward to virtual functions for value output
            serializeMember(os, descriptor.getName(), descriptor.getMemberValue(object));
        }

    /** used to convert member ptr to the type of the member */
    template <class SerializeableT, class MemberT>
    MemberT memberPtrToType(MemberT SerializeableT::*);

    template <class MemberT,
        typename std::enable_if_t<
            !std::is_same_v<char, MemberT> &&
            !std::is_same_v<int, MemberT> &&
            !std::is_same_v<const char*, MemberT> &&
            !std::is_same_v<bool, MemberT> &&
            !std::is_integral_v<MemberT>, int>  = 0>
    void serializeDescriptor(std::ostream& os, const char* const name)
    {
        serializeDescriptorInnerClassName(os, name);
        serializeStructure<MemberT>(os);
    }

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<char, MemberT>, int> = 0>
    void serializeDescriptor(std::ostream& os, const char* const name)
    {
        serializeDescriptorChar(os, name);
    }

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<int, MemberT>, int> = 0>
    void serializeDescriptor(std::ostream& os, const char* const name)
    {
        serializeDescriptorInt(os, name);
    }

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<const char*, MemberT>, int> = 0>
    void serializeDescriptor(std::ostream& os, const char* const name)
    {
        serializeDescriptorString(os, name);
    }

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<bool, MemberT>, int> = 0>
    void serializeDescriptor(std::ostream& os, const char* const name)
    {
        serializeDescriptorBool(os, name);
    }
    
    /**
     * @brief serializes a member descriptor of a serializeable class
     * 
     * @tparam SerializeableT 
     * @tparam MemberT 
     * @param os 
     * @param descriptor 
     */
    template <class SerializeableT, class MemberT>
    void serializeDescriptor(
        std::ostream& os,
        const MemberDescriptor<SerializeableT, MemberT>& descriptor,
        bool& firstDescriptor)
        {
            // forward seperator serialization
            if (!firstDescriptor) {
                serializeDescriptorSeperator(os);
            } else {
                firstDescriptor = false;
            }

            serializeDescriptor<MemberT>(os, descriptor.getName());
        }
    
};
} // Serial

// template functions
#include "Serializer.cpp"
#endif //__SERIALIZER_H__