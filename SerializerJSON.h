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

namespace Serialization
{
//-------------------------------- CONSTANTS ----------------------------------

//---------------------------- CLASS DEFINITION -------------------------------

/**
 * @brief automatic json serializer
 */
class JSONSerializer
{
    template <class T>
    friend class Serialization::Serializer;

    // delete default constructors
    JSONSerializer() = delete;
    JSONSerializer(const JSONSerializer& other) = delete;
    JSONSerializer& operator=(const JSONSerializer& other) = delete;

private:
    constexpr const char* const ObjectStart = "{";
    constexpr const char* const ObjectEnd = "}";
    constexpr const char* const ArrayStart = "[";
    constexpr const char* const ArrayEnd = "]";
    constexpr const char* const BeforeName = "\"";
    constexpr const char* const AfterName = "\":";
    constexpr const char* const Seperator = ",";

    constexpr const char* const TypeChar = "\"CHAR\"";
    constexpr const char* const TypeInt = "\"INT\"";
    constexpr const char* const TypeString = "\"STRING\"";
    constexpr const char* const TypeBool = "\"BOOL\"";

    constexpr const char* const FieldNameClass = "ClassName";
    constexpr const char* const FieldNameMembers = "Members";
    constexpr const char* const FieldNameFunctions = "Functions";
    constexpr const char* const FieldNameArguments = "Arguments";

    void serializeValue(std::ostream& os, const int& value)
    {
        os << value;
    }

    void serializeValue(std::ostream& os, const char& value)
    {
        os << value;
    }

    void serializeValue(std::ostream& os, const bool& value)
    {
        os << (value ? "true" : "false");
    }

    void serializeValue(std::ostream& os, const char* const value)
    {
        os << "\"" << value << "\"";
    }
};
} // Serialization
#endif //__SERIALIZERJSON_H__