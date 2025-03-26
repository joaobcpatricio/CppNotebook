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