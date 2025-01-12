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

// Struct
struct Entity
{
    static int x, y;
    void Print()
    {
        std::cout << x << "," << y << std::endl;
    }
};

//Enums
enum class DayOfWeek { 
    Monday=1, Tuesday=2, Wednesday=3, Thursday=4, Friday=5, Saturday=6, Sunday=0 
};

//Constructor
class Dog {
public:
  Dog(std::string name, int age) : name_(name), age_(age) {
    std::cout << "Dog constructor called\n";
  }
  // Default constructor
  Dog() : name_("Unknown"), age_(0) {}
  ~Dog() = default; // Explicitly use the default destructor

  std::string getName() const { return name_; }
  int getAge() const { return age_; }

private:
  std::string name_;
  int age_;
};



#endif //TEMPLATE_EXAMPLE_CLASS_HPP
