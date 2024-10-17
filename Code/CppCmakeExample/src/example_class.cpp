#include "example_class.h"

void ExampleClass::CounterAddOne() {
    counter++;
}

uint8_t ExampleClass::GetCounter() {
    return counter;
}

void ExampleClass::Reset() {
    counter = 0;
}
