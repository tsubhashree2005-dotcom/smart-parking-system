# Linux-Based Smart Parking Management System

## 1. Project Overview

The **Linux-Based Smart Parking Management System** is a software-based smart parking application developed using **C++ on Linux**.

The system manages parking slots, vehicles, waiting queues, parking history, data persistence, virtual parking sensors, Linux logging, FIFO inter-process communication, and a Linux character-device driver.

The project demonstrates the integration of:

- C++
- C
- Linux system programming
- Linux device-driver concepts
- Object-oriented programming
- STL data structures
- File handling
- Exception handling
- Pointers and smart pointers
- Linked lists
- Queues
- Linux system calls
- FIFO inter-process communication
- Virtual sensors
- Linux kernel/user-space interaction
- Computer architecture concepts
- Software development lifecycle
- Git/GitHub

---

## 2. Objectives

The main objectives of the project are:

1. Develop a software-based smart parking management system running on Linux.
2. Implement the main parking-management application using C++.
3. Develop a virtual parking device using a Linux kernel-module and character-device approach.
4. Demonstrate communication between user-space software and a Linux device interface.
5. Apply Linux system-programming concepts such as file operations, processes, and IPC.
6. Demonstrate C++ object-oriented and modular software design.
7. Use appropriate data structures such as vectors, queues, and linked lists.
8. Maintain persistent parking information using file handling.
9. Maintain the project using Git/GitHub with staged development and documentation.

---

## 3. Technology Stack

| Component | Technology |
|---|---|
| Main Application | C++17 |
| Kernel Driver | C |
| Operating System | Ubuntu Linux |
| Architecture | ARM64 |
| Application Type | Command-Line Application |
| Device Interface | Linux Character Device |
| IPC | Linux Named FIFO |
| Build System | GNU Make |
| Compiler | g++ / GCC |
| Debugging | GDB |
| Version Control | Git / GitHub |
| Data Storage | Text File |
| Sensor | Software / Virtual Sensor |
| Logging | Linux file-descriptor operations |

---

## 4. System Architecture

The project follows a user-space and kernel-space architecture.

```text
                    SMART PARKING SYSTEM
                             |
             +---------------+---------------+
             |                               |
         USER SPACE                     KERNEL SPACE
             |                               |
     +-------+--------+                      |
     |                |                      |
C++ Main         IPC Monitor                 |
Application          |                       |
     |                |                       |
     +-------+--------+                       |
             |                                |
      ParkingSystem                           |
             |                                |
   +---------+----------+                     |
   |         |          |                     |
Parking   Sensors    Logger                    |
Slots                 |                       |
   |              parking.log                 |
   |                                          |
Waiting Queue                                 |
   |                                          |
History                                       |
   |                                          |
parking_data.txt                              |
                                              |
      ParkingIPC                              |
          |                                   |
          v                                   |
/tmp/smart_parking_fifo                       |
          |                                   |
          v                                   |
   Parking Monitor                            |
                                              |
                                              |
Driver Test Program                           |
          |                                   |
          | read/write                        |
          v                                   |
 /dev/smart_parking                           |
          |                                   |
          v                                   |
 Linux Character Device Driver ---------------+