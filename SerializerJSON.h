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

    virtual void serializeName(std::ostream& os, const char* const name) override
    {
        os << "\"" << name << "\":";
    }

    virtual void serializeSeperator(std::ostream& os) override
    {
        os << ",";
    }

    virtual void serializeValue(std::ostream& os, const int& value) override
    {
        os << value;
    }

    virtual void serializeValue(std::ostream& os, const char& value) override
    {
        os << value;
    }

    virtual void serializeValue(std::ostream& os, const bool& value) override
    {
        os << (value ? "true" : "false");
    }

    virtual void serializeValue(std::ostream& os, const char* const value) override
    {
        os << "\"" << value << "\"";
    }

    virtual void serializeTypeChar(std::ostream& os) override
    {
        os << "\"CHAR\"";
    }

    virtual void serializeTypeInt(std::ostream& os) override
    {
        os << "\"INT\"";
    }

    virtual void serializeTypeString(std::ostream& os) override
    {
        os << "\"STRING\"";
    }

    virtual void serializeTypeBool(std::ostream& os) override
    {
        os << "\"BOOLEAN\"";
    }

    virtual const char* const getClassNameFieldName() override 
    {
        return "ClassName";
    }

    virtual const char* const getMembersFieldName() override
    {
        return "Members";
    }
};
} // Serialization
#endif //__SERIALIZERJSON_H__