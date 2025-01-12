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


struct Entity
{
    static int x, y;
    void Print()
    {
        std::cout << x << "," << y << std::endl;
    }
};


enum class DayOfWeek { 
    Monday=1, Tuesday=2, Wednesday=3, Thursday=4, Friday=5, Saturday=6, Sunday=0 
};



#endif //TEMPLATE_EXAMPLE_CLASS_HPP
