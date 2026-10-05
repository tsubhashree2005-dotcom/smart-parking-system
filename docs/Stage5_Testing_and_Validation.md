Stage 5 — Testing and Validation

1. Introduction

Stage 5 focuses on testing, integration, debugging, validation, and improvement of the Linux-Based Smart Parking Management System.

Testing was performed in the Ubuntu Linux environment after implementation of the C++ application, Linux logging, virtual sensors, FIFO IPC, automated tests, and Linux character-device driver.

The testing process covered individual components as well as integrated system functionality.



2. Testing Objectives

The main objectives of testing were:





Verify successful compilation.



Verify correct execution of the C++ application.



Verify vehicle parking and removal.



Verify compatible-slot allocation.



Verify waiting-queue functionality.



Verify automatic allocation from the waiting queue.



Verify vehicle searching.



Verify parking history.



Verify data persistence.



Verify virtual parking sensors.



Verify Linux logging.



Verify FIFO-based IPC.



Verify Linux kernel-driver compilation.



Verify kernel-module loading.



Verify /dev/smart_parking.



Verify driver read/write communication.



Verify custom IOCTL communication.



Verify automated test-suite execution.



Verify integrated system behavior.



Verify the final project build and repository state.





3. Testing Environment

Testing was performed in:

Operating System : Ubuntu Linux
Architecture     : ARM64
Compiler         : g++
C++ Standard     : C++17
Build System     : GNU Make
Debugger         : GDB
Version Control  : Git

The project was tested exclusively in the Linux environment required by the project constraints.





4. Testing Strategy

Testing was performed at multiple levels:

Build Testing
      |
      v
Unit / Component Testing
      |
      v
Functional Testing
      |
      v
Linux Feature Testing
      |
      v
Kernel Driver Testing
      |
      v
IOCTL Testing
      |
      v
IPC Integration Testing
      |
      v
System Testing
      |
      v
Final Validation

This approach allowed individual components to be verified before complete system integration.





5. Build Testing

The complete C++ project was rebuilt using:

make clean
make

The build completed successfully without compilation errors.

The generated application components included:

smart_parking
parking_monitor
parking_driver_test

The project build script was also verified:

./build.sh

The build script performs a clean build through the project Makefile.

Result

BUILD SUCCESSFUL





6. Functional Testing

The main parking-system functionality was tested through the application menu.

6.1 Vehicle Parking

Test:

Enter vehicle details
Select Park Vehicle

Expected:

Vehicle assigned to a compatible free slot.

Result:

PASS





6.2 Vehicle Removal

Test:

Select Remove Vehicle
Enter an existing vehicle number

Expected:

Vehicle removed and slot becomes available.

Result:

PASS





6.3 Vehicle Search

Test:

Select Search Vehicle
Enter a vehicle number

Expected:

Vehicle information and parking slot are displayed.

Result:

PASS





6.4 Parking Status

Test:

Select Display Parking Status

Expected:

Total slots
Occupied slots
Free slots
Waiting vehicles
Sensor status

Result:

PASS





6.5 Waiting Queue

When no compatible slot is available, a vehicle is added to the waiting queue.

Expected:

Vehicle placed in waiting queue.

Result:

PASS





6.6 Automatic Waiting-Queue Allocation

After a compatible slot becomes available, the system checks the waiting queue and automatically assigns a compatible vehicle.

Expected:

Compatible waiting vehicle assigned automatically.

Result:

PASS





6.7 Parking History

Parking and removal operations were checked against the history list.

Expected:

Parking actions recorded correctly.

Result:

PASS





7. Data Persistence Testing

The persistence mechanism was tested by:





Parking vehicles.



Saving the parking data.



Closing the application.



Restarting the application.



Checking the restored parking state.

Data is stored in:

parking_data.txt

Expected:

Previously saved vehicle information is restored.

Result:

PASS

The application also validates loaded records and ignores malformed records.





8. Virtual Sensor Testing

