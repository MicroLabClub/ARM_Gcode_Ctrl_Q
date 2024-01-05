#ifndef SOADTRANSMITER_H
#define SOADTRANSMITER_H

#include "pdudatatypes.h"
#include <QObject>
#include <QMutex>
#include <QSemaphore>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The SoAdTransmiter class
 */
class SoAdTransmiter: public QObject {
    Q_OBJECT

public:

    /**
     * @brief SoAdTransmiter
     */
    explicit SoAdTransmiter();

    /**
     * Dtor
     */
    ~SoAdTransmiter();

public slots:

    /**
     * @brief transmitSlot
     * @param txPduId
     * @param netPdu
     */
    void transmitSlot(const Communication::PduIdType txPduId, const QByteArray &netPdu);

    /**
     * @brief txConfirmationSlot
     * @param writtenBytes
     */
    void txConfirmationSlot(qint64 writtenBytes);

signals:

    /**
     * @brief transmitSig
     * @param netPdu
     */
    void transmitSig(QByteArray &netPdu);

private:

};

} // end namespace

#endif // SOADTRANSMITER_H
