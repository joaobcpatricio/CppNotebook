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


### Scheduling Algorithms

| Algorithm | Pros | Cons |
|--|--|--|
| First-come, first-served (FCFS) |Simple and easy to implement. |Can cause long waiting times (convoy effect).|
| Shortest Job Nect (SJN) | Minimizes average waiting time. | Requires knowledge fo processes execution time, can cause starvation.|
|Round Robin (RR) |Ensures fairness, good for time-sharing systems. |High context-switching overhead if time quantum is too small.|


### Criteria for MCU selection?
* Power consuption
* Processing power
* Peripherals
* Memory
* Connectivity
* Cost
* Development ecosystem
* etc.


### MCU power saving methods
Low power mode, clock scaling, peripheral gating, dynamic voltage scaling, interrupts instead of polling, etc.


### MCU block diagram

Example:
```mermaid
    graph TD;
        DS[Digit Sensor]<-->I2C[I2C Controller]
        subgraph MCU
            I2C<-->CPU
            CPU<-->SPI            
            CPU<-->IO[General purpose I/O interface]
            IO<-->ADC            
        end
        SPI<-->RT[Radio Transceiver]
        ADC<-->AS[Analog Sensor]
```
















### MPU vs MMU?
* **MPU** (Memory Protection Unit) → Enforces memory protection, but does not support virtual memory. Used in embedded systems.
* **MMU** (Memory Management Unit) → Handles virtual memory translation and memory protection. Used in OS-based systems.




### What happens after **power up**, before entering main?
The **start up code** runs, with reset vector execution, stack and heap setup, variable initializations, construct calls, etc..




### Program to transfer bytes from UART to ethernet (UDP) and blink a led, using some APIs?
* Use an interrupt-driven UART receive function;
* Forward received data to a UDP send function;
* Use a timer interrupt to blink the led periodically.

*Note*: **FTDI** => USB to serial (e.g. UART)



### What API would you create for working with a DMA controller?

* **DMA_Init()** - init specific settings;
* **DMA_SetDirection()** & **DMA_SetTransferSize()** - also configure source/destination addresses
* **DMA_Start()** & **DMA_STOP()** 
* **DMA_EnableInterrupt()** & **DMA_DisableInterrupt()**
* **DMA_IsTransferComplete()** & **DMA_ClearFlags()** - clear error flags
* **DMA_AlocateBuffer()** & **DMA_FreeBuffer()**

This API abstracts DMA configuration, control, and monitoring for easier use in embedded systems.



### I2C vs SPI vs UART

| Feature |I2C |SPI |UART |
|-|-|-|-|
| Pins required | 2 (SDA, SCL) | 4 (MOSI, MISO, SCL, CS) | 2 (TX, RX) |
| Speed | Slow (100kHz to 1 MHz) | Fast, more than 10-50MHz |Moderate, 1-2Mbps |
| Full/half-duplex |Half duplex |Full duplex | full duplex |
| Addressing | Uses device addresses | Select device via chip select | Point-to-point, no addressing |
| Communication type | Master-slave | Master-slave | Point-to-point |
| Bus complexity | More complex | Less complex | Moderate |
| Power consumption | Low |High | Moderate |

* **UART**: both can send data at any time, simple to use. Protocols/data arguments would be on you, since all is single bytes ==> E.g. USB - FTDI, Bluetooth, etc.
* **SPI**: One device controls when transfers go. E.g. ADC, oled display.
* **I2C**: Network, all devices can address other devices at any time. Works in packets. Every device needs an address. E.g. sensors (temperature).



### Structure packing: How does this differ in 8-bit architecture vs 32 bit? Can you save space by packing structures differently? Think about word alignment (and what a 'word' means in different architectures).

Structure packing differs between 8-bit and 32-bit architectures primarily in default alignment rules and the potential for space savings. 32-bit architectures typically have stricter alignment requirements (e.g., 4-byte alignment for integers), leading to more padding and larger structure sizes if packing isn't used. 8-bit architectures often have less stringent alignment (e.g., 1-byte alignment), so packing provides smaller savings. Packing, achieved via compiler directives or reordering, can always reduce structure size but might impact performance due to unaligned memory access, especially on 32-bit systems. Word size (1 byte vs 4 bytes) directly influences these alignment behaviors.

```cpp
//Example struct
struct Example {
    char a; //8bit = 1byte + maybe 1 byte padding; 32bit = 1 byte + 3 byte padding
    int b;  //32bit = 4 byte
    char c; //8bit = 1byte + maybe 1 byte padding; 32bit = 1 byte + 3 byte padding
};

//8-bit: No packing might be 4/6 bytes, packing likely also 4/6 bytes.
//32-bit: No packing might be 12 bytes (due to int alignment), packing is 6 bytes.
```


