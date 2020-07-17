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
#include <tuple>

//--------------------------- STRUCTS AND ENUMS -------------------------------

class MyClass
{
public:
    MyClass(int a, char b) : a(a), b(b)
    {

    }

private:
    int a;
    char b;

public:
    static Serialization::MemberDescriptor<MyClass, decltype(MyClass::a), &MyClass::a> descriptorA;
    static Serialization::MemberDescriptor<MyClass, decltype(MyClass::b), &MyClass::b> descriptorB;    

    static std::tuple<decltype(descriptorA)&, decltype(descriptorB)&> descriptors;
};

Serialization::MemberDescriptor<MyClass, decltype(MyClass::a), &MyClass::a> MyClass::descriptorA{"a"};
Serialization::MemberDescriptor<MyClass, decltype(MyClass::b), &MyClass::b> MyClass::descriptorB{"b"};
std::tuple<decltype(MyClass::descriptorA)&, decltype(MyClass::descriptorB)&> descriptors = {MyClass::descriptorA, MyClass::descriptorB};

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

//--------------------------- EXPOSED FUNCTIONS -------------------------------

int main(int argc, char* argv[], char* env[])
{
    MyClass mc1{1,2};
    MyClass mc2{3,4};

    std::cout << MyClass::descriptorA.getMemberValue(mc1) << std::endl;
    std::cout << MyClass::descriptorB.getMemberValue(mc1) << std::endl;

    std::cout << MyClass::descriptorA.getMemberValue(mc2) << std::endl;
    std::cout << MyClass::descriptorB.getMemberValue(mc2) << std::endl;
    return 0;
}

//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------