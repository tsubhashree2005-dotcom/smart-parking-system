#include "parking_ipc.h"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

ParkingIPC::ParkingIPC(const std::string& path)
    : fifoPath(path) {

    if (fifoPath.empty()) {
        throw std::invalid_argument(
            "FIFO path cannot be empty."
        );
    }
}

void ParkingIPC::createFIFO() const {

    if (exists()) {
        return;
    }

    if (mkfifo(fifoPath.c_str(), 0666) == -1) {

        if (errno == EEXIST) {
            return;
        }

        throw std::runtime_error(
            "Unable to create FIFO '" +
            fifoPath +
            "': " +
            std::strerror(errno)
        );
    }
}

void ParkingIPC::removeFIFO() const {

    if (!exists()) {
        return;
    }

    if (unlink(fifoPath.c_str()) == -1) {

        throw std::runtime_error(
            "Unable to remove FIFO '" +
            fifoPath +
            "': " +
            std::strerror(errno)
        );
    }
}

void ParkingIPC::sendMessage(
    const std::string& message
) const {

    createFIFO();

    int fd = open(
        fifoPath.c_str(),
        O_WRONLY
    );

    if (fd == -1) {

        throw std::runtime_error(
            "Unable to open FIFO for writing: " +
            std::string(std::strerror(errno))
        );
    }

    std::string data = message + "\n";

    ssize_t bytesWritten = write(
        fd,
        data.c_str(),
        data.size()
    );

    int savedErrno = errno;

    if (close(fd) == -1) {

        throw std::runtime_error(
            "Unable to close FIFO after writing: " +
            std::string(std::strerror(errno))
        );
    }

    if (bytesWritten == -1) {

        throw std::runtime_error(
            "Unable to write to FIFO: " +
            std::string(std::strerror(savedErrno))
        );
    }

    if (static_cast<std::size_t>(bytesWritten)
        != data.size()) {

        throw std::runtime_error(
            "Incomplete message written to FIFO."
        );
    }
}

std::string ParkingIPC::receiveMessage() const {

    createFIFO();

    int fd = open(
        fifoPath.c_str(),
        O_RDONLY
    );

    if (fd == -1) {

        throw std::runtime_error(
            "Unable to open FIFO for reading: " +
            std::string(std::strerror(errno))
        );
    }

    char buffer[1024];

    ssize_t bytesRead = read(
        fd,
        buffer,
        sizeof(buffer) - 1
    );

    int savedErrno = errno;

    if (close(fd) == -1) {

        throw std::runtime_error(
            "Unable to close FIFO after reading: " +
            std::string(std::strerror(errno))
        );
    }

    if (bytesRead == -1) {

        throw std::runtime_error(
            "Unable to read from FIFO: " +
            std::string(std::strerror(savedErrno))
        );
    }

    buffer[bytesRead] = '\0';

    std::string message(buffer);

    if (!message.empty() && message.back() == '\n') {
        message.pop_back();
    }

    return message;
}

bool ParkingIPC::exists() const {

    struct stat fileInfo {};

    return stat(
        fifoPath.c_str(),
        &fileInfo
    ) == 0;
}

std::string ParkingIPC::getPath() const {
    return fifoPath;
}