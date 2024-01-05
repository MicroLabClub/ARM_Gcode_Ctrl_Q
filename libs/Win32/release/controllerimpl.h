#ifndef CONTROLLERIMPL_H
#define CONTROLLERIMPL_H

#include "controller.h"
#include <QSharedPointer>
#include <QObject>

/**
 * @namespace Controller
 */
namespace Controller {

/**
 * @brief The ControllerImpl class
 */
class ControllerImpl {
public:

    /**
     * @brief GetController Retrieves the controller object with the given type.
     *              If no such controller interface is found, an empty pointer is returned (nullptr).
     *
     * @param type  Type of the controller interface to be created and retreived.
     *
     * @return Tp address.
     */
    static Controller *GetController(const QString &type);

    /**
     * @brief ~ControllerImpl
     */
    virtual ~ControllerImpl();
};

} // end namespace

#endif // CONTROLLERIMPL_H
