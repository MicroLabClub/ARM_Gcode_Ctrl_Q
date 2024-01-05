#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "arscoreglobal.h"
#include <QObject>

/**
 * @namespace Controller
 */
namespace Controller {

/**
 * @brief Class containing all public resource management facilities of controller interface.
 *        The methods of this class shall be used to manage a controller interface.
 */
class ARSCORE_EXPORT Controller {
public:

    /**
     * @brief The ControllerState enum
     */
    enum ControllerState {
        eControllerDisconnected,
        eControllerConnectionInProgress,
        eControllerDisconnectionInProgress,
        eControllerConnected
    };

    /**
     * @brief The ControllerJobState enum
     */
    enum ControllerJobState {
        eControllerJobStopped,
        eControllerJobIni,
        eControllerJobCalib,
        eControllerJobHome,
        eControllerJobSetPos,
        eControllerJobSetSpeed,
        eControllerJobSetGpio
    };

    /**
     * @brief The ControllerCalibState enum
     */
    enum ControllerCalibState {
        eControllerNotCalibrated,
        eControllerCalibrationIntialized,
        eControllerCalibrated
    };

    /**
     * @brief The ControllerCmdResponse enum
     */
    enum ControllerCmdResponse {
        eControllerIntializedCmdResp,
        eControllerCalibratedCmdResp,
        eControllerHomeCmdResp,
        eControllerSetPosCmdResp,
        eControllerSetSpeedCmdResp,
        eControllerGripperCmdReps
    };

    /**
     * @brief GetController
     * @param type
     * @return
     */
    static Controller * GetController(const QString &type);

    /**
     * @brief Dtor.
     */
    virtual ~Controller(){}

    /**
     * @brief connect
     * @param comPort
     * @param baudRate
     * @return
     */
    virtual bool connect(QString &comPort, QString &baudRate) = 0;

    /**
     * @brief disconnect
     */
    virtual void disconnect() = 0;

    /**
     * @brief connectToConnectionStatusSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    virtual bool connectToConnectionStatusSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const = 0;

    /**
     * @brief connectToCommandResponseSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    virtual bool connectToCommandResponseSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const = 0;

    /**
     * @brief calibrate
     * @return
     */
    virtual bool calibrate() = 0;

    /**
     * @brief goHome
     * @return
     */
    virtual bool goHome() = 0;

    /**
     * @brief setPosition
     * @param x
     * @param y
     * @param z
     * @param b
     * @return
     */
    virtual bool setPosition(double x, double y, double z, double a, double b) = 0;

    /**
     * @brief getPosition
     * @param x
     * @param y
     * @param z
     * @param a
     * @param b
     */
    virtual void getPosition(double *x, double *y, double *z, double *a, double *b) const = 0;

    /**
     * @brief setCommand
     * @param cmd
     * @return
     */
    virtual bool setCommand(QString &cmd) = 0;

    /**
     * @brief setSpeed
     * @param speed
     * @return
     */
    virtual bool setSpeed(uint8_t speed) = 0;

    /**
     * @brief getSpeed
     * @return
     */
    virtual uint8_t getSpeed() const = 0;

    virtual void pumpOff() = 0;
    virtual void pumpOn() = 0;
    virtual void releaseStart() = 0;
    virtual void catchStart() = 0;

    /**
     * @brief getState
     * @return
     */
    virtual Controller::ControllerJobState getState() const = 0;

    /**
     * @brief getCalibState
     * @return
     */
    virtual Controller::ControllerCalibState getCalibState() const = 0;
};

} // end namespace

#endif // CONTROLLER_H
