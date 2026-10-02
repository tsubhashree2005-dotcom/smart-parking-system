# Linux-Based Smart Parking Management System

## 1. Project Overview

The **Linux-Based Smart Parking Management System** is a software-based smart parking application developed using **C++ on Linux**.

The system manages parking slots, vehicles, waiting queues, parking history, data persistence, virtual parking sensors, Linux IPC, logging, and a Linux character-device driver.

The project demonstrates the integration of:

- C++
- Linux system programming
- Linux device drivers
- C programming
- Object-oriented programming
- STL data structures
- File handling
- Inter-process communication
- Virtual sensors
- Linux kernel/user-space interaction
- Computer architecture concepts
- Software development lifecycle
- Git/GitHub based development

---

## 2. Objectives

The main objectives of the project are:

1. Develop a software-based smart parking management system running on Linux.
2. Implement the main parking management application using C++.
3. Develop a virtual parking device using a Linux kernel-module/character-device approach.
4. Demonstrate communication between user-space software and the Linux device interface.
5. Apply Linux system-programming concepts such as file operations and IPC.
6. Demonstrate C++ object-oriented and modular software design.
7. Maintain the project using Git/GitHub with proper documentation and staged development.

---

## 3. Technology Stack

| Component | Technology |
|---|---|
| Main Language | C++ |
| Driver Language | C |
| Operating System | Linux |
| Application Type | Command-Line Application |
| Device Interface | Linux Character Device |
| IPC | Linux Named FIFO |
| Build System | GNU Make |
| Compiler | GCC/G++ |
| Debugging | GDB |
| Version Control | Git/GitHub |
| Data Storage | Text File |
| Sensor | Software/Virtual Sensor |

---

## 4. System Architecture

The system follows a user-space and kernel-space architecture.

```text
                    SMART PARKING SYSTEM
                             |
              +--------------+--------------+
              |                             |
          USER SPACE                   KERNEL SPACE
              |                             |
        C++ Application                C Driver
              |                             |
    +---------+---------+                 |
    |         |         |                 |
 Parking   Vehicle   IPC Monitor          |
 Manager   Manager                       |
    |         |                           |
    +---------+                           |
              |                            |
       Data Structures                     |
       STL / Algorithms                    |
              |                            |
       Files / Logging                     |
              |                            |
        System Calls ----------------------+
                                           |
                                  Character Device
                                           |
                                  /dev/smart_parking
                                           |
                                  Virtual Parking Device