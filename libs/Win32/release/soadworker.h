#ifndef SOADWORKER_H
#define SOADWORKER_H

#include "device.h"
#include <QObject>
#include <QList>
#include <QString>
#include <QByteArray>
#include <atomic>

/**
 * @namespace Communication
 */
namespace Communication {

using namespace Devices;

/**
 * @brief The SoAdWorker class
 */
class SoAdWorker: public QObject {
    Q_OBJECT

public:

    /**
     * @brief SoAdWorker
     */
    explicit SoAdWorker();

    /**
     * @brief Dtor
     */
    ~SoAdWorker();

    /**
     * @brief getConnectionStatus
     * @return
     */
    bool getConnectionStatus();

public slots:

    /**
     * @brief connectSlot
     * @param connSettings
     */
    void connectSlot(QList<QString> &connSettings);

    /**
     * @brief disconnectSlot
     */
    void disconnectSlot();

    /**
     * @brief connectStatusSlot
     * @param connStatus
     */
    void connectStatusSlot(bool connStatus);

    /**
     * @brief transmitSlot
     * @param netPdu
     */
    void transmitSlot(QByteArray &netPdu);

    /**
     * @brief txConfirmationSlot
     * @param writtenBytes
     */
    void txConfirmationSlot(qint64 writtenBytes);

    /**
     * @brief rxIndicationSlot
     * @param netPdu
     */
    void rxIndicationSlot(QByteArray &netPdu);

signals:

    /**
     * @brief connectionStatusSig
     * @param connStatus
     */
    void connectionStatusSig(bool connStatus);

    /**
     * @brief txConfirmationSig
     * @param writtenBytes
     */
    void txConfirmationSig(qint64 writtenBytes);

    /**
     * @brief rxIndicationSig
     * @param netPdu
     */
    void rxIndicationSig(QByteArray &netPdu);

private:

    // Connection indication
    std::atomic<bool> _isConnected;

    // Connection settings
    QList<QString> _connSetting;

    // Device interface
    std::shared_ptr<Device> _device;
};

} // end namespace

#endif // SOADWORKER_H
