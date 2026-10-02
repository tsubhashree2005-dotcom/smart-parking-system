CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET = smart_parking
MONITOR = parking_monitor
DRIVER_TEST = parking_driver_test

SOURCES = main.cpp \
          parking_system.cpp \
          parking_sensor.cpp \
          parking_ipc.cpp \
          linux_logger.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET) $(MONITOR) $(DRIVER_TEST)

# Main Smart Parking application
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# IPC monitoring application
$(MONITOR): parking_monitor.o parking_ipc.o
	$(CXX) $(CXXFLAGS) parking_monitor.o parking_ipc.o -o $(MONITOR)

# Linux character-device driver test program
$(DRIVER_TEST): parking_driver_test.cpp
	$(CXX) $(CXXFLAGS) parking_driver_test.cpp -o $(DRIVER_TEST)

# Compile C++ source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the main application
run: $(TARGET)
	./$(TARGET)

# Run the IPC monitor
run-monitor: $(MONITOR)
	./$(MONITOR)

# Run the driver test
run-driver-test: $(DRIVER_TEST)
	./$(DRIVER_TEST)

# Remove generated files
clean:
	rm -f $(OBJECTS) \
	      parking_monitor.o \
	      $(TARGET) \
	      $(MONITOR) \
	      $(DRIVER_TEST)

.PHONY: all clean run run-monitor run-driver-test