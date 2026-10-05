#!/bin/bash

set -e

echo "======================================"
echo " Smart Parking System - Build"
echo "======================================"

make clean
make

echo ""
echo "BUILD SUCCESSFUL"