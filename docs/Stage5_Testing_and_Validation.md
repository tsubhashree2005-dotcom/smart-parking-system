# Stage 5 — Testing and Validation

## 1. Introduction

This stage describes the testing and validation performed for the Linux-Based Smart Parking Management System.

Testing verifies the functionality of the parking application, virtual sensors, file handling, Linux logging, FIFO IPC, character-device driver, and build system.

---

## 2. Testing Objectives

The main objectives are:

- Verify parking operations
- Verify vehicle removal
- Verify parking-slot allocation
- Verify vehicle-type compatibility
- Verify waiting-queue operation
- Verify parking-history operation
- Verify file persistence
- Verify virtual parking sensors
- Verify Linux logging
- Verify FIFO IPC
- Verify character-device driver communication
- Verify project compilation

---

## 3. Build Testing

The project is compiled using the root Makefile.

The main build command is:

```bash
make