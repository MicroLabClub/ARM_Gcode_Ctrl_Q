#ifndef PDUDATATYPES_H
#define PDUDATATYPES_H

#include <QObject>

/**
 * @namespace Communication
 */
namespace Communication {

    /**
     * @brief PduLengthType
     */
    typedef uint16_t PduLengthType;

    /**
     * @brief PduIdType
     */
    typedef uint8_t PduIdType;

    /**
     * @brief The PduInfoType struct
     */
    struct PduInfoType
    {
        const uint8_t  * sduDataPtr;
              uint16_t   sduLength;
    };

} // end namespace

#endif // PDUDATATYPES_H
