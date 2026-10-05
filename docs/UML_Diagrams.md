# UML Diagrams — Linux-Based Smart Parking Management System

This document presents the UML and system architecture diagrams for the Linux-Based Smart Parking Management System.

The diagrams describe the system actors, classes, components, communication flows, data flow, and Linux kernel interaction.

--

# 1. Use Case Diagram

The Use Case Diagram represents the major operations performed by the parking system user and system administrator.

```mermaid
flowchart LR

USER["Parking System User"]

ADMIN["System Administrator"]



PARK["Park Vehicle"]

REMOVE["Remove Vehicle"]

SEARCH["Search Vehicle"]

STATUS["View Parking Status"]

HISTORY["View Parking History"]

QUEUE["Manage Waiting Queue"]

SENSOR["Use Virtual Sensors"]

IPC["Send IPC Status"]

SAVE["Save Parking Data"]

LOAD["Load Parking Data"]

LOG["View System Logs"]

DRIVER["Manage Linux Driver"]

DEVICE["Test Device Communication"]

MONITOR["Monitor IPC Messages"]



USER --> PARK

USER --> REMOVE

USER --> SEARCH

USER --> STATUS

USER --> HISTORY

USER --> QUEUE

USER --> SENSOR

USER --> IPC



ADMIN --> SAVE

ADMIN --> LOAD

ADMIN --> LOG

ADMIN --> DRIVER

ADMIN --> DEVICE

ADMIN --> MONITOR
```

### Main Use Cases

 Actor | Use Case | Description |

---|---|---|

 User | Park Vehicle | Parks a vehicle in a compatible available slot |

 User | Remove Vehicle | Removes a vehicle from its parking slot |

 User | Search Vehicle | Searches for a vehicle in the system |

 User | View Parking Status | Displays occupied and available slots |

 User | View Parking History | Displays previous parking records |

 User | Manage Waiting Queue | Maintains vehicles waiting for available slots |

 User | Use Virtual Sensors | Simulates parking slot occupancy |

 User | Send IPC Status | Sends system status through FIFO IPC |

 Administrator | Save Parking Data | Saves parking information to persistent storage |

 Administrator | Load Parking Data | Loads previously saved parking information |

 Administrator | View System Logs | Reviews Linux system activity logs |

 Administrator | Manage Linux Driver | Builds, loads and unloads the kernel driver |

 Administrator | Test Device Communication | Tests the character device |

 Administrator | Monitor IPC Messages | Receives messages from the parking application |



# 2. Class Diagram

The Class Diagram represents the major C++ classes and their relationships.

```mermaid
classDiagram

class Vehicle {

    string number

    string owner

    string type

}



class ParkingSlot {

    int slotNumber

    string slotType

    bool occupied

    parkVehicle()

    removeVehicle()

    isAvailable()

}



class HistoryNode {

    Vehicle vehicle

    int slotNumber

    HistoryNode next

}



class ParkingSystem {

    vector slots

    queue waitingQueue

    HistoryNode historyHead

    parkVehicle()

    removeVehicle()

    searchVehicle()

    displayStatus()

    displayHistory()

    saveData()

    loadData()

    processWaitingQueue()

}



class ParkingSensor {

    int sensorId

    int slotNumber

    bool occupied

    detectVehicle()

    clearVehicle()

    toggle()

    setOccupied()

    getStatus()

    displaySensor()

}



class ParkingIPC {

    string fifoPath

    createFIFO()

    sendStatus()

    receiveStatus()

}



class LinuxLogger {

    string logFile

    logInfo()

    logError()

    writeLog()

}



class DriverTest {

    openDevice()

    writeToDriver()

    readFromDriver()

    closeDevice()

}



ParkingSystem --> ParkingSlot

ParkingSystem --> Vehicle

ParkingSystem --> HistoryNode

ParkingSystem --> ParkingSensor

ParkingSystem --> ParkingIPC

ParkingSystem --> LinuxLogger

DriverTest --> ParkingIPC

ParkingSlot --> Vehicle

HistoryNode --> HistoryNode
```

## Class Responsibilities

### Vehicle

Stores vehicle information:

 Vehicle number

 Owner name

 Vehicle type

### ParkingSlot

Represents an individual parking slot.

The system contains:

 Slots 1 to 3 for cars

 Slots 4 to 5 for bikes

### ParkingSystem

The main C++ class responsible for:

 Parking vehicles

 Removing vehicles

 Searching vehicles

 Managing slots

 Managing the waiting queue

 Maintaining parking history

 Saving data

 Loading data

### HistoryNode

Represents a node in the linked-list based parking history.

### ParkingSensor

Provides virtual parking sensor functionality.

### ParkingIPC

Implements FIFO-based inter-process communication.

### LinuxLogger

Provides Linux file-descriptor based logging.

