#ifndef WEBSOCKSERVER_H
#define WEBSOCKSERVER_H

#include <device.h>
#include <QObject>
#include <QtWebSockets/QtWebSockets>
#include <QtWebSockets/QWebSocketServer>

namespace Devices {

#define DEV_CONN_SETTINGS_SIZE      ((qsizetype)5)

class WebSockServer : public QObject, public Device {
    Q_OBJECT

    #define TIMEOUT   1000 // Default connection timeout in milliseconds

public:

    explicit WebSockServer(QObject *parent = nullptr);

    /**
     * @brief startScan
     * @param timeout
     * @return
     */
    bool startScan(const uint16_t timeout) override;

    /**
     * @brief stopScan
     */
    void stopScan() override;

    /**
     * @brief connectToDev
     * @param connSettings
     * @return
     */
    bool connect(const QList<QString> &connSettings) override;

    /**
     * @brief disconnect
     * @return
     */
    bool disconnect() override;

    /**
     * @brief connectToScanFinishedConfirmationSig
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToScanFinishedConfirmationSig(QObject *pReceiver, const char *pszSlot, bool bConnect) const override;

    /**
     * @brief connectToConnectionConfirmationSig
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToConnectionConfirmationSig(QObject *pReceiver, const char *pszSlot, bool bConnect) const override;

    /**
     * @brief connectToTxConfirmationSig
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToTxConfirmationSig(QObject *pReceiver, const char *pszSlot, bool bConnect) const override;

    /**
     * @brief connectToRxIndicationSig
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToRxIndicationSig(QObject *pReceiver, const char *pszSlot, bool bConnect) const override;

    /**
     * @brief write
     * @param data
     * @return
     */
    bool write(const QByteArray &data) override;

public slots:

    /**
     * @brief deviceConnectedSlot
     */
    void deviceConnectedSlot();

    /**
     * @brief deviceDisconnectedSlot
     */
    void deviceDisconnectedSlot();

    /**
     * @brief bytesWrittenSlot
     * @param bytes
     */
    void bytesWrittenSlot(const qint64 bytes);

    /**
     * @brief readyReadTextSlot
     * @param message
     */
    void readyReadTextSlot(const QString &message);

    /**
     * @brief readyReadSlot
     */
    void readyReadSlot(const QByteArray &data);

signals:

    /**
     * @brief connectionConfirmationSig
     * @param connStatus
     */
    void connectionConfirmationSig(const bool connStatus);

    /**
     * @brief txConfirmationSig
     * @param writtenBytes
     */
    void txConfirmationSig(qint64 writtenBytes);

    /**
     * @brief rxIndicationSig
     * @param data
     */
    void rxIndicationSig(QByteArray &data);

private:

    // Current device state
    std::atomic<Device::DeviceState> _devState;

    // Device connection settings
    QList<QString> _connSettings;

    // Socket and server device
    QWebSocketServer *_server;
    QWebSocket *_socket;
};

} // end namespace

#endif // WEBSOCKSERVER_H