The virtual parking sensor functionality was tested for:





Occupied state



Available state



Detection



Clearing



Toggling



Status display

Expected:

Sensor state correctly reflects parking-slot state.

Result:

PASS

The automated test suite also includes a dedicated virtual-sensor test.





9. Linux Logging Testing

The Linux logger was tested using Linux file-system operations.

The logger writes information to:

parking.log

The implementation uses Linux system calls:

open()
write()
close()

Expected:

Parking-system events are written to the log.

Result:

PASS





10. FIFO IPC Testing

FIFO IPC was tested using two terminals.

Terminal 1

./parking_monitor



Terminal 2

./smart_parking

The main application was used to send the parking status through the IPC option.

The monitor received a message similar to:

[IPC MESSAGE] SMART PARKING STATUS | Total Slots=5 | Occupied=0 | Free=5 | Waiting=0

Expected:

Status successfully transferred between two user-space processes.

Result:

PASS





11. Linux Kernel Driver Build Testing

The kernel driver was built using:

cd ~/smart-parking-system/kernel_driver
make

The kernel module was generated successfully:

parking_driver.ko

A standard BTF-related informational message may appear when vmlinux is unavailable. This does not prevent the module from being generated.

Expected:

parking_driver.ko created successfully.

Result:

PASS





12. Kernel Module Loading Testing

The driver was loaded using:

sudo insmod parking_driver.ko

The loaded module was verified using:

lsmod | grep parking_driver

Expected:

parking_driver

Result:

PASS





13. Character Device Testing

After loading the driver, the device node was verified using:

ls -l /dev/smart_parking

The device was successfully created as a Linux character device.

Expected:

/dev/smart_parking exists

Result:

PASS





14. Driver Read/Write Testing

The driver test application was compiled from:

src/parking_driver_test.cpp

It was executed using:

sudo ./parking_driver_test

The driver successfully accepted data through write() and returned it through read().

Observed result:

Written to driver: Parking driver test: Slot 1 OCCUPIED
Read from driver: Parking driver test: Slot 1 OCCUPIED

Driver communication successful.

Result:

PASS





15. IOCTL Testing

The character-device driver was enhanced with custom IOCTL operations.

Definitions are provided in:

kernel_driver/parking_ioctl.h

The supported commands are:

SMART_PARKING_IOCTL_GET_BUFFER_SIZE
SMART_PARKING_IOCTL_CLEAR_BUFFER

The driver test validates:

write()
ioctl(GET_BUFFER_SIZE)
read()
ioctl(CLEAR_BUFFER)

Final test result:

SMART PARKING DRIVER IOCTL TEST

[1] write() successful
[2] ioctl GET_BUFFER_SIZE successful
    Buffer size: 36 bytes
[3] read() successful
    Data: Parking driver test: Slot 1 OCCUPIED
[4] ioctl CLEAR_BUFFER successful
[5] Buffer size after clear: 0 bytes

IOCTL TEST SUCCESSFUL

Result:

PASS

This confirms successful user-space to kernel-space control communication through the character device.





16. Automated Test Suite

A dedicated automated test suite was added at:

tests/test_parking_system.cpp

The suite validates seven important application behaviors:







Test



Result





Vehicle parking



PASS





Vehicle removal



PASS





Waiting queue



PASS





Automatic waiting-queue allocation



PASS





Data persistence



PASS





Virtual parking sensor



PASS





Invalid vehicle validation



PASS

Final result:

Passed : 7
Failed : 0
ALL TESTS PASSED

This provides repeatable validation of the main C++ application functionality.





17. Input Validation and Error Testing

The application was tested with invalid input conditions.

Examples include:





Invalid vehicle number



Invalid vehicle type



Invalid menu input



Invalid or malformed persisted records



Attempting to remove a vehicle that is not parked



Attempting to park when compatible slots are unavailable

The application uses validation and C++ exception handling to prevent invalid operations from terminating the system unexpectedly.

