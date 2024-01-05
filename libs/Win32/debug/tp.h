#ifndef ITPINTERFACE_H
#define ITPINTERFACE_H

#include "pdudatatypes.h"
#include <QObject>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief Class containing all public resource management facilities of communication transport interface.
 *        The methods of this class shall be used to manage a transport interface.
 */
class Tp {
public:

    /**
     * @brief GetTp
     * @param type
     * @return
     */
    static Tp * GetTp(const QString &type);

    /**
     * @brief Dtor.
     */
    virtual ~Tp(){}

    /**
     * @brief connect
     * @param tpSettings
     * @return
     */
    virtual bool connect(QList<QString> &tpSettings) = 0;

    /**
     * @brief disconnect
     */
    virtual void disconnect() = 0;

    /**
     * @brief connectToConnectionStatusSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    virtual bool connectToConnectionStatusSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const = 0;

    /**
     * @brief connectToRxIndicationSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */

    virtual bool connectToRxIndicationSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const = 0;
    /**
     * @brief transmit
     * @param txPduId
     * @param pduInfo
     * @return
     */
    virtual uint32_t transmit(const PduIdType txPduId, const PduInfoType *pduInfo) = 0;
};

} // end namespace

#endif // ITPINTERFACE_H
