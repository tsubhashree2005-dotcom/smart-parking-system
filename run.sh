#!/bin/bash

echo "=========================================="
echo "   LINUX SMART PARKING MANAGEMENT SYSTEM"
echo "=========================================="

if [ ! -f "./smart_parking" ]; then
    echo ""
    echo "Smart Parking executable not found."
    echo "Building the project first..."
    echo ""

    ./build.sh

    if [ $? -ne 0 ]; then
        echo ""
        echo "ERROR: Build failed."
        exit 1
    fi
fi

echo ""
echo "Starting Smart Parking System..."
echo ""

./smart_parking

STATUS=$?

echo ""
echo "=========================================="

if [ $STATUS -eq 0 ]; then
    echo "Smart Parking System exited successfully."
else
    echo "Smart Parking System exited with an error."
fi

echo "=========================================="

exit $STATUS