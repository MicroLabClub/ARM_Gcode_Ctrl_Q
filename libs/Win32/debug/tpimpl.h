#ifndef TPIMPL_H
#define TPIMPL_H

#include "tp.h"
#include "pdudatatypes.h"
#include <QSharedPointer>
#include <QObject>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The TpImpl class
 */
class TpImpl {
public:

    /**
     * @brief GetTp Retrieves the transport object with the given type.
     *              If no such transport interface is found, an empty pointer is returned (nullptr).
     *
     * @param type  Type of the transport interface to be created and retreived.
     *
     * @return Tp address.
     */
    static Tp *GetTp(const QString &type);

    /**
     * @brief ~TpImpl
     */
    virtual ~TpImpl();
};

} // end namespace

#endif // TPIMPL_H
