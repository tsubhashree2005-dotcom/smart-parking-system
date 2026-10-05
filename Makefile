CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET = smart_parking
MONITOR = parking_monitor

SOURCES = src/main.cpp \
          src/parking_system.cpp \
          src/parking_sensor.cpp \
          src/parking_ipc.cpp \
          src/linux_logger.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET) $(MONITOR) parking_driver_test

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

$(MONITOR): src/parking_monitor.o src/parking_ipc.o
	$(CXX) $(CXXFLAGS) src/parking_monitor.o src/parking_ipc.o -o $(MONITOR)

parking_driver_test: src/parking_driver_test.cpp
	$(CXX) $(CXXFLAGS) src/parking_driver_test.cpp -o parking_driver_test

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET) $(MONITOR) parking_driver_test

run: $(TARGET)
	./$(TARGET)

run-monitor: $(MONITOR)
	./$(MONITOR)

.PHONY: all clean run run-monitor
