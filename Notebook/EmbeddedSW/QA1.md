# Random Embedded Software Questions

# Part 1

### Name 4 Pillars of Object Oriented Programming

1. **Encapsulation** - bundle of data and methods that operate on the data into a single unit => an object, restricting direct access.
2. **Abstraction** - hides complex details and shows only essential features;
3. **Inheritance** - allows a class to inherit properties and behaviors from another class.
4. **Polymorphism** - enables one interface to be used for different data types and methods.


### What is the shortest way to return the sum of even numbers in an int array?

```cpp
int sumEven(int arr[], int size){
    return std::accumulate(arr, arr.size, 0, [](int sum, int n){
        return sum + (n%2 == 0 ? n : 0);})
}
```
or
```cpp
int sumEven(int arr[], int size){
    int sum = 0;
    for(int i=0; i<size; i++){
        if(arr[i]%2 == 0){
            sum += arr[i];
        }
    }
    return sum;
}
```

### What is the **startup code**?
Code called before the execution of main. it creates a platform for an application to run (initializes system HW and sets up the environment).


### What is a **Semaphore**?
A semaphore is a synchronization primitive used to control access to a shared resource among multiple threads or processes. It helps prevent race conditions and ensures proper synchronization.

* **Binary Semaphore** (0,1) => works like a mutex (lock/unlock), allows onl< one thread at a time.
* **Counting Semaphore** (>1) => allows a fixed number of threads to access a resource.

Example where only 2 threads can run at the same time:
```cpp
#include <iostream>
#include <thread>
#include <semaphore>  // C++20
std::counting_semaphore<2> sem(2); // Max 2 threads can enter
void task(int id) {
    sem.acquire();  // Decrease semaphore count (wait)
    std::cout << "Thread " << id << " is running\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    sem.release();  // Increase semaphore count (signal)
}
int main() {
    std::thread t1(task, 1), t2(task, 2), t3(task, 3);
    t1.join(); t2.join(); t3.join();
}
```


### ISR
**Interrupt Service Routines** - is a special function that runs automatically when an interrupt occurs, handling events like hardware signals or timers. Used when an interruption occurs, these procedures are started at a memory location in the Software.


### When to use **volatile**?
For variables that can change unexpectedly, preventing the compilöer from optimizing them away.

*E.g.: a variable set=1, that we later do while(variable), the compiler would optimize and remove this, and if changed by an interrupt ISR, it would miss is effect.*

*E.g., sed for memory-mapped registers, shared variables in ISR.*


### Thread vs Process

A **Process** is a program under execution running in seperate memory spaces, whereas a **thread** is a segment of a process, that shares information with other threads while containing its registers, counters, etc. .


### Interrupt latency?
Is the time taken by ISR to respond to an interrupt, the less the better.


### Can a variable be **volatile** and **const**?
Yes, const is only a promise.


### What is a **reentrant** function?
When a function can be interrupted during execution and can be called back safely, resuming from the same point it was left.

*Using a mutex one can make a function reentrant.*


### Loop-construct to ' VS cont up?
Countdown to 0, as it is better to compare to 0 as it is more optimized.


### What is a watchdog timer?
Prevents system from dangerous situations by detecting faults in advance.


### What is faster: '++i' or 'i+1'?
'++i' is faster as it uses single machine instruction, while the other requires loading for the addition.


### Can printf() be used inside ISR?
No, as it is a non-reentrant and thread-safe function.


### Can we pass or return a value in ISR?
Both are not allowed.



### Why interrupts latency happen?
* Signal sync with the CPU can take up to 3 CPU cycles to reach the process.
* After execution, it takes some extra CPU cycles to refill the pipeline again with the instructions.


### Levels of testing
1. Unit testing;
2. Integration testing;
3. System testing;
4. User acceptance testing.


### Types of buses in Embedded system?
* **Memory Bus** - memory-connected processes.
* **Multiplexed Bus** - reads and writes in memory.
* **De-multiplexed Bus** - two wires into the same Bus, one has the address and other the data.
* **Input/output (I/O) Bus** - is a communication pathway that allows multiple devices to share the same input and output signals for data transfer between the processor and peripherals.