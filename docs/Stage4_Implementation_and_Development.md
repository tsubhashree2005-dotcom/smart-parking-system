Stage 4 — Implementation and Development

1. Introduction

Stage 4 focuses on implementing the Linux-Based Smart Parking Management System according to the architecture and requirements defined in the previous stages.

The implementation combines C++ object-oriented programming, STL data structures, file handling, Linux system calls, FIFO inter-process communication, virtual sensors, Linux logging, automated testing, and a Linux kernel character device driver.

The implementation is modular so that each major responsibility is handled by a separate component.



2. Implementation Environment

The project was developed and tested in a Linux environment.







Component



Technology





Operating System



Ubuntu Linux





Architecture



ARM64





Programming Language



C++17





Compiler



g++





Build System



GNU Make





Kernel Module



C / Linux Kernel API





Debugging



GDB





Version Control



Git





Repository



GitHub

The project was implemented exclusively in the Ubuntu Linux environment as required by the project constraints.





3. Source-Code Organization

The source code was organized into separate user-space, kernel-space, testing, and documentation components.

smart-parking-system/
├── src/
│   ├── main.cpp
│   ├── parking_system.cpp
│   ├── parking_system.h
│   ├── parking_sensor.cpp
│   ├── parking_sensor.h
│   ├── parking_ipc.cpp
│   ├── parking_ipc.h
│   ├── parking_monitor.cpp
│   ├── parking_driver_test.cpp
│   ├── linux_logger.cpp
│   └── linux_logger.h
│
├── kernel_driver/
│   ├── Makefile
│   ├── parking_driver.c
│   └── parking_ioctl.h
│
├── tests/
│   └── test_parking_system.cpp
│
├── docs/
├── Makefile
├── build.sh
├── run.sh
├── parking_data.txt
└── README.md

This organization keeps the main application, Linux driver, automated tests, and documentation clearly separated.





4. Main C++ Application

The main application is implemented using C++17 and follows an object-oriented modular design.

The central class is:

ParkingSystem

It manages:





Parking slots



Vehicles



Waiting queue



Parking history



Data persistence



Virtual sensors



FIFO IPC



Status display



Input validation



Automatic queue allocation

The application provides a menu-driven interface for operating the parking system.





5. Vehicle and Parking-Slot Management

The system represents vehicles using a C++ structure containing:





Vehicle number



Owner name



Vehicle type

Parking slots are represented using a separate structure.

The final implementation supports compatible vehicle/slot allocation:





Slots 1–3: CAR



Slots 4–5: BIKE

A vehicle is assigned only to a compatible free slot.

If a compatible slot is unavailable, the vehicle is placed in the waiting queue.





6. Data Structures and C++ Concepts

The implementation uses several STL and C++ concepts from the training material.

STL Containers

vector
queue

vector is used for parking slots.

queue is used for vehicles waiting for a compatible parking slot.

Linked List

Parking history is implemented using a linked-list structure:

HistoryNode
    |
    +-- vehicleNumber
    +-- slotNumber
    +-- action
    +-- next

This demonstrates dynamic node-based data structures and pointer traversal.

Smart Pointers

shared_ptr<Vehicle> is used for vehicle ownership inside parking slots.

This reduces manual memory-management requirements for stored vehicle objects.

STL Algorithms and Iteration

The implementation uses C++ range-based iteration and STL container operations for managing parking data and queues.





7. Parking Operations

The following core operations were implemented:





Park vehicle



Remove vehicle



Display parking status



Search vehicle



Display waiting queue



Display parking history



Save data



Send status through FIFO IPC



Exit

The application validates vehicle information and handles invalid input using C++ exception handling.





8. Waiting Queue and Automatic Allocation

A waiting queue is used when no compatible parking slot is available.

When a vehicle is removed, the system checks the waiting queue for a vehicle compatible with the newly available slot.

The implementation does not simply select the first queue element. It searches the queue while preserving the order of vehicles that are not compatible with the released slot.

This provides correct CAR/BIKE slot allocation while retaining waiting-queue behavior.





9. File Handling and Data Persistence

The system stores parking information in:

parking_data.txt

C++ file streams are used for persistence:

ifstream
ofstream

The system:





Loads saved parking data during startup.



Saves occupied-slot information.



Validates loaded records.



Ignores malformed records safely.



Automatically saves important parking changes.

Exception handling is used for file-opening and runtime errors.





10. Virtual Parking Sensors

A virtual parking sensor module was implemented using:

parking_sensor.cpp
parking_sensor.h

Each sensor maintains:





Sensor ID



Associated slot number



Occupancy state

Sensor operations include:





Detect



Clear



Toggle



Set state



Get status



Display status

The sensors simulate hardware-level parking detection without requiring physical hardware.





11. Linux Logging

The Linux logger module provides system-level logging.

Files:

linux_logger.cpp
linux_logger.h

The logger uses Linux file operations such as:

open()
write()
close()

Logging information is stored in:

parking.log

This demonstrates Linux system-call based file handling rather than relying only on high-level C++ streams.





12. FIFO Inter-Process Communication

Linux FIFO IPC was implemented using:

/tmp/smart_parking_fifo

