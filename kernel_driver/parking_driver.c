#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>

#define DRIVER_NAME "smart_parking"
#define DEVICE_NAME "smart_parking"
#define BUFFER_SIZE 256

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smart Parking System");
MODULE_DESCRIPTION("Linux character device driver for Smart Parking System");
MODULE_VERSION("1.0");
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>

#include "parking_ioctl.h"

#define DRIVER_NAME "smart_parking"
#define DEVICE_NAME "smart_parking"
#define BUFFER_SIZE 256

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smart Parking System");
MODULE_DESCRIPTION(
    "Linux character device driver for Smart Parking System"
);
MODULE_VERSION("2.0");

static dev_t device_number;
static struct cdev parking_cdev;
static struct class *parking_class;
static struct device *parking_device;

static char device_buffer[BUFFER_SIZE];
static size_t buffer_size;

static DEFINE_MUTEX(parking_mutex);


/*
 * Device open operation
 */
static int parking_open(
    struct inode *inode,
    struct file *file
)
{
    pr_info(
        "smart_parking: device opened\n"
    );

    return 0;
}


/*
 * Device read operation
 */
static ssize_t parking_read(
    struct file *file,
    char __user *user_buffer,
    size_t count,
    loff_t *offset
)
{
    size_t bytes_to_copy;

    if (*offset >= buffer_size) {
        return 0;
    }

    if (mutex_lock_interruptible(&parking_mutex)) {
        return -ERESTARTSYS;
    }

    bytes_to_copy = buffer_size - *offset;

    if (count < bytes_to_copy) {
        bytes_to_copy = count;
    }

    if (copy_to_user(
            user_buffer,
            device_buffer + *offset,
            bytes_to_copy
        )) {

        mutex_unlock(&parking_mutex);

        return -EFAULT;
    }

    *offset += bytes_to_copy;

    mutex_unlock(&parking_mutex);

    pr_info(
        "smart_parking: read %zu bytes\n",
        bytes_to_copy
    );

    return bytes_to_copy;
}


/*
 * Device write operation
 */
static ssize_t parking_write(
    struct file *file,
    const char __user *user_buffer,
    size_t count,
    loff_t *offset
)
{
    size_t bytes_to_copy;

    if (count == 0) {
        return 0;
    }

    if (mutex_lock_interruptible(&parking_mutex)) {
        return -ERESTARTSYS;
    }

    bytes_to_copy = count;

    if (bytes_to_copy >= BUFFER_SIZE) {
        bytes_to_copy = BUFFER_SIZE - 1;
    }

    if (copy_from_user(
            device_buffer,
            user_buffer,
            bytes_to_copy
        )) {

        mutex_unlock(&parking_mutex);

        return -EFAULT;
    }

    device_buffer[bytes_to_copy] = '\0';
    buffer_size = bytes_to_copy;

    mutex_unlock(&parking_mutex);

    pr_info(
        "smart_parking: received %zu bytes\n",
        bytes_to_copy
    );

    return bytes_to_copy;
}


/*
 * IOCTL operation
 */
static long parking_ioctl(
    struct file *file,
    unsigned int command,
    unsigned long argument
)
{
    unsigned int size;

    if (mutex_lock_interruptible(&parking_mutex)) {
        return -ERESTARTSYS;
    }

    switch (command) {

        case SMART_PARKING_IOCTL_GET_BUFFER_SIZE:

            size = (unsigned int)buffer_size;

            if (copy_to_user(
                    (unsigned int __user *)argument,
                    &size,
                    sizeof(size)
                )) {

                mutex_unlock(&parking_mutex);

                return -EFAULT;
            }

            pr_info(
                "smart_parking: ioctl GET_BUFFER_SIZE = %u\n",
                size
            );

            break;


        case SMART_PARKING_IOCTL_CLEAR_BUFFER:

            device_buffer[0] = '\0';
            buffer_size = 0;

            pr_info(
                "smart_parking: ioctl CLEAR_BUFFER\n"
            );

            break;


        default:

            mutex_unlock(&parking_mutex);

            return -ENOTTY;
    }

    mutex_unlock(&parking_mutex);

    return 0;
}


/*
 * Device close operation
 */
static int parking_release(
    struct inode *inode,
    struct file *file
)
{
    pr_info(
        "smart_parking: device closed\n"
    );

    return 0;
}


/*
 * File operations table
 */
static const struct file_operations parking_fops = {
    .owner = THIS_MODULE,
    .open = parking_open,
    .read = parking_read,
    .write = parking_write,
    .release = parking_release,
    .unlocked_ioctl = parking_ioctl,
};


/*
 * Driver initialization
 */
static int __init parking_driver_init(void)
{
    int result;

    pr_info(
        "smart_parking: initializing driver\n"
    );

    result = alloc_chrdev_region(
        &device_number,
        0,
        1,
        DRIVER_NAME
    );

    if (result < 0) {
        pr_err(
            "smart_parking: failed to allocate device number\n"
        );

        return result;
    }

    pr_info(
        "smart_parking: major=%d minor=%d\n",
        MAJOR(device_number),
        MINOR(device_number)
    );

    cdev_init(
        &parking_cdev,
        &parking_fops
    );

    parking_cdev.owner = THIS_MODULE;

    result = cdev_add(
        &parking_cdev,
        device_number,
        1
    );

    if (result < 0) {

        pr_err(
            "smart_parking: failed to add cdev\n"
        );

        unregister_chrdev_region(
            device_number,
            1
        );

        return result;
    }

    parking_class = class_create(
        DRIVER_NAME
    );

    if (IS_ERR(parking_class)) {

        pr_err(
            "smart_parking: failed to create class\n"
        );

        cdev_del(&parking_cdev);

        unregister_chrdev_region(
            device_number,
            1
        );

        return PTR_ERR(parking_class);
    }

    parking_device = device_create(
        parking_class,
        NULL,
        device_number,
        NULL,
        DEVICE_NAME
    );

    if (IS_ERR(parking_device)) {

        pr_err(
            "smart_parking: failed to create device\n"
        );

        class_destroy(parking_class);

        cdev_del(&parking_cdev);

        unregister_chrdev_region(
            device_number,
            1
        );

        return PTR_ERR(parking_device);
    }

    mutex_init(&parking_mutex);

    buffer_size = 0;

    pr_info(
        "smart_parking: driver loaded successfully\n"
    );

    return 0;
}


/*
 * Driver cleanup
 */
static void __exit parking_driver_exit(void)
{
    pr_info(
        "smart_parking: removing driver\n"
    );

    device_destroy(
        parking_class,
        device_number
    );

    class_destroy(
        parking_class
    );

    cdev_del(
        &parking_cdev
    );

    unregister_chrdev_region(
        device_number,
        1
    );

    pr_info(
        "smart_parking: driver removed\n"
    );
}


module_init(parking_driver_init);
module_exit(parking_driver_exit);
