#include "linux_logger.h"

#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>

LinuxLogger::LinuxLogger(const std::string& fileName)
    : fileName(fileName) {
}

void LinuxLogger::log(const std::string& message) const {
    const int fd = open(
        fileName.c_str(),
        O_WRONLY | O_CREAT | O_APPEND,
        0644
    );

    if (fd == -1) {
        throw std::runtime_error(
            "Unable to open Linux log file: " +
            std::string(std::strerror(errno))
        );
    }

    const std::string logMessage = message + "\n";

    const ssize_t bytesWritten = write(
        fd,
        logMessage.c_str(),
        logMessage.size()
    );

    const int savedErrno = errno;

    if (close(fd) == -1) {
        throw std::runtime_error(
            "Unable to close Linux log file: " +
            std::string(std::strerror(errno))
        );
    }

    if (bytesWritten == -1) {
        throw std::runtime_error(
            "Unable to write Linux log file: " +
            std::string(std::strerror(savedErrno))
        );
    }

    if (static_cast<std::size_t>(bytesWritten) != logMessage.size()) {
        throw std::runtime_error(
            "Incomplete write to Linux log file."
        );
    }
}