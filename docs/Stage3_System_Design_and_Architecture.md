# Stage 3 — System Design and Architecture

## 1. Introduction

This stage defines the detailed architecture and internal design of the Linux-Based Smart Parking Management System.

The system is designed as a modular Linux application consisting of:

- C++ parking-management software.
- Virtual parking sensors.
- Linux system-call based logging.
- FIFO-based inter-process communication.
- A separate IPC monitoring process.
- A Linux kernel character-device driver.
- A user-space driver test program.

The main parking application operates in user space. The character-device driver operates in kernel space and is accessed through `/dev/smart_parking` by the dedicated driver test program.

---

## 2. System Architecture

```text
                         USER
                           |
                           v
              +-------------------------+
              | Main C++ Application    |
              |       main.cpp          |
              +-----------+-------------+
                          |
                          v
              +-------------------------+
              |     ParkingSystem       |
              +-----------+-------------+
                          |
          +---------------+----------------+
          |               |                |
          v               v                v
   Parking Slots     Virtual Sensors   Linux Logger
          |               |                |
          |               |                v
          |               |          parking.log
          |               |
          |               v
          |         Occupancy State
          |
          +--------------------------+
                                     |
                                     v
                              Parking Data File
                                     |
                                     v
                              parking_data.txt

              ParkingSystem
                    |
                    v
               ParkingIPC
                    |
                    v
        /tmp/smart_parking_fifo
                    |
                    v
             IPC Monitor


              USER SPACE
------------------------------------------------------------

                    |
                    | open/read/write
                    v

             /dev/smart_parking
                    |
                    v

       Linux Character Device Driver
          kernel_driver/parking_driver.c
                    |
                    v

              KERNEL SPACE