#ifndef GCODECONTORLLER_H
#define GCODECONTORLLER_H

#include "arscoreglobal.h"
#include "controller.h"
#include "comm.h"
#include <QObject>

namespace Controller {

using namespace Communication;

/**
 * @brief The GcodeController class
 *        This class contains controller managment interfaces
 */
class ARSCORE_EXPORT GcodeController : public QObject, public Controller {
    Q_OBJECT

    #define TIMEOUT   1000 // Default connection timeout in milliseconds

public:

    /**
     * @brief Controller
     * @param parent
     */
    explicit GcodeController(QObject *parent = nullptr);

    /**
     * Dtor.
     */
    ~GcodeController();

    /**
     * @brief connect
     * @param comPort
     * @param baudRate
     * @return
     */
    bool connect(QString &comPort, QString &baudRate) override;

    /**
     * @brief disconnect
     */
    void disconnect() override;

    /**
     * @brief connectToConnectionStatusSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToConnectionStatusSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const override;

    /**
     * @brief connectToCommandResponseSignal
     * @param pReceiver
     * @param pszSlot
     * @param bConnect
     * @return
     */
    bool connectToCommandResponseSignal(QObject *pReceiver, const char *pszSlot, bool bConnect) const override;

    /**
     * @brief calibrate
     */
    bool calibrate() override;

    /**
     * @brief goHome
     * @return
     */
    bool goHome() override;

    /**
     * @brief setPosition
     * @param x
     * @param y
     * @param z
     * @param a
     * @param b
     * @return
     */
    bool setPosition(double x, double y, double z, double a, double b) override;

    /**
     * @brief getPosition
     * @param x
     * @param y
     * @param z
     * @param a
     * @param b
     */
    void getPosition(double *x, double *y, double *z, double *a, double *b) const override;

    /**
     * @brief setCommand
     * @param cmd
     * @return
     */
    bool setCommand(QString &cmd) override;

    /**
     * @brief setSpeed
     * @param speed
     * @return
     */
    bool setSpeed(uint8_t speed) override;

    /**
     * @brief getSpeed
     * @return
     */
    uint8_t getSpeed() const override;

    void pumpOff() override;
    void pumpOn() override;
    void releaseStart() override;
    void catchStart() override;

    /**
     * @brief getState
     * @return
     */
    Controller::ControllerJobState getState() const override;

    /**
     * @brief getCalibState
     * @return
     */
    Controller::ControllerCalibState getCalibState() const override;

private slots:

    /**
     * @brief onCallbackConnectionStatusChangedSlot
     * @param status
     */
    void onCallbackConnectionStatusChangedSlot(const bool status);

    /**
     * @brief onMessageCallbackSlot
     * @param data
     */
    void onMessageCallbackSlot(const QByteArray &data);

signals:

    /**
     * @brief connectionStatusChangedSignal
     * @param status
     */
    void connectionStatusChangedSignal(bool status);

    /**
     * @brief commandResponseSignal
     * @param response
     */
    void commandResponseSignal(Controller::Controller::ControllerCmdResponse response);

private:

    // Communication stack
    std::shared_ptr<ComM> _comM;

    // Current controller state
    std::atomic<Controller::ControllerState> _controllerState;

    // Current controller job state
    std::atomic<Controller::ControllerJobState> _controllerJobState;

    // Current controller calibration state
    std::atomic<Controller::ControllerCalibState> _controllerCalibState;

    // Controller current position
    std::atomic<double> _x;
    std::atomic<double> _y;
    std::atomic<double> _z;
    std::atomic<double> _a;
    std::atomic<double> _b;

    std::atomic<double> _xTemp;
    std::atomic<double> _yTemp;
    std::atomic<double> _zTemp;
    std::atomic<double> _aTemp;
    std::atomic<double> _bTemp;

    std::atomic<uint8_t> _speed;
    std::atomic<uint8_t> _speedTemp;
};

} // end namespace

#endif // GCODECONTORLLER_H
