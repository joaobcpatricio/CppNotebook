# Notebook 1

## Embedded Recommended Books

* Embedded Systems: Real-Time Operaing Systems for ARM Cortex-M Microcontrollers
* Making Embedded Systems
* The Firmware Handbook
* Pratical Reverse Engineering
* ARM Assembly Language: Fundamentals and Techniques
* Clean Code

## Recall Main Topics

**Core Embedded Concepts**
| Concept |Summary |
| --------|--------|
| Stack vs Heap | Stack = fast, small, used for local variables; Heap = dynamic, riskier in safety-critical. |
| Memory-Mapped I/O | Hardware peripherals are accessed via specific memory addresses. |
| ISR (Interrupt Service Routine) | Code that runs in response to a hardware interrupt. Keep ISRs fast and deterministic.|
| Polling vs Interrupts | Polling wastes CPU time; interrupts are efficient for event-driven designs. |

**Real-Time Operating Syste,s (RTOS) Basics**
| RTOS Element | Purpose |
|--------------|---------|
| Task (Thread) | Independent execution context, managed by scheduler. |
| Context Switch | Saving/restoring CPU state when switching tasks. |
| Semaphore |Used for resource sharing and signaling between tasks. |
| Mutex | Prevents race conditions when tasks access shared data. |
| Priority Inversion | Lower-priority task holding resource blocks higher-priority one, must be handled in critical systems. |

**Safety Critical Software**
| Principle | Meaning |
| ----------|---------|
| Determinism | Behavior must be predictable - no race conditions or timing surprises. | 
| Avoid malloc() | Dynamic memory causes fragmentation and nondeterminism. Prefer static allocation. |
| Watchdog Timer | Hardware timer that resets system if software hangs - critical for fault recovery. |
| Redundancy | Systems must tolerate failures gracefully - often have backup units or checks. |
| MISRA C | Safety coding standard for embedded C - restricts risky constructs like `goto`, recursion. |

**Debugging & Testing**
| Tool/Concept | Usage |
|--------------|-------|
| BReakpoints/Watchpoints | Pause or monitor variable access during execution. |
| Static Analysis (e.g. Cppcheck) | Detects bugs before running code. |
| Unit Tests | Small testable components. Use mocks for hardware. |
| Integration Tests | Full systems or subsystems interacting. |
| Code Coverage | Ensure all logic paths are tested, especially in certifications (e.g. aerospace DO-178C). |

**Binary & Firmware Awareness**
| Topic |Why it matters |
|-------|---------------|
| Linker Script | Defines memory layout (flash, RAM). Must match hardware. |
| Bootloader | First code run on power-up; may handle firmware updates. |
| Disassembly (e.g. Ghidra) | Helps understand compile code at instruction level. |

**Essential Tools**
| Tool | Purpose |
|------|---------|
| STM32CubeIDE / Keil / IAR | IDEs for ARM-based embedded development. |
| FreeRTOS | Popular RTOS with source code. Great for practice. |
| Ghidra | Reverse engineering / disassembly. |
| OpenOCD / ST_Link | Debugging tools for ARM boards. |



## Notes

### Making Embedded Systems

**Debugging**
Debuging an embedded system requires a cross-debugger, that allows to communicate with the target processor through a special processor interface, often called  JTAG.

**Resource Constrains**
Some under consideration include:
* Memory (RAM)
* Code space (ROM or flash)
* Processor cycles or speed
* Power consumption (which translates into battery life)
* Processor peripherals

**Core Principles from SW design to increase system flexibility**
- Modularity - separate the functionality into subsystems and hide the data each subsystem uses.
- Encapsulation - create interfaces between the subsystems so they do not know much about each other. 