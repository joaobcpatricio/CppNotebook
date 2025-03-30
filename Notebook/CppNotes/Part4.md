# **C++** 
# Part 4


#### [Table of Contents](README.md#table-of-contents)


## Object Lifetime

**Scope**: can be anything inside an if or similar statement, a class or anything that lives inside *{}*, and as long as the objects are not allocated on the heap, they are also "scope lived".

Example: *a* has shorter life than *b*, it is deleted once out of scope.
```cpp
int main(){
    int b = 3;
    {
        int a = 2;
    }
}
```

Example under next topics, smart-pointer that is a scope pointer. 

Lets see next an example for its logic:

```cpp
class Entity{
public:
    Entity(){
        std::cout << "Created Entity!" << setd::endl;
    }
    ~Entity(){
        std::cout << "Destroyed Entity!" << setd::endl;
    }
};
class ScopedPtr{
private:
    Entity* m_Ptr;
public:
    ScopedPtr(Entity* ptr) : m_Ptr(ptr){}
    ~ScopedPtr(){
        delete m_Ptr;
    }
};
int main(){
    {
        ScopedPtr e = new Entity;   //same as Scoped e(new Entity());   //this has implicit conversion
        //Since e was allocated on the stack, when we get out of scope, it will call the destructor and, therefore, eliminate the heap pointer for us. This is kind of the logic of smart pointers.
    }
}
```


## Smart Pointers

*New* and *delete* are used to allocate the object on the heap. Smart pointers automate that process, allocating it when created and deleting it when out of scope.

### Unique Pointer
**Unique Pointers** cannot be copied, to avoid having 2 pointers to the same memory and that one that memory is freed, we do not end up having the other pointer still pointing to it by mistake.

Example:

```cpp
#include <memory>
class Entity{
public:
    Entity(){
        std::cout << "Created Entity!" << setd::endl;
    }
    ~Entity(){
        std::cout << "Destroyed Entity!" << setd::endl;
    }
    void Print();
};
int main(){
    {
        //1: std::unique_ptr<Entity> entity(new Entity());  //it is explicit, so it has to call the constructor like this. But a better way is:
        std::unique_ptr<Entity> entity = std::make_unique<Entity>();    //this has exception safety
        entity->Print();
        //std::unique_ptr<Entity> e0 = entity; //=>this will give an error, if you check the liv, the copy constructor and assign operators are deleted. 
    }
    //By here entity will be destroyed.
}
```

### Shared Pointer

Shared pointer implementation depends also on the compiler and library being used, but it usually uses a reference counting that keeps track of how many references exist to that pointer and once it gets to 0  it deletes the pointer.

Example:
```cpp
#include <memory>
class Entity{
public:
    Entity(){
        std::cout << "Created Entity!" << setd::endl;
    }
    ~Entity(){
        std::cout << "Destroyed Entity!" << setd::endl;
    }
    void Print();
};
int main(){
    {
        std::shared_ptr<Entity> e0 = std::make_shared<Entity>(); //HEre we really want to initialize it alike this instead of using new first (see previous example *1:*), otherwise will have two allocations as we're constructing the entity first and then the sharepoint has to construct the control block. This way it does both right away and together.
        {          
            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
            e0 = sharedEntity;
        }
    }
    //By here shared_ptr entity will be destroyed.
}
```

Under the previous example, if we debug we will see that the delete from *sharedEntity* will not be called once we get out of its scope, only we get out of the e0 scope, as it is when the shared pointer counter gets to 0.

### Weak Pointer

When assigning a shared pointer to another, this gets increased. But when assigning a shared pointer to a weak pointer, it does not! This is great if you do not want to take ownership of the entity. It prevents circular references.

Example:
```cpp
#include <memory>
class Entity{
public:
    Entity(){
        std::cout << "Created Entity!" << setd::endl;
    }
    ~Entity(){
        std::cout << "Destroyed Entity!" << setd::endl;
    }
    void Print();
};
int main(){
    {
        std::weak_ptr<Entity> e0; 
        {          
            std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
            std::weak_ptr<Entity> weakEntity = sharedEntity;
            e0 = sharedEntity;
        }
        //By here shared_ptr entity will be destroyed.
    }
}
```

