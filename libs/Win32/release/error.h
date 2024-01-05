#ifndef ERROR_H
#define ERROR_H

#include <QObject>

/**
 * @namespace Communication
 */
namespace Communication {

/**
 * @brief The Error enum
 */
enum Error {
    ErrNone            =  0, //!< No error, success.
    ErrParam           =  1, //!< Invalid parameter supplied, e.g. NULL pointer supplied.
    ErrParamVal        =  2, //!< Invalid parameter value supplied.
    ErrNotSupported    =  3, //!< Functionality is not supported.
    ErrNotImplemented  =  4, //!< Functionality is not (yet) implemented.
    ErrNotAvailable    =  5, //!< Desired entity is not available.
    ErrNotActive       =  6, //!< Desired entity is not active.
    ErrNotExpected     =  7, //!< Received data not expected.
    ErrType            =  8, //!< Invalid type supplied.
    ErrSize            =  9, //!< Invalid size supplied.
    ErrRange           = 10, //!< Range error.
    ErrOutOfMemory     = 11, //!< No more memory available.
    ErrBufferOverflow  = 12, //!< Buffer to small to yield intended data.
    ErrNoData          = 13, //!< No data available.
    ErrNoNet           = 14, //!< Connection lost.
    ErrDenied          = 15, //!< Access denied.
    ErrTime            = 16, //!< Timeout.
    ErrIo              = 17, //!< IO error while performing action.
    ErrHandle          = 18, //!< Handle error, invalid or uninitialized handled supplied.
    ErrLayer           = 19, //!< Layer error, a layer specific error code.
    ErrBusy            = 20, //!< Busy error, a command is still running.
    ErrCorrupted       = 21, //!< Message or data corrupted.
    ErrOs              = 22, //!< Os error.
    ErrBufferUnderflow = 23, //!< Buffer contains less data than expected.
    ErrExecution       = 24, //!< Desired action or function couldn't be executed successful, a refined entity specific error code is available for further evaluation.
    ErrInterface       = 25, //!< Invalid interface Supplied.
    ErrId              = 26, //!< Invalid id supplied.
    ErrOffset          = 27, //!< Invalid offset supplied.
    ErrNotPossible     = 28, //!< Functionality can't be executed in the entities current state.
    ErrIndex           = 29, //!< Invalid index supplied.

    /* --- */
    ErrLast, //!< Internal Limit. Do NOT use as error code.
};

} // end namespace

#endif // ERROR_H
