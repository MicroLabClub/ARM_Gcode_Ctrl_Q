#ifndef SERIALTPDATATYPES_H
#define SERIALTPDATATYPES_H

#include <QObject>

/**
 * @namespace SerialTpDataTypes
 * @brief Contain serial adapter's transport data types
 */
namespace SerialTpDataTypes {

/**
 * @brief The SerialHeaderType class
 */
struct SerialTpHeaderType
{
    uint8_t stx1;
    uint8_t stx2;
    uint8_t clientAddr;
    uint8_t serverAddr;
    uint8_t sduLenght;
    uint8_t pduId;
    uint8_t ack;
};

} // end namespace

#endif // SERIALTPDATATYPES_H
