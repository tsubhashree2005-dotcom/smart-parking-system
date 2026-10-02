# Stage 2 — Requirements and System Analysis

## 1. Introduction

The Linux-Based Smart Parking Management System is a software-based parking management application developed using C++ and Linux system programming concepts.

The system simulates parking sensors and provides parking management functionality through a command-line interface. It also demonstrates Linux inter-process communication, file handling, logging, and a Linux character device driver.

---

## 2. Problem Statement

Traditional parking management can require manual monitoring of parking spaces and vehicle records.

The proposed system provides a software-based solution that can:

- Track available and occupied parking slots.
- Assign suitable slots to vehicles.
- Maintain a waiting queue when parking is unavailable.
- Automatically assign a freed slot to a waiting vehicle.
- Search for parked vehicles.
- Maintain parking history.
- Store parking information persistently.
- Simulate parking sensors.
- Exchange status information using Linux FIFO IPC.
- Communicate with a Linux character device driver.
- Maintain system activity logs.

---

## 3. Objectives

The main objectives are:

1. Develop a Linux-based parking management application.
2. Implement the application using C++.
3. Apply object-oriented programming concepts.
4. Use C++ STL data structures and algorithms.
5. Implement file-based data persistence.
6. Implement exception handling.
7. Implement a virtual parking sensor.
8. Implement a waiting queue for vehicles.
9. Implement parking history using a linked list.
10. Implement Linux FIFO-based IPC.
11. Implement Linux file-descriptor based logging.
12. Develop a Linux character device driver.
13. Provide a user-space driver test program.
14. Demonstrate interaction between user space and kernel space.

---

## 4. Functional Requirements

### FR1 — Vehicle Parking

The system shall allow the user to enter:

- Vehicle number
- Owner name
- Vehicle type

The system shall assign a compatible available parking slot.

---

### FR2 — Vehicle Removal

The system shall allow a parked vehicle to be removed using its vehicle number.

The corresponding parking slot shall become available.

---

### FR3 — Parking Status

The system shall display:

- Total parking slots
- Occupied slots
- Free slots
- Slot number
- Vehicle information
- Slot type
- Sensor status

---

### FR4 — Vehicle Search

The system shall allow the user to search for a vehicle using its vehicle number.

---

### FR5 — Waiting Queue

If no compatible parking slot is available, the vehicle shall be placed in a waiting queue.

The queue shall follow FIFO ordering.

---

### FR6 — Automatic Queue Parking

When a parking slot becomes available, the system shall check the waiting queue and automatically assign the slot to a compatible waiting vehicle.

---

### FR7 — Parking History

The system shall maintain a history of parking operations.

The history shall use a linked-list based structure.

---

### FR8 — Data Persistence

The system shall save parking information to a data file.

Previously stored parking information shall be loaded when the application starts.

---

### FR9 — Virtual Parking Sensor

Each parking slot shall have a software-simulated parking sensor.

The sensor shall maintain an occupied/free state corresponding to the parking slot.

---

### FR10 — Linux Logging

The system shall maintain a Linux log file containing important system events such as:

- System startup
- Vehicle parking
- Vehicle removal
- Waiting queue operations
- Automatic queue parking

---

### FR11 — FIFO IPC

The system shall provide communication between the main parking application and the IPC monitor using a Linux named FIFO.

The parking application shall send parking status information through:

```text
/tmp/smart_parking_fifo