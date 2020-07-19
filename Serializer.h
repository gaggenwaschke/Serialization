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
    virtual void serializeObjectStart(std::ostream& os)
    {
        os << "{";
    }

    virtual void serializeObjectEnd(std::ostream& os)
    {
        os << "}";
    }

    virtual void serializeMember(std::ostream& os, const char* const memberName, int value)
    {
        os << "\"" << memberName << "\":" << value;
    }

    virtual void serializeMember(std::ostream& os, const char* const memberName, char value)
    {
        os << "\"" << memberName << "\":" << value;
    }

    virtual void serializeMember(std::ostream& os, const char* const memberName, bool value)
    {
        os << "\"" << memberName << "\":" << (value ? "true" : "false");
    }

    virtual void serializeMember(std::ostream& os, const char* const memberName, const char* const value)
    {
        os << "\"" << memberName << "\":\"" << value << "\"";
    }

    virtual void serializeMemberSeperator(std::ostream& os)
    {
        os << ",";
    }

    virtual void serializeDescriptorsStart(std::ostream& os)
    {
        serializeObjectStart(os);
    }

    virtual void serializeDescriptorsEnd(std::ostream& os)
    {
        serializeObjectEnd(os);
    }

    virtual void serializeDescriptorSeperator(std::ostream& os)
    {
        serializeMemberSeperator(os);
    }

    virtual void serializeDescriptorChar(std::ostream& os, const char* const name)
    {
        os << "\"" << name << "\":\"CHAR\"";
    }

    virtual void serializeDescriptorInt(std::ostream& os, const char* const name)
    {
        os << "\"" << name << "\":\"INT\"";
    }

    virtual void serializeDescriptorString(std::ostream& os, const char* const name)
    {
        os << "\"" << name << "\":\"STRING\"";
    }

    virtual void serializeDescriptorBool(std::ostream& os, const char* const name)
    {
        os << "\"" << name << "\":\"BOOLEAN\"";
    }

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

    template <class T,
        typename std::enable_if_t<std::is_same_v<char, T>, int> = 0>
    void serializeDescriptor(std::ostream& os, const char* const name)
    {
        serializeDescriptorChar(os, name);
    }

    template <class T,
        typename std::enable_if_t<std::is_same_v<int, T>, int> = 0>
    void serializeDescriptor(std::ostream& os, const char* const name)
    {
        serializeDescriptorInt(os, name);
    }

    template <class T,
        typename std::enable_if_t<std::is_same_v<const char*, T>, int> = 0>
    void serializeDescriptor(std::ostream& os, const char* const name)
    {
        serializeDescriptorString(os, name);
    }

    template <class T,
        typename std::enable_if_t<std::is_same_v<bool, T>, int> = 0>
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