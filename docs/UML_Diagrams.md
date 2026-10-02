# UML Diagrams — Linux-Based Smart Parking Management System

## 1. Use Case Diagram

```mermaid
flowchart LR

    User([Parking System User])
    Admin([System Administrator])

    subgraph System[Linux-Based Smart Parking Management System]

        UC1((Park Vehicle))
        UC2((Remove Vehicle))
        UC3((Display Parking Status))
        UC4((Search Vehicle))
        UC5((Display Waiting Queue))
        UC6((Display Parking History))
        UC7((Save Parking Data))
        UC8((Send Status via FIFO IPC))
        UC9((Monitor Parking Status))
        UC10((Read Parking Sensor))
        UC11((Write System Log))
        UC12((Communicate with Character Driver))

    end

    User --> UC1
    User --> UC2
    User --> UC3
    User --> UC4
    User --> UC5
    User --> UC6
    User --> UC7
    User --> UC8

    Admin --> UC9
    Admin --> UC12

    UC1 --> UC10
    UC2 --> UC10
    UC1 --> UC11
    UC2 --> UC11
    UC5 --> UC11
    UC8 --> UC9
    UC12 --> UC11

---

## 2. Class Diagram

```mermaid
classDiagram

    class Vehicle {
        +string vehicleNumber
        +string ownerName
        +string vehicleType
    }

    class ParkingSlot {
        +int slotNumber
        +string slotType
        +bool occupied
        +Vehicle vehicle
    }

    class HistoryNode {
        +Vehicle vehicle
        +int slotNumber
        +HistoryNode* next
    }

    class ParkingSensor {
        -int sensorId
        -int slotNumber
        -bool occupied
        +detectVehicle()
        +clearVehicle()
        +toggle()
        +setOccupied()
        +getSensorId()
        +getSlotNumber()
        +isOccupied()
        +getStatus()
        +display()
    }

    class LinuxLogger {
        -string logFile
        +LinuxLogger()
        +LinuxLogger(string)
        +log(string)
    }

    class ParkingIPC {
        +createFIFO()
        +sendMessage(string)
        +receiveMessage()
        +removeFIFO()
    }

    class ParkingSystem {
        -vector~ParkingSlot~ slots
        -vector~ParkingSensor~ sensors
        -queue~Vehicle~ waitingQueue
        -HistoryNode* historyHead
        -string dataFile
        -LinuxLogger logger

        +ParkingSystem(int, string)
        +~ParkingSystem()
        +parkVehicle()
        +removeVehicle()
        +displayStatus()
        +searchVehicle()
        +displayWaitingQueue()
        +displayHistory()
        +saveData()
        +loadData()
        +sendStatusViaIPC()
        +findVehicleSlot()
        +findSensorForSlot()
        +isValidVehicleNumber()
    }

    ParkingSystem "1" *-- "many" ParkingSlot
    ParkingSystem "1" *-- "many" ParkingSensor
    ParkingSystem "1" *-- "many" Vehicle
    ParkingSystem "1" *-- "many" HistoryNode
    ParkingSystem --> LinuxLogger
    ParkingSystem --> ParkingIPC

    ParkingSlot --> Vehicle
    HistoryNode --> Vehicle
    HistoryNode --> HistoryNode
    ParkingSensor --> ParkingSlot

---

## 3. Component / System Architecture Diagram

```mermaid
flowchart TB

    User[Parking System User]

    subgraph UserSpace[USER SPACE]

        Main[Main C++ Application]

        PS[ParkingSystem]
        Sensor[ParkingSensor]
        Logger[LinuxLogger]
        IPC[ParkingIPC]
        Monitor[IPC Monitor]
        DriverTest[Driver Test Program]

        Main --> PS
        PS --> Sensor
        PS --> Logger
        PS --> IPC

        IPC -->|Named FIFO| Monitor

    end

    subgraph KernelSpace[KERNEL SPACE]

        Driver[Linux Character Device Driver]
        Device[/dev/smart_parking]

        Driver --> Device

    end

    PS -->|System Calls| Device
    DriverTest -->|open / read / write| Device

    User --> Main

    style UserSpace fill:none
    style KernelSpace fill:none

---

## 4. Sequence Diagram — Vehicle Parking

```mermaid
sequenceDiagram

    actor User
    participant Main as Main Application
    participant PS as ParkingSystem
    participant Sensor as ParkingSensor
    participant Logger as LinuxLogger
    participant IPC as ParkingIPC
    participant Monitor as IPC Monitor

    User->>Main: Select Park Vehicle
    Main->>PS: parkVehicle()

    PS->>PS: Validate vehicle details
    PS->>PS: Find compatible free slot

    alt Free slot available

        PS->>PS: Assign vehicle to slot
        PS->>Sensor: setOccupied(true)
        Sensor-->>PS: Sensor status updated

        PS->>Logger: log("Vehicle parked")
        Logger-->>PS: Log written

        PS->>IPC: sendMessage(parking status)
        IPC->>Monitor: Write status through FIFO
        Monitor-->>IPC: Status received

        PS-->>Main: Parking successful
        Main-->>User: Display parking details

    else No compatible slot

        PS->>PS: Add vehicle to waiting queue
        PS->>Logger: log("Vehicle added to queue")
        Logger-->>PS: Log written

        PS-->>Main: Vehicle queued
        Main-->>User: Display queue message

    end

