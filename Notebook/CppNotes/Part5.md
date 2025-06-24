# **C++** 
# Part 5


#### [Table of Contents](README.md#table-of-contents)


## The this keyword

It is only accessible through a member function, meaning, a function that belongs to a class (a method). Using *.this* one can access to the object instance the method belongs to, pointing to it as a pointer.

Example:

```cpp
void PrintEntity(const Entity& e);
class Entity{
public:
    int x, y;
    Entity(int x, int y){
        this->x = x;
        this->y = y;

        PrintEntity(*this);
    }

    int GetX() const{
        return this->x;
    }
}
```