Result:

PASS





18. Integration Testing

The major system components were tested together:

C++ Main Application
        |
        +---- Parking Slots
        |
        +---- Waiting Queue
        |
        +---- Parking History
        |
        +---- File Persistence
        |
        +---- Virtual Sensors
        |
        +---- Linux Logger
        |
        +---- FIFO IPC
        |         |
        |         +---- Parking Monitor
        |
        +---- Linux Character Driver
                  |
                  +---- Driver Test
                  |
                  +---- IOCTL

The integrated system was tested for interaction between these components.

Result:

PASS





19. System Testing

System-level testing verified the complete workflow:

Start Application
       |
       v
Load Saved Data
       |
       v
Park / Remove Vehicles
       |
       v
Update Sensors
       |
       v
Update History
       |
       v
Save Data
       |
       v
Send Status through FIFO
       |
       v
Verify Linux Driver Separately
       |
       v
Exit

The final application operated correctly across the tested workflow.

Result:

PASS





20. Debugging and Issues Resolved

Several implementation issues were encountered during development and testing.

20.1 Source-Code Organization

Moving source files into the src/ directory required updates to:





Root Makefile



Build script



Run script



VS Code tasks

The build configuration was updated and verified successfully.

20.2 Kernel Driver Compilation

The driver required correct Linux kernel APIs and file-operation definitions.

After correcting the driver implementation, the module built successfully.

20.3 Duplicate Driver Definitions

During IOCTL integration, duplicate driver initialization and cleanup definitions were temporarily introduced.

The duplicate module_init() and module_exit() sections were removed.

The final driver contained one initialization path and one cleanup path and compiled successfully.

20.4 Driver-Test Source Location

The driver-test program is stored under:

src/parking_driver_test.cpp

The final compilation command was corrected to use the src/ path.

20.5 IOCTL Integration

The driver test was updated to use:

kernel_driver/parking_ioctl.h

The final test confirmed successful buffer-size retrieval and buffer clearing.





21. Final Validation Summary

The following major tests were completed successfully:







Category



Result





Clean project build



PASS





C++ application execution



PASS





Vehicle parking



PASS





Vehicle removal



PASS





Vehicle search



PASS





Parking status



PASS





Waiting queue



PASS





Automatic queue allocation



PASS





Parking history



PASS





Data persistence



PASS





Virtual sensors



PASS





Linux logging



PASS





FIFO IPC



PASS





Kernel driver build



PASS





Kernel module loading



PASS





/dev/smart_parking



PASS





Driver read/write



PASS





Driver IOCTL



PASS





Automated test suite



7/7 PASS





Final integration



PASS





22. Repository and Build Validation

The final project repository was checked using:

git status

The final source, test, driver, and documentation changes were staged and committed locally.

The repository remote was corrected to the intended project repository:

https://github.com/tsubhashree2005-dotcom/smart-parking-system

The final changes were pushed successfully to the main branch.

The working tree was clean after the final commit.





23. Testing Outcome

Stage 5 testing confirms that the Smart Parking Management System functions correctly across application-level, Linux system-level, IPC, and kernel-driver components.

The addition of automated tests provides repeatable verification of the core C++ functionality, while the IOCTL test verifies an extended kernel-driver interface.

The final result was:

7 automated tests passed
0 automated tests failed
IOCTL test successful
Kernel driver communication successful
Integrated system testing successful

Stage 5 is therefore completed successfully.





24. Conclusion

The testing and validation stage confirmed that the implemented system satisfies the major functional and technical requirements established in the earlier stages.

The project demonstrates:





C++ application testing



STL and data-structure validation



File persistence testing



Virtual sensor testing



Linux system-call testing



FIFO IPC testing



Character-device driver testing



User-space/kernel-space communication



Custom IOCTL testing



Automated software testing



Integration and system testing



Git/GitHub repository validation

The system is ready for final deployment documentation and presentation.