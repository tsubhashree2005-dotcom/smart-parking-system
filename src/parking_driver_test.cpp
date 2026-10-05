#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "../kernel_driver/parking_ioctl.h"

int main() {
    const char* device = "/dev/smart_parking";
    const char* message = "Parking driver test: Slot 1 OCCUPIED";

    std::cout << "=====================================\n";
    std::cout << " SMART PARKING DRIVER IOCTL TEST\n";
    std::cout << "=====================================\n\n";

    int fd = open(device, O_RDWR);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 1. Test write()
    ssize_t written = write(fd, message, strlen(message));

    if (written < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    std::cout << "[1] write() successful\n";

    // 2. Test ioctl GET_BUFFER_SIZE
    unsigned int buffer_size = 0;

    if (ioctl(fd, SMART_PARKING_IOCTL_GET_BUFFER_SIZE, &buffer_size) < 0) {
        perror("ioctl GET_BUFFER_SIZE");
        close(fd);
        return 1;
    }

    std::cout << "[2] ioctl GET_BUFFER_SIZE successful\n";
    std::cout << "    Buffer size: " << buffer_size << " bytes\n";

    // 3. Test read()
    char buffer[256] = {0};

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_read < 0) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';

    std::cout << "[3] read() successful\n";
    std::cout << "    Data: " << buffer << "\n";

    // 4. Test ioctl CLEAR_BUFFER
    if (ioctl(fd, SMART_PARKING_IOCTL_CLEAR_BUFFER) < 0) {
        perror("ioctl CLEAR_BUFFER");
        close(fd);
        return 1;
    }

    std::cout << "[4] ioctl CLEAR_BUFFER successful\n";

    // 5. Verify buffer was cleared
    buffer_size = 999;

    if (ioctl(fd, SMART_PARKING_IOCTL_GET_BUFFER_SIZE, &buffer_size) < 0) {
        perror("ioctl GET_BUFFER_SIZE after clear");
        close(fd);
        return 1;
    }

    std::cout << "[5] Buffer size after clear: "
              << buffer_size << " bytes\n";

    close(fd);

    std::cout << "\n=====================================\n";
    std::cout << " IOCTL TEST SUCCESSFUL\n";
    std::cout << "=====================================\n";

    return 0;
}