The main application can send the current parking status through the FIFO.

A separate program:

parking_monitor

receives and displays the status.

The communication flow is:

Smart Parking Application
          |
          v
ParkingIPC
          |
          v
/tmp/smart_parking_fifo
          |
          v
Parking Monitor

The final IPC test successfully transferred parking status information between the two user-space processes.





13. Linux Character Device Driver

A Linux character-device driver was implemented under:

kernel_driver/

The driver creates the device:

/dev/smart_parking

The driver demonstrates:





Kernel module development



Character-device registration



Major/minor device numbers



cdev



Device creation



Kernel/user-space data transfer



copy_to_user()



copy_from_user()



Mutex-based protection



File operations



open()



read()



write()



ioctl()



release()

The main parking application does not directly access the character device. A separate driver-test program demonstrates communication with the device interface.





14. IOCTL Support

As a final technical enhancement, the character-device driver was extended with custom IOCTL operations.

The definitions are maintained in:

kernel_driver/parking_ioctl.h

The driver supports:

SMART_PARKING_IOCTL_GET_BUFFER_SIZE
SMART_PARKING_IOCTL_CLEAR_BUFFER



GET_BUFFER_SIZE

Returns the current amount of data stored in the driver buffer to user space.

CLEAR_BUFFER

Clears the driver buffer and resets its stored size.

The driver exposes the IOCTL interface through the Linux file-operations structure.

This demonstrates a richer user-space/kernel-space control interface beyond basic read() and write() operations.





15. Kernel Driver Test Program

The driver test program is:

src/parking_driver_test.cpp

It validates:

write()
ioctl(GET_BUFFER_SIZE)
read()
ioctl(CLEAR_BUFFER)

The final test produced:

SMART PARKING DRIVER IOCTL TEST

[1] write() successful
[2] ioctl GET_BUFFER_SIZE successful
    Buffer size: 36 bytes
[3] read() successful
    Data: Parking driver test: Slot 1 OCCUPIED
[4] ioctl CLEAR_BUFFER successful
[5] Buffer size after clear: 0 bytes

IOCTL TEST SUCCESSFUL

The driver was also loaded and unloaded successfully using standard Linux module commands.





16. Automated Test Suite

A dedicated automated test suite was added under:

tests/test_parking_system.cpp

The suite validates:





Vehicle parking



Vehicle removal



Waiting queue handling



Automatic waiting-queue allocation



Data persistence



Virtual parking sensor operation



Invalid vehicle validation

Final automated test result:

Passed : 7
Failed : 0
ALL TESTS PASSED

This provides repeatable verification of the main parking-system functionality.





17. Build System

The project uses GNU Make for compilation.

The root Makefile builds:

smart_parking
parking_monitor
parking_driver_test

The kernel driver has its own Makefile for building the Linux kernel module.

A clean project build can be performed using:

./build.sh

The build script performs:

make clean
make

The application can be started using:

./run.sh





18. Development and Integration

The implementation was developed incrementally.

The major development sequence was:

Core C++ Parking System
        |
        v
STL Data Structures
        |
        v
File Persistence
        |
        v
Virtual Sensors
        |
        v
Linux Logger
        |
        v
FIFO IPC
        |
        v
Parking Monitor
        |
        v
Linux Character Driver
        |
        v
Driver Test Program
        |
        v
Automated Test Suite
        |
        v
IOCTL Enhancement

Each component was compiled and tested before being integrated into the final project.





19. Issues Encountered and Resolutions

During implementation, several development issues were identified and resolved.

Source Organization

The project source files were reorganized into a dedicated src/ directory.

The Makefile, build script, and VS Code tasks were updated accordingly.

Kernel Driver Integration

The character driver required correct Linux kernel APIs and user/kernel data-transfer functions.

The driver was rebuilt and tested successfully after resolving implementation issues.

IOCTL Integration

The driver was extended with a dedicated IOCTL header and corresponding driver-test operations.

The final IOCTL test confirmed successful buffer-size retrieval and buffer clearing.

Waiting Queue Compatibility

The waiting queue required compatibility handling because CAR and BIKE slots are different.

The allocation logic was updated so that a freed slot is assigned only to a compatible waiting vehicle.





20. Implementation Status

The Stage 4 implementation is complete.

The implemented system contains:





C++ OOP architecture



STL containers



Linked-list parking history



Smart pointers



File persistence



Exception handling



Vehicle validation



CAR/BIKE slot compatibility



Waiting queue



Automatic queue allocation



Virtual parking sensors



Linux system-call based logging



FIFO IPC



Parking monitor



Linux character-device driver



User/kernel communication



Custom IOCTL interface



Automated test suite



GNU Make build system



Git/GitHub version control



Complete project documentation





21. Stage 4 Outcome

The final Stage 4 implementation successfully transformed the design from the previous stages into a working Linux-based prototype and integrated system.

The project now demonstrates both application-level C++ development and Linux system-level programming, including interaction with a character device driver.

The automated tests and final IOCTL verification provide additional evidence that the implemented components are functioning as intended.

Stage 4 is therefore completed and the project is ready for final testing, validation, deployment documentation, and presentation.