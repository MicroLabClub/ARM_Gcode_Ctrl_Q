#ifndef COMSIGNAL_H
#define COMSIGNAL_H

#include <QObject>

/**
 * @namespace Communication
 * @brief Contains communication signal class.
 */
namespace Communication {

/**
 * @brief The ComSignal class
 */
struct ComSignal : public QObject {
    Q_OBJECT

signals:

    /**
     * @brief notificationMessageReceivedSignal
     * @param payload
     */
    void notificationMessageReceivedSignal(const QByteArray &payload);
};

}

#endif // COMSIGNAL_H
