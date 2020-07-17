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
#include <iostream>
#include <array>

//--------------------------- STRUCTS AND ENUMS -------------------------------

class MyClass
{
    friend class Descriptor;

public:
    MyClass(int a, char b) : a(a), b(b)
    {

    }



private:
    int a;
    char b;    
};

class Descriptor
{
public:
    static Serialization::MemberDescriptor<MyClass, decltype(MyClass::a), &MyClass::a> descriptorA;
    static Serialization::MemberDescriptor<MyClass, decltype(MyClass::b), &MyClass::b> descriptorB;
};

Serialization::MemberDescriptor<MyClass, decltype(MyClass::a), &MyClass::a> Descriptor::descriptorA{"a"};
Serialization::MemberDescriptor<MyClass, decltype(MyClass::b), &MyClass::b> Descriptor::descriptorB{"b"};


//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

//--------------------------- EXPOSED FUNCTIONS -------------------------------

int main(int argc, char* argv[], char* env[])
{
    MyClass mc1{1,2};
    MyClass mc2{3,4};

    std::cout << Descriptor::descriptorA.getMemberValue(mc1) << std::endl;
    std::cout << Descriptor::descriptorB.getMemberValue(mc1) << std::endl;

    std::cout << Descriptor::descriptorA.getMemberValue(mc2) << std::endl;
    std::cout << Descriptor::descriptorB.getMemberValue(mc2) << std::endl;
    return 0;
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------