Example where a share pointer can create circular dependency and weak solves it:
```cpp
#include <memory>
#include <iostream>

class B;  // Forward declaration

class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A Destroyed\n"; }
};

class B {
public:
    std::shared_ptr<A> a_ptr;
    ~B() { std::cout << "B Destroyed\n"; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a; // Circular reference

    return 0;
} // Objects never get deleted -> Memory leak!

```
```cpp
#include <memory>
#include <iostream>

class B;  // Forward declaration

class A {
public:
    std::weak_ptr<B> b_ptr; // Use weak_ptr to break the cycle
    ~A() { std::cout << "A Destroyed\n"; }
};

class B {
public:
    std::shared_ptr<A> a_ptr;
    ~B() { std::cout << "B Destroyed\n"; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();

    a->b_ptr = b; // weak_ptr now
    b->a_ptr = a; // shared_ptr

    return 0;
} // Objects are properly destroyed!

```


## Copying and Copy Constructors

Copying takes time and we do want to avoid that as much as possible as it wastes performance.

Example, avoiding using modern C++ to show how this works.

```cpp
#include <string>
class String{
private:
    char* m_Buffer;
    unsigned int m_Size;
public:
    String(conts char* string){
        m_Size = strlen(string);
        m_Buffer = new char[m_Size+1];
        memcpy(m_Buffer,string, m_Size);    //strcpy includes the null termination character, so no need to do the next
        m_Buffer[m_Size] = 0;
    }
    ~String(){
        delete[] m_Buffer;
    }

    char& operator[](unsigned int index){   //this allows to address specific char in the string
        return m_Buffer[index];
    }

    friend std::ostream& operator<<(std::ostream& stream, const String& string);    //without this i could not directly call "string.m_Buffer" on the under function.
};
//use overload operator to make this printable
std::ostream& operator<<(std::ostream& stream, const String& string){
    stream << string.m_Buffer;
    return stream;
}
int main(){
    String string = "Cherno";
    std::cout << string << std::endl;

    String second = string;
    std::cout << second << std::endl;

    //Doing this without a Copy constructor, the compiler is by default copying the same pointer and memory address, so when we get out of scope it calls the delete 2 times, but on the second it will crash as it already deleted! Also, a change on either affects both!
}
```
To fix the previous issue we need a deep copy. For this you need a copy constructor:
```cpp
#include <string>
class String{
private:
    char* m_Buffer;
    unsigned int m_Size;
public:
    String(conts char* string){
        m_Size = strlen(string);
        m_Buffer = new char[m_Size+1];
        memcpy(m_Buffer,string, m_Size);   
        m_Buffer[m_Size] = 0;
    }

    String(const String& other) : m_Size(other.m_Size){
        m_Buffer = new char[m_Size+1];
        memcpy(m_Buffer, other.m_Buffer, m_Size+1); //no need to add null as it is a String so it will already have that
    }

    //If you dont want a copy, do:
    //String(const String& other) = delete; // and String second = string; will no longer work

    ~String(){
        delete[] m_Buffer;
    }
    char& operator[](unsigned int index){   /
        return m_Buffer[index];
    }
    friend std::ostream& operator<<(std::ostream& stream, const String& string);   
};
std::ostream& operator<<(std::ostream& stream, const String& string){
    stream << string.m_Buffer;
    return stream;
}

void PrintString(String string){    //This will make a copy
    std::cout << string << std::endl;
}

void PrintStringR(const String& string){    //This will not make a copy but directly access the content: passing by reference. Use const to promise no change, and also not passing temporary l values.
    std::cout << string << std::endl;
}

int main(){
    String string = "Cherno";
    std::cout << string << std::endl;

    String second = string;
    std::cout << second << std::endl;
}
```

Conclusion: in general, pass objects as const reference.


## Operators and operator overloading

An operator is basically some kind of symbol we use usually instead of a function, including mathematical operators but others.

Overloading in this subject mostly means gibing a new meaning to or adding parameters to or creating. Operator overloading allows to define or change the behavior of an operator on the program.

The use should, in reality, be minimal and only where it makes sense.

Lets see some examples.

