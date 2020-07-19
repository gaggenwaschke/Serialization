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
#include "Serializer.h"
#include <iostream>
#include <tuple>

//--------------------------- STRUCTS AND ENUMS -------------------------------

class MyClass
{
    template <auto> struct DeduceType;
public:
    MyClass(int a, char b, int c) : a(a), b(b), c(c)
    {
    }

private:
    int a;
    char b;
    int c;
    const char* const d = "Hello World!";

public:
    static constexpr auto descriptors = std::make_tuple(
        Serialization::MemberDescriptor(&MyClass::a, "a"),
        Serialization::MemberDescriptor(&MyClass::b, "b"),
        Serialization::MemberDescriptor(&MyClass::c, "c"),
        Serialization::MemberDescriptor(&MyClass::d, "d")
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
    MyClass mc1{1, '2', 3};
    MyClass mc2{4, '5', 6};

    Serialization::Serializer s1;

    s1.serialize(std::cout, mc1);

    //std::cout << "number of decriptors: " << std::tuple_size<decltype(MyClass::descriptors)>::value << std::endl;
    // print name value pairs
    
    std::apply([&mc1, &s1](const auto &... args) {
        (s1.serialize(std::cout, args), ...);
    }, MyClass::descriptors);
    
    

    return 0;
}
 
//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------