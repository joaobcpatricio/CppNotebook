# Key Embedded Questions

## Index

- [Basic Concepts and Theory](#basic-concepts-and-theory)
- [Programming and Software Design](#programming-and-software-design)
- [Low-Level Programming](#low-level-programming)
- [Performance and Optimization](#performance-and-optimization)


## Basic Concepts and Theory

1. What is an **embedded system**?

    A dedicated computer system designed to perform specific tasks with hardware and software tightly integrated.

2. Can you explain the difference between a **microprocessor** and a **microcontroller**?
    
    A microprocessor is a general-purpose processor for computing, while a microcontroller integrates a processor, memory, and peripherals on a single chip for specific control tasks.

3. Describe the various types of memory in an embedded system.

    * **ROM** (Read-Only Memory): Non-volatile storage for firmware.

    * **RAM** (Random Access Memory): Volatile memory for temporary data storage.

    * **EEPROM/Flash**: Non-volatile memory for storing configuration or data.

    * **Cache**: Fast, small memory for speeding up data access.


## Programming and Software Design

4. How do you write an interrupt service routine in C?

    Use the `ISR()` or `interrupt` keyword (depending on the platform) to define a function that handles the interrupt, ensuring it is marked with the appropriate interrupt vector.

5. Explain the concept of a real-time operating system (RTOS). How does it differ from a general-purpose operating system?

    An **RTOS** guarantees task execution within specific time constrains, while general purpose OS focuses on multitasking without strict timing requirements.

6. What are the different states of a thread in an RTOS?
    * **Ready**: Waiting to be executed.
    * **Running**: Currently being executed.
    * **Blocked**: Waiting for an event or resource.
    * **Suspended**: Paused, not ready to run.


## Low-level Programming

10. How do you access and use registers in an embedded C program?

    Use **pointers** or predefined macros to directly access hardware registers (e.g. `PORTA`, `DDRB`for specific microcontrollers).

11. What are volatile and static variables in embedded C, and why are they important?

    * **Volatile**: Tells the compiler not to optimize the variable, ensuring the program always reads it from memory.
    * **Static**: Keeps the variable's value between function calls, maintaining its state within the scope. It also limits the visibility of the variable to a scope (e.g. localized scope variable accessible only within the file but alive the hole program)


12. Explain bit manipulation in embedded systems.

    Involves using bitwise operators (*AND* `&`, *OR* `|`, *XOR* `^`, *SHIFT* `>>` `<<`) to manipulate bits of a variable or register, often for setting, clearing, or toggling flags.


## Performance and Optimization

13. How do you optimize code for an embedded system?

    Use efficient algorithms, minimize memory usage, reduce function calls, and optimize loops. Avoid unnecessary operations and use low-level hardware features.

14. What are the common techniques to reduce power consumption in embedded devices?

    Use low-power modes (sleep/standby), optimize clock frequencies, minimize active time, disable unused peripherals, clock scaling, peripheral gating, dynamic voltage scaling, interrupts instead of polling, etc.

15. How do you debug a memory leak in an embedded system?

    Use tools like memory profilers, manual tracking of memory allocation/deallocation, check for forgotten free() calls or buffer overflows.