Initially:
```cpp
struct Vector2{
    float x, y;
    Vector2(float x, float y) : x(x), y(y){}
    Vector2 Add(const Vector2& other) const{
        return Vector2(x+other.x, y+other.y);
    }
    Vector2 Multiply(const Vector2& other) const{
        return Vector2(x*other.x, y*other.y);
    }
}
int main(){
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 result = position.Add(speed);

    Vector2 powerup(1.1f, 1.1f);
    Vector2 result2 = position.Add(speed.Multiply(powerup));

}
```

With operator overloading:
```cpp
struct Vector2{
    float x, y;
    Vector2(float x, float y) : x(x), y(y){}
    Vector2 Add(const Vector2& other) const{
        return Vector2(x+other.x, y+other.y);
    }

    Vector2 operator+(const Vector2& other) const{
        return Add(other);
    }
    
    Vector2 Multiply(const Vector2& other) const{
        return Vector2(x*other.x, y*other.y);
    }

    Vector2 operator*(const Vector2& other) const{
        return Multiply(other);
    }
}
int main(){
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 result = position.Add(speed);

    Vector2 powerup(1.1f, 1.1f);
    Vector2 result2 = position + speed * powerup;
}
```
Example now for the left shift operator:
```cpp
struct Vector2{
    float x, y;
    Vector2(float x, float y) : x(x), y(y){}
    Vector2 Add(const Vector2& other) const{
        return Vector2(x+other.x, y+other.y);
    }

    Vector2 operator+(const Vector2& other) const{
        return Add(other);
    }
    
    Vector2 Multiply(const Vector2& other) const{
        return Vector2(x*other.x, y*other.y);
    }

    Vector2 operator*(const Vector2& other) const{
        return Multiply(other);
    }
}

std::ostream& operator<<(std::ostream& stream, const Vector2& other){
    stream << other.x << "," << other.y;
    return stream;
}
int main(){
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 result = position.Add(speed);

    Vector2 powerup(1.1f, 1.1f);
    Vector2 result2 = position + speed * powerup;

    std::cout << result2 <<< std::endl; //current there is no support for Vector2 type to go into cout, so we need to overload it!
    //4.55, 5.65
}
```

Example now for equal comparison operator:
```cpp
struct Vector2{
    float x, y;
    Vector2(float x, float y) : x(x), y(y){}
    Vector2 Add(const Vector2& other) const{
        return Vector2(x+other.x, y+other.y);
    }

    Vector2 operator+(const Vector2& other) const{
        return Add(other);
    }
    
    Vector2 Multiply(const Vector2& other) const{
        return Vector2(x*other.x, y*other.y);
    }

    Vector2 operator*(const Vector2& other) const{
        return Multiply(other);
    }

    bool operator==(const Vector2& other) const{
        return x==other.x && y == other.y;
    }
    bool operator!=(const Vector2& other) const{
        return !(*this == other);   //return !operator==(other)
    }
}

std::ostream& operator<<(std::ostream& stream, const Vector2& other){
    stream << other.x << "," << other.y;
    return stream;
}
int main(){
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 result = position.Add(speed);

    Vector2 powerup(1.1f, 1.1f);
    Vector2 result2 = position + speed * powerup;

    std::cout << result2 <<< std::endl;

    if(result == result2){
        ...
    }
}
```


## Local Static

Static in a local scope.

A local static variable allows us to have a variable that basically lives our entire program, however its scope is constrained. 

```cpp

void Function(){
    static int i = 0;
    i++;
    std::cout << i << std::endl;
}

void FunctionS(){
    static int i = 0;   //same behavior if it was declared outside the function, but this limits the scope access to here.
    i++;
    std::cout << i << std::endl;
}
int main(){
    Function(); //1
    Function(); //1
    Function(); //1
    Function(); //1
    Function(); //1

    FunctionS(); //1
    FunctionS(); //2
    FunctionS(); //3
    FunctionS(); //4
    FunctionS(); //5
}
```

Example for a singleton class

```cpp
class Singleton{
private:
    static Singleton* s_Instance;
public:
    static Singleton& Get(){ return *s_Instance;}
    void Hello(){}
};
Singleton* Singleton::s_Instance = nullptr;
int main(){
    Singleton::Get().Hello();
}
```
Another way is to do:

```cpp
class Singleton{
public:
    static Singleton& Get(){
        static Singleton instance;  //the static here keeps it alive and no need to have it elsewhere
        return instance;
    }
    void Hello(){}
};
int main(){
    Singleton::Get().Hello();
}
```