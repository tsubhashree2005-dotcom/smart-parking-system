#include "parking_system.h"

int main()
{
    try {

        // Create parking system with 5 slots
        ParkingSystem parkingSystem(
            5,
            "parking_data.txt"
        );

        parkingSystem.run();

    }
    catch (const exception& e) {

        cerr << "Fatal Error: "
             << e.what()
             << endl;

        return 1;
    }

    return 0;
}