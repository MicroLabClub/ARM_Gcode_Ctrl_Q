#ifndef SERIALTPTRANSMITER_H
#define SERIALTPTRANSMITER_H

#include "pdudatatypes.h"
#include <QObject>
#include <QMutex>
#include <QSemaphore>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The SerialTpTransmiter class
 */
class SerialTpTransmiter: public QObject {
    Q_OBJECT

public:

    /**
     * @brief SerialTpTransmiter
     */
    explicit SerialTpTransmiter();

    /**
     * Dtor
     */
    ~SerialTpTransmiter();

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

#endif // SERIALTRANSMITER_H
