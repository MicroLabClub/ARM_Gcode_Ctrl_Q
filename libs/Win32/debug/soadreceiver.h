#ifndef SOADRECEIVER_H
#define SOADRECEIVER_H

#include "pdudatatypes.h"
#include "commdefines.h"
#include "soaddatatypes.h"
#include <QObject>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The SoAdReceiver class
 */
class SoAdReceiver: public QObject {
    Q_OBJECT

public:

    /**
     * @brief SoAdReceiver
     */
    explicit SoAdReceiver();

    /**
     * Dtor
     */
    ~SoAdReceiver();

    /**
     * @brief run
     */
    void run();

    /**
     * @brief connectToRduRRxIndicationSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToRduRRxIndicationSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const;

public slots:

    /**
     * @brief rxIndicationSlot
     * @param netPdu
     */
    void rxIndicationSlot(QByteArray &netPdu);

signals:

    /**
     * @brief pduRRxIndicationSig
     * @param pduId
     * @param netPdu
     */
    void pduRRxIndicationSig(Communication::PduIdType pduId, QByteArray &netPdu);
};

} // end namespace

#endif // SOADRECEIVER_H
