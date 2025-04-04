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


## Static

In C there are mostly 3 uses:

1. A variable declared static within the body of a function maintains its value between function invocation:
```cpp
void counter(){
    static int count = 0;
    count ++;
}
int main(){
    counter();  //1
    counter();  //2
    counter();  //3
}
```
2. A variable declared static within a module, but outside of a function, is accessible by all functions within that module (file). It is not accessible by a function within any other module (file). That is, it is a **localized global**.

*module1.c*
```cpp
static int globalVar = 10;
void printVar(){
    printf("%d\n", globalVar);
}
void modifyVar(){
    globalVar += 5;
}
```

*main.c*
```cpp
extern void printVar();
extern void modifyVar();
int main(){
    printVar(); //10
    modifyVar();
    printVar(); //15
}
```
*If another file tries "extern int globalVar;" it will fail.*

3. Functions declared static within a module may only be called by other function within that module.That is, the scope of the function is localized to the module within which it is declared.

*module.c*
```cpp
static void hiddenFunction(){
    print ...
}
void callHiddenFunction(){
    hiddenFunction();
}
```

*main.c*
```cpp
extern void callHiddenFunction();
int main(){
    callHiddenFunction();   //Works
    //hiddenFunction();     //Does not work
}
```


## How to deal with multiple return values

There are several ways to achieve it, being some:
- The probably best is through a struct.
- Another is passing the parameters by reference, and then change them under the function. Similar by pointers.
- Return,for example, an array or vector;
- Tuple - does not care about the variable types and can return multiple values.

| **Aspect**             | **Pros ✅** | **Cons ❌** |
|------------------------|------------|------------|
| **Multiple Return Values** | Can return multiple values of different types from a function. | Values have no explicit names, making it unclear what each represents. |
| **Structured Bindings (C++17+)** | Enables easy unpacking with `auto [a, b] = tuple;`, improving readability. | Requires `std::get<N>(tuple)`, which is less readable and error-prone. |
| **Generic & Type-Safe** | Works with any data type while maintaining type safety at compile time. | Adding/removing elements requires modifying all `std::get<N>` calls, making maintenance harder. |

---

```cpp
#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> getData() {
    return {42, 3.14, "Hello"};
}
int main() {
    auto [num, pi, text] = getData();  // Structured binding (C++17+)    
    std::cout << "Num: " << num << ", Pi: " << pi << ", Text: " << text << std::endl;
    //Num: 42, Pi: 3.14, Text: Hello
}
```


- Pair - more readable but limited to two values.


| **Aspect**             | **Pros ✅** | **Cons ❌** |
|------------------------|------------|------------|
| **Simple & Lightweight** | Easy to use for returning two values. | Limited to only two values, not scalable. |
| **Readable with `first` & `second`** | More readable than `std::tuple` due to named fields. | `first` and `second` may not be meaningful names, reducing clarity. |
| **Efficient & Type-Safe** | No extra overhead, works well with STL containers. | Less flexible than a custom `struct` for complex data. |

```cpp
#include <iostream>
#include <utility>  // For std::pair

std::pair<int, std::string> getUser() {
    return {42, "Alice"};
}

int main() {
    std::pair<int, std::string> user = getUser();
    std::cout << "ID: " << user.first << ", Name: " << user.second << std::endl;
    //ID: 42, Name: Alice
}
```


## Binary and Bitwise Operators

```cpp
int a = 5;  // [0000 0101][0000 0000][0000 0000][0000 0000]
//4 bytes   //lille endian

```

```cpp
<<  // left shift
>>  // right shift
&   // bitwise AND
|   // bitwise OR
^   // bitwise XOR
~   // bitwise NOT
```

Example:
```cpp
int a = 5;  //0101
int b = 5;
a << 1 = 10  //1010 (2^3+0+2^1+0)   //IT MULTIPLYES x2^n
b >> 1 = 2; //0010                  //IT HALVES /2^n
```

For a signed type, the behavior would be more tricky.

