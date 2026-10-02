# Stage 5 — Testing and Validation

## 1. Introduction

Stage 5 focuses on testing, integration, debugging, validation, and improvement of the Linux-Based Smart Parking Management System.

Testing was performed in the Ubuntu Linux environment after implementation of the C++ application, Linux logging, virtual sensors, FIFO IPC, and Linux character-device driver.

The testing process covered both individual components and integrated system functionality.

---

## 2. Testing Objectives

The main objectives of testing were:

1. Verify successful compilation.
2. Verify correct execution of the C++ application.
3. Verify vehicle parking and removal.
4. Verify compatible-slot allocation.
5. Verify waiting-queue functionality.
6. Verify automatic allocation from the waiting queue.
7. Verify vehicle searching.
8. Verify parking history.
9. Verify data persistence.
10. Verify virtual parking sensors.
11. Verify Linux logging.
12. Verify FIFO-based IPC.
13. Verify Linux kernel-driver compilation.
14. Verify kernel-module loading.
15. Verify `/dev/smart_parking`.
16. Verify driver read/write communication.
17. Verify integrated system behavior.
18. Verify the final project build and repository state.

---

## 3. Testing Environment

Testing was performed in:

```text
Operating System : Ubuntu Linux
Architecture     : ARM64
Compiler         : g++
C++ Standard     : C++17
Build System     : GNU Make
Debugger         : GDB
Version Control  : Git