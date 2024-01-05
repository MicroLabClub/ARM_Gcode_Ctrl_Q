#ifndef COM_H
#define COM_H

#include "comworker.h"
#include <QThread>
#include <QObject>

/**
 * @namespace Communication
 * @brief Contains communication stack classes and resources
 */
namespace Communication {

/**
 * @brief The Com class
 */
class Com : public QObject {
    Q_OBJECT

public:

    /**
     * @brief Com
     * @param interface
     */
    explicit Com(TpInterfaceType interface);

    /**
     * @brief Dtor
     */
    ~Com();

    /**
     * @brief comCreateMessage
     * @param messageId
     * @param payloadSize
     * @param direction
     * @param txMode
     * @param repetionTimeFactor
     * @return
     */
    bool comCreateMessage(
            const PduIdType             messageId,
            const uint8_t               payloadSize,
            const ComIPduDirectionType  direction,
            const ComIPduTxModeModeType txMode,
            const uint32_t              repetionTimeFactor);

    /**
     * @brief comRegisterMessageRecivedHanler
     * @param pReceiver
     * @param pszSlot
     * @param messageId
     * @param bConnect
     * @return
     */
    bool comRegisterMessageRecivedHanler(QObject *pReceiver, const char *pszSlot, const PduIdType messageId, const bool bConnect);

    /**
     * @brief comSetMessageState
     * @param messageId
     * @param state
     * @return
     */
    bool comSetMessageState(const PduIdType messageId, const bool state);

    /**
     * @brief comSendMessage
     * @param messageId
     * @param payload
     * @return
     */
    bool comSendMessage(PduIdType messageId, QByteArray &payload);

signals:

    /**
     * @brief registerMessageToIpduSignal
     * @param messageId
     * @param payloadSize
     * @param direction
     * @param txMode
     * @param repetionTimeFactor
     */
    void registerMessageToIpduSignal(
            const Communication::PduIdType             messageId,
            const uint8_t                              payloadSize,
            const Communication::ComIPduDirectionType  direction,
            const Communication::ComIPduTxModeModeType txMode,
            const uint32_t                             repetionTimeFactor);

    /**
     * @brief registerSignalHandleSignal
     * @param pReceiver
     * @param pszSlot
     * @param messageId
     * @param bConnect
     */
    void registerSignalHandleSignal(QObject *pReceiver, const char *pszSlot, const Communication::PduIdType messageId, const bool bConnect);

    /**
     * @brief setIpduStateSignal
     * @param pduId
     * @param state
     * @return
     */
    void setIpduStateSignal(const Communication::PduIdType pduId, const bool state);

    /**
     * @brief sendMessageSignal
     * @param messageId
     * @param payload
     */
    void sendMessageSignal(Communication::PduIdType messageId, QByteArray &payload);

private:

    /**
     * @brief stopWorker
     */
    void stopWorker();

    // Communication stack's worker thread
    QThread _comStackThread;
    Communication::ComStackWorkerThread * _comStackWorkerThread;
};

} // end namespace

#endif // COM_H