### Reverse a byte (or arbitrary length integer) in a function.


To reverse we want that the first bit is the last, so with bit shifting we go over each bit and save it starting from the end. 

```cpp
#include <iostream>
#include <cstdint>

uint64_t reverseBits(uint64_t n, int numBits) {
  uint64_t result = 0;
  for (int i = 0; i < numBits; ++i) {
    if ((n >> i) & 1) {
      result |= (uint64_t)1 << (numBits - 1 - i);
    }
  }
  return result;
}
```

E.g. `(num>>i)&1 = (5>>i)&1=(0101>>0)&1 = 0101&0001=1;` so we need to save 1 at the beginning, that is the full size-1: `result |= 1<<(size-1-i)`; 

Next iteration `(num>>i)&1 = (5>>1)&1=(0101>>1)&1 = 0010&0001=0;` 0 we dont need to add as we already initialized result as 0s.

Next iteration `(num>>i)&1 = (5>>2)&1=(0101>>2)&1 = 0001&0001=1;`, so we add the 1 that was on the 3rd position to the left, on the 3rd to the right. Same logic as before, we use *i* to move to that position as it should be mirrored: `result |= 1<<(size-1-2) => 1000|=1<<(4-3) => 1000|=1<<(1) => 1000|=10 =1010`; 


### Find if a string is a palindrome. 

A palindrome is a word, phrase, number, or sequence that reads the same forward and backward. E.g. *level*.

E.g. using std library and `s.rbegin()` that reverses that characters.
```cpp
#include <iostream>
#include <algorithm>
bool isPalindrome(const std::string& s) {
    return std::equal(s.begin(), s.begin() + s.size() / 2, s.rbegin());
}
int main() {
    std::string str = "racecar";
    std::cout << (isPalindrome(str) ? "Palindrome" : "Not a Palindrome") << std::endl;
}
```

Not using `std::equal`:
```cpp
#include <iostream>
bool isPalindrome(const std::string& s) {
    int left = 0, right = s.length() - 1;

    while (left < right) {
        if (s[left] != s[right]) {
            return false;  // Mismatch found, not a palindrome
        }
        left++;
        right--;
    }
    return true;  // No mismatches, it's a palindrome
}
int main() {
    std::string str = "racecar";
    std::cout << (isPalindrome(str) ? "Palindrome" : "Not a Palindrome") << std::endl;
}
```


### Find if a point is within a given circle of radius R and offset x and y.

If we draw a circle under a x,y plane, we want to know what is *d* for distance between the center of this circle and the point, that is the hypotenuse. We know that `h^2?(x-cx)^2+(y-cy)^2` so `d=sqrt((x-cx)^2+(y-cy)^2)` (if you are facing issues on getting to this, just draw a circle that is not centered on your plane, place a point somewhere and get to the equation of the distance).

Using this:
```cpp
#include <iostream>
#include <cmath>
bool isPointInCircle(int px, int py, int cx, int cy, int R) {
    // Calculate the squared distance between the point and the center of the circle
    int distSquared = (px - cx) * (px - cx) + (py - cy) * (py - cy);
    // Compare the squared distance with the squared radius
    return distSquared <= R * R;
}

int main() {
    int px = 3, py = 4;  // Point to check
    int cx = 0, cy = 0;  // Center of the circle
    int R = 5;           // Radius of the circle

    if (isPointInCircle(px, py, cx, cy, R)) {
        std::cout << "The point is inside the circle." << std::endl;
    } else {
        std::cout << "The point is outside the circle." << std::endl;
    }
    return 0;
}
```

By keeping the comparison using multiplications instead of calculating `sqrt` that are computationally expensive due to floating point math. Another option could be first make sure that the point was even inside the bounding box of the circle: `cx-R <=x<=cx+R` and `cy-R<=y<=cy+R`.



### Mutex vs Semaphore

**Mutex** is for exclusive control (one thread at a time), while **Semaphore** can allow multiple threads to access shared resources concurrently up to a set limit.

| Feature              | Mutex                                      | Semaphore                              |
|----------------------|--------------------------------------------|----------------------------------------|
| **Purpose**           | Ensures mutual exclusion (one thread at a time) | Controls access to multiple resources |
| **Ownership**         | Only the thread that locks can unlock it   | No ownership, any thread can signal or wait |
| **Type**              | Binary (locked/unlocked)                   | Counting (allows multiple threads if value > 1) |
| **Usage**             | Used for exclusive access to a critical section | Used for signaling and limiting access to resources |
| **Access Control**    | One thread at a time                       | Multiple threads allowed (up to a set limit) |
| **Common Use Case**   | Protecting a shared resource from concurrent access | Managing a pool of resources or coordinating threads |


### What does it mean for a function to be reentrant? When would you avoid a non-reentrant function?

