#ifndef DEVICEIMPL_H
#define DEVICEIMPL_H

#include "device.h"

/**
 * @namespace Devices.
 */
namespace Devices {

/**
 * @brief Class containing all public resource management facilities of communication device.
 *        The methods of this class shall be used to create instances of all the devices provided by configuration.
 */
class DeviceImpl : public Device {
public:

    /**
     * @brief Retrieves the device object with the given type. If no such device is found, an empty pointer is returned (nullptr).
     *
     * @param type Type of the device to be created and retreived.
     *
     * @return Address of instance.
     */
    static std::shared_ptr<Device> GetDevice(const QString &type);

    /**
     * @brief ~DeviceImpl
     */
    virtual ~DeviceImpl();
};

} // end namespace

#endif // DEVICEIMPL_H
