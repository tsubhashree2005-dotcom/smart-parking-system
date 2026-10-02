#ifndef PARKING_SYSTEM_H
#define PARKING_SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <cctype>
#include <limits>

#include "parking_sensor.h"
#include "linux_logger.h"
#include "parking_ipc.h"

using namespace std;

// ============================================================
// VEHICLE
// ============================================================

struct Vehicle {
    string vehicleNumber;
    string ownerName;
    string vehicleType;
};

// ============================================================
// PARKING SLOT
// ============================================================

struct ParkingSlot {
    int slotNumber;
    string slotType;
    bool occupied;
    shared_ptr<Vehicle> vehicle;

    ParkingSlot(
        int number,
        const string& type
    )
        : slotNumber(number),
          slotType(type),
          occupied(false),
          vehicle(nullptr) {}
};

// ============================================================
// PARKING HISTORY LINKED LIST NODE
// ============================================================

struct HistoryNode {
    string vehicleNumber;
    int slotNumber;
    string action;
    HistoryNode* next;

    HistoryNode(
        string vehicle,
        int slot,
        string act
    )
        : vehicleNumber(vehicle),
          slotNumber(slot),
          action(act),
          next(nullptr) {}
};

// ============================================================
// PARKING SYSTEM CLASS
// ============================================================

class ParkingSystem {

private:

    vector<ParkingSlot> slots;

    // Software-simulated parking sensors
    vector<ParkingSensor> sensors;

    // FIFO waiting queue
    queue<Vehicle> waitingQueue;

    // Linked list for parking history
    HistoryNode* historyHead;

    // Persistent data file
    string dataFile;

    // Linux system-call based event logger
    LinuxLogger logger;

    // Linux FIFO-based inter-process communication
    ParkingIPC ipc;

    // --------------------------------------------------------
    // Internal helper functions
    // --------------------------------------------------------

    int findFreeSlot(
        const string& vehicleType
    ) const;

    int findVehicleSlot(
        const string& vehicleNumber
    ) const;

    ParkingSensor* findSensorForSlot(
        int slotNumber
    );

    const ParkingSensor* findSensorForSlot(
        int slotNumber
    ) const;

    void addHistory(
        const string& vehicleNumber,
        int slotNumber,
        const string& action
    );

    bool isValidVehicleNumber(
        const string& vehicleNumber
    ) const;

    string normalizeVehicleType(
        const string& vehicleType
    ) const;

    bool isValidVehicleType(
        const string& vehicleType
    ) const;

public:

    // --------------------------------------------------------
    // Constructor / Destructor
    // --------------------------------------------------------

    ParkingSystem(
        int totalSlots,
        const string& fileName
    );

    ~ParkingSystem();

    // --------------------------------------------------------
    // Parking operations
    // --------------------------------------------------------

    void parkVehicle(
        const Vehicle& vehicle
    );

    void removeVehicle(
        const string& vehicleNumber
    );

    // --------------------------------------------------------
    // Display operations
    // --------------------------------------------------------

    void displayParkingStatus() const;

    void searchVehicle(
        const string& vehicleNumber
    ) const;

    void displayWaitingQueue();

    void displayHistory() const;

    // --------------------------------------------------------
    // File operations
    // --------------------------------------------------------

    void saveData() const;

    void loadData();

    // --------------------------------------------------------
    // Main menu
    // --------------------------------------------------------

    // Send a parking-system status message through the Linux FIFO.
    void sendStatusViaIPC() const;

    void run();
};

#endif
