/**
 * @file main.cpp
 * @author Joshua Lauterbach (joshua@aconno.de)
 * @brief test file for Serialization
 * @version 1.0
 * @date 2020-07-17
 * 
 * @copyright aconno GmbH (c) 2020
 * 
 */

//--------------------------------- INCLUDES ----------------------------------

#include "MemberDescriptor.h"
#include "SerializerJSON.h"
#include <iostream>
#include <tuple>

//--------------------------- STRUCTS AND ENUMS -------------------------------

class InnerClass
{
public:
    InnerClass() : a(1) {}

private:
    int a;

public:
    static constexpr auto descriptors = std::make_tuple(
        Serialization::MemberDescriptor(&InnerClass::a, "a")
    );
};

class MyClass
{
public:
    MyClass(int a, char b, int c, const char* const d, bool e) :
        a(a), b(b), c(c), d(d), e(e), f()
    {
    }

private:
    int a;
    char b;
    int c;
    const char* const d;
    bool e;
    InnerClass f;

public:
    static constexpr auto descriptors = std::make_tuple(
        Serialization::MemberDescriptor(&MyClass::a, "a"),
        Serialization::MemberDescriptor(&MyClass::b, "b"),
        Serialization::MemberDescriptor(&MyClass::c, "c"),
        Serialization::MemberDescriptor(&MyClass::d, "d"),
        Serialization::MemberDescriptor(&MyClass::e, "e"),
        Serialization::MemberDescriptor(&MyClass::f, "f")
    );
};

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

//--------------------------- EXPOSED FUNCTIONS -------------------------------

template <class SerializeableT, class MemberT>
void print(const Serialization::MemberDescriptor<SerializeableT, MemberT>& descriptor, SerializeableT& object)
{
    std::cout << descriptor.getName() << "(" << typeid(MemberT).name() << "): " << descriptor.getMemberValue(object) << std::endl;
}

int main(int argc, char* argv[], char* env[])
{
    MyClass mc1{1, '2', 3, "Hello Serial World!", true};
    MyClass mc2{4, '5', 6, "This is going well", false};

    Serialization::JSONSerializer s1;

    s1.serialize(std::cout, mc1);
    std::cout << std::endl;
    s1.serialize(std::cout, mc2);
    std::cout << std::endl;
    s1.serializeStructure<MyClass>(std::cout);
    std::cout << std::endl;

    //std::cout << "number of decriptors: " << std::tuple_size<decltype(MyClass::descriptors)>::value << std::endl;
    // print name value pairs

    return 0;
}
 
//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------