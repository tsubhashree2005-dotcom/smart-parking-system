Final Test Results — Linux-Based Smart Parking Management System

1. Testing Overview

The Linux-Based Smart Parking Management System was tested progressively during development to verify its core functionality, Linux integration, inter-process communication, kernel-driver communication, data persistence, and runtime behavior.

Testing was performed in the Ubuntu Linux environment using the project's C++ application, Linux character-device driver, FIFO-based IPC monitor, virtual parking sensors, file storage, Linux logging mechanism, automated test suite, and IOCTL driver test application.





2. Build and Compilation Testing







Test ID



Test Description



Result





A1



Build the main C++ application using Makefile



PASS





A2



Build the Linux kernel character driver



PASS





B1



Clean rebuild using make clean followed by make



PASS





B2



Build the driver test application



PASS

The project compiled successfully during the final clean build.

The root build system successfully produced:

smart_parking
parking_monitor
parking_driver_test

The kernel-driver build successfully produced:

parking_driver.ko





3. Parking Management Functional Testing







Test ID



Test Description



Result





A6



Park a vehicle in an available slot



PASS





A7



Remove a parked vehicle



PASS





A8



Search for a vehicle



PASS





A9



Add vehicle to waiting queue when parking is unavailable



PASS





A10



Automatically assign a freed compatible slot to a waiting vehicle



PASS





A11



Display parking history



PASS





A12



Save and reload parking data



PASS

The main parking operations were verified through the C++ application menu. The application successfully handled parking, removal, searching, waiting-queue processing, history, and persistence operations.





4. Vehicle and Parking-Slot Validation

The system validates vehicle information and parking-slot compatibility before assigning a vehicle.

The implemented system supports:





Vehicle registration



Vehicle removal



Vehicle searching



Duplicate vehicle validation



Vehicle type validation



CAR and BIKE slot types



Compatible-slot allocation



Waiting queue management



Automatic allocation after a slot becomes available

These validations help prevent incorrect vehicle-slot assignments and maintain consistent parking data.

Result: PASS





5. Waiting Queue Testing

The waiting queue was tested by filling available parking capacity and introducing additional vehicles.

The system was verified to:





Detect that no compatible slot is available.



Add the vehicle to the waiting queue.



Display the queue information.



Detect when a parking slot becomes available.



Automatically process the waiting vehicle.

The queue functionality therefore integrates parking management with dynamic slot availability.

Result: PASS





6. Data Persistence Testing

The application stores parking information using file operations.

Persistence testing verified that:





Parking data can be saved.



Stored data can be loaded again.



Parking information is retained between application executions.



File-based storage integrates with the main C++ application.

The implementation uses C++ file handling through input/output file streams.

Result: PASS





7. Virtual Parking Sensor Testing

The project includes a virtual parking sensor component representing hardware-level parking detection.

Sensor functionality tested includes:





Sensor identification



Slot association



Occupancy detection



Occupancy clearing



Sensor state toggling



Sensor state display

The sensor component demonstrates how software can represent and process parking hardware signals in a Linux-based system.

Test ID: A13

Result: PASS





8. Linux Logging Testing

The project includes a Linux logging component using Linux file-descriptor based operations.

The logger uses Linux system calls for:





Opening the log file



Writing log messages



Closing the file

Parking events and system-related activities can therefore be recorded in the project log.

Test ID: A14

Result: PASS





9. FIFO IPC Testing

The project implements inter-process communication using a Linux named pipe (FIFO).

Components





Main parking application



FIFO: /tmp/smart_parking_fifo



Parking monitor process



Test Procedure

The parking monitor was started using:

./parking_monitor

The main application was then started separately and used to send parking-status information through the FIFO.

The monitor successfully received and displayed the transmitted parking status.

Result: PASS





10. Linux Character-Device Driver Testing

The Linux character-device driver was tested separately from the main parking application.

Driver Components

kernel_driver/parking_driver.c
kernel_driver/parking_ioctl.h



Device

/dev/smart_parking

The driver was successfully:





Compiled as a kernel module.



Loaded using insmod.



Verified using lsmod.



Exposed as /dev/smart_parking.



Tested from user space.



Unloaded using rmmod.

Result: PASS





