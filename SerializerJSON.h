/**
 * @file SerializerJSON.h
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief automatic json serializer
 * @version 1.0
 * @date 2020-07-20
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

#ifndef __SERIALIZERJSON_H__
#define __SERIALIZERJSON_H__

//-------------------------------- PROTOTYPES ---------------------------------

namespace Serialization
{
class JSONSerializer;
}

//--------------------------------- INCLUDES ----------------------------------

#include "Serializer.h"

namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief automatic json serializer
 */
class JSONSerializer : public Serializer
{
    // delete default constructors
    JSONSerializer(const JSONSerializer& other) = delete;
    JSONSerializer& operator=(const JSONSerializer& other) = delete;
public:
    JSONSerializer(){}

protected:
    virtual void serializeObjectStart(std::ostream& os) override
    {
        os << "{";
    }

    virtual void serializeObjectEnd(std::ostream& os) override
    {
        os << "}";
    }

    virtual void serializeMember(std::ostream& os, const char* const memberName, int value) override
    {
        os << "\"" << memberName << "\":" << value;
    }

    virtual void serializeMember(std::ostream& os, const char* const memberName, char value) override
    {
        os << "\"" << memberName << "\":" << value;
    }

    virtual void serializeMember(std::ostream& os, const char* const memberName, bool value) override
    {
        os << "\"" << memberName << "\":" << (value ? "true" : "false");
    }

    virtual void serializeMember(std::ostream& os, const char* const memberName, const char* const value) override
    {
        os << "\"" << memberName << "\":\"" << value << "\"";
    }

    virtual void serializeMemberSeperator(std::ostream& os) override
    {
        os << ",";
    }

    virtual void serializeDescriptorInnerClassName(std::ostream& os, const char* const name) override
    {
        os << "\"" << name << "\":";
    }

    virtual void serializeDescriptorChar(std::ostream& os, const char* const name) override
    {
        os << "\"" << name << "\":\"CHAR\"";
    }

    virtual void serializeDescriptorInt(std::ostream& os, const char* const name) override
    {
        os << "\"" << name << "\":\"INT\"";
    }

    virtual void serializeDescriptorString(std::ostream& os, const char* const name) override
    {
        os << "\"" << name << "\":\"STRING\"";
    }

    virtual void serializeDescriptorBool(std::ostream& os, const char* const name) override
    {
        os << "\"" << name << "\":\"BOOLEAN\"";
    }
};
} // Serialization
#endif //__SERIALIZERJSON_H__