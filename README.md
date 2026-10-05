# Linux-Based Smart Parking Management System

## 1. Project Overview

The Linux-Based Smart Parking Management System is a software-only smart parking management application developed using C++ and Linux system programming.

The system manages:

 Parking slots

 Vehicle registration

 Vehicle removal

 Vehicle search

 Waiting queues

 Automatic queue parking

 Parking history

 Persistent parking data

 Virtual parking sensors

 Linux-based logging

 FIFO inter-process communication

 Linux character-device driver interaction

The project demonstrates the integration of C++, C, Linux, system programming, device-driver concepts, OOP, STL, file handling, IPC, data structures, and Git/GitHub.

--

## 2. Project Objectives

The main objectives are:

1 Develop a software-based smart parking management system running exclusively on Linux.

2 Implement the main parking-management application using C++.

3 Apply object-oriented programming principles.

4 Use STL data structures such as vectors and queues.

5 Implement linked-list-based parking history.

6 Implement persistent parking information using file handling.

7 Implement virtual parking sensors.

8 Implement Linux system-call based logging.

9 Implement FIFO-based inter-process communication.

10 Develop a Linux character-device kernel module.

11 Demonstrate user-space and kernel-space interaction.

12 Apply Linux system-programming concepts.

13 Demonstrate Git/GitHub-based development and documentation.

--

## 3. Key Features

### Parking Management

 Add and park vehicles

 Remove vehicles

 Search vehicles

 Display parking status

 Display available slots

 Automatic slot allocation

 Vehicle type compatibility

### Waiting Queue

 Queue vehicles when parking is full

 Maintain FIFO order

 Automatically assign slots when they become available

### Parking History

 Maintain parking history using a linked list

 Display previously processed parking records

### Data Persistence

Parking information is stored in:

text

parking_data.txt



The file is intentionally kept empty in the clean project. Runtime parking information is written to the file when vehicles are parked.

### Virtual Parking Sensors

The project includes software-based parking sensors that simulate:

 Occupied state

 Free state

 Sensor detection

 Sensor clearing

 Sensor toggling

### Linux Logging

The project uses Linux file-descriptor operations for logging.

Runtime log file:

text

parking.log



### FIFO IPC

The project implements Linux named-pipe communication using:

text

/tmp/smart_parking_fifo



A separate parking-monitor process receives parking-status messages from the main application.

### Linux Character Device Driver

A Linux kernel character-device driver is implemented in:

text

kernel_driver/



The driver creates a device interface:

text

/dev/smart_parking



The driver supports:

 open

 read

 write

 ioctl

 release

operations.

Custom IOCTL commands are defined in kernel_driver/parking_ioctl.h:

 SMART_PARKING_IOCTL_GET_BUFFER_SIZE — retrieves the current driver buffer size.

 SMART_PARKING_IOCTL_CLEAR_BUFFER — clears the driver buffer.

A separate driver-test program verifies user-space communication with the device, including read/write and IOCTL operations.

--

## 4. System Architecture

The project follows a Linux user-space and kernel-space architecture.

text

                SMART PARKING SYSTEM

                         |

         +---------------+---------------+

         \|                               |

     USER SPACE                      KERNEL SPACE

         \|                               |

 +-------+--------+                      |

 \|                |                      |

 C++ Main        IPC Monitor                 |

 Application          |                      |

 \|                |                      |

 +-------+--------+                      |

         \|                               |

   ParkingSystem                         |

         \|                               |

 +-------+--------+                      |

 \|       |        |                      |

  Parking  Sensors  Logger                  |

   Slots              |                     |

 \|            parking.log               |

 \|                                      |

 Waiting Queue                              |

 \|                                      |

  History                                   |

 \|                                      |

 parking_data.txt                           |

                                         |

   ParkingIPC                            |

       \|                                 |

       v                                 |

 /tmp/smart_parking_fifo                     |

       \|                                 |

       v                                 |

   Parking Monitor                           |

                                         |

 Driver Test Program                         |

       \|                                 |

   read/write                            |

       \|                                 |

       v                                 |

 /dev/smart_parking                          |

       \|                                 |

       v                                 |

 Linux Character Device Driver --------------+



--

## 5. User Space and Kernel Space

### User Space

The user-space portion contains:

 Main parking application

 Parking management logic

 Virtual sensors

 FIFO IPC

 Linux logger

 Parking monitor

 Driver test application

### Kernel Space

The kernel-space component contains:

 Linux character-device driver

 Device registration

 Character-device operations

 Kernel/user-space data transfer

The main parking application does not directly access the character device. The separate driver-test program demonstrates communication with the Linux device interface.

--

## 6. Project Structure

text

smart-parking-system/

│

├── src/

│   ├── main.cpp

│   ├── parking_system.cpp

│   ├── parking_system.h

│   ├── parking_sensor.cpp

│   ├── parking_sensor.h

│   ├── parking_ipc.cpp

│   ├── parking_ipc.h

│   ├── linux_logger.cpp

│   ├── linux_logger.h

│   ├── parking_monitor.cpp

│   └── parking_driver_test.cpp

│

├── kernel_driver/

│   ├── Makefile

│   └── parking_driver.c

│

├── docs/

│   ├── Stage1_Project_Introduction.md

│   ├── Stage2_Requirements_and_System_Analysis.md

│   ├── Stage3_System_Design_and_Architecture.md

│   ├── Stage4_Implementation_and_Development.md

│   ├── Stage5_Testing_and_Validation.md

│   ├── Stage6_Deployment_and_Final_Documentation.md

│   ├── UML_Diagrams.md

│   ├── Final_Test_Results.md

│   └── Final_Project_Report.md

│

├── .vscode/

│   └── tasks.json

│

├── Makefile

├── build.sh

├── run.sh

├── parking_data.txt

├── README.md

└── .gitignore



Generated build files such as object files and executables are excluded from the clean GitHub source structure through .gitignore.

--

## 7. Technologies Used

 Component | Technology |

---|---|

 Main Application | C++17 |

 Kernel Driver | C |

 Operating System | Ubuntu Linux |

 Architecture | ARM64 |

 Application Type | Command-Line Application |

 Build System | GNU Make |

 Compiler | g++ / GCC |

 Debugging | GDB |

 IPC | Linux Named FIFO |

 Device Interface | Linux Character Device |

 Data Storage | Text File |

 Sensor | Virtual Software Sensor |

 Logging | Linux file-descriptor system calls |

 Version Control | Git / GitHub |

--

## 8. C++ Concepts Demonstrated

The project applies:

 Classes and objects

 Encapsulation

 Constructors

 Member functions

 Structures

 STL vectors

 STL queues

 Shared pointers

 Linked lists

 Iteration

 File streams

 Exception handling

 Input validation

 Modular programming

 Header/source separation

--

## 9. Linux Concepts Demonstrated

The project demonstrates:

 Linux command-line environment

 Linux file system

 File permissions

 Processes

 Inter-process communication

 Named FIFO

 File descriptors

 System calls

 Kernel modules

 Character devices

 /dev device interface

 insmod

 rmmod

 lsmod

 dmesg

 User-space/kernel-space interaction

 Linux logging

--

## 10. Data Structures Used

### Vector

Used for managing parking slots.

text

vectorParkingSlot>



### Queue

Used for waiting vehicles.

text

queueVehicle>



### Linked List

Used for parking history.

text

HistoryNode



### Smart Pointer

Used where dynamic vehicle ownership is required.

text

shared_ptrVehicle>



--

## 11. Kernel Driver

The kernel driver is located in:

text

kernel_driver/parking_driver.c



It implements a Linux character device and exposes:

text

/dev/smart_parking



### Driver Operations

The driver implements:

text

open()

read()

write()

release()



The driver is built as a kernel module:

text

parking_driver.ko



### Build Driver

bash

cd kernel_driver

make



### Load Driver

bash

sudo insmod parking_driver.ko



### Verify Driver

bash

lsmod | grep parking_driver



bash

ls -l /dev/smart_parking



### Test Driver

Return to the project root:

bash

cd ..

sudo ./parking_driver_test



Expected result:

text

Written to driver: Parking driver test: Slot 1 OCCUPIED

Read from driver: Parking driver test: Slot 1 OCCUPIED

Driver communication successful.



### Remove Driver

bash

sudo rmmod parking_driver



--

## 12. Building the Project

The project uses GNU Make.

From the project root:

bash

cd /smart-parking-system



Run:

bash

make



Or use the build script:

bash

./build.sh



Expected output:

text

BUILD SUCCESSFUL



The build creates the application executables:

text

smart_parking

parking_monitor

parking_driver_test



--

## 13. Running the Main Application

Run:

bash

./smart_parking



The application provides menu-based operations for:

1 Park vehicle

2 Remove vehicle

3 Search vehicle

4 Display parking status

5 Display waiting queue

6 Display parking history

7 Save data

8 Send status through IPC

9 Exit

The exact menu displayed by the application should be used during the live demonstration.

--

## 14. FIFO IPC Demonstration

Open a second Linux terminal.

### Terminal 1

Run:

bash

./parking_monitor



The monitor waits for messages from:

text

/tmp/smart_parking_fifo



### Terminal 2

Run:

bash

./smart_parking



Select the IPC/status option from the menu.

The monitor receives a parking-status message similar to:

text

[IPC MESSAGE] SMART PARKING STATUS | Total Slots=5 | Occupied=0 | Free=5 | Waiting=0



This demonstrates communication between two Linux user-space processes using a named FIFO.

--

## 15. Logging

The application uses Linux file-descriptor operations for logging.

The runtime log is stored in:

text

parking.log



The logger demonstrates Linux:

text

open()

write()

close()



system calls.

--

## 16. Data Persistence

Parking information is stored in:

text

parking_data.txt



The clean project starts with this file empty.

When vehicles are parked, the application stores parking information in the file.

This demonstrates persistent storage using C++ file handling.

--

## 17. Build and Run Scripts

### Build Script

bash

./build.sh



The build script performs a clean build using the project Makefile.

### Run Script

bash

./run.sh



The run script launches:

text

./smart_parking



--

## 18. Testing

The project was tested through multiple levels:

### Build Testing

 Clean compilation

 Compiler warning checks

 Executable generation

### Functional Testing

 Vehicle parking

 Vehicle removal

 Vehicle search

 Parking status

 Waiting queue

 Automatic queue parking

 Parking history

 Data persistence

### Linux Feature Testing

 Virtual parking sensor

 Linux logging

 FIFO IPC

 Character-device driver

 /dev/smart_parking

 Driver read/write communication

### Automated Testing

A dedicated automated test suite is provided in:

text

tests/test_parking_system.cpp



The automated suite validates:

1 Vehicle parking

2 Vehicle removal

3 Waiting queue handling

4 Automatic waiting-queue allocation

5 Data persistence

6 Virtual parking sensor operation

7 Invalid vehicle validation

Final automated test result:

text

Passed : 7

Failed : 0

ALL TESTS PASSED



IOCTL Testing**

The kernel driver was additionally tested using:

text

src/parking_driver_test.cpp



The final IOCTL test successfully verified:

 write()

 ioctl(GET_BUFFER_SIZE)

 read()

 ioctl(CLEAR_BUFFER)

 Buffer size becomes 0 bytes after clearing

Final result:

text

IOCTL TEST SUCCESSFUL



Integration Testing**

The complete application was tested across:

text

C++ Application

   |

   +---- Virtual Sensors

   |

   +---- File Persistence

   |

   +---- Linux Logger

   |

   +---- FIFO IPC

   |

   +---- Parking Monitor

   |

   +---- Linux Character Driver



Detailed test cases and results are available in:

text

docs/Stage5_Testing_and_Validation.md

docs/Final_Test_Results.md



--

## 19. Documentation

The project documentation is organized according to the six development stages.

### Stage 1

text

docs/Stage1_Project_Introduction.md



Project idea, objectives, scope, applications, and expected outcome.

### Stage 2

text

docs/Stage2_Requirements_and_System_Analysis.md



Requirements, modules, development plan, and system analysis.

### Stage 3

text

docs/Stage3_System_Design_and_Architecture.md



Architecture, components, data structures, workflows, and implementation design.

### Stage 4

text

docs/Stage4_Implementation_and_Development.md



Implementation details, modules, Linux integration, automated testing, IOCTL support, and development progress.

### Stage 5

text

docs/Stage5_Testing_and_Validation.md



Testing, debugging, automated validation, IOCTL verification, and integration results.

### Stage 6

text

docs/Stage6_Deployment_and_Final_Documentation.md



Deployment, demonstration, final implementation, limitations, and future improvements.

### UML Diagrams

text

docs/UML_Diagrams.md



Includes:

 Use Case Diagram

 Class Diagram

 Component Architecture

 Sequence Diagrams

 Data Flow

 Kernel Interaction

 System Workflow

 Device Driver Workflow

### Final Test Results

text

docs/Final_Test_Results.md



Contains the final verification and testing results.

### Final Project Report

text

docs/Final_Project_Report.md



Contains the consolidated project report.

--

## 20. Git and GitHub

The project is maintained using Git and hosted on GitHub.

Repository:

https//github.com/tsubhashree2005-dotcom/smart-parking-system

Git is used for:

 Version control

 Staged development

 Documentation tracking

 Source-code management

 Project history

 GitHub-based project presentation

--

## 21. Project Development Stages

The project follows six stages:

text

Stage 1

Project Introduction

    |

    v

Stage 2

Requirements & System Analysis

    |

    v

Stage 3

System Design & Architecture

    |

    v

Stage 4

Implementation & Development

    |

    v

Stage 5

Testing & Validation

    |

    v

Stage 6

Deployment & Final Documentation



--

## 22. Training Concepts Integrated

The project integrates concepts from the training program, including:

### C / C++

 C++ programming

 Object-oriented programming

 STL

 File handling

 Exception handling

 Pointers

 Smart pointers

 Modular programming

### Data Structures

 Vector

 Queue

 Linked list

### Linux

 Linux CLI

 File system

 File permissions

 Processes

 IPC

 File descriptors

 System calls

### Kernel Programming

 Linux kernel module

 Character device

 Device registration

 Read/write operations

 User-space/kernel-space communication

### Computer Architecture

 User space and kernel space

 Memory and address-space concepts

 CPU/system interaction

 Interrupt and device concepts

### Software Development

 Requirements analysis

 System design

 UML

 Implementation

 Testing

 Debugging

 Documentation

 Git/GitHub

--

## 23. Limitations

The current implementation is software-based and uses virtual parking sensors rather than physical hardware sensors.

The project focuses on demonstrating Linux, C++, system programming, IPC, and device-driver concepts rather than providing a production-scale commercial parking platform.

Parking data persistence is implemented for active parking information. Runtime history and waiting-queue state are not intended to persist across application restarts.

--

## 24. Future Improvements

Possible future improvements include:

 Physical sensor integration

 RFID-based vehicle identification

 Camera-based vehicle detection

 Web-based monitoring dashboard

 Mobile application

 Database-backed storage

 Multi-location parking management

 Network-based monitoring

 Real-time notifications

 Authentication and access control

--

## 25. Final Outcome

The completed project demonstrates a complete Linux-based smart parking management workflow combining:

text

C++

  |

  +-- Object-Oriented Programming

  |

  +-- STL Data Structures

  |

  +-- File Handling

  |

  +-- Virtual Sensors

  |

  +-- Linux System Calls

  |

  +-- Linux Logging

  |

  +-- FIFO IPC

  |

  +-- Separate Monitoring Process

  |

  +-- Linux Character Device

  |

  +-- Kernel Module

  |

  +-- User/Kernel Interaction

  |

  +-- Git/GitHub



The project is designed to be demonstrated and evaluated on a Linux environment and provides both the source code and complete stage-wise documentation required for the training capstone.

--

## 26. Quick Demonstration

### Build

bash

cd /smart-parking-system

./build.sh



### Run Application

bash

./smart_parking



### Run IPC Monitor

In another terminal:

bash

cd /smart-parking-system

./parking_monitor



### Build and Test Kernel Driver

bash

cd /smart-parking-system/kernel_driver

make

sudo insmod parking_driver.ko

lsmod | grep parking_driver

ls -l /dev/smart_parking

cd ..

sudo ./parking_driver_test

cd kernel_driver

sudo rmmod parking_driver



### Clean Build Files

From the project root:

bash

cd /smart-parking-system

make clean



--

## Final Enhancements

The final implementation includes two additional technical upgrades.

### Automated Test Suite

A dedicated automated test program was added under:

text

tests/test_parking_system.cpp



It validates core parking functionality, queue handling, persistence, virtual sensors, and invalid-input handling.

Final result:

text

Passed : 7

Failed : 0

ALL TESTS PASSED



### Linux Kernel IOCTL Support

The character-device driver was extended with custom IOCTL operations defined in:

text

kernel_driver/parking_ioctl.h



Supported operations:

text

SMART_PARKING_IOCTL_GET_BUFFER_SIZE

SMART_PARKING_IOCTL_CLEAR_BUFFER



The driver test successfully verified:

text

[1] write() successful

[2] ioctl GET_BUFFER_SIZE successful

Buffer size: 36 bytes

[3] read() successful

[4] ioctl CLEAR_BUFFER successful

[5] Buffer size after clear: 0 bytes

IOCTL TEST SUCCESSFUL



These additions demonstrate automated software validation and a richer user-space/kernel-space interface.

--

## 28. Conclusion

The Linux-Based Smart Parking Management System demonstrates how a practical parking-management application can be implemented using Linux and C++ while integrating system-level concepts.

The project combines application-level functionality with Linux system programming, FIFO IPC, virtual sensors, file persistence, logging, and a Linux character-device driver.

It provides a complete learning-oriented implementation covering software design, data structures, Linux programming, kernel interaction, testing, documentation, and Git/GitHub-based project management.