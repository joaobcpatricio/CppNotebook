#ifndef TEMPLATE_EXAMPLE_CLASS_H
#define TEMPLATE_EXAMPLE_CLASS_H

#include <cstdint>

class ExampleClass {
private:
    uint8_t counter = 0;
public:
    uint8_t GetCounter();
    void CounterAddOne();
    void Reset();
};


#endif //TEMPLATE_EXAMPLE_CLASS_H
