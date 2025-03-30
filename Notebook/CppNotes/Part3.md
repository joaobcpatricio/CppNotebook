# **C++** 
# Part 3


#### [Table of Contents](README.md#table-of-contents)


## Const

Provides visibility and make the code cleaner, since it is just a promise that something is constant, but can actually be broken.

`const int* a = new int;` I cannot assign a value by doing ` *a = 2`

`int* const a = new int;` I cannot assign a value by doing `a = (int*)&MAX_AGE;`

To not be abler to change content of trhe pointer and the pointer: `const int* const a = new int;`

Example for classes, a method that does not change the class variables:

```cpp
class Entity{
private: 
    int m_X, m_Y;
public:
    int GetX() const{
        return m_X;
    }
     
};
```


## Mutable

Mutable has 2 fairly different uses. One has to do with const and another with lambdas.

First example, where we have a const method that returns a value to be const (not changed as is passed by reference), meaning, we do not change the class variables. But, let's imagine, maybe for debug purposes, we want to have an internal counter for hou much the method was called. This would not be possible if it was not a mutable as this variable would not be const:
```cpp
class Entity{
private:
    std::string m_Name;
    mutable int m_DebugCount = 0;
public:
    const std::string& GetName() const{
        m_DebugCount++;
        return m_Name;
    }
}
int main(){
    const Entity e;
    e.GetName();
}
```

Shortly, a lambda is like a little throwaway function that one can write and assign to a variable quickly.

```cpp
int main(){
    int x=8;
    auto f = [=](){ //passing a copy
        //x++;    //this would not work, solution:
        int y = x;
        y++;
       
        std::cout << x << std::endl;
    }
    f();
}
```
Solution:
```cpp
int main(){
    int x=8;
    auto f = [=]() mutable {  
        x++;       
        std::cout << x << std::endl;
    }
    f();
}
```
This makes the code look cleaner, and of course, it will not actually change x outside as it was passed by value. In reality, is very unusual to need to do this.


## Member Initializer Lists
*Constructor Initializer List*

It is a way to initialize class member functions in the constructor.

There are two ways:
```cpp
class Entit<{
private:
    std::string m_Name;
    int m_Score;
public:
    Entity(){
        m_Name = "Unknown";
        m_Score = 0;
    }

    Entity(const std::string& name){
        m_Name = name;
    }

    const std::string& GetName() const { return m_Name; }
};
int main(){
    Entity e0;
    std::cout << e0.GetName() << std::endl; //Unknown

    Entity e1("Cherno");
    std::cout << e1.GetName() << std::endl; //Cherno
}
```
Another (most performant) way:
```cpp
class Entit<{
private:
    std::string m_Name;
    int m_Score;
public:
    Entity() 
        : m_Name("Unknown"), m_Score(0) //follow the same order as declared above!
    {
    }

    Entity(const std::string& name)
        : m_Name(name), m_Score(0)
    {
    }

    const std::string& GetName() const { return m_Name; }
};
int main(){
    Entity e0;
    std::cout << e0.GetName() << std::endl; //Unknown

    Entity e1("Cherno");
    std::cout << e1.GetName() << std::endl; //Cherno
}
```

This make code cleaner and split from actual logic in the method.

It has better performance, as in the first case it will construct, in case of a string, for example, the variable twice, at declaration and then when we set. With the latter way it only directly sets the variable value when declaring it.

*Note: in case of integers these are only initialized when a value is actually set.*


## Ternary Operators

Is syntax sugar for *if statements*. By many clean code styles, it is considered not a good practice to be used.

Due to compiling optimization, it might also be more performant. 

Example:
```cpp
static int s_Level = 1;
static int s_Speed = 2;
int main(){
    if(s_Level)>5{
        s_Speed = 10;
    }else{
        s_Speed = 5;
    }
}
```

```cpp
static int s_Level = 1;
static int s_Speed = 2;
int main(){
    s_Speed = s_Level > 5 ? 10 : 5;  //first member is if true, the second if false
}
```

```cpp
static int s_Level = 1;
static int s_Speed = 2;
int main(){
    s_Speed = s_Level > 5 ? s_Level > 10 ? 15 : 10 : 5;  //this is where it starts getting confusing...

    s_Speed = s_Level > 5 && s_Level < 100 ? s_Level > 10 ? 15 : 10 : 5;    //the && goes first
}
```


## Create Instantiate Objects

When we create an object in C++ it needs to occupy some memory. 
We can control if this object is created on the stack or on the heap.

Stack objects have an automatic lifespan, controlled by the scope they are declared, being freed once out.

At the heap, the object will stay there until we say we no longer need it.

Example:
```cpp
using String = std::string; //for readability of the example
class Entity{
private:
    String m_Name;
public:
    Entity() : m_Name("Unknown"){}
    Entity(const String& name) : m_Name(name) {}
    const String& GetName() const {return m_Name; }
}

int main(){
    Entity e0; //created in the stack
    //same as Entity e0("Cherno); or Entity e0 = Entity("Cherno");
    std::cout << e0.GetName() << std::endl; //Unknown
    //We should by default create objects like this, is the fastest and safest/managed way.
    Entity e1 = new Entity
}
```

If we want that to actually live outside of that function, or it is too large (stack is usually around 1 or 2 MB), there we want to use the heap.
Example:
```cpp
using String = std::string; //for readability of the example
class Entity{
private:
    String m_Name;
public:
    Entity() : m_Name("Unknown"){}
    Entity(const String& name) : m_Name(name) {}
    const String& GetName() const {return m_Name; }
}

int main(){
    Entity* e;
    {//We create a scope
        Entity* entity = new Entity("Cherno");
        e = entity;
        std::cout << entity->GetName() << std::endl;        
    }
    delete e;
}
```


## The New keyword

The mane purpose of *new* operator is to allocate memory, specifically on the heap. 

When used it also calls the constructor.

Do not forget to always call the delete once done!

If, for example, we call new with *[]*, then we call delete also with *[]*.



```cpp
int main(){
    int a = 2;
    int* b = new int[50];   //200bytes of memory

    Entity* e = new Entity();   //not mandatory to have the ()
 // Entity* e = (Entity*)malloc(sizeof(Entity));    //same as is before in C

 // Entity* e = new(b) Entity();    //this allocates the Entity at the b location in memory, more on this topic later under placement.

    delete e;
    delete[] b; 
}
```


## Implicit Conversion and the Explicit keyword

TBD
```cpp

```