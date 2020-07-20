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

    template <class SerializeableT,
        typename std::enable_if_t<
            !(std::is_same_v<char, SerializeableT> ||
            std::is_same_v<int, SerializeableT> ||
            std::is_same_v<const char*, SerializeableT> ||
            std::is_same_v<bool, SerializeableT>), int>  = 0>
    void serialize(std::ostream& os, const SerializeableT& object);

    template <class SerializeableT,
        typename std::enable_if_t<
        (
            std::is_same_v<char, SerializeableT> ||
            std::is_same_v<int, SerializeableT> ||
            std::is_same_v<const char*, SerializeableT> ||
            std::is_same_v<bool, SerializeableT>
        ), int>  = 0>
    void serialize(std::ostream& os, const SerializeableT& value)
    {
        serializeValue(os, value);
    }


    template <class SerialzeableT>
    void serializeStructure(std::ostream& os);

protected:
    virtual void serializeObjectStart(std::ostream& os) = 0;
    virtual void serializeObjectEnd(std::ostream& os) = 0;
    virtual void serializeName(std::ostream& os, const char* const name) = 0;
    virtual void serializeSeperator(std::ostream& os) = 0;

    virtual void serializeValue(std::ostream& os, const int& value) = 0;
    virtual void serializeValue(std::ostream& os, const char& value) = 0;
    virtual void serializeValue(std::ostream& os, const bool& value) = 0;
    virtual void serializeValue(std::ostream& os, const char* const value) = 0;

    virtual void serializeTypeInt(std::ostream& os) = 0;
    virtual void serializeTypeChar(std::ostream& os) = 0;
    virtual void serializeTypeBool(std::ostream& os) = 0;
    virtual void serializeTypeString(std::ostream& os) = 0;

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
                serializeSeperator(os);
            } else {
                firstMember = false;
            }

            serializeName(os, descriptor.getName());
            // forward to virtual functions for value output
            serialize(os, descriptor.getMemberValue(object));
        }

    /** used to convert member ptr to the type of the member */
    template <class SerializeableT, class MemberT>
    MemberT memberPtrToType(MemberT SerializeableT::*);

    template <class MemberT,
        typename std::enable_if_t<
            !std::is_same_v<char, MemberT> &&
            !std::is_same_v<int, MemberT> &&
            !std::is_same_v<const char*, MemberT> &&
            !std::is_same_v<bool, MemberT>, int>  = 0>
    void serializeType(std::ostream& os)
    {
        serializeStructure<MemberT>(os);
    }

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<char, MemberT>, int> = 0>
    void serializeType(std::ostream& os)
    {
        serializeTypeChar(os);
    }

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<int, MemberT>, int> = 0>
    void serializeType(std::ostream& os)
    {
        serializeTypeInt(os);
    }

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<const char*, MemberT>, int> = 0>
    void serializeType(std::ostream& os)
    {
        serializeTypeString(os);
    }

    template <class MemberT,
        typename std::enable_if_t<std::is_same_v<bool, MemberT>, int> = 0>
    void serializeType(std::ostream& os)
    {
        serializeTypeBool(os);
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
                serializeSeperator(os);
            } else {
                firstDescriptor = false;
            }

            // forward member name serialization
            serializeName(os, descriptor.getName());

            // forward serialization of type info
            serializeType<MemberT>(os);
        }
    
};
} // Serial

// template functions
#include "Serializer.cpp"
#endif //__SERIALIZER_H__