11. Character-Device Read/Write Testing

The driver test application verified communication with the character device.

The following operations were tested:





open()



write()



read()



close()

The test successfully wrote parking-driver test data to the device and read the same data back.

Example verified data:

Parking driver test: Slot 1 OCCUPIED

Result: PASS





12. IOCTL Testing

The character driver implements two IOCTL commands.

12.1 GET_BUFFER_SIZE

The test application used:

SMART_PARKING_IOCTL_GET_BUFFER_SIZE

The driver successfully returned the current buffer size.

Verified result:

Buffer size: 36 bytes



12.2 CLEAR_BUFFER

The test application used:

SMART_PARKING_IOCTL_CLEAR_BUFFER

The driver successfully cleared the device buffer.

Verified result:

Buffer size after clear: 0 bytes



IOCTL Test Result

[1] write() successful
[2] ioctl GET_BUFFER_SIZE successful
[3] read() successful
[4] ioctl CLEAR_BUFFER successful
[5] Buffer size after clear: 0 bytes

IOCTL TEST SUCCESSFUL

Result: PASS





13. Automated Functional Testing

An automated C++ test suite was added to validate core application functionality.

Test file:

tests/test_parking_system.cpp

The automated test suite covers:





Parking a vehicle.



Removing a vehicle.



Waiting queue behavior.



Automatic waiting-queue allocation.



Data persistence.



Virtual parking sensor behavior.



Invalid vehicle validation.



Final Automated Test Result

Passed : 7
Failed : 0
ALL TESTS PASSED

Result: PASS





14. Integration Testing

The following components were verified as part of the integrated system:







Component



Result





C++ Parking Application



PASS





Parking Slot Management



PASS





Vehicle Management



PASS





Waiting Queue



PASS





Automatic Queue Allocation



PASS





Parking History



PASS





Data Persistence



PASS





Virtual Parking Sensor



PASS





Linux Logger



PASS





FIFO IPC



PASS





Character Device Driver



PASS





Driver Read/Write



PASS





IOCTL GET_BUFFER_SIZE



PASS





IOCTL CLEAR_BUFFER



PASS





Driver Test Application



PASS





Automated Test Suite



PASS





15. Error Handling and Debugging

During development, several implementation and integration issues were identified and resolved.

The final implementation was verified for:





Invalid vehicle input.



Duplicate vehicle validation.



Incompatible parking-slot allocation.



Full parking capacity.



Waiting-queue processing.



File-operation handling.



FIFO communication.



Kernel-driver build issues.



Character-device creation.



User/kernel data transfer.



IOCTL command handling.

The final build and runtime tests completed successfully.





16. Final Test Summary







Test Category



Result





Main Application Build



PASS





Kernel Driver Build



PASS





Driver Test Build



PASS





Parking Operations



PASS





Vehicle Removal



PASS





Vehicle Search



PASS





Waiting Queue



PASS





Automatic Queue Allocation



PASS





Parking History



PASS





Data Persistence



PASS





Virtual Sensor



PASS





Linux Logging



PASS





FIFO IPC



PASS





Character Device



PASS





Driver Read/Write



PASS





IOCTL GET_BUFFER_SIZE



PASS





IOCTL CLEAR_BUFFER



PASS





Automated Tests



7 PASS / 0 FAIL





Overall System



PASS





17. Final Validation

The final validation confirmed that the major project components operate correctly in the Ubuntu Linux environment.

The final system successfully demonstrates:





C++ application development.



Linux system programming.



C++ STL data structures.



File handling and persistence.



Virtual sensor simulation.



Linux file-descriptor based logging.



FIFO-based IPC.



Linux character-device development.



User-space/kernel-space interaction.



IOCTL-based device control.



Automated functional testing.



Build automation using GNU Make.





18. Conclusion

The Linux-Based Smart Parking Management System successfully passed the final functional, integration, driver, IPC, persistence, and automated testing activities.

The automated test suite achieved 7 passed and 0 failed, while the Linux character-device driver and IOCTL test also completed successfully.

The final results confirm that the system meets the major functional and technical requirements defined for the project and provides a working Linux-based demonstration of C++, system programming, IPC, virtual device interaction, kernel-driver concepts, and software testing.