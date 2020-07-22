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

#include "Descriptor.h"
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
    static constexpr auto descriptor = Serialization::Descriptor::makeClassDescriptor(
        "InnerClass",
        &InnerClass::a, "a"
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
    int fct(int a){
        std::cout << "Hello from fct" << std::endl;
        return a;
    }

public:
    static constexpr auto descriptor = Serialization::Descriptor::makeClassDescriptor(
        "MyClass",
        &MyClass::a, "a",
        &MyClass::b, "b",
        &MyClass::c, "c",
        &MyClass::d, "d",
        &MyClass::e, "e",
        &MyClass::f, "f"
    );
};

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

//--------------------------- EXPOSED FUNCTIONS -------------------------------

struct A
{
    int a;
    char b;
};

int main(int argc, char* argv[], char* env[])
{
    MyClass mc1{1, '2', 3, "Hello Serial World!", true};
    MyClass mc2{4, '5', 6, "This is going well", false};

    Serialization::JSONSerializer s1;

    auto descriptor = Serialization::Descriptor::makeClassDescriptor(
        "A",
        &A::a, "a",
        &A::b, "b"
    );

    s1.serialize(std::cout, mc1);
    std::cout << std::endl;
    s1.serialize(std::cout, mc2);
    std::cout << std::endl;
    s1.serializeStructure<MyClass>(std::cout);
    std::cout << std::endl;

    //std::cout << "number of decriptors: " << std::tuple_size<decltype(MyClass::descriptors)>::value << std::endl;
    

    return 0;
}
 
//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------