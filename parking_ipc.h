#ifndef PARKING_IPC_H
#define PARKING_IPC_H

#include <string>

class ParkingIPC {
private:
    std::string fifoPath;

public:
    explicit ParkingIPC(const std::string& path);

    // Create the named FIFO if it does not exist
    void createFIFO() const;

    // Remove the named FIFO
    void removeFIFO() const;

    // Send a message through the FIFO
    void sendMessage(const std::string& message) const;

    // Receive a message from the FIFO
    std::string receiveMessage() const;

    // Check whether the FIFO exists
    bool exists() const;

    // Return FIFO path
    std::string getPath() const;
};

#endif