### DriverTest

Tests communication with the Linux character device.



# 3. Component and System Architecture

The following diagram represents the overall system architecture.

```mermaid
flowchart TB

USER["User"]



MAIN["Smart Parking Application"]

SYSTEM["ParkingSystem"]

SLOTS["Parking Slots"]

VEHICLE["Vehicle Management"]

QUEUE["Waiting Queue"]

HISTORY["Parking History"]

SENSOR["Virtual Parking Sensors"]

LOGGER["Linux Logger"]

IPCMODULE["Parking IPC"]

MONITOR["Parking Monitor"]

TEST["Driver Test Program"]



DATA["parking_data.txt"]

LOGFILE["parking.log"]

FIFO["smart parking FIFO"]



DEVICE["smart parking Device"]

DRIVER["Linux Character Driver"]

KERNEL["Linux Kernel"]



USER --> MAIN

MAIN --> SYSTEM



SYSTEM --> SLOTS

SYSTEM --> VEHICLE

SYSTEM --> QUEUE

SYSTEM --> HISTORY

SYSTEM --> SENSOR

SYSTEM --> LOGGER

SYSTEM --> IPCMODULE



SYSTEM --> DATA

LOGGER --> LOGFILE



IPCMODULE --> FIFO

FIFO --> MONITOR



TEST --> DEVICE

DEVICE --> DRIVER

DRIVER --> KERNEL
```

## Architecture Layers

### User Space

The user-space layer contains the main C++ application and supporting programs.

text

main.cpp

parking_system.cpp

parking_sensor.cpp

parking_ipc.cpp

linux_logger.cpp

parking_monitor.cpp

parking_driver_test.cpp



### Persistent Storage

The project uses files for persistent storage and logging.

text

parking_data.txt

parking.log



### IPC Layer

The main application communicates with the separate monitoring process using a Linux named FIFO.

text

/tmp/smart_parking_fifo



### Kernel Space

The Linux character device driver provides the kernel-level device interface.

text

parking_driver.ko

    |

    v

/dev/smart_parking





# 4. Vehicle Parking Sequence Diagram

This sequence shows the major operations performed when a vehicle is parked.

```mermaid
sequenceDiagram

actor User

participant Main as Main Application

participant System as ParkingSystem

participant Slot as ParkingSlot

participant Sensor as ParkingSensor

participant Logger as LinuxLogger

participant Data as Parking Data



User->>Main: Select Park Vehicle

Main->>System: parkVehicle

System->>System: Validate vehicle

System->>Slot: Find compatible slot



alt Slot available

    Slot-->>System: Available slot

    System->>Slot: Park vehicle

    System->>Sensor: Set occupied

    Sensor-->>System: Occupied

    System->>Logger: Log parking event

    System->>Data: Save parking data

    System-->>Main: Parking successful

    Main-->>User: Display assigned slot
```

else No slot available

    System->>System: Add vehicle to queue

    System->>Logger: Log queue event

    System-->>Main: Vehicle queued

    Main-->>User: Display queue message

end







# 5. Vehicle Removal Sequence Diagram

This sequence represents vehicle removal and waiting queue processing.

```mermaid
sequenceDiagram

actor User

participant Main as Main Application

participant System as ParkingSystem

participant Slot as ParkingSlot

participant Sensor as ParkingSensor

participant Queue as Waiting Queue

participant Logger as LinuxLogger

participant Data as Parking Data



User->>Main: Select Remove Vehicle

Main->>System: removeVehicle

System->>Slot: Search vehicle



alt Vehicle found

    Slot-->>System: Vehicle found

    System->>Slot: Remove vehicle

    System->>Sensor: Clear sensor

    Sensor-->>System: Slot free

    System->>System: Add record to history

    System->>Queue: Check waiting queue



    alt Waiting vehicle exists

        Queue-->>System: Waiting vehicle

        System->>Slot: Assign available slot

        System->>Sensor: Set occupied

        System->>Logger: Log automatic allocation

    else Queue empty

        System->>System: Keep slot available

    end



    System->>Logger: Log removal

    System->>Data: Save updated data

    System-->>Main: Removal successful

    Main-->>User: Display updated status
```

else Vehicle not found

    System-->>Main: Vehicle not found

    Main-->>User: Display error

end





# 6. FIFO IPC Sequence Diagram

This sequence represents communication between the main parking application and the monitoring process.

```mermaid
sequenceDiagram

participant Main as Smart Parking Application

participant IPC as ParkingIPC

participant FIFO as Linux FIFO

participant Monitor as Parking Monitor



Monitor->>FIFO: Open FIFO for reading

Main->>IPC: Send parking status

IPC->>FIFO: Write status message

FIFO-->>Monitor: Status message

Monitor->>Monitor: Display message
```

Example message:

