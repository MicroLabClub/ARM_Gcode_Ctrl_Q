#ifndef SOADDATATYPES_H
#define SOADDATATYPES_H

#include <QObject>

/**
 * @namespace SoAdDataTypes
 * @brief Contain socket adapter's transport data types
 */
namespace SoAdDataTypes {

/**
 * @brief The SoAdHeaderType class
 */
struct SoAdHeaderType
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
