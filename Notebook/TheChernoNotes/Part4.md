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

When assigning a shared pointer to another, this gets increased. But when assigning a shared pointer to a weak pointer, it does not! This is great if you do not want to take ownership of the entity. It prevents cycling references.

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