text

SMART PARKING STATUS

Total Slots=5

Occupied=0

Free=5

Waiting=0





# 7. Linux Character Device Driver Sequence Diagram

This sequence represents communication between the user-space driver test program and the Linux kernel driver.

```mermaid
sequenceDiagram

participant Test as Driver Test Program

participant Device as Smart Parking Device

participant Driver as Linux Character Driver

participant Kernel as Linux Kernel



Test->>Device: open

Device->>Driver: Open request

Driver->>Kernel: Access driver buffer



Test->>Device: write

Device->>Driver: Write request

Driver->>Kernel: Copy data from user

Kernel-->>Driver: Data stored



Test->>Device: read

Device->>Driver: Read request

Driver->>Kernel: Copy data to user

Kernel-->>Driver: Data returned



Device-->>Test: Driver data

Test->>Device: close

Device->>Driver: Release
```



# 8. System Data Flow

The following diagram represents the overall data flow.

```mermaid
flowchart LR

INPUT["User Input"]

VALIDATE["Input Validation"]

SYSTEM["ParkingSystem"]

SLOTS["Parking Slots"]

QUEUE["Waiting Queue"]

HISTORY["Parking History"]

SENSOR["Virtual Sensors"]

DATA["Parking Data"]

LOGGER["Linux Logger"]

LOGFILE["System Log"]

IPC["FIFO IPC"]

MONITOR["Parking Monitor"]



INPUT --> VALIDATE

VALIDATE --> SYSTEM



SYSTEM --> SLOTS

SYSTEM --> QUEUE

SYSTEM --> HISTORY

SYSTEM --> SENSOR

SYSTEM --> DATA

SYSTEM --> LOGGER

LOGGER --> LOGFILE

SYSTEM --> IPC

IPC --> MONITOR
```



# 9. Linux Kernel Interaction

The project demonstrates communication between user space and kernel space using a Linux character device driver.

```mermaid
flowchart TB

APP["User Space Application"]

TEST["Driver Test Program"]

DEVICE["Smart Parking Device"]

DRIVER["Linux Character Driver"]

KERNEL["Linux Kernel"]

SYSTEM["Linux System"]



APP --> TEST

TEST --> DEVICE

DEVICE --> DRIVER

DRIVER --> KERNEL

KERNEL --> SYSTEM
```

The character driver provides:

 Character device registration

 Major and minor device numbers

 Open operation

 Read operation

 Write operation

 Release operation

 Kernel logging

 User-space and kernel-space data transfer

 Mutex protection

The device is exposed to user space as:

text

/dev/smart_parking



The kernel module is:

text

parking_driver.ko





# 10. Overall System Workflow

```mermaid
flowchart TD

START["Start System"]

LOAD["Load Parking Data"]

MENU["Display Main Menu"]

INPUT["User Selects Operation"]

VALIDATE["Validate Input"]

PARK["Park Vehicle"]

REMOVE["Remove Vehicle"]

SEARCH["Search Vehicle"]

STATUS["View Status"]

HISTORY["View History"]

QUEUE["Process Waiting Queue"]

SENSOR["Update Virtual Sensor"]

SAVE["Save Data"]

EXIT["Exit System"]



START --> LOAD

LOAD --> MENU

MENU --> INPUT

INPUT --> VALIDATE



VALIDATE --> PARK

VALIDATE --> REMOVE

VALIDATE --> SEARCH

VALIDATE --> STATUS

VALIDATE --> HISTORY

VALIDATE --> QUEUE

VALIDATE --> SENSOR



PARK --> SAVE

REMOVE --> SAVE

QUEUE --> SAVE

SENSOR --> SAVE



SAVE --> MENU

SEARCH --> MENU

STATUS --> MENU

HISTORY --> MENU



INPUT --> EXIT
```



# 11. Linux Device Driver Workflow

```mermaid
flowchart LR

SOURCE["parking_driver.c"]

BUILD["Kernel Module Build"]

MODULE["parking_driver.ko"]

LOAD["insmod"]

DEVICE["Smart Parking Device"]

TEST["Driver Test Program"]

READ["read"]

WRITE["write"]

UNLOAD["rmmod"]



SOURCE --> BUILD

BUILD --> MODULE

MODULE --> LOAD

LOAD --> DEVICE

DEVICE --> TEST

TEST --> READ

TEST --> WRITE

DEVICE --> UNLOAD
```



**# 12. IOCTL Device-Control Design

The Linux character-device driver provides an ioctl interface defined in:

kernel_driver/parking_ioctl.h

The supported commands are:







IOCTL Command



Purpose





SMART_PARKING_IOCTL_GET_BUFFER_SIZE



Returns the current device-buffer size





SMART_PARKING_IOCTL_CLEAR_BUFFER



Clears the device buffer and resets its size

The driver test program verifies both commands after performing a device write and read operation.

The final IOCTL test result was:

Buffer size: 36 bytes
Buffer size after clear: 0 bytes
IOCTL TEST SUCCESSFUL





14. Automated Testing Architecture

The project includes a dedicated automated C++ test suite for validating core parking functionality.

Test file:

tests/test_parking_system.cpp

The automated suite covers:





Vehicle parking.



Vehicle removal.



Waiting queue behavior.



Automatic waiting-queue allocation.



Data persistence.



Virtual parking sensor behavior.



Invalid vehicle validation.

Final result:

Passed : 7
Failed : 0
ALL TESTS PASSED

The automated tests validate the application layer independently from the kernel-driver test application.





13. Project Data Structures**

The project uses multiple data structures.

 Data Structure | Usage |

---|---|

 Vector | Stores parking slots |

 Queue | Stores vehicles waiting for parking |

 Linked List | Stores parking history |

 Smart Pointer | Manages dynamic vehicle objects |

 Strings | Stores vehicle and owner information |

### Vector

Parking slots are maintained using a C++ vector.

text

ParkingSystem

  |

  +---- Slot 1

  +---- Slot 2

  +---- Slot 3

  +---- Slot 4

  +---- Slot 5



### Queue

Vehicles that cannot immediately be parked are placed into the waiting queue.

text

Front

  |

  v

Vehicle A -> Vehicle B -> Vehicle C

                          |

                         Rear



### Linked List

Parking history is maintained using linked-list nodes.

text

History Head

 |

 v

+---------+     +---------+     +---------+

 Vehicle | --> | Vehicle | --> | Vehicle |

+---------+     +---------+     +---------+



--

# 14. Linux User Space and Kernel Space

```mermaid
flowchart TB

subgraph USERSPACE["USER SPACE"]

    APP["Smart Parking Application"]

    DRIVERTEST["Driver Test Program"]

    MONITOR["Parking Monitor"]

end



subgraph KERNELSPACE["KERNEL SPACE"]

    DRIVER["Linux Character Driver"]

    KERNEL["Linux Kernel"]

end



APP --> DRIVERTEST

DRIVERTEST --> DRIVER

DRIVER --> KERNEL

APP --> MONITOR
```

The architecture separates normal application execution from privileged kernel-level driver execution.



# 15. Training Concepts Demonstrated

The project demonstrates the following training concepts.

## C++

 Classes and objects

 Encapsulation

 STL containers

 Vector

 Queue

 Smart pointers

 Linked lists

 File handling

 Exception handling

 Modular programming

## Linux System Programming

 Linux file descriptors

 File operations

 open

 read

 write

 close

 FIFO IPC

 Process communication

 Linux logging

 User space and kernel space

## Linux Device Drivers

 Kernel modules

 Character devices

 Major and minor numbers

 Device files

 cdev

 open

 read

 write

 release

 copy_to_user

 copy_from_user

 Mutex protection

 insmod

 rmmod

 lsmod

## Data Structures

 Vector

 Queue

 Linked list

 Searching

 Dynamic memory

 Smart pointers

## Operating Systems and Computer Architecture

 User space

 Kernel space

 System calls

 File descriptors

 Memory protection

 Device abstraction

 Kernel interface

--

# 16. UML and Architecture Summary

 Diagram | Purpose |

---|---|

 Use Case Diagram | Shows system actors and operations |

 Class Diagram | Shows C++ classes and relationships |

 Component Architecture | Shows system components and layers |

 Parking Sequence | Shows vehicle parking workflow |

 Removal Sequence | Shows vehicle removal workflow |

 FIFO IPC Sequence | Shows inter-process communication |

 Driver Sequence | Shows user-space and kernel communication |

 Data Flow | Shows system information flow |

 Kernel Interaction | Shows Linux driver architecture |

 Overall Workflow | Shows application execution flow |

 Driver Workflow | Shows driver build and execution |

 Data Structure Diagram | Shows vector, queue and linked list usage |

 User/Kernel Diagram | Shows Linux privilege separation |

--

# 17. Conclusion

The Linux-Based Smart Parking Management System integrates application-level programming with Linux system programming and kernel-level device-driver concepts.

The overall architecture can be summarized as:

text

C++ Application

   |

   +-- Object-Oriented Programming

   |

   +-- STL Data Structures

   |

   +-- File Handling

   |

   +-- Virtual Parking Sensors

   |

   +-- Linux Logging

   |

   +-- FIFO IPC

   |

   +-- Driver Test Program

   |

   +-- /dev/smart_parking

   |

   +-- Linux Character Device Driver

   |

   +-- Linux Kernel



The UML diagrams provide a complete design representation of the project's functional behavior, software structure, communication mechanisms, data flow, and Linux kernel interaction.
