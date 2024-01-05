#ifndef COMWORKER_H
#define COMWORKER_H

#include "error.h"
#include "comdatatypes.h"
#include "pdudatatypes.h"
#include <QThread>
#include <QObject>
#include <QMutex>
#include <QTimer>

/**
 * @namespace Communication
 * @brief Contains communication classes and resources
 */
namespace Communication {

/**
 * @brief The ComStackWorkerThread class
 */
class ComStackWorkerThread: public ComSignal {
    Q_OBJECT

public:

    /**
     * @brief ComStackWorkerThread
     * @param interfaces
     */
    explicit ComStackWorkerThread(TpInterfaceType interfaces);

    /**
     * @brief Dtor
     */
    ~ComStackWorkerThread();

    /**
     * @brief checkMessageIdAndSizeToIpduId
     * @param messageId
     * @param payloadSize
     * @return
     */
    bool checkMessageIdAndSizeToIpduId(const PduIdType messageId, const uint8_t payloadSize);

public slots:

    /**
     * @brief run
     */
    void run();

    /**
     * @brief comRxIndicationSlot
     * @param pduId
     * @param nPdu
     * @return
     */
    Communication::Error comRxIndicationSlot(Communication::PduIdType pduId, QByteArray &nPdu);

    /**
     * @brief registerMessageToIpduSlot
     * @param messageId
     * @param payloadSize
     * @param direction
     * @param txMode
     * @param repetionTimeFactor
     */
    void registerMessageToIpduSlot(
            const Communication::PduIdType             messageId,
            const uint8_t                              payloadSize,
            const Communication::ComIPduDirectionType  direction,
            const Communication::ComIPduTxModeModeType txMode,
            const uint32_t                             repetionTimeFactor);

    /**
     * @brief registerSignalHandleSlot
     * @param pReceiver
     * @param pszSlot
     * @param messageId
     * @param bConnect
     */
    void registerSignalHandleSlot(QObject *pReceiver, const char *pszSlot, const Communication::PduIdType messageId, const bool bConnect);

    /**
     * @brief setIpduStateSlot
     * @param messageId
     * @param state
     */
    void setIpduStateSlot(const Communication::PduIdType messageId, const bool state);

    /**
     * @brief sendMessageSlot
     * @param messageId
     * @param payload
     */
    void sendMessageSlot(Communication::PduIdType messageId, QByteArray &payload);

private:

    /**
     * @brief triggerIPduSend
     * @param pduId
     * @return
     */
    Error triggerIPduSend(const PduIdType pduId);

    /**
     * @brief processMixedOrPeriodicTxMode
     * @param pduId
     * @return
     */
    Error processMixedOrPeriodicTxMode(const PduIdType pduId);

    /**
     * @brief processDirectTxMode
     * @param pduId
     * @return
     */
    Error processDirectTxMode(const PduIdType pduId);

    /**
     * @brief triggerTxOnConditions
     * @param pduId
     * @return
     */
    Error triggerTxOnConditions(const PduIdType pduId);

    // Tp Interface
    TpInterfaceType _interface;

    // Handle I-PDU send timeout
    QTimer * _timer;

    // IPDU data storage
    ComIPduType _ipdu[COM_MAX_NOF_IPDUS];

    // Signals class storage
    ComSignal _signals[COM_MAX_NOF_IPDUS];
};

} // end namespace

#endif // COMWORKER_H
