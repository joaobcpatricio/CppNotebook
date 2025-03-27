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