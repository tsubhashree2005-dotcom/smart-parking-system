#!/bin/bash

echo "=========================================="
echo "   SMART PARKING SYSTEM - BUILD"
echo "=========================================="

echo ""
echo "[1/2] Cleaning previous build..."
make clean

if [ $? -ne 0 ]; then
    echo "ERROR: Clean failed."
    exit 1
fi

echo ""
echo "[2/2] Building project..."
make

if [ $? -ne 0 ]; then
    echo ""
    echo "ERROR: Build failed."
    exit 1
fi

echo ""
echo "=========================================="
echo "   BUILD SUCCESSFUL"
echo "=========================================="

echo ""
echo "Generated executables:"
echo "  - smart_parking"
echo "  - parking_monitor"
echo "  - parking_driver_test"
echo ""

echo "To run the main application:"
echo "  ./smart_parking"

echo ""
echo "To run the IPC monitor:"
echo "  ./parking_monitor"

echo ""
echo "To test the character driver:"
echo "  ./parking_driver_test"