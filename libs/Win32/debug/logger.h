#ifndef LOGGER_H
#define LOGGER_H

#include "arscorejoystick_global.h"
#include <string>
#include <memory>
#include <functional>

/**
 * @brief The Logger class.
 */
class ARSCOREJOYSTICK_EXPORT Logger {
public:

    /**
     * @brief The Level enum
     */
    enum Level {
        CRITICAL,
        WARNING,
        INFO,
        DEBUG
    };

    /**
     * @brief CreateLogger
     * @param func
     */
    static void CreateLogger(std::function<std::shared_ptr<Logger>()> func);

    /**
     * @brief GetLogger
     * @return
     */
    static std::shared_ptr<Logger> GetLogger();

    /**
     * @brief Dtor
     */
    virtual ~Logger() {}

    /**
     * @brief logMessage
     */
    virtual void logMessage(std::string&& /* msg */, Level /* lvl */, std::string /* domain */) {}
};

#endif // NCGLOGGER_H
