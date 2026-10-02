# Stage 4 — Implementation and Development

## 1. Introduction

Stage 4 focuses on implementing the Linux-Based Smart Parking Management System according to the architecture and requirements defined in the previous stages.

The implementation combines C++ object-oriented programming, STL data structures, file handling, Linux system calls, FIFO inter-process communication, virtual sensors, Linux logging, and a Linux kernel character device driver.

The implementation is modular so that each major responsibility is handled by a separate component.

---

## 2. Implementation Environment

The project was developed and tested in a Linux environment.

| Component | Technology |
|---|---|
| Operating System | Ubuntu Linux |
| Architecture | ARM64 |
| Programming Language | C++17 |
| Compiler | g++ |
| Build System | GNU Make |
| Kernel Module | C / Linux Kernel API |
| Debugging | GDB |
| Version Control | Git |
| Repository | GitHub |

---

## 3. Source-Code Organization

The main project files are:

```text
main.cpp
parking_system.cpp
parking_system.h
parking_sensor.cpp
parking_sensor.h
parking_ipc.cpp
parking_ipc.h
parking_monitor.cpp
parking_driver_test.cpp
linux_logger.cpp
linux_logger.h
Makefile
build.sh
run.sh