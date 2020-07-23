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

#include <chrono>
#include <fstream>

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

    char fct2(int a, char b) {
        std::cout << "Hello from fct 2" << std::endl;
        return b;
    }

public:
    static constexpr auto descriptor = Serialization::Descriptor::makeClassDescriptor(
        "MyClass",
        &MyClass::a, "a",
        &MyClass::b, "b",
        &MyClass::c, "c",
        &MyClass::d, "d",
        &MyClass::e, "e",
        &MyClass::f, "f",
        &MyClass::fct, "fct", std::array<const char* const, 1>({"a"}),
        &MyClass::fct2, "fct2", std::array<const char* const, 2> ({"a", "b"})
    );
};

//-------------------------------- CONSTANTS ----------------------------------

//------------------------------ CONSTRUCTOR ----------------------------------

//--------------------------- EXPOSED FUNCTIONS -------------------------------

int main(int argc, char* argv[], char* env[])
{
    MyClass mc1{1, '2', 3, "Hello Serial World!", true};
    MyClass mc2{4, '5', 6, "This is going well", false};

    Serialization::Serializer<Serialization::JSONSerializer>::serialize(std::cout, mc1);
    std::cout << std::endl;
    Serialization::Serializer<Serialization::JSONSerializer>::serialize(std::cout, mc2);
    std::cout << std::endl;
    Serialization::Serializer<Serialization::JSONSerializer>::serializeStructure<MyClass>(std::cout);
    std::cout << std::endl;

    // test time
    std::ofstream myfile;
    constexpr size_t count = 1e7;
    myfile.open("/dev/null");
    myfile << "{";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (size_t ii = 0; ii < count; ++ii) {
        Serialization::Serializer<Serialization::JSONSerializer>::serialize(myfile, mc1);
        if (ii < (count -1))
        {
           myfile << ",";
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    myfile << "}";
    std::cout << "Made " << count << " serializations in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "µs" << std::endl;

    return 0;
}
 
//----------------------- INTERFACE IMPLEMENTATIONS ---------------------------

//--------------------------- PRIVATE FUNCTIONS -------------------------------

//---------------------------- STATIC FUNCTIONS -------------------------------