# **C++** 
# Part 2


#### [Table of Contents](README.md#table-of-contents)

## Constructors

In C++, constructors are special member functions of a class that are automatically called when an object of that class is created. Their primary purpose is to initialize the object's member variables.

Key features:

* **Same name as the class**: A constructor has the same name as the class it belongs to.
* **No return type**: Constructors don't have a return type (not even void).
* **Multiple constructors (overloading)**: A class can have multiple constructors with different parameter lists (constructor overloading), allowing for flexible object creation.
* **Default constructor**: If you don't define any constructors, the compiler provides a default constructor (which does nothing).
* **Initialization list**: Member variables are typically initialized in the constructor's initializer list (using : member1(value1), member2(value2) ...) for better performance and avoiding potential issues with default constructors of members.
* **Destructors**: Constructors are paired with destructors (~ClassName()), which are called when an object is destroyed.
* 
Example:

```cpp
#include <iostream>
#include <string>

class Dog {
public:
  // Constructor with initialization list
  Dog(std::string name, int age) : name_(name), age_(age) {
    std::cout << "Dog constructor called\n";
  }

  // Default constructor
  Dog() : name_("Unknown"), age_(0) {}

  void bark() {
    std::cout << "Woof!\n";
  }

private:
  std::string name_;
  int age_;
};

int main() {
  Dog myDog("Buddy", 3);
  myDog.bark();

  Dog anotherDog; // Uses the default constructor
  anotherDog.bark();
  return 0;
}
```
Constructors ensure that objects are properly initialized before they're used, preventing errors and improving code reliability.


## Destructors

In C++, a destructor is a special member function of a class that's automatically called when an object of that class goes out of scope or is explicitly deleted. Its primary purpose is to perform cleanup actions before the object's memory is released.

Key features:

* **Same name as the class, prefixed with a tilde (~)**: A destructor has the same name as the class, but with a tilde (~) character before it (e.g., ~MyClass()).
* **No parameters**: Destructors don't take any arguments.
* **No return type**: Destructors don't have a return type.
* **Automatic invocation**: The destructor is called automatically when an object is no longer needed. This happens when:
    * An object goes out of scope (e.g., at the end of a function or block).
    * An object is explicitly deleted using delete.
    * A program terminates.
* **Cleanup tasks**: Destructors are used to release resources held by the object, such as dynamically allocated memory, open files, network connections, etc. Failing to release these resources can lead to memory leaks or other problems.
* **Order of destruction**: Destructors are called in the reverse order of construction (Last-In, First-Out, or LIFO).

Example: 
```cpp
#include <iostream>

class ResourceHolder {
public:
  ResourceHolder() {
    resource_ = new int(10);
    std::cout << "ResourceHolder constructor called. Resource allocated at: " << resource_ << "\n";
  }

  ~ResourceHolder() {
    delete resource_;
    std::cout << "ResourceHolder destructor called. Resource deallocated.\n";
  }

private:
  int* resource_;
};

int main() {
  { //ResourceHolder object goes out of scope at the end of this block
    ResourceHolder rh;
  }
  std::cout << "End of main function\n";
  return 0;
}
```
In this example, the ResourceHolder destructor releases the dynamically allocated memory pointed to by resource_. If the destructor weren't present, a memory leak would occur. The output clearly shows the constructor and destructor being called at the appropriate times. Proper use of destructors is essential for writing robust and leak-free C++ programs.