A reentrant function can be safely interrupted and called again before its previous executions finish, without causing issues.

Avoid non-reentrant functions when using multithreading or handling interrupts, as they may lead to race conditions or data corruption.


### How do you calculate the baud rate of a UART connection?

`Baud Rate = Clock Frequency / Divisor`

- Clock Frequency is the frequency of the clock driving the UART (e.g., 16 MHz).
- Divisor is the value that is set in the UART configuration to achieve the desired baud rate.

Example:
Baud Rate = 16000000 / 104 ≈ 153846 baud


### What are the RTX and CTX pins used for

The RTX (Receiver Transmit) and CTX (Clear Transmit) pins are typically used in serial communication.

* RTX: Often used to indicate the receive data line or signal used by a device to receive information.

* CTX: Typically refers to the clear transmit signal, which is used to manage or clear the state of transmission in certain communication systems.

These pins might vary depending on the specific context or devic



### For SPI, what are some common ways a master and a slave could fail to communicate (think about how SPI settings could be different)

Some common ways a master and a slave could fail to communicate in SPI due to different settings include:

1. Clock Polarity (CPOL): If the master and slave have different settings for the clock polarity, they may misinterpret the data.
2. Clock Phase (CPHA): If the phase is mismatched, data may be sampled at the wrong time.
3. Clock Speed: If the master sends data at a speed too high for the slave to handle, communication will fail.
4. Data Order (MSB/LSB): If the master and slave are configured to send/receive data in different bit orders (MSB first vs. LSB first), data will be interpreted incorrectly.
5. Chip Select (CS): If the slave is not properly selected or the CS is held incorrectly, the slave will not respond.

These mismatched settings can cause the devices to fail in syncing or interpreting transmitted data correctly.


### For I2C, what happens if you fail to have sufficient pull-ups?

If you fail to have sufficient pull-up resistors on the SDA (data) and SCL (clock) lines in I2C, the signals won't be able to properly return to a high voltage level when not actively driven low. This can cause communication errors, signal corruption, or the bus to become unresponsive, resulting in failed data transmission or complete communication breakdown.


### When would you want to use SPI over I2C?

You would use SPI over I2C when you need:

1. Higher data transfer speeds (SPI is typically faster).
2. Full-duplex communication (SPI allows simultaneous send and receive).
3. Multiple devices with individual chip select lines, and you need more control over individual devices.
4. Lower complexity in protocol (SPI has simpler communication rules).

I2C is better for lower-speed, simpler setups with multiple devices sharing the same bus, but SPI is preferred for speed and more precise control.


### What is a DMA, and when would you want to use one?

A DMA (Direct Memory Access) is a feature that allows peripherals or memory blocks to transfer data directly to/from memory without involving the CPU, freeing up processing power.

You would want to use DMA when you need high-speed data transfers (e.g., large amounts of data between memory and peripherals) and want to reduce CPU load, allowing the CPU to focus on other tasks while the DMA handles the data transfer.


### Knowledge of how a SAR ADC works.

A SAR (Successive Approximation Register) ADC works by approximating an input voltage in discrete steps to convert it into a digital value. Here's how it works briefly:

1. **Initial Guess**: The ADC starts with an initial guess (e.g., half of the reference voltage).
2. **Comparison**: It compares the input voltage to the guessed value using a comparator.
3. **Adjust Guess**: Based on the comparison, the SAR adjusts the guess by either increasing or decreasing the value.
4. **Repeat**: This process is repeated, refining the guess bit by bit, until the input voltage is approximated to a high degree of accuracy (usually 8-16 bits).
5. **Output**: Once the approximation is complete, the final binary value is output.

The SAR ADC uses a binary search method, which makes it fast and efficient for medium-resolution conversions (typically 8-16 bits).

The binary search method efficiently finds a target in a sorted list by repeatedly dividing the search interval in half.


### Electronics

* A **capacitor** stores and releases electrical energy, influencing voltage changes in a circuit.
* An **inductor** stores energy in a magnetic field and resists changes in current flow.

* Using a **transistor** as an amplifier in its linear range allows it to amplify signals without distortion, where the output is directly proportional to the input (linear).

* Kirchhoff's laws state that the sum of currents entering a junction equals the sum of currents leaving (current law), and the sum of voltages around a closed loop equals zero (voltage law).

* Ampere's Law states that the magnetic field around a closed loop is proportional to the electric current passing through the loop.

* Ohm law: `V=R*I`

* In an inverting op-amp circuit, the input signal is applied to the inverting terminal, with feedback from the output to the inverting input through a resistor, resulting in a 180° phase-shifted output.
* In a non-inverting op-amp circuit, the input signal is applied to the non-inverting terminal, with feedback from the output to the inverting input, resulting in an amplified output without a phase shift.