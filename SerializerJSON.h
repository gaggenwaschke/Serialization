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
    static constexpr const char* const ObjectStart = "{";
    static constexpr const char* const ObjectEnd = "}";
    static constexpr const char* const ArrayStart = "[";
    static constexpr const char* const ArrayEnd = "]";
    static constexpr const char* const BeforeName = "\"";
    static constexpr const char* const AfterName = "\":";
    static constexpr const char* const Seperator = ",";

    static constexpr const char* const TypeChar = "\"CHAR\"";
    static constexpr const char* const TypeInt = "\"INT\"";
    static constexpr const char* const TypeString = "\"STRING\"";
    static constexpr const char* const TypeBool = "\"BOOL\"";

    static constexpr const char* const FieldNameClass = "ClassName";
    static constexpr const char* const FieldNameMembers = "Members";
    static constexpr const char* const FieldNameFunctions = "Functions";
    static constexpr const char* const FieldNameArguments = "Arguments";

    static void serializeValue(std::ostream& os, const int& value)
    {
        os << value;
    }

    static void serializeValue(std::ostream& os, const char& value)
    {
        os << value;
    }

    static void serializeValue(std::ostream& os, const bool& value)
    {
        os << (value ? "true" : "false");
    }

    static void serializeValue(std::ostream& os, const char* const value)
    {
        os << "\"" << value << "\"";
    }

    template <class T>
    static constexpr const char* const getTypeName()
    {
        return "\"unknown\"";
    }
};
} // Serialization
#endif //__SERIALIZERJSON_H__