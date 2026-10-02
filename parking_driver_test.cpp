#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

namespace {

constexpr const char* DEVICE_PATH = "/dev/smart_parking";
constexpr std::size_t BUFFER_SIZE = 256;

void writeToDriver(const std::string& message)
{
    const int fd = open(
        DEVICE_PATH,
        O_WRONLY
    );

    if (fd == -1) {
        throw std::runtime_error(
            "Unable to open " +
            std::string(DEVICE_PATH) +
            " for writing: " +
            std::strerror(errno)
        );
    }

    const ssize_t bytesWritten = write(
        fd,
        message.c_str(),
        message.size()
    );

    const int savedErrno = errno;

    close(fd);

    if (bytesWritten == -1) {
        throw std::runtime_error(
            "Unable to write to driver: " +
            std::string(std::strerror(savedErrno))
        );
    }

    std::cout
        << "Written to driver: "
        << message
        << '\n';
}

std::string readFromDriver()
{
    const int fd = open(
        DEVICE_PATH,
        O_RDONLY
    );

    if (fd == -1) {
        throw std::runtime_error(
            "Unable to open " +
            std::string(DEVICE_PATH) +
            " for reading: " +
            std::strerror(errno)
        );
    }

    char buffer[BUFFER_SIZE] = {};

    const ssize_t bytesRead = read(
        fd,
        buffer,
        BUFFER_SIZE - 1
    );

    const int savedErrno = errno;

    close(fd);

    if (bytesRead == -1) {
        throw std::runtime_error(
            "Unable to read from driver: " +
            std::string(std::strerror(savedErrno))
        );
    }

    buffer[bytesRead] = '\0';

    return std::string(buffer);
}

} // namespace

int main()
{
    try {
        std::cout
            << "=====================================\n"
            << "   SMART PARKING DRIVER TEST\n"
            << "=====================================\n";

        const std::string message =
            "Parking driver test: Slot 1 OCCUPIED";

        writeToDriver(message);

        const std::string response =
            readFromDriver();

        std::cout
            << "Read from driver: "
            << response
            << '\n';

        std::cout
            << "\nDriver communication successful.\n";
    }
    catch (const std::exception& error) {

        std::cerr
            << "Driver test error: "
            << error.what()
            << '\n';

        return 1;
    }

    return 0;
}