#include "../src/parking_system.h"
#include "../src/parking_sensor.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

static int testsPassed = 0;
static int testsFailed = 0;

#define TEST(name) \
    cout << "[TEST] " << name << " ... "

#define PASS() \
    do { \
        cout << "PASS\n"; \
        ++testsPassed; \
    } while (0)

#define FAIL(msg) \
    do { \
        cout << "FAIL: " << msg << "\n"; \
        ++testsFailed; \
    } while (0)

void testParkingVehicle()
{
    TEST("Parking a vehicle");

    const string file = "tests/test_parking_data.txt";
    remove(file.c_str());

    try {
        ParkingSystem system(5, file);

        Vehicle vehicle{
            "OD01AB1234",
            "Test User",
            "CAR"
        };

        system.parkVehicle(vehicle);

        ostringstream output;
        streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

        system.searchVehicle("OD01AB1234");

        cout.rdbuf(oldBuffer);

        if (output.str().find("Vehicle Found") != string::npos &&
            output.str().find("OD01AB1234") != string::npos) {
            PASS();
        } else {
            FAIL("Parked vehicle could not be found.");
        }
    }
    catch (const exception& e) {
        FAIL(e.what());
    }

    remove(file.c_str());
}

void testVehicleRemoval()
{
    TEST("Removing a vehicle");

    const string file = "tests/test_parking_data.txt";
    remove(file.c_str());

    try {
        ParkingSystem system(5, file);

        Vehicle vehicle{
            "OD02CD5678",
            "Test Owner",
            "CAR"
        };

        system.parkVehicle(vehicle);
        system.removeVehicle("OD02CD5678");

        ostringstream output;
        streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

        system.searchVehicle("OD02CD5678");

        cout.rdbuf(oldBuffer);

        if (output.str().find("Vehicle not found") != string::npos) {
            PASS();
        } else {
            FAIL("Vehicle still appears as parked.");
        }
    }
    catch (const exception& e) {
        FAIL(e.what());
    }

    remove(file.c_str());
}

void testWaitingQueue()
{
    TEST("Waiting queue");

    const string file = "tests/test_parking_data.txt";
    remove(file.c_str());

    try {
        ParkingSystem system(5, file);

        // Fill all three CAR slots.
        system.parkVehicle({"CAR001", "Owner1", "CAR"});
        system.parkVehicle({"CAR002", "Owner2", "CAR"});
        system.parkVehicle({"CAR003", "Owner3", "CAR"});

        // Fourth CAR must enter waiting queue.
        system.parkVehicle({"CAR004", "Owner4", "CAR"});

        ostringstream output;
        streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

        system.displayWaitingQueue();

        cout.rdbuf(oldBuffer);

        if (output.str().find("CAR004") != string::npos) {
            PASS();
        } else {
            FAIL("Vehicle was not added to waiting queue.");
        }
    }
    catch (const exception& e) {
        FAIL(e.what());
    }

    remove(file.c_str());
}

void testAutomaticQueueAllocation()
{
    TEST("Automatic waiting-queue allocation");

    const string file = "tests/test_parking_data.txt";
    remove(file.c_str());

    try {
        ParkingSystem system(5, file);

        system.parkVehicle({"CAR001", "Owner1", "CAR"});
        system.parkVehicle({"CAR002", "Owner2", "CAR"});
        system.parkVehicle({"CAR003", "Owner3", "CAR"});
        system.parkVehicle({"CAR004", "Owner4", "CAR"});

        // Removing a CAR frees a compatible CAR slot.
        system.removeVehicle("CAR001");

        ostringstream output;
        streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

        system.searchVehicle("CAR004");

        cout.rdbuf(oldBuffer);

        if (output.str().find("Vehicle Found") != string::npos &&
            output.str().find("CAR004") != string::npos) {
            PASS();
        } else {
            FAIL("Waiting vehicle was not automatically parked.");
        }
    }
    catch (const exception& e) {
        FAIL(e.what());
    }

    remove(file.c_str());
}

void testPersistence()
{
    TEST("Data persistence");

    const string file = "tests/test_parking_data.txt";
    remove(file.c_str());

    try {
        {
            ParkingSystem system(5, file);

            system.parkVehicle({
                "OD03EF9012",
                "Persistent User",
                "CAR"
            });
        }

        ParkingSystem restoredSystem(5, file);

        ostringstream output;
        streambuf* oldBuffer = cout.rdbuf(output.rdbuf());

        restoredSystem.searchVehicle("OD03EF9012");

        cout.rdbuf(oldBuffer);

        if (output.str().find("Vehicle Found") != string::npos &&
            output.str().find("OD03EF9012") != string::npos) {
            PASS();
        } else {
            FAIL("Saved vehicle was not restored.");
        }
    }
    catch (const exception& e) {
        FAIL(e.what());
    }

    remove(file.c_str());
}

void testSensor()
{
    TEST("Virtual parking sensor");

    try {
        ParkingSensor sensor(1, 1);

        if (sensor.isOccupied()) {
            FAIL("Sensor should initially be free.");
            return;
        }

        sensor.detectVehicle();

        if (!sensor.isOccupied()) {
            FAIL("Sensor did not detect vehicle.");
            return;
        }

        sensor.clearVehicle();

        if (sensor.isOccupied()) {
            FAIL("Sensor did not clear vehicle.");
            return;
        }

        sensor.toggle();

        if (!sensor.isOccupied()) {
            FAIL("Sensor toggle failed.");
            return;
        }

        PASS();
    }
    catch (const exception& e) {
        FAIL(e.what());
    }
}

void testInvalidVehicle()
{
    TEST("Invalid vehicle validation");

    const string file = "tests/test_parking_data.txt";
    remove(file.c_str());

    try {
        ParkingSystem system(5, file);

        bool exceptionThrown = false;

        try {
            system.parkVehicle({
                "A",
                "Invalid User",
                "CAR"
            });
        }
        catch (const invalid_argument&) {
            exceptionThrown = true;
        }

        if (exceptionThrown) {
            PASS();
        } else {
            FAIL("Invalid vehicle number was accepted.");
        }
    }
    catch (const exception& e) {
        FAIL(e.what());
    }

    remove(file.c_str());
}

int main()
{
    cout << "\n========================================\n";
    cout << " SMART PARKING AUTOMATED TEST SUITE\n";
    cout << "========================================\n\n";

    testParkingVehicle();
    testVehicleRemoval();
    testWaitingQueue();
    testAutomaticQueueAllocation();
    testPersistence();
    testSensor();
    testInvalidVehicle();

    cout << "\n========================================\n";
    cout << " TEST SUMMARY\n";
    cout << "========================================\n";

    cout << "Passed : " << testsPassed << '\n';
    cout << "Failed : " << testsFailed << '\n';

    if (testsFailed == 0) {
        cout << "\nALL TESTS PASSED\n";
        return 0;
    }

    cout << "\nSOME TESTS FAILED\n";
    return 1;
}
