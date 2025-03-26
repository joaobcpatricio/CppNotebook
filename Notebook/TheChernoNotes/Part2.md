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


## Inheritance

Inheritance is one of the most powerful features one can leverage in OOP. It allows us to have a hierarchy of classes which relate to each other. In oder words, it allows us to have a base class with common functionality and then it allows us to branch of from that class and create sub-classes from that initial parent class. This reduces code duplication.

Example:
```cpp
class Entity{
  public:
  float X, Y;
  void Move(float ya, float ya){
    Y += xa;
    Y += ya;
  }
};

class Player{
public:
  const char* Name;
  float X, Y;
  void Move(float ya, float ya){
    Y += xa;
    Y += ya;
  }
    void PrintName(
    std::cout << Name yy std::endl;>>
  );
};
```

```cpp
class Entity{
  public:
  float X, Y;
  void Move(float ya, float ya){
    Y += xa;
    Y += ya;
  }
};

class Player : public Entity{
public:
  const char* Name;
  void PrintName(
    std::cout << Name yy std::endl;>>
  );
};

int main(){
  Player player;
  player.PrintName();
  player.Move(1,1);
  player.X = 2;
}
```

Player is now polymorph, a superset of Entity, we can use it in whatever we need that uses Entity, with extra stuff. That means if I am expecting somewhere in code an Entity I can provide Player and it will work fine.

*Side note that will be approached along this series: The V-table (short for Virtual Table) is a mechanism used in C++ (and other object-oriented languages) to support runtime polymorphism, which enables the correct method to be called based on the actual type of the object, rather than the type of the pointer or reference (virtual functions). When a virtual function is called on an object, the compiler doesn't call the function directly through the class. Instead, it accesses the V-table via the V-pointer and looks up the correct function to call. This allows the correct function to be called based on the actual type of the object at runtime (not compile time).*


## Virtual Functions

Virtual functions allow to override methods in subclasses.

Example:
```cpp
class Entity{
  public:
  std::string GetName() {return "Entity";}
}

class Player : public Entity{
private:
  std::string m_Name;
public:
  Player(const std::string& name) : m_Name(name) {}

  std::string GetName() { return m_Name; }
}
```
With this, if we call `player->GetName()` we get the name we set, but if we use polymorphism and pass down the player as an entity, it will now return *"Entity"* instead. 
```cpp
int main(){
  Entity* e = new Entity();
  std::cout << e->GetName() << std::endl; //Entity

  Player* p = new Player("Cherno");
  std::cout << p->GetName() << std::endl; // Cherno

  Entity* entity = p;
  std::cout << entity->GetName() << std::endl; //Entity
}
```

To avoid such, we need to make it virtual.
Virtual functions introduces dynamic dispatch, where the compilation is usually implemented with a V table.
A V table contains a map of all the virtual functions of our base class to the actual overwritten function in runtime.

```cpp
class Entity{
  public:
  virtual std::string GetName() {return "Entity";}
}

class Player : public Entity{
private:
  std::string m_Name;
public:
  Player(const std::string& name) : m_Name(name) {}

  std::string GetName() override { return m_Name; }
}
int main(){
  Entity* e = new Entity();
  std::cout << e->GetName() << std::endl; //Entity

  Player* p = new Player("Cherno");
  std::cout << p->GetName() << std::endl; // Cherno

  Entity* entity = p;
  std::cout << entity->GetName() << std::endl; //Cherno
}
```

Adding *override* is not required for it to work, but it is advised as it makes the code more readable and to prevent bugs, like from misspelling mistakes. E.g. if I wrote *Getname* instead of *GetName* it would warn be about it as it does not exist on the base class.

Virtual functions come a two runtime costs:
1. Additional memory is needed to store information in the V table so that we can send it to the function with the parameter pointing to V table in the base class with the True Pointer
2. every time we call a virtual function it needs to go through that table and check which function is mapped to.

With most modern HW, this performance costs is redundant, except for possibly some limited embedded devices.


## Interfaces

A type of virtual functions are pure virtual functions, that are similar to abstract method or interface in other languages like C# or Java.

It allows the definition of a method in a base class that does not have an implementation and to force subclasses to actually implement that function. Doing this is often referred to as an interface. 

