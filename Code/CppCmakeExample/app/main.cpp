#include <iostream>

#include "example_class.hpp"
#include "config.hpp"

int main() {
    std::cout << project_name << "\n";
    std::cout << project_version << "\n";

    ExampleClass exampleClass;
    exampleClass.PrintConfigured();
    
    return 0;
}