No need to force using bitshifting for multiplication or division, as it is not so readable and the compiler will already do this for us.



## Threads

Example:
```cpp
#include <iostream>
#include <thread>

void DoWork(){

}
int main(){
    std::thread worker(DoWork); //We are passing a pointer to the method, it runs it

    worker.join();  //will wait on the current thread to finish.
}
```

Example where we want to keep printing until we press the Enter key.
```cpp
#include <iostream>
#include <thread>

static bool s_Finished = false;
void DoWork(){
    using namespace std::literals::chrono_literals;
    std::cout << "Started thread id=" << std::this_thread::get_id() << std::endl;
    while(!s_Finished){
        std::cout << "Working..\n";
        std::this_thread::sleep_for(1s);    //to prevent 100% Thread usage for no need
    }
}
int main(){
    std::cout << "Started thread id=" << std::this_thread::get_id() << std::endl;
    std::thread worker(DoWork); 
    std::cint.get();    //while we dont press the other is ongoing as the while is true
    s_Finished = true;  //while of the other thread will stop
    worker.join();  
    std::cout << "Finished" << std::endl;
}
```


## Timing

Using chrono library, a standard, measure how much time it passes between code.

Useful, for example, for benchmarking.

Example:
```cpp
#include <iostream>
#include <chrono>
#include <thread>
int main(){
    using namespace std::literals::chrono_literals;

    auto start = std::chrono::high_resolution_clock::now(); //get current time
    std::this_thread::sleap_for(1s);    //1s comes from chrono literals
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end-start;
    std::cout << duration.count() << "s"<< std::endl;
}
```
A better way:
```cpp
#include <iostream>
#include <chrono>
#include <thread>
struct Timer{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    Timer(){
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer(){
        end = std::chrono::high_resolution_clock::now();
        duration = end-start;
        float ms = duration.count()*1000.0f;
        std::cout << "Timer took " << ms <<< "ms " << std::endl;
    }
}
void Function(){
    Timer timer;
    for(int i=0; i<100; i++){
        std::cout << "Hello" << std::endl;
    }
}
int main(){
    Function(); //122.114ms
}
```


## Sorting

We can write our own algorithm, or just use the standard library.
Tip: consult cppreference for more information on `std::sort`.

Example:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::vector<int> values = {3, 5, 1, 4, 2};
    std::sort(values.begin(), values.end());
    for(int value : values){
        std::cout << value << std::endl;
    }   //1 2 3 4 5
}
```

Another example:
Example:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main(){
    std::vector<int> values = {3, 5, 1, 4, 2};
    std::sort(values.begin(), values.end(), std::greater<int>());   //greater will go big to low
    for(int value : values){
        std::cout << value << std::endl;
    }   //5 4 3 2 1
}
```

Example using a lambda:
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main(){
    std::vector<int> values = {3, 5, 1, 4, 2};
    std::sort(values.begin(), values.end(), [](int a, int b) //if we return true, it uses a, else, b
    {
        return a<b;
    }]);   
    for(int value : values){
        std::cout << value << std::endl;
    }   //1 2 3 4 5
}
```

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main(){
    std::vector<int> values = {3, 5, 1, 4, 2};
    std::sort(values.begin(), values.end(), [](int a, int b) //if we return true, it uses a, else, b
    {
        return a>b;
    }]);   
    for(int value : values){
        std::cout << value << std::endl;
    }   //5 4 3 2 1
}
```

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main(){
    std::vector<int> values = {3, 5, 1, 4, 2};
    std::sort(values.begin(), values.end(), [](int a, int b) //if we return true, it uses a, else, b
    {
        if( a == 1 ){
            return false;
        }
        if( b == 1){
            return true;
        }
        return a><b;
    }]);   
    for(int value : values){
        std::cout << value << std::endl;
    }   //2 3 4 5 1
}
```


## Function Pointers

**Raw function pointers** are a way to assign a function to a variable.

```cpp
#include <iostream>

void HelloWorld(){
    std::cout "Hello World!" << std::endl;
}
int main(){
    void(*function)();
    function = HelloWorld; //remove the () and we get the memory address of that function

    function(); //This is one then calls it
}
```
Here using auto makes it less confusing.
```cpp
#include <iostream>

void HelloWorld(){
    std::cout "Hello World!" << std::endl;
}
int main(){
    auto function = HelloWorld; //remove the () and we get the memory address of that function

    function(); //This is one then calls it
}
```
Another good practice for this case is use a *typedef*:
```cpp
#include <iostream>

void HelloWorld(){
    std::cout "Hello World!" << std::endl;
}
int main(){
    typedef void(*HelloWorldFunction)();
    HelloWorldFunction cherno = HelloWorld; 
    cherno(); 
}
```
Now with parameters:
```cpp
#include <iostream>

void HelloWorld(int a){
    std::cout "Hello World! Value: " << a << std::endl;
}
int main(){
    typedef void(*HelloWorldFunction)(int);
    HelloWorldFunction cherno = HelloWorld; 
    cherno(8); 
}
```

Useful example:
```cpp
#include <iostream>
#include <vector>

void PrintValue(itn value){
    std::cout << value << std::endl;
}
void ForEach(const std::vector<int>& values, void(*func)(int)){
    for ( int value : values){
        func(value);
    }
}
int main(){
    std::vector<int> values = {1, 5, 4, 2, 3};
    ForEach(values, PrintValue);    //1 5 4 2 3
}
```
Way to do this better using a lambda:
```cpp
#include <iostream>
#include <vector>


void ForEach(const std::vector<int>& values, void(*func)(int)){
    for ( int value : values){
        func(value);
    }
}
int main(){
    std::vector<int> values = {1, 5, 4, 2, 3};
    ForEach(values, [](int value){
        std::cout << value << std::endl;
    });    //1 5 4 2 3
}
```



## Lambdas

Is a way to create a function without actually having to physically create it, for example, when we want to treat a function more like a variable.

In short, whenever we have a function pointer we can use a lambda (see *function pointer* section).

```cpp
#include <iostream>
#include <vector>


void ForEach(const std::vector<int>& values, void(*func)(int)){
    for ( int value : values){
        func(value);    //this calls the lambda we passed
    }
}
int main(){
    std::vector<int> values = {1, 5, 4, 2, 3};
    ForEach(values, [](int value){
        std::cout << value << std::endl;
    });    //1 5 4 2 3
}
```
Evolving the example:
```cpp
#include <iostream>
#include <vector>


void ForEach(const std::vector<int>& values, void(*func)(int)){
    for ( int value : values){
        func(value);    //this calls the lambda we passed
    }
}
int main(){
    std::vector<int> values = {1, 5, 4, 2, 3};
    auto lambda = [](int value){std::cout << value << std::endl;}; 
    ForEach(values, lambda);    //1 5 4 2 3
}
```
`[]` - also consult [cppreference](https://en.cppreference.com/w/cpp/language/lambda), capturing allows to pass outside values.
```cpp
#include <iostream>
#include <vector>
#include <functional>

void ForEach(const std::vector<int>& values, std::function<void(int)>& func){ //For this instead of a raw function pointer we need to use the std
    for ( int value : values){
        func(value);    //this calls the lambda we passed
    }
}
int main(){
    std::vector<int> values = {1, 5, 4, 2, 3};
    int a = 5;
    auto lambda = [&a](int value){std::cout << value << a << std::endl;}; //if we jus use & or = i takes all. For this instead of a raw function pointer we need to use the std
    ForEach(values, lambda);    //1 5 4 2 3
}
```

Another example:
```cpp
#include <iostream>
#include <vector>
#include <functional>

int main(){
    std::vector<int> values = {1, 5, 4, 2, 3};
    auto it = std::find_if(values.begin(), values.end(), [](int value){return value>3;})
    std::cout << *it << std::endl;  //5
}
```