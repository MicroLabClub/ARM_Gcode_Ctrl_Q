#ifndef COMMIMPL_H
#define COMMIMPL_H

#include "comm.h"
#include "com.h"
#include "tp.h"
#include <QObject>
#include <QSharedPointer>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The ComMImpl class
 */
class ComMImpl : public QObject, public ComM {
    Q_OBJECT

public:

    /**
     * @brief The ComMConnectionState enum
     */
    enum ComMConnectionState {
        eComMDisconnected,
        eComMConnectionInProgress,
        eComMDisconnectionInProgress,
        eComMConnected,
    };

    /**
     * @brief GetComM
     * @return
     */
    static std::shared_ptr<ComMImpl> GetComM();

    /**
     * @brief Dtor
     */
    virtual ~ComMImpl();

    /**
     * @brief connect
     * @param settings
     * @return
     */
    bool connect(QList<QString> &settings) override;

    /**
     * @brief disconnect
     * @return
     */
    bool disconnect() override;

    /**
     * @brief registerStateHandler
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool registerStateHandler(QObject *pReceiver, const char *pszSlot, const bool bConnect) const override;

    /**
     * @brief createMessage
     * @param messageId
     * @param payloadSize
     * @param direction
     * @param txMode
     * @param repetionTimeFactor
     * @return
     */
    bool createMessage(
            const PduIdType             messageId,
            const uint8_t               payloadSize,
            const ComIPduDirectionType  direction,
            const ComIPduTxModeModeType txMode,
            const uint32_t              repetionTimeFactor) const override;

    /**
     * @brief registerSignalHandler
     * @param pReceiver
     * @param pszSlot
     * @param messageId
     * @param bConnect
     * @return
     */
    bool registerSignalHandler(QObject *pReceiver, const char *pszSlot, const PduIdType messageId, const bool bConnect) override;

    /**
     * @brief setMessageState
     * @param messageId
     * @param state
     * @return
     */
    bool setMessageState(const PduIdType messageId, const bool state) override;

    /**
     * @brief sendMessage
     * @param messageId
     * @param payload
     * @return
     */
    bool sendMessage(PduIdType messageId, QByteArray &payload) override;

public slots:

    /**
     * @brief connectionStatusSlot
     * @param connStatus
     */
    void connectionStatusSlot(bool connStatus);

signals:

    /**
     * @brief connectionStatusSignal
     * @param connStatus
     */
    void connectionStatusSignal(bool connStatus);

private:

    // Communication stack
    QSharedPointer<Com> _com;

    // Transport interface
    QSharedPointer<Tp> _tpIf;

    // Connection indication status
    std::atomic<ComMConnectionState> _connectionState{eComMDisconnected};
};

} // end namespace

#endif // COMMIMPL_H
