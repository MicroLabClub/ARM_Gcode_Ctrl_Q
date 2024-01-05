#ifndef SOAD_H
#define SOAD_H

#include "tpdatatypes.h"
#include "tp.h"
#include "soadworker.h"
#include "soadtransmiter.h"
#include "soadreceiver.h"
#include <QObject>
#include <QString>
#include <QList>
#include <QThread>
#include <QTimer>
#include <atomic>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The SoAd class
 */
class SoAd : public QObject, public Tp {
    Q_OBJECT

public:

    /**
     * @brief SerialTp
     */
    explicit SoAd();

    /**
     * @brief ~SerialTp
     */
    virtual ~SoAd();

    /**
     * @brief connect
     * @param connSettings
     * @return
     */
    bool connect(QList<QString> &connSettings) override;

    /**
     * @brief disconnect
     */
    void disconnect() override;

    /**
     * @brief connectToConnectionStatusSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToConnectionStatusSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const override;

    /**
     * @brief connectToRxIndicationSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToRxIndicationSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const override;

    /**
     * @brief transmit
     * @param pduId
     * @param pduInfo
     * @return
     */
    uint32_t transmit(const Communication::PduIdType pduId, const Communication::PduInfoType * pduInfo) override;

public slots:

    /**
     * @brief connectionStatusSlot
     * @param connStatus
     */
    void connectionStatusSlot(bool connStatus);

signals:

    /**
     * @brief connectSig
     * @param connSettings
     */
    void connectSig(QList<QString> &connSettings);

    /**
     * @brief disconnectSig
     */
    void disconnectSig();

    /**
     * @brief connectionIndicationSig
     * @param status
     * @param id
     * @return
     */
    bool connectionIndicationSig(bool status, uint8_t id);

    /**
     * @brief transmitSig
     * @param txPduId
     * @param netPdu
     */
    void transmitSig(Communication::PduIdType txPduId, QByteArray& netPdu);

private:

    /**
     * @brief startDeviceWorker
     */
    void startDeviceWorker();

    /**
     * @brief startTransmiter
     */
    void startTransmiter();

    /**
     * @brief startReceiver
     */
    void startReceiver();

    // Connection indication status
    std::atomic<TpConnectionState> _connectionState;

    // Interface ID
    uint8_t _id;

    // Worker thread
    QThread _txThread;
    QThread _rxThread;
    QThread _devWorkerThread;

    // Worker thread
    SoAdWorker     * _soadDevWorkerThread;
    SoAdTransmiter * _soadTxWorkerThread;
    SoAdReceiver   * _soadRxWorkerThread;
};

} // end namespace

#endif // SOAD_H
