#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QString>

/**
 * @namespace Devices
 */
namespace Devices {

/**
 * @brief Class containing all public resource management facilities of communication device.
 *        The methods of this class shall be used to manage a devices.
 */
class Device {
public:

    /**
     * @brief The DeviceState enum.
     */
    enum DeviceState {
        eDeviceDisconnected,
        eScanInProgress,
        eDeviceConnectionInProgress,
        eDeviceConnected,
        eDeviceDisconnectionInProgress
    };

    /**
     * @brief Retrieves the device object with the given type. If no such device is found, an empty pointer is returned (nullptr).
     *
     * @param type Type of the device to be created and retreived.
     *
     * @return Address of instance.
     */
    static std::shared_ptr<Device> GetDevice(const QString &type);

    /**
     * @brief Dtor
     */
    virtual ~Device(){}

    /**
     * @brief startScan
     * @param timeout
     * @return
     */
    virtual bool startScan(const uint16_t timeout) = 0;

    /**
     * @brief stopScan
     */
    virtual void stopScan() = 0;

    /**
     * @brief connect
     * @param connSettings
     * @return
     */
    virtual bool connect(const QList<QString>& connSettings) = 0;

    /**
     * @brief disconnect
     * @return
     */
    virtual bool disconnect() = 0;

    /**
     * @brief connectToScanFinishedConfirmationSig
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    virtual bool connectToScanFinishedConfirmationSig(QObject *pReceiver, const char *pszSlot, bool bConnect) const = 0;

    /**
     * @brief connectToConnectionConfirmationSig
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    virtual bool connectToConnectionConfirmationSig(QObject *pReceiver, const char *pszSlot, bool bConnect) const = 0;

    /**
     * @brief connectToTxConfirmationSig
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    virtual bool connectToTxConfirmationSig(QObject *pReceiver, const char *pszSlot, bool bConnect) const = 0;

    /**
     * @brief connectToRxIndicationSig
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    virtual bool connectToRxIndicationSig(QObject *pReceiver, const char *pszSlot, bool bConnect) const = 0;

    /**
     * @brief write
     * @param data
     * @return
     */
    virtual bool write(const QByteArray &data) = 0;
};

} // end namespace

#endif // DEVICE_H
