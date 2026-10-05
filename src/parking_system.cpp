#include "parking_system.h"

#include <cctype>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

// ============================================================
// CONSTRUCTOR
// ============================================================

ParkingSystem::ParkingSystem(int totalSlots, const string& fileName)
    : historyHead(nullptr), dataFile(fileName), logger("parking.log"), ipc("/tmp/smart_parking_fifo")
{
    if (totalSlots <= 0) {
        throw invalid_argument(
            "Number of parking slots must be greater than zero."
        );
    }

    // Slots 1-3 are CAR slots.
    // Remaining slots are BIKE slots.
    for (int i = 1; i <= totalSlots; ++i) {
        if (i <= 3) {
            slots.emplace_back(i, "CAR");
        } else {
            slots.emplace_back(i, "BIKE");
        }

        // One software-simulated sensor per parking slot.
        sensors.emplace_back(i, i);
    }

    loadData();

    // Synchronize software sensor states with loaded parking data.
    for (auto& sensor : sensors) {
        const int slotNumber = sensor.getSlotNumber();

        if (slotNumber >= 1 &&
            slotNumber <= static_cast<int>(slots.size())) {
            sensor.setOccupied(
                slots[slotNumber - 1].occupied
            );
        }
    }

    logger.log("Smart Parking System started.");
}

// ============================================================
// DESTRUCTOR
// ============================================================

ParkingSystem::~ParkingSystem()
{
    HistoryNode* current = historyHead;

    while (current != nullptr) {
        HistoryNode* next = current->next;
        delete current;
        current = next;
    }
}

// ============================================================
// NORMALIZE VEHICLE TYPE
// ============================================================

string ParkingSystem::normalizeVehicleType(const string& vehicleType) const
{
    string normalized = vehicleType;

    for (char& ch : normalized) {
        ch = static_cast<char>(
            toupper(static_cast<unsigned char>(ch))
        );
    }

    return normalized;
}

// ============================================================
// VALIDATE VEHICLE TYPE
// ============================================================

bool ParkingSystem::isValidVehicleType(const string& vehicleType) const
{
    const string normalized = normalizeVehicleType(vehicleType);

    return normalized == "CAR" || normalized == "BIKE";
}

// ============================================================
// FIND FREE SLOT
// ============================================================

int ParkingSystem::findFreeSlot(const string& vehicleType) const
{
    const string normalizedType = normalizeVehicleType(vehicleType);

    for (const auto& slot : slots) {
        if (!slot.occupied &&
            slot.slotType == normalizedType) {
            return slot.slotNumber;
        }
    }

    return -1;
}

// ============================================================
// FIND VEHICLE SLOT
// ============================================================

int ParkingSystem::findVehicleSlot(
    const string& vehicleNumber
) const
{
    for (const auto& slot : slots) {
        if (slot.occupied &&
            slot.vehicle != nullptr &&
            slot.vehicle->vehicleNumber == vehicleNumber) {
            return slot.slotNumber;
        }
    }

    return -1;
}

// ============================================================
// FIND SENSOR FOR SLOT
// ============================================================

ParkingSensor* ParkingSystem::findSensorForSlot(int slotNumber)
{
    for (auto& sensor : sensors) {
        if (sensor.getSlotNumber() == slotNumber) {
            return &sensor;
        }
    }

    return nullptr;
}

const ParkingSensor* ParkingSystem::findSensorForSlot(
    int slotNumber
) const
{
    for (const auto& sensor : sensors) {
        if (sensor.getSlotNumber() == slotNumber) {
            return &sensor;
        }
    }

    return nullptr;
}

// ============================================================
// VALIDATE VEHICLE NUMBER
// ============================================================

bool ParkingSystem::isValidVehicleNumber(
    const string& vehicleNumber
) const
{
    if (vehicleNumber.empty()) {
        return false;
    }

    // Vehicle number must not contain spaces.
    for (char ch : vehicleNumber) {
        if (isspace(static_cast<unsigned char>(ch))) {
            return false;
        }
    }

    // Minimum reasonable length.
    return vehicleNumber.length() >= 4;
}

// ============================================================
// ADD HISTORY
// ============================================================

void ParkingSystem::addHistory(
    const string& vehicleNumber,
    int slotNumber,
    const string& action
)
{
    HistoryNode* newNode =
        new HistoryNode(vehicleNumber, slotNumber, action);

    if (historyHead == nullptr) {
        historyHead = newNode;
        return;
    }

    HistoryNode* current = historyHead;

    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
}

// ============================================================
// PARK VEHICLE
// ============================================================

void ParkingSystem::parkVehicle(const Vehicle& inputVehicle)
{
    Vehicle vehicle = inputVehicle;

    // Validate vehicle number.
    if (!isValidVehicleNumber(vehicle.vehicleNumber)) {
        throw invalid_argument("Invalid vehicle number.");
    }

    // Validate owner name.
    if (vehicle.ownerName.empty()) {
        throw invalid_argument("Owner name cannot be empty.");
    }

    // Normalize and validate vehicle type.
    vehicle.vehicleType =
        normalizeVehicleType(vehicle.vehicleType);

    if (!isValidVehicleType(vehicle.vehicleType)) {
        throw invalid_argument(
            "Invalid vehicle type. Use CAR or BIKE."
        );
    }

    // Check duplicate parked vehicle.
    if (findVehicleSlot(vehicle.vehicleNumber) != -1) {
        throw runtime_error(
            "This vehicle is already parked."
        );
    }

    // Check duplicate waiting vehicle.
    queue<Vehicle> tempQueue = waitingQueue;

    while (!tempQueue.empty()) {
        if (tempQueue.front().vehicleNumber ==
            vehicle.vehicleNumber) {
            throw runtime_error(
                "This vehicle is already in the waiting queue."
            );
        }

        tempQueue.pop();
    }

    // IMPORTANT:
    // Find a slot compatible with the vehicle type.
    const int freeSlot = findFreeSlot(vehicle.vehicleType);

    if (freeSlot == -1) {
        waitingQueue.push(vehicle);

        cout << "\nParking is full for vehicle type "
             << vehicle.vehicleType << ".\n";

        cout << "Vehicle added to waiting queue.\n";

        logger.log(
            "Vehicle " + vehicle.vehicleNumber +
            " added to waiting queue."
        );

        return;
    }

    slots[freeSlot - 1].vehicle =
        make_shared<Vehicle>(vehicle);

    slots[freeSlot - 1].occupied = true;

    ParkingSensor* sensor =
        findSensorForSlot(freeSlot);

    if (sensor != nullptr) {
        sensor->detectVehicle();
    }

    addHistory(
        vehicle.vehicleNumber,
        freeSlot,
        "PARKED"
    );

    saveData();

    logger.log(
        "Vehicle " + vehicle.vehicleNumber +
        " parked in slot " + to_string(freeSlot) + "."
    );

    cout << "\nVehicle parked successfully.\n";
    cout << "Vehicle Number : "
         << vehicle.vehicleNumber << endl;
    cout << "Owner Name     : "
         << vehicle.ownerName << endl;
    cout << "Vehicle Type   : "
         << vehicle.vehicleType << endl;
    cout << "Assigned Slot  : "
         << freeSlot << endl;
    cout << "Slot Type      : "
         << slots[freeSlot - 1].slotType << endl;
}

// ============================================================
// REMOVE VEHICLE
// ============================================================

void ParkingSystem::removeVehicle(
    const string& vehicleNumber
)
{
    if (!isValidVehicleNumber(vehicleNumber)) {
        throw invalid_argument(
            "Invalid vehicle number."
        );
    }

    const int slotNumber =
        findVehicleSlot(vehicleNumber);

    if (slotNumber == -1) {
        throw runtime_error(
            "Vehicle not found in parking area."
        );
    }

    // Remember the type of the vehicle being removed.
    string freedSlotType =
        slots[slotNumber - 1].slotType;

    // Release the slot.
    slots[slotNumber - 1].vehicle.reset();
    slots[slotNumber - 1].occupied = false;

    ParkingSensor* sensor =
        findSensorForSlot(slotNumber);

    if (sensor != nullptr) {
        sensor->clearVehicle();
    }

    addHistory(
        vehicleNumber,
        slotNumber,
        "REMOVED"
    );

    cout << "\nVehicle removed successfully.\n";
    cout << "Released Slot : "
         << slotNumber << endl;

    logger.log(
        "Vehicle " + vehicleNumber +
        " removed from slot " + to_string(slotNumber) + "."
    );

    // ========================================================
    // AUTOMATIC WAITING-QUEUE ALLOCATION
    // ========================================================
    //
    // Do not simply take waitingQueue.front().
    // The first waiting vehicle might be a BIKE while the
    // freed slot is a CAR slot, or vice versa.
    //
    // We therefore rotate the queue until we find the first
    // compatible vehicle, preserving the order of the others.
    // ========================================================

    if (!waitingQueue.empty()) {
        queue<Vehicle> compatibleQueue;
        Vehicle* selectedVehicle = nullptr;

        while (!waitingQueue.empty()) {
            Vehicle currentVehicle =
                waitingQueue.front();

            waitingQueue.pop();

            if (selectedVehicle == nullptr &&
                currentVehicle.vehicleType == freedSlotType) {

                selectedVehicle =
                    new Vehicle(currentVehicle);
            } else {
                compatibleQueue.push(currentVehicle);
            }
        }

        waitingQueue = compatibleQueue;

        if (selectedVehicle != nullptr) {
            slots[slotNumber - 1].vehicle =
                make_shared<Vehicle>(*selectedVehicle);

            slots[slotNumber - 1].occupied = true;

            ParkingSensor* sensor =
                findSensorForSlot(slotNumber);

            if (sensor != nullptr) {
                sensor->detectVehicle();
            }

            addHistory(
                selectedVehicle->vehicleNumber,
                slotNumber,
                "PARKED_FROM_QUEUE"
            );

            cout << "\nWaiting vehicle automatically parked.\n";
            cout << "Vehicle Number : "
                 << selectedVehicle->vehicleNumber << endl;
            cout << "Owner Name     : "
                 << selectedVehicle->ownerName << endl;
            cout << "Vehicle Type   : "
                 << selectedVehicle->vehicleType << endl;
            cout << "Assigned Slot  : "
                 << slotNumber << endl;

            logger.log(
                "Vehicle " + selectedVehicle->vehicleNumber +
                " automatically parked from waiting queue in slot " +
                to_string(slotNumber) + "."
            );

            delete selectedVehicle;
        }
    }

    saveData();
}

// ============================================================
// DISPLAY PARKING STATUS
// ============================================================

void ParkingSystem::displayParkingStatus() const
{
    cout << "\n=====================================\n";
    cout << "         PARKING STATUS\n";
    cout << "=====================================\n";

    int occupiedCount = 0;

    for (const auto& slot : slots) {
        cout << "Slot " << slot.slotNumber
             << " [" << slot.slotType << "] : ";

        if (!slot.occupied) {
            cout << "AVAILABLE";
        } else {
            ++occupiedCount;

            cout << "OCCUPIED";

            if (slot.vehicle != nullptr) {
                cout << " | Vehicle: "
                     << slot.vehicle->vehicleNumber;

                cout << " | Owner: "
                     << slot.vehicle->ownerName;

                cout << " | Type: "
                     << slot.vehicle->vehicleType;
            }
        }

        const ParkingSensor* sensor =
            findSensorForSlot(slot.slotNumber);

        if (sensor != nullptr) {
            cout << " | Sensor: "
                 << sensor->getStatus();
        }

        cout << endl;
    }

    cout << "-------------------------------------\n";

    cout << "Total Slots    : "
         << slots.size() << endl;

    cout << "Occupied Slots : "
         << occupiedCount << endl;

    cout << "Free Slots     : "
         << slots.size() - occupiedCount << endl;

    cout << "Waiting        : "
         << waitingQueue.size() << endl;

    cout << "=====================================\n";
}

// ============================================================
// SEND STATUS THROUGH LINUX FIFO IPC
// ============================================================

void ParkingSystem::sendStatusViaIPC() const
{
    std::string message = "SMART PARKING STATUS | ";

    int occupiedCount = 0;

    for (const auto& slot : slots) {
        if (slot.occupied) {
            ++occupiedCount;
        }
    }

    message += "Total Slots=" +
               std::to_string(slots.size());

    message += " | Occupied=" +
               std::to_string(occupiedCount);

    message += " | Free=" +
               std::to_string(slots.size() - occupiedCount);

    message += " | Waiting=" +
               std::to_string(waitingQueue.size());

    ipc.sendMessage(message);

    cout << "\nStatus sent through FIFO IPC.\n";
    cout << "FIFO: " << ipc.getPath() << endl;
}

// ============================================================
// SEARCH VEHICLE
// ============================================================

void ParkingSystem::searchVehicle(
    const string& vehicleNumber
) const
{
    if (!isValidVehicleNumber(vehicleNumber)) {
        cout << "\nInvalid vehicle number.\n";
        return;
    }

    const int slotNumber =
        findVehicleSlot(vehicleNumber);

    if (slotNumber == -1) {
        cout << "\nVehicle not found.\n";
        return;
    }

    const auto& vehicle =
        slots[slotNumber - 1].vehicle;

    cout << "\nVehicle Found\n";
    cout << "-----------------------------\n";

    cout << "Vehicle Number : "
         << vehicle->vehicleNumber << endl;

    cout << "Owner Name     : "
         << vehicle->ownerName << endl;

    cout << "Vehicle Type   : "
         << vehicle->vehicleType << endl;

    cout << "Parking Slot   : "
         << slotNumber << endl;

    cout << "Slot Type      : "
         << slots[slotNumber - 1].slotType << endl;
}

// ============================================================
// DISPLAY WAITING QUEUE
// ============================================================

void ParkingSystem::displayWaitingQueue()
{
    if (waitingQueue.empty()) {
        cout << "\nWaiting queue is empty.\n";
        return;
    }

    queue<Vehicle> temp = waitingQueue;

    cout << "\n=====================================\n";
    cout << "         WAITING QUEUE\n";
    cout << "=====================================\n";

    int position = 1;

    while (!temp.empty()) {
        const Vehicle& vehicle = temp.front();

        cout << position << ". "
             << vehicle.vehicleNumber
             << " | "
             << vehicle.ownerName
             << " | "
             << vehicle.vehicleType
             << endl;

        temp.pop();
        ++position;
    }

    cout << "=====================================\n";
}

// ============================================================
// DISPLAY HISTORY
// ============================================================

void ParkingSystem::displayHistory() const
{
    if (historyHead == nullptr) {
        cout << "\nNo parking history available.\n";
        return;
    }

    cout << "\n=====================================\n";
    cout << "         PARKING HISTORY\n";
    cout << "=====================================\n";

    HistoryNode* current = historyHead;

    while (current != nullptr) {
        cout << "Vehicle : "
             << current->vehicleNumber;

        cout << " | Slot : "
             << current->slotNumber;

        cout << " | Action : "
             << current->action
             << endl;

        current = current->next;
    }

    cout << "=====================================\n";
}

// ============================================================
// SAVE DATA
// ============================================================

void ParkingSystem::saveData() const
{
    ofstream file(dataFile);

    if (!file.is_open()) {
        throw runtime_error(
            "Unable to open parking data file."
        );
    }

    for (const auto& slot : slots) {
        if (slot.occupied &&
            slot.vehicle != nullptr) {

            file << slot.slotNumber
                 << "|"
                 << slot.vehicle->vehicleNumber
                 << "|"
                 << slot.vehicle->ownerName
                 << "|"
                 << slot.vehicle->vehicleType
                 << "\n";
        }
    }

    file.close();
}

// ============================================================
// LOAD DATA
// ============================================================

void ParkingSystem::loadData()
{
    ifstream file(dataFile);

    // It is valid for the data file not to exist
    // on the first run.
    if (!file.is_open()) {
        return;
    }

    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        try {
            const size_t p1 = line.find('|');
            const size_t p2 =
                line.find('|', p1 == string::npos ? 0 : p1 + 1);
            const size_t p3 =
                line.find('|', p2 == string::npos ? 0 : p2 + 1);

            if (p1 == string::npos ||
                p2 == string::npos ||
                p3 == string::npos) {
                continue;
            }

            const int slotNumber =
                stoi(line.substr(0, p1));

            const string vehicleNumber =
                line.substr(
                    p1 + 1,
                    p2 - p1 - 1
                );

            const string ownerName =
                line.substr(
                    p2 + 1,
                    p3 - p2 - 1
                );

            const string vehicleType =
                normalizeVehicleType(
                    line.substr(p3 + 1)
                );

            if (slotNumber < 1 ||
                slotNumber >
                    static_cast<int>(slots.size())) {
                continue;
            }

            if (!isValidVehicleNumber(vehicleNumber) ||
                ownerName.empty() ||
                !isValidVehicleType(vehicleType)) {
                continue;
            }

            // Ensure the saved vehicle type matches
            // the physical/software slot type.
            if (slots[slotNumber - 1].slotType !=
                vehicleType) {
                continue;
            }

            Vehicle vehicle{
                vehicleNumber,
                ownerName,
                vehicleType
            };

            slots[slotNumber - 1].vehicle =
                make_shared<Vehicle>(vehicle);

            slots[slotNumber - 1].occupied = true;
        }
        catch (const exception&) {
            // Ignore malformed records and continue loading.
            continue;
        }
    }

    file.close();
}

// ============================================================
// MAIN MENU
// ============================================================

void ParkingSystem::run()
{
    string input;

    while (true) {
        cout << "\n\n";
        cout << "========================================\n";
        cout << "       SMART PARKING SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Display Parking Status\n";
        cout << "4. Search Vehicle\n";
        cout << "5. Display Waiting Queue\n";
        cout << "6. Display Parking History\n";
        cout << "7. Save Data\n";
        cout << "8. Send Status via IPC\n";
        cout << "9. Exit\n";
        cout << "========================================\n";

        cout << "Enter choice: ";
        cin >> input;

        try {
            int choice;

            try {
                choice = stoi(input);
            }
            catch (...) {
                throw invalid_argument(
                    "Please enter a number between 1 and 9."
                );
            }

            switch (choice) {

                // ------------------------------------------------
                // PARK VEHICLE
                // ------------------------------------------------
                case 1:
                {
                    Vehicle vehicle;

                    cout << "\nEnter Vehicle Number: ";
                    cin >> vehicle.vehicleNumber;

                    cin.ignore(
                        numeric_limits<streamsize>::max(),
                        '\n'
                    );

                    cout << "Enter Owner Name: ";
                    getline(cin, vehicle.ownerName);

                    cout << "Enter Vehicle Type (CAR/BIKE): ";
                    getline(cin, vehicle.vehicleType);

                    parkVehicle(vehicle);
                    break;
                }

                // ------------------------------------------------
                // REMOVE VEHICLE
                // ------------------------------------------------
                case 2:
                {
                    string vehicleNumber;

                    cout << "\nEnter Vehicle Number: ";
                    cin >> vehicleNumber;

                    removeVehicle(vehicleNumber);
                    break;
                }

                // ------------------------------------------------
                // STATUS
                // ------------------------------------------------
                case 3:
                    displayParkingStatus();
                    break;

                // ------------------------------------------------
                // SEARCH
                // ------------------------------------------------
                case 4:
                {
                    string vehicleNumber;

                    cout << "\nEnter Vehicle Number: ";
                    cin >> vehicleNumber;

                    searchVehicle(vehicleNumber);
                    break;
                }

                // ------------------------------------------------
                // WAITING QUEUE
                // ------------------------------------------------
                case 5:
                    displayWaitingQueue();
                    break;

                // ------------------------------------------------
                // HISTORY
                // ------------------------------------------------
                case 6:
                    displayHistory();
                    break;

                // ------------------------------------------------
                // SAVE
                // ------------------------------------------------
                case 7:
                    saveData();
                    cout << "\nData saved successfully.\n";
                    break;

                // ------------------------------------------------
                // SEND STATUS VIA IPC
                // ------------------------------------------------
                case 8:
                {
                    sendStatusViaIPC();
                    break;
                }

                // ------------------------------------------------
                // EXIT
                // ------------------------------------------------
                case 9:
                    saveData();

                    cout << "\nData saved successfully.\n";
                    cout << "Exiting Smart Parking System...\n";

                    return;

                default:
                    cout << "\nInvalid choice.\n";
                    cout << "Please enter 1-8.\n";
            }
        }
        catch (const exception& e) {
            cout << "\nERROR: "
                 << e.what()
                 << endl;
        }
    }
}
