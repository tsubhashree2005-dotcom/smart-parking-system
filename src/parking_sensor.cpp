#include "parking_sensor.h"

#include <iostream>
#include <stdexcept>

ParkingSensor::ParkingSensor(int sensorId, int slotNumber)
    : sensorId(sensorId),
      slotNumber(slotNumber),
      occupied(false) {

    if (sensorId <= 0) {
        throw std::invalid_argument("Sensor ID must be greater than zero.");
    }

    if (slotNumber <= 0) {
        throw std::invalid_argument("Slot number must be greater than zero.");
    }
}

void ParkingSensor::detectVehicle() {
    occupied = true;
}

void ParkingSensor::clearVehicle() {
    occupied = false;
}

void ParkingSensor::toggle() {
    occupied = !occupied;
}

void ParkingSensor::setOccupied(bool status) {
    occupied = status;
}

int ParkingSensor::getSensorId() const {
    return sensorId;
}

int ParkingSensor::getSlotNumber() const {
    return slotNumber;
}

bool ParkingSensor::isOccupied() const {
    return occupied;
}

std::string ParkingSensor::getStatus() const {
    if (occupied) {
        return "OCCUPIED";
    }

    return "FREE";
}

void ParkingSensor::display() const {
    std::cout << "Sensor ID : " << sensorId << '\n';
    std::cout << "Slot      : " << slotNumber << '\n';
    std::cout << "Status    : " << getStatus() << '\n';
}