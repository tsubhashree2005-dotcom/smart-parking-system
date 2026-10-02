# Linux-Based Smart Parking Management System

## Final Project Report

---

## 1. Project Information

**Project Title:** Linux-Based Smart Parking Management System

**Programming Language:** C++

**Operating System:** Ubuntu Linux

**Development Environment:** Ubuntu Server 24.04 LTS

**Build System:** GNU Make

**Version Control:** Git and GitHub

**Project Type:** Linux System Programming and Smart Parking Management

---

# 2. Abstract

The Linux-Based Smart Parking Management System is a C++ application developed on the Linux operating system to simulate and manage a smart parking facility.

The system provides vehicle parking, vehicle removal, parking-slot management, vehicle searching, waiting-queue management, parking history, data persistence, virtual parking sensors, Linux-based logging, inter-process communication, and Linux kernel character-device communication.

A major objective of the project is to connect application-level programming with Linux system programming concepts. The project therefore includes both user-space C++ components and a Linux kernel character device driver.

The system uses C++ object-oriented programming, STL containers, linked lists, queues, smart pointers, file handling, exception handling, Linux system calls, FIFO-based IPC, and a kernel character device.

The completed system was developed, tested, documented, and maintained using Git and GitHub.

---

# 3. Introduction

Parking management becomes increasingly difficult as the number of vehicles and parking facilities increases. Manual parking management can result in inefficient slot allocation, difficulty tracking vehicles, and limited visibility of parking availability.

The objective of this project is to develop a Linux-based software system that simulates the operation of a smart parking facility while demonstrating important concepts from C++, Linux system programming, computer architecture, hardware/software interaction, and software engineering.

The system provides a structured interface for managing parking slots and vehicles while also demonstrating how a user-space application can interact with Linux operating-system facilities and a virtual hardware device.

---

# 4. Problem Statement

Traditional or manually managed parking systems may have difficulties with:

- Tracking occupied and available parking slots.
- Assigning vehicles to appropriate slots.
- Managing vehicles when parking capacity is full.
- Maintaining parking history.
- Persisting parking information.
- Monitoring parking status.
- Representing sensor-based occupancy information.
- Communicating between independent processes.
- Demonstrating interaction between user-space software and device-level components.

The proposed system addresses these requirements through a modular Linux-based C++ implementation.

---

# 5. Project Objectives

The main objectives of the project are:

1. Develop a Linux-based smart parking management system.
2. Implement the main application using C++.
3. Apply object-oriented programming principles.
4. Implement parking-slot and vehicle management.
5. Implement compatible-slot allocation.
6. Implement a waiting queue for vehicles.
7. Implement parking history.
8. Implement persistent storage using files.
9. Simulate parking sensors.
10. Implement Linux-based system logging.
11. Implement inter-process communication using FIFO.
12. Develop a Linux character device driver.
13. Demonstrate user-space and kernel-space communication.
14. Apply Linux system programming concepts.
15. Maintain the project using Git and GitHub.
16. Provide complete project documentation and UML diagrams.

---

# 6. Project Scope

The project covers the following functionality:

- Vehicle registration.
- Vehicle parking.
- Vehicle removal.
- Vehicle searching.
- Parking-slot status display.
- Vehicle-type based slot compatibility.
- Waiting-queue management.
- Automatic processing of waiting vehicles.
- Parking history.
- File-based persistence.
- Virtual parking sensors.
- Linux logging.
- FIFO-based IPC.
- Linux character device driver.
- Driver read/write communication.
- Build automation using Makefile.
- Git/GitHub version control.
- UML and technical documentation.

The project is implemented as a Linux application and does not depend on a physical parking facility or physical sensors.

---

# 7. Functional Requirements

The system provides the following functional requirements.

## 7.1 Vehicle Management

The system allows users to:

- Enter vehicle information.
- Park vehicles.
- Remove vehicles.
- Search for vehicles.
- Display parking information.

## 7.2 Parking-Slot Management

The parking area contains multiple slots.

The implemented configuration contains:

- Slots 1–3: CAR
- Slots 4–5: BIKE

The system checks vehicle type before assigning a parking slot.

## 7.3 Waiting Queue

If a compatible parking slot is unavailable, the vehicle can be placed in a waiting queue.

When a compatible slot becomes available, the system can process the waiting vehicle automatically.

## 7.4 Parking History

The system maintains a history of parking-related operations.

A linked-list based structure is used for historical records.

## 7.5 Data Persistence

Parking information is stored using file operations so that data can be saved and loaded between application executions.

## 7.6 Virtual Sensors

Each parking slot can be associated with a virtual parking sensor.

The sensor represents occupancy information that would normally be obtained from hardware.

## 7.7 Linux Logging

The system provides Linux-based logging using file-descriptor operations.

## 7.8 Inter-Process Communication

The system uses a Linux named pipe (FIFO) to communicate parking-status information to a separate monitoring process.

## 7.9 Character Device Driver

The project contains a Linux kernel character device driver exposed through:

```text
/dev/smart_parking