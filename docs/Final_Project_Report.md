Linux-Based Smart Parking Management System

Final Project Report



1. Project Information

Project Title: Linux-Based Smart Parking Management System

Programming Language: C++ (main application) and C (Linux kernel driver)

Operating System: Ubuntu Linux

Development Environment: Ubuntu Server 24.04 LTS

Build System: GNU Make

Version Control: Git and GitHub

Project Type: Linux System Programming and Smart Parking Management

Application Type: Command-line software system

Hardware Requirement: None; parking sensors are software-simulated





2. Abstract

The Linux-Based Smart Parking Management System is a C++ application developed on the Linux operating system to simulate and manage a smart parking facility.

The system provides vehicle parking, vehicle removal, parking-slot management, vehicle searching, waiting-queue management, parking history, data persistence, virtual parking sensors, Linux-based logging, inter-process communication, and Linux kernel character-device communication.

A major objective of the project is to connect application-level programming with Linux system programming concepts. The project therefore includes both user-space C++ components and a Linux kernel character-device driver.

The system uses C++ object-oriented programming, STL containers, linked lists, queues, smart pointers, file handling, exception handling, Linux system calls, FIFO-based IPC, character-device operations, and an ioctl interface.

The project also includes an automated C++ test suite for validating core parking functionality and a dedicated user-space driver test program for validating character-device operations.

The completed system was developed, tested, documented, and maintained using Git and GitHub.





3. Introduction

Parking management becomes increasingly difficult as the number of vehicles and parking facilities increases. Manual parking management can result in inefficient slot allocation, difficulty tracking vehicles, and limited visibility of parking availability.

The objective of this project is to develop a Linux-based software system that simulates the operation of a smart parking facility while demonstrating important concepts from C++, Linux system programming, computer architecture, hardware/software interaction, and software engineering.

The system provides a structured command-line interface for managing parking slots and vehicles while also demonstrating how user-space software can use Linux operating-system facilities and interact with a virtual character device.





4. Problem Statement

Traditional or manually managed parking systems may have difficulties with:





Tracking occupied and available parking slots.



Assigning vehicles to appropriate slots.



Managing vehicles when parking capacity is full.



Maintaining parking history.



Persisting parking information.



Monitoring parking status.



Representing sensor-based occupancy information.



Communicating between independent processes.



Demonstrating interaction between user-space software and device-level components.

The proposed system addresses these requirements through a modular Linux-based C++ implementation with supporting Linux kernel-driver functionality.





5. Project Objectives

The main objectives of the project are:





Develop a Linux-based smart parking management system.



Implement the main application using C++.



Apply object-oriented programming principles.



Implement parking-slot and vehicle management.



Implement compatible-slot allocation.



Implement a waiting queue for vehicles.



Implement automatic allocation of released slots to compatible waiting vehicles.



Implement parking history using a linked-list based structure.



Implement persistent storage using files.



Simulate parking sensors.



Implement Linux-based system logging.



Implement inter-process communication using FIFO.



Develop a Linux character device driver.



Implement character-device read() and write() operations.



Implement device-control operations using ioctl.



Provide a user-space driver test application.



Provide automated functional testing.



Demonstrate user-space and kernel-space communication.



Apply Linux system programming concepts.



Maintain the project using Git and GitHub.



Provide complete project documentation and UML diagrams.





6. Project Scope

The project covers the following functionality:





Vehicle registration.



Vehicle parking.



Vehicle removal.



Vehicle searching.



Parking-slot status display.



Vehicle-type based slot compatibility.



Waiting-queue management.



Automatic processing of waiting vehicles.



Parking history.



File-based persistence.



Virtual parking sensors.



Linux logging.



FIFO-based IPC.



Linux character device driver.



Character-device read/write communication.



ioctl device control.



User-space driver testing.



Automated functional testing.



Build automation using Makefile.



Git/GitHub version control.



UML and technical documentation.

The project is implemented as a Linux application and does not depend on a physical parking facility or physical sensors.





7. Functional Requirements

The system provides the following functional requirements.

7.1 Vehicle Management

The system allows users to:





Enter vehicle information.



Park vehicles.



Remove vehicles.



Search for vehicles.



Display parking information.



Validate vehicle information before parking.



7.2 Parking-Slot Management

The parking area contains multiple slots.

The implemented configuration contains:





Slots 1–3: CAR



Slots 4–5: BIKE

The system checks vehicle type before assigning a parking slot.

7.3 Waiting Queue

If a compatible parking slot is unavailable, the vehicle can be placed in a waiting queue.

When a compatible slot becomes available, the system checks the waiting queue and automatically assigns the slot to a compatible waiting vehicle.

The queue follows FIFO ordering.

7.4 Parking History

The system maintains a history of parking-related operations.

A linked-list based structure is used for historical records.

7.5 Data Persistence

Parking information is stored using file operations so that data can be saved and loaded between application executions.

The primary parking data file is:

parking_data.txt



7.6 Virtual Sensors

Each parking slot can be associated with a virtual parking sensor.

The sensor represents occupancy information that would normally be obtained from hardware.

The sensor implementation supports operations such as detecting, clearing, toggling, and displaying sensor state.

7.7 Linux Logging

The system provides Linux-based logging using file-descriptor operations.

Important parking events are recorded in:

parking.log



7.8 Inter-Process Communication

The system uses a Linux named pipe (FIFO) to communicate parking-status information to a separate monitoring process.

The FIFO is:

/tmp/smart_parking_fifo

The main application writes status information and the parking_monitor application reads and displays it.

7.9 Character Device Driver

The project contains a Linux kernel character-device driver exposed through:

/dev/smart_parking

The driver supports:





Device open.



Device read.



Device write.



Device release.



Mutex-protected buffer access.



7.10 IOCTL Device Control

The driver provides an ioctl interface defined in:

kernel_driver/parking_ioctl.h

The implemented operations are:

SMART_PARKING_IOCTL_GET_BUFFER_SIZE
SMART_PARKING_IOCTL_CLEAR_BUFFER

GET_BUFFER_SIZE returns the current number of bytes stored in the driver buffer.

CLEAR_BUFFER clears the driver buffer and resets its size to zero.

Unsupported commands return an appropriate Linux error.

7.11 Driver Test Application

The project contains a dedicated user-space C++ driver test program:

src/parking_driver_test.cpp

The test application verifies:





Writing data to the character device.



Retrieving the buffer size using ioctl.



Reading the stored data.



Clearing the buffer using ioctl.



Confirming that the buffer size becomes zero.

The final driver test completed successfully.

7.12 Automated Functional Testing

The project includes an automated C++ test suite:

tests/test_parking_system.cpp

The suite validates:





Vehicle parking.



Vehicle removal.



Waiting queue behavior.



Automatic waiting-queue allocation.



Data persistence.



Virtual parking sensor behavior.



Invalid vehicle validation.

Final automated test result:

Passed : 7
Failed : 0
ALL TESTS PASSED





8. System Architecture

The system follows a modular architecture consisting of user-space application components and a kernel-space device component.

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
                    | ioctl
                    v

             /dev/smart_parking
                    |
                    v

       Linux Character Device Driver
          kernel_driver/parking_driver.c
                    |
                    v

                KERNEL SPACE

The normal parking application and the driver test application are separate user-space components. The main parking application does not directly communicate with /dev/smart_parking; the dedicated driver test application demonstrates the user-space/kernel-space device interface.





9. Major Software Components







Component



Responsibility





main.cpp



Command-line interface and application control





ParkingSystem



Core parking-management logic





ParkingSensor



Virtual parking-slot sensor





ParkingIPC



FIFO-based IPC





parking_monitor.cpp



IPC monitoring process





LinuxLogger



Linux-based event logging





parking_driver.c



Linux kernel character-device driver





parking_ioctl.h



IOCTL command definitions





parking_driver_test.cpp



User-space driver verification





test_parking_system.cpp



Automated functional testing





10. Data Structures and Programming Concepts

The project applies several C++ data structures and programming concepts.

10.1 Vector

Parking slots are managed using:

vector<ParkingSlot>

This provides indexed storage and management of parking slots.

10.2 Queue

Waiting vehicles are managed using:

queue<Vehicle>

The queue follows FIFO ordering.

10.3 Linked List

Parking history uses a linked-list based structure consisting of history nodes connected through pointers.

10.4 Smart Pointers

The project uses:

shared_ptr<Vehicle>

where appropriate to demonstrate managed dynamic memory.

10.5 File Handling

The application uses C++ file streams for parking-data persistence.

10.6 Linux System Calls

Linux operations are demonstrated through system interfaces such as:

open()
read()
write()
close()

The logger and device-related components demonstrate low-level Linux file-descriptor operations.

10.7 Exception Handling

Application-level validation and file-operation errors are handled using C++ exception-handling mechanisms where appropriate.





11. Linux Kernel Driver Design

The Linux character driver is implemented in:

kernel_driver/parking_driver.c

The driver registers a character device and creates:

/dev/smart_parking

The driver uses:





alloc_chrdev_region()



cdev_init()



cdev_add()



class_create()



device_create()



copy_to_user()



copy_from_user()



Linux mutex synchronization



unlocked_ioctl

The driver maintains an internal buffer protected by a mutex.





12. User-Space and Kernel-Space Interaction

The project demonstrates the following communication path:

User-Space Driver Test
          |
          | open()
          | write()
          | read()
          | ioctl()
          v
 /dev/smart_parking
          |
          v
 Linux Character Driver
          |
          v
 Kernel-Space Buffer

This demonstrates the boundary between user space and kernel space and the use of Linux device interfaces.





13. IOCTL Design

The IOCTL interface provides device-specific control operations.

The interface is defined using Linux IOCTL macros.

The supported operations are:







Operation



Purpose





GET_BUFFER_SIZE



Returns current driver-buffer size





CLEAR_BUFFER



Clears driver buffer and resets size

The driver test confirmed both operations successfully.





14. Inter-Process Communication Design

The project uses a Linux named FIFO for communication between the main application and the monitoring process.

Main Application
       |
       | write()
       v
/tmp/smart_parking_fifo
       |
       | read()
       v
Parking Monitor

This demonstrates Linux IPC and communication between independent processes.





15. Testing and Validation

Testing was performed at multiple levels.

15.1 Build Testing

The complete C++ project was built using:

./build.sh

The build completed successfully.

15.2 Automated Functional Testing

The automated test suite produced:

Passed : 7
Failed : 0
ALL TESTS PASSED



15.3 Driver Testing

The kernel module was built successfully and loaded using Linux module tools.

The device was created as:

/dev/smart_parking

The driver test verified:

write()       -> successful
ioctl GET     -> successful
read()        -> successful
ioctl CLEAR   -> successful
buffer reset  -> successful

Final result:

IOCTL TEST SUCCESSFUL



15.4 Integration Testing

The following components were validated together:





Parking management.



Data persistence.



Virtual sensors.



Linux logging.



FIFO IPC.



Character-device driver.



IOCTL interface.



Automated testing.





16. Development and Build Process

The project uses GNU Make for compilation.

The root Makefile builds:

smart_parking
parking_monitor
parking_driver_test

The kernel-driver Makefile builds:

parking_driver.ko

Helper scripts are also provided:

build.sh
run.sh

The project follows a modular development process in which application components, Linux system features, kernel-driver functionality, automated tests, and documentation were integrated progressively.





17. Project Directory Structure

smart-parking-system/
|
+-- src/
|   +-- main.cpp
|   +-- parking_system.cpp
|   +-- parking_system.h
|   +-- parking_sensor.cpp
|   +-- parking_sensor.h
|   +-- parking_ipc.cpp
|   +-- parking_ipc.h
|   +-- parking_monitor.cpp
|   +-- parking_driver_test.cpp
|   +-- linux_logger.cpp
|   +-- linux_logger.h
|
+-- kernel_driver/
|   +-- parking_driver.c
|   +-- parking_ioctl.h
|   +-- Makefile
|
+-- tests/
|   +-- test_parking_system.cpp
|
+-- docs/
|   +-- Stage1_Project_Introduction.md
|   +-- Stage2_Requirements_and_System_Analysis.md
|   +-- Stage3_System_Design_and_Architecture.md
|   +-- Stage4_Implementation_and_Development.md
|   +-- Stage5_Testing_and_Validation.md
|   +-- Stage6_Deployment_and_Final_Documentation.md
|   +-- UML_Diagrams.md
|   +-- Final_Test_Results.md
|   +-- Final_Project_Report.md
|
+-- .vscode/
|   +-- tasks.json
|
+-- Makefile
+-- build.sh
+-- run.sh
+-- README.md
+-- parking_data.txt

Generated object files, executables, kernel build artifacts, and runtime files are excluded from version control where appropriate.





18. Training Concepts Demonstrated

The project integrates concepts from multiple training areas.

C/C++





C++17



Object-oriented programming



Classes and structures



STL



Vectors



Queues



Linked lists



Smart pointers



File handling



Exception handling



Linux System Programming





Linux command-line environment



File descriptors



System calls



Processes



FIFO IPC



File operations



Permissions



Kernel modules



Character devices



Synchronization



Linux Device Drivers





Kernel module development



Character-device registration



Major/minor device handling



open



read



write



release



ioctl



Mutex synchronization



User/kernel data transfer



Computer Architecture and Hardware/Software Concepts

The project demonstrates the relationship between:

User Application
       |
       v
Operating System
       |
       v
Device Interface
       |
       v
Kernel Driver
       |
       v
Virtual Device

Although no physical hardware is used, the virtual device provides a software representation of hardware/software interaction.

Software Engineering





SDLC



Modular development



Requirements analysis



System design



UML



Testing



Debugging



Documentation



Git/GitHub version control





19. Achievements

The completed project successfully provides:





Linux-based smart parking management.



C++ command-line application.



Vehicle and parking-slot management.



Vehicle-type compatible slot allocation.



FIFO waiting queue.



Automatic queue processing.



Linked-list parking history.



File-based persistence.



Virtual parking sensors.



Linux system-call based logging.



FIFO-based IPC.



Linux character-device driver.



Character-device read/write operations.



IOCTL-based device control.



User-space driver test application.



Automated functional test suite.



Successful build and integration.



Complete project documentation.



UML and architecture documentation.



Git/GitHub version control.





20. Limitations

The current system has the following limitations:





It is a software simulation and does not use physical parking sensors.



The parking facility is represented by a fixed number of simulated slots.



The interface is command-line based.



The character device is a virtual device and does not control physical parking hardware.



The system is intended primarily as a training and demonstration project rather than a production parking-management platform.





21. Future Enhancements

Possible future improvements include:





Integration with real parking sensors.



Support for a larger number of parking slots.



Database-backed storage.



Network-based remote monitoring.



Authentication and role-based access.



Real-time device events and notifications.



More advanced kernel-driver event handling.



Additional automated test coverage.



Mobile or web-based interfaces.

These enhancements are outside the current project scope.





22. Final Demonstration Flow

The final project can be demonstrated using the following sequence:

1. Build the project
        |
        v
2. Start Smart Parking Application
        |
        v
3. Park a vehicle
        |
        v
4. Display parking status
        |
        v
5. Demonstrate waiting queue
        |
        v
6. Remove a vehicle
        |
        v
7. Demonstrate automatic queue allocation
        |
        v
8. Demonstrate sensor status
        |
        v
9. Demonstrate parking history/persistence
        |
        v
10. Demonstrate FIFO IPC monitor
        |
        v
11. Build and load character driver
        |
        v
12. Demonstrate /dev/smart_parking
        |
        v
13. Run driver IOCTL test
        |
        v
14. Run automated tests
        |
        v
15. Show documentation and GitHub repository





23. Final Test Summary







Test Area



Result





C++ Build



PASS





Parking Operations



PASS





Vehicle Removal



PASS





Waiting Queue



PASS





Automatic Queue Allocation



PASS





Data Persistence



PASS





Virtual Sensor



PASS





Input Validation



PASS





Linux Logging



PASS





FIFO IPC



PASS





Kernel Driver Build



PASS





Character Device Creation



PASS





Driver Read/Write



PASS





IOCTL GET_BUFFER_SIZE



PASS





IOCTL CLEAR_BUFFER



PASS





Automated Tests



7 PASS / 0 FAIL





Overall System



PASS





24. Conclusion

The Linux-Based Smart Parking Management System successfully integrates C++ application development with Linux system programming and Linux kernel concepts.

The project demonstrates object-oriented programming, STL data structures, linked lists, queues, file handling, exception handling, virtual sensors, Linux system calls, FIFO IPC, Linux logging, character-device development, IOCTL-based device control, user-space/kernel-space communication, automated testing, and Git/GitHub-based project management.

The completed system provides a functional software-based smart parking environment while demonstrating how application-level software can interact with Linux operating-system facilities and a virtual kernel device.

The successful build, automated test result of 7 passed and 0 failed, and successful IOCTL driver test confirm that the major project components were implemented and integrated successfully.

The project therefore fulfills its purpose as a comprehensive Linux-based training capstone demonstrating C++, Linux system programming, device-driver concepts, software architecture, testing, and software engineering practices.