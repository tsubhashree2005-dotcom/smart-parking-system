#ifndef SMART_PARKING_IOCTL_H
#define SMART_PARKING_IOCTL_H

#ifdef __KERNEL__
#include <linux/ioctl.h>
#else
#include <sys/ioctl.h>
#endif

#define SMART_PARKING_IOC_MAGIC 'P'

#define SMART_PARKING_IOCTL_GET_BUFFER_SIZE \
    _IOR(SMART_PARKING_IOC_MAGIC, 1, unsigned int)

#define SMART_PARKING_IOCTL_CLEAR_BUFFER \
    _IO(SMART_PARKING_IOC_MAGIC, 2)

#endif
