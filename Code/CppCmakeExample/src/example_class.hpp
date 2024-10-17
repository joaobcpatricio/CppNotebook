#ifndef TEMPLATE_EXAMPLE_CLASS_HPP
#define TEMPLATE_EXAMPLE_CLASS_HPP

#include <cstdint>

class ExampleClass {
private:
    uint8_t counter = 0;
public:
    uint8_t GetCounter();
    void CounterAddOne();
    void Reset();
    void PrintConfigured();
};


#endif //TEMPLATE_EXAMPLE_CLASS_HPP