When an Interface is only consistent of virtual methods, one cannot directly instantiate one.

Example:
```cpp
class Entity{
  public:
  virtual std::string GetName() = 0;  //=0 makes it pure virtual.
}

class Player : public Entity{
private:
  std::string m_Name;
public:
  Player(const std::string& name) : m_Name(name) {}

  std::string GetName() override { return m_Name; }
}
int main(){
  // Entity* e = new Entity(); => this is no more possible
  Entity* e = new Player("");
  std::cout << e->GetName() << std::endl; //Entity

  Player* p = new Player("Cherno");
  std::cout << p->GetName() << std::endl; // Cherno

  Entity* entity = p;
  std::cout << entity->GetName() << std::endl; //Cherno
}
```

Example of interface usage:

```cpp
class Printable{
public:
  virtual std::string GetClassName() = 0;
}

class Entity : public Printable{
  public:
  virtual std::string GetName() {return "Entity";}
  std::string GetClassName() override { return "Entity"; }
}

class Player : public Entity{
private:
  std::string m_Name;
public:
  Player(const std::string& name) : m_Name(name) {}

  std::string GetName() override { return m_Name; }
  std::string GetClassName() override { return "Entity"; }
}

void PrintName(Entity* entity){
  std::cout << entity->GetName() << std::endl;
}

void Print( Printable obj){
  std::cout << obj->GetClassName() << std::endl;
}

int main(){
  Entity* e = new Entity();
  Print(e); //Entity

  Player* p = new Player("Cherno");
  Print(p); // Player
}
```

On the previous example, we have the Printable as an interface and Player inherits that from the Entity.

This is useful so we can guarantee that a class has certain defined method calls, that then change on implementation due to their specifics.

For example, by having an interface of some code, another person can work on the part that only consumes it, testing with a mock, before it is ready, not being blocked by the developer that is working on the actual class that inherits from that interface.


## Visibility

In C++, visibility (or access control) determines which parts of your code can access the members (variables and functions) of a class. There are three main keywords that control visibility:

* public: Members declared as public are accessible from anywhere, both inside and outside the class. This is generally used for the interface of the class, the things you want other parts of your code to use.

* private: Members declared as private are only accessible from within the same class. Not even derived classes can access them. This is used to hide internal implementation details and protect the integrity of the class's state.

* protected: Members declared as protected are accessible from within the same class and from derived (child) classes. They are not accessible from outside the class hierarchy. This is useful for providing functionality that derived classes need but that should not be exposed to the general public.

In C++ classes, the default is private, while a struct is public.


## Arrays

Array is a collection of variables in a particular order (in a row) that make sense to be together.

Example:

```cpp
int main(){
  int example[5];   //goes from index 0 to 4  
                    //example is a memory address itself pointing to the start of the array, the index moves from its start.
  example[0] = 1;
  example[4] = 5;

  std::cout<<example[0] << std::endl;

  for(int i=0; i<5; i++){
    example[i] = i+1;
  }

  int* ptr = example; //array "is just a pointer"
  *(ptr +2) = 6;  //same as doing example[2]=6 // same as *(int*)*((char*)ptr + 8) = 6 // because type char is only 1 byte while int is 4
}
```

```cpp
int main(){
  int example[5]; //created on the stack, will be deleted once we get out of scope

  int * another = new int[5]; //created on the heap, will be alive until we delete it
  delete[] another;
}
```

Using heap can add more jumps and decrease performance, stack optimizes to have the code together.

To know the size of the array there are some ways, compiler dependent and non trustable:
```cpp
int main(){
  int a[5];
  sizeof(a);//4*5=20 bytes
  int count = sizeof(a)/sizeof(int);  //=5  //only works with stack allocated variables
}
```

```cpp
class Entity{
public:
  static cons int exampleSize = 5;
  int example[exampleSize];
  Entity(){
    for(int i=0; i<exampleSize; i++){
      example[i] = 2;
    }
  }
}
```

With C++ version 11 or higher, best is tu use the standard library:
```cpp
#include <array>
class Entity{
public:
  std::array<int, 5> another;
  Entity(){
    for(int i=0; i<another.size(); i++){
      example[i] = 2;
    }
  }
}
```