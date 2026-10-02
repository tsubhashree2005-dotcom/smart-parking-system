# Stage 3 — System Design and Architecture

## 1. Introduction

This stage describes the architecture and internal design of the Linux-Based Smart Parking Management System.

The system is divided into user-space and kernel-space components. The main parking application is implemented in C++, while the virtual character device driver is implemented as a Linux kernel module in C.

---

## 2. Overall System Architecture

```text
+------------------------------------------------------+
|                    USER SPACE                        |
|                                                      |
|  +-------------------+                               |
|  | C++ Main          |                               |
|  | Parking           |                               |
|  | Application       |                               |
|  +---------+---------+                               |
|            |                                         |
|     +------+-------+-------------+                   |
|     |              |             |                   |
|     v              v             v                   |
| Parking         Virtual       Linux                  |
| System          Sensor        Logger                 |
|     |              |             |                   |
|     +--------------+-------------+                   |
|            |                                         |
|            v                                         |
|       FIFO IPC                                       |
|            |                                         |
|            v                                         |
|     +--------------+                                 |
|     | IPC Monitor  |                                 |
|     +--------------+                                 |
|                                                      |
+------------------------|-----------------------------+
                         |
                    /dev/smart_parking
                         |
+------------------------|-----------------------------+
|                    KERNEL SPACE                      |
|                                                      |
|     +--------------------------------------+         |
|     | Linux Character Device Driver        |         |
|     | parking_driver.c                     |         |
|     +--------------------------------------+         |
|                                                      |
+------------------------------------------------------+