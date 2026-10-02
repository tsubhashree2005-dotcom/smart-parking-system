#ifndef LINUX_LOGGER_H
#define LINUX_LOGGER_H

#include <string>

class LinuxLogger {
public:
    explicit LinuxLogger(const std::string& fileName);

    void log(const std::string& message) const;

private:
    std::string fileName;
};

#endif