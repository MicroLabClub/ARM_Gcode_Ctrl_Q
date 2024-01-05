#ifndef COMM_H
#define COMM_H

#include "arscoreglobal.h"
#include "pdudatatypes.h"
#include "comdatatypes.h"
#include <QObject>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief Class containing all public resource management facilities of communication manager interface.
 *        The methods of this class shall be used to manage a communication.
 */
class ARSCORE_EXPORT ComM {
public:

    /**
     * @brief GetComM
     * @return
     */
    static std::shared_ptr<ComM> GetComM();

    /**
     * @brief Dtor
     */
    virtual ~ComM(){}

    /**
     * @brief connect
     * @param settings
     * @return
     */
    virtual bool connect(QList<QString> &settings) = 0;

    /**
     * @brief disconnect
     * @return
     */
    virtual bool disconnect() = 0;

    /**
     * @brief createMessage
     * @param messageId
     * @param payloadSize
     * @param direction
     * @param txMode
     * @param repetionTimeFactor
     * @return
     */
    virtual bool createMessage(
            const PduIdType             messageId,
            const uint8_t               payloadSize,
            const ComIPduDirectionType  direction,
            const ComIPduTxModeModeType txMode,
            const uint32_t              repetionTimeFactor) const = 0;

    /**
     * @brief registerStateHandler
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    virtual bool registerStateHandler(QObject *pReceiver, const char *pszSlot, const bool bConnect) const = 0;

    /**
     * @brief registerSignalHandler
     * @param pReceiver
     * @param pszSlot
     * @param meessageId
     * @param bConnect
     * @return
     */
    virtual bool registerSignalHandler(QObject *pReceiver, const char *pszSlot, const PduIdType meessageId, const bool bConnect) = 0;

    /**
     * @brief setMessageState
     * @param messageId
     * @param state
     * @return
     */
    virtual bool setMessageState(const PduIdType messageId, const bool state) = 0;

    /**
     * @brief sendMessage
     * @param messageId
     * @param payload
     * @return
     */
    virtual bool sendMessage(PduIdType messageId, QByteArray &payload) = 0;
};

} // end namespace

#endif // COMM_H
