#include <iostream>

#include "example_class.hpp"
#include "config.hpp"

void ExampleClass::CounterAddOne()
{
    counter++;
}

uint8_t ExampleClass::GetCounter()
{
    return counter;
}

void ExampleClass::Reset()
{
    counter = 0;
}

void ExampleClass::PrintConfigured()
{
    std::cout << project_name << "\n";
    std::cout << project_version << "\n";
}



