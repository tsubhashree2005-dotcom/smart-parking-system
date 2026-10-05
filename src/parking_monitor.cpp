#include "parking_ipc.h"

#include <iostream>
#include <stdexcept>

int main()
{
    try {
        ParkingIPC ipc("/tmp/smart_parking_fifo");
        ipc.createFIFO();

        std::cout << "========================================\n";
        std::cout << "     SMART PARKING IPC MONITOR\n";
        std::cout << "========================================\n";
        std::cout << "Waiting for messages on: "
                  << ipc.getPath() << "\n\n";

        while (true) {
            const std::string message = ipc.receiveMessage();

            if (message == "EXIT") {
                break;
            }

            std::cout << "[IPC MESSAGE] "
                      << message << std::endl;
        }

        ipc.removeFIFO();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "IPC monitor error: "
                  << e.what() << std::endl;
        return 1;
    }
}
