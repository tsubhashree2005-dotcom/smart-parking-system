#ifndef PARKING_SENSOR_H
#define PARKING_SENSOR_H

#include <string>

class ParkingSensor {
private:
    int sensorId;
    int slotNumber;
    bool occupied;

public:
    ParkingSensor(int sensorId, int slotNumber);

    // Simulate sensor detecting a vehicle
    void detectVehicle();

    // Simulate sensor detecting an empty slot
    void clearVehicle();

    // Toggle sensor state
    void toggle();

    // Set sensor state directly
    void setOccupied(bool status);

    // Get sensor information
    int getSensorId() const;
    int getSlotNumber() const;
    bool isOccupied() const;

    // Get readable sensor status
    std::string getStatus() const;

    // Display sensor information
    void display() const;
};

#endif