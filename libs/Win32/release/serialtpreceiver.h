#ifndef SERIALTPRECEIVER_H
#define SERIALTPRECEIVER_H

#include "pdudatatypes.h"
#include <QObject>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The SerialTpReceiver class
 */
class SerialTpReceiver: public QObject {
    Q_OBJECT

public:

    /**
     * @brief SerialTpReceiver
     */
    explicit SerialTpReceiver();

    /**
     * Dtor
     */
    ~SerialTpReceiver();

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

#endif // SERIALRECEIVER_H
