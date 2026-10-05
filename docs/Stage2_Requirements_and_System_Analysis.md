Stage 2 — Requirements and System Analysis

1. Introduction

The Linux-Based Smart Parking Management System is a software-based parking management application developed using C++ and Linux system programming concepts.

The system simulates parking sensors and provides parking management functionality through a command-line interface. It also demonstrates Linux inter-process communication, file handling, logging, and a Linux character device driver.



2. Problem Statement

Traditional parking management can require manual monitoring of parking spaces and vehicle records.

The proposed system provides a software-based solution that can:





Track available and occupied parking slots.



Assign suitable slots to vehicles.



Maintain a waiting queue when parking is unavailable.



Automatically assign a freed slot to a waiting vehicle.



Search for parked vehicles.



Maintain parking history.



Store parking information persistently.



Simulate parking sensors.



Exchange status information using Linux FIFO IPC.



Communicate with a Linux character device driver.



Maintain system activity logs.



Provide user-space control of the virtual device through ioctl.





3. Objectives

The main objectives are:





Develop a Linux-based parking management application.



Implement the application using C++.



Apply object-oriented programming concepts.



Use C++ STL data structures and algorithms.



Implement file-based data persistence.



Implement exception handling.



Implement a virtual parking sensor.



Implement a waiting queue for vehicles.



Implement parking history using a linked-list based structure.



Implement Linux FIFO-based IPC.



Implement Linux file-descriptor based logging.



Develop a Linux character device driver.



Implement character-device read() and write() operations.



Implement ioctl operations for device control.



Provide a user-space driver test program.



Provide automated functional tests for core parking functionality.



Demonstrate interaction between user space and kernel space.





4. Functional Requirements



FR1 — Vehicle Parking

The system shall allow the user to enter:





Vehicle number



Owner name



Vehicle type

The system shall assign a compatible available parking slot.





FR2 — Vehicle Removal

The system shall allow a parked vehicle to be removed using its vehicle number.

The corresponding parking slot shall become available.





FR3 — Parking Status

The system shall display:





Total parking slots



Occupied slots



Free slots



Slot number



Vehicle information



Slot type



Sensor status





FR4 — Vehicle Search

The system shall allow the user to search for a vehicle using its vehicle number.





FR5 — Waiting Queue

If no compatible parking slot is available, the vehicle shall be placed in a waiting queue.

The queue shall follow FIFO ordering.





FR6 — Automatic Queue Parking

When a parking slot becomes available, the system shall check the waiting queue and automatically assign the slot to a compatible waiting vehicle.





FR7 — Parking History

The system shall maintain a history of parking operations.

The history shall use a linked-list based structure.





FR8 — Data Persistence

The system shall save parking information to a data file.

Previously stored parking information shall be loaded when the application starts.





FR9 — Virtual Parking Sensor

Each parking slot shall have a software-simulated parking sensor.

The sensor shall maintain an occupied/free state corresponding to the parking slot.





FR10 — Linux Logging

The system shall maintain a Linux log file containing important system events such as:





System startup



Vehicle parking



Vehicle removal



Waiting queue operations



Automatic queue parking

The logger uses Linux file operations and system calls such as open(), write(), and close().





FR11 — FIFO IPC

The system shall provide communication between the main parking application and the IPC monitor using a Linux named FIFO.

The parking application shall send parking status information through:

/tmp/smart_parking_fifo

The separate monitor application shall receive and display the status information.





FR12 — Linux Character Device

The system shall provide a virtual Linux character device through:

/dev/smart_parking

The kernel module shall support:





Device open



Device read



Device write



Device release



Mutex-protected device-buffer access





FR13 — IOCTL Device Control

The character device shall provide ioctl controls for:





Retrieving the current device-buffer size.



Clearing the device buffer.

The interface is defined in:

kernel_driver/parking_ioctl.h

The driver shall return an appropriate error for unsupported ioctl commands.





FR14 — Driver Test Application

A user-space C++ test application shall verify the character device by:





Opening /dev/smart_parking.



Writing test data.



Reading the stored data.



Using ioctl to retrieve buffer size.



Using ioctl to clear the buffer.



Verifying that the buffer size becomes zero.





FR15 — Automated Functional Testing

The project shall include an automated C++ test suite covering core functionality, including:





Vehicle parking.



Vehicle removal.



Waiting queue behavior.



Automatic queue allocation.



Data persistence.



Virtual parking sensor behavior.



Invalid vehicle validation.

The final automated test result is 7 tests passed and 0 tests failed.





5. Non-Functional Requirements



NFR1 — Operating System

The system shall run exclusively on Linux.

NFR2 — Programming Language

The main application shall use C++.

The Linux kernel driver shall use C as required by Linux kernel module development.

NFR3 — Performance

The system shall provide responsive command-line operations for the simulated parking environment.

NFR4 — Reliability

The system shall validate user input and handle file and device-operation errors appropriately.

NFR5 — Maintainability

The system shall use modular source files, classes, functions, and clearly separated application and driver components.

NFR6 — Portability

The application shall target Linux environments with the required C++ compiler and Linux kernel development environment.

NFR7 — Security and Access Control

Operations involving the kernel module and /dev/smart_parking shall follow Linux device permissions and require appropriate privileges where necessary.

NFR8 — Documentation

The project shall maintain documentation covering requirements, architecture, implementation, testing, deployment, UML, and final results.





6. System Modules

The system is divided into the following major modules:







Module



Responsibility





Parking Management



Vehicle and parking-slot operations





Vehicle Management



Vehicle information and validation





Waiting Queue



FIFO management of waiting vehicles





Parking History



Linked-list based parking history





Data Persistence



Saving and loading parking data





Parking Sensor



Virtual slot-occupancy simulation





Linux Logger



System-event logging





FIFO IPC



Application-to-monitor communication





Character Driver



Linux kernel-space virtual device





IOCTL Interface



Device control operations





Driver Test



User-space driver verification





Automated Tests



Core functional validation





7. Data Requirements

The system maintains information related to:





Vehicle number



Owner name



Vehicle type



Parking slot number



Slot type



Occupancy state



Sensor state



Parking history



Waiting vehicles



Device-buffer data

Parking information is persisted using a file-based storage mechanism.





8. Constraints

The project follows these constraints:





The system must run on Linux.



The main application must be implemented in C++.



The kernel driver must be implemented using Linux kernel C interfaces.



No physical parking hardware is required.



Parking sensors are software simulations.



The system is primarily command-line based.



Kernel-driver operations requiring elevated privileges must be executed with appropriate Linux permissions.



The project must use Git/GitHub for version control and documentation.





9. Development Environment

The project is developed and tested in a Linux environment using:





Ubuntu Linux



C++17



GCC/G++



GNU Make



Linux kernel module build tools



Bash



Git/GitHub



GDB for debugging



VS Code Remote-SSH

The project directory contains separate application, driver, test, and documentation components.





10. Development Deliverables

The major project deliverables are:





Working C++ smart parking application.



Virtual parking sensor implementation.



Parking data persistence.



Linux logging implementation.



FIFO IPC monitor.



Linux character-device kernel module.



ioctl interface.



User-space driver test application.



Automated functional test suite.



Make/build scripts.



UML and architecture documentation.



Stage-wise project documentation.



Final testing and validation results.



Git/GitHub repository containing the complete project.





11. Acceptance Criteria

The project shall be considered successfully implemented when:





The application builds successfully using the provided build system.



Vehicles can be parked and removed.



Compatible parking slots are assigned correctly.



Waiting vehicles are handled using FIFO ordering.



Waiting vehicles can be automatically assigned when slots become available.



Parking data can be saved and loaded.



Virtual sensors correctly represent slot occupancy.



Linux logs are generated.



FIFO IPC successfully transfers parking status.



The character driver builds and creates /dev/smart_parking.



Driver read/write operations work correctly.



ioctl buffer-size and clear operations work correctly.



The driver test application completes successfully.



The automated test suite reports 7 passed and 0 failed.



The project documentation is complete and the source code is maintained through Git/GitHub.





12. Conclusion

The requirements define a complete Linux-based smart parking system combining C++ application development, data structures, file handling, virtual sensors, Linux system programming, FIFO IPC, Linux character-device development, ioctl control, automated testing, and user/kernel interaction.

These requirements provide the foundation for the system architecture, implementation, integration, testing, and final deployment described in the subsequent project stages.