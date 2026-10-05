Stage 3 — System Design and Architecture

1. Introduction

This stage defines the detailed architecture and internal design of the Linux-Based Smart Parking Management System.

The system is designed as a modular Linux application consisting of:





C++ parking-management software.



Virtual parking sensors.



Linux system-call based logging.



FIFO-based inter-process communication.



A separate IPC monitoring process.



A Linux kernel character-device driver.



An ioctl interface for device control.



A user-space driver test program.



An automated C++ test suite.

The main parking application operates in user space. The character-device driver operates in kernel space and is accessed through /dev/smart_parking by the dedicated driver test program.





2. System Architecture

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

The architecture separates the normal parking application from the kernel-space driver. The main application manages parking operations, while the dedicated driver test application verifies the virtual character device.





3. Architectural Layers



3.1 User Interface Layer

The command-line interface is implemented through the main C++ application.

Responsibilities:





Display menu options.



Accept user input.



Validate input.



Invoke parking-system operations.



Display parking status and results.

Main file:

src/main.cpp



3.2 Parking Management Layer

The ParkingSystem component contains the main parking-management logic.

Responsibilities:





Manage parking slots.



Park vehicles.



Remove vehicles.



Search vehicles.



Manage the waiting queue.



Automatically allocate freed slots.



Maintain parking history.



Save and load parking data.

Main files:

src/parking_system.cpp
src/parking_system.h



3.3 Sensor Layer

The virtual sensor component simulates parking-slot occupancy.

Responsibilities:





Maintain sensor ID.



Maintain slot number.



Track occupied/free state.



Detect and clear occupancy.



Toggle sensor state.



Display sensor information.

Files:

src/parking_sensor.cpp
src/parking_sensor.h



3.4 Logging Layer

The Linux logger records important system events using Linux file operations/system calls.

Responsibilities:





Open the log file.



Write event messages.



Close the file.



Record parking-related operations.

Files:

src/linux_logger.cpp
src/linux_logger.h

Output:

parking.log



3.5 IPC Layer

The IPC component provides communication between the main application and the monitoring application through a Linux named FIFO.

Files:

src/parking_ipc.cpp
src/parking_ipc.h
src/parking_monitor.cpp

FIFO:

/tmp/smart_parking_fifo



3.6 Kernel Driver Layer

The Linux character driver provides a virtual device interface.

Files:

kernel_driver/parking_driver.c
kernel_driver/parking_ioctl.h

Device:

/dev/smart_parking

The driver supports:





open()



read()



write()



release()



ioctl()

A mutex protects access to the device buffer.

3.7 Driver Test Layer

The user-space driver test program verifies communication with the kernel driver.

File:

src/parking_driver_test.cpp

It verifies:





write()



read()



ioctl(GET_BUFFER_SIZE)



ioctl(CLEAR_BUFFER)



3.8 Automated Testing Layer

The automated test suite validates important application functionality.

File:

tests/test_parking_system.cpp

The test suite covers:





Vehicle parking.



Vehicle removal.



Waiting queue.



Automatic queue allocation.



Data persistence.



Virtual parking sensor.



Invalid vehicle validation.

Final result:

Passed : 7
Failed : 0
ALL TESTS PASSED





4. Major Components and Responsibilities







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



Receives and displays IPC status





LinuxLogger



Linux-based event logging





parking_driver.c



Linux character-device driver





parking_ioctl.h



IOCTL command definitions





parking_driver_test.cpp



User-space driver testing





test_parking_system.cpp



Automated functional tests





5. Data Structures

The system uses C++ STL and pointer-based data structures.

5.1 Vector

Parking slots are managed using a vector:

vector<ParkingSlot>

It provides indexed access to the parking slots.

5.2 Queue

Waiting vehicles are maintained using:

queue<Vehicle>

The queue follows FIFO ordering.

5.3 Linked List

Parking history is represented using linked-list nodes.

Conceptually:

Head
 |
 v
[HistoryNode] -> [HistoryNode] -> [HistoryNode] -> NULL



5.4 Shared Pointer

Vehicle-related dynamic objects can use:

shared_ptr<Vehicle>

This demonstrates managed dynamic memory.





6. Parking Slot Design

The parking facility contains five simulated slots.

The slots are divided according to vehicle compatibility:

Slot 1 -> CAR
Slot 2 -> CAR
Slot 3 -> CAR
Slot 4 -> BIKE
Slot 5 -> BIKE

A vehicle is assigned only to a compatible free slot.





7. Parking Workflow

The parking workflow is:

User enters vehicle information
            |
            v
      Validate input
            |
            v
 Find compatible free slot
       /          \
     Found       Not Found
       |             |
       v             v
 Assign slot     Add to queue
       |             |
       v             v
 Update sensor    Wait for slot
       |
       v
 Save data + log event

When a slot becomes available:

Vehicle removed
      |
      v
Slot becomes free
      |
      v
Check waiting queue
      |
      v
Find compatible waiting vehicle
      |
      v
Assign slot automatically
      |
      v
Update sensor + save + log





8. Character Device Architecture

The Linux character-device architecture is:

User-space driver test
          |
          | open()
          | write()
          | read()
          | ioctl()
          v
 /dev/smart_parking
          |
          v
 Character-device driver
          |
          v
 Device buffer
          |
          v
 Kernel space

The driver uses Linux kernel interfaces for device registration and user/kernel data transfer.

Important driver components include:





alloc_chrdev_region()



cdev_init()



cdev_add()



class_create()



device_create()



copy_to_user()



copy_from_user()



mutex



unlocked_ioctl





9. IOCTL Design

The IOCTL interface is defined in:

kernel_driver/parking_ioctl.h

The project defines two device-control commands:

SMART_PARKING_IOCTL_GET_BUFFER_SIZE
SMART_PARKING_IOCTL_CLEAR_BUFFER



GET_BUFFER_SIZE

Returns the current number of bytes stored in the device buffer.

CLEAR_BUFFER

Clears the device buffer and resets its stored size to zero.

Unsupported IOCTL commands return an appropriate Linux error.





10. User Space and Kernel Space Separation

The project demonstrates the separation between:

USER SPACE
--------------------------------
main C++ application
IPC monitor
driver test application
automated tests
--------------------------------
            |
            | system calls / device interface
            v
KERNEL SPACE
--------------------------------
Linux character-device driver
device buffer
kernel synchronization
--------------------------------

The normal parking application does not directly communicate with /dev/smart_parking. The dedicated parking_driver_test program is responsible for demonstrating the user-space to kernel-space device interaction.





11. File and Data Flow



Parking Data

ParkingSystem
     |
     v
parking_data.txt



Logging

LinuxLogger
     |
     v
parking.log



IPC

ParkingSystem
     |
     v
/tmp/smart_parking_fifo
     |
     v
parking_monitor



Character Device

parking_driver_test
     |
     v
/dev/smart_parking
     |
     v
parking_driver.ko





12. Process and IPC Design

The project uses separate user-space processes for the main application and monitoring application.

The communication flow is:

Main Application
      |
      | write()
      v
Named FIFO
      |
      | read()
      v
IPC Monitor

The FIFO allows status information to be transferred without directly coupling the two applications.





13. Error Handling Design

The system uses validation and error handling for:





Invalid vehicle numbers.



Invalid owner names.



Invalid vehicle types.



Full parking capacity.



File-operation failures.



Device-operation failures.



Unsupported IOCTL commands.

C++ exception handling is used where appropriate for application-level errors.

Linux system calls and driver operations return error codes that are checked by the corresponding components.





14. Build and Development Architecture

The project uses GNU Make for compilation.

The root Makefile builds:

smart_parking
parking_monitor
parking_driver_test

The kernel-driver Makefile builds:

parking_driver.ko

The development workflow is:

Source Code
    |
    v
GNU Make
    |
    +----> C++ Executables
    |
    +----> Kernel Module
    |
    v
Testing
    |
    v
Documentation
    |
    v
Git/GitHub





15. Project Directory Architecture

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
+-- Makefile
+-- build.sh
+-- run.sh
+-- README.md
+-- parking_data.txt

Generated object files, executables, kernel build artifacts, and runtime log files are excluded from version control where appropriate through .gitignore.





16. UML and Design Model

The system design is represented using UML and architecture diagrams covering:





System components.



Classes and responsibilities.



Parking workflow.



IPC communication.



Character-device interaction.



User-space/kernel-space separation.



Testing structure.

The UML documentation is maintained separately in:

docs/UML_Diagrams.md





17. Security and Synchronization Considerations

The character driver protects its shared device buffer using a Linux mutex.

User-space access to the device follows Linux file permissions.

The driver uses safe kernel/user-space data transfer mechanisms such as:

copy_to_user()
copy_from_user()

The project therefore demonstrates basic synchronization and safe boundary crossing between user space and kernel space.





18. Design Outcome

The final architecture provides a clear separation between:





User interaction.



Parking-management logic.



Data structures.



Virtual sensors.



File persistence.



Linux logging.



FIFO IPC.



Kernel device functionality.



IOCTL control.



Automated testing.

This modular design improves maintainability, testing, debugging, and demonstration of the Linux and C++ concepts covered during the training.





19. Conclusion

The system architecture integrates C++ object-oriented programming, STL data structures, file handling, Linux system calls, FIFO IPC, virtual sensors, Linux logging, character-device development, ioctl, kernel/user-space interaction, and automated testing.

The architecture provides the foundation for the implementation, testing, deployment, and final demonstration stages of the Linux-Based Smart Parking Management System.