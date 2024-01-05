#ifndef TPDATATYPES_H
#define TPDATATYPES_H

#include <QObject>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The TpConnectionState enum.
 */
enum TpConnectionState {
    eTpDisconnected,
    eTpConnectionInProgress,
    eTpDisconnectionInProgress,
    eTpConnected,
};

} // end namespace

#endif // TPDATATYPES_H
