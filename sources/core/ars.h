#ifndef ARS_H
#define ARS_H

#include "controller.h"
#include "workers/stdworker.h"
#include "workers/jogworker.h"
#include "workers/teachworker.h"
#include "workers/fileworker.h"
#include <QObject>

/**
 * @brief The Ars class
 */
class Ars : public QObject {
    Q_OBJECT

    Q_PROPERTY(Controller::Controller::ControllerState connectionState READ connectionState WRITE setConnectionState NOTIFY connectionStateChangedSignal);
    Q_PROPERTY(Controller::Controller::ControllerCalibState calibState READ calibState WRITE setCalibState NOTIFY calibStateChangedSignal);
    Q_PROPERTY(uint8_t speed READ speed WRITE setSpeed NOTIFY speedChangedSignal);
    Q_PROPERTY(std::vector<double> position READ position WRITE setPosition NOTIFY positionChangedSignal);

public:

    /**
     * @brief Ars
     * @param parent
     */
    explicit Ars(QObject *parent = nullptr);

    /**
     * Dtor.
     */
    ~Ars();

    /**
     * @brief start
     */
    void start();

    /**
     * @brief stop
     */
    void stop();

    /**
     * @brief calibrate
     */
    bool calibrate();

    /**
     * @brief home
     */
    bool home();

    /**
     * @brief jogModeStart
     */
    void jogModeStart();

    /**
     * @brief jogModeStop
     */
    void jogModeStop();

    /**
     * @brief teachModeStart
     */
    void teachModeStart();

    /**
     * @brief teachModeStop
     */
    void teachModeStop();

    /**
     * @brief fileModeStart
     */
    void fileModeStart();

    /**
     * @brief fileModeStop
     */
    void fileModeStop();

    /**
     * @brief pumpOff
     */
    void pumpOff();

    /**
     * @brief pumpOn
     */
    void pumpOn();

    /**
     * @brief releaseStart
     */
    void releaseStart();

    /**
     * @brief catchStart
     */
    void catchStart();

    Controller::Controller::ControllerState connectionState() const
    {
        return _connectionState;
    }

    Controller::Controller::ControllerCalibState calibState() const
    {
        return _calibState;
    }

    uint8_t speed() const
    {
        return _speed;
    }

    std::vector<double> position() const
    {
        return _position;
    }

signals:

    void connectionStateChangedSignal(Controller::Controller::ControllerState);
    void calibStateChangedSignal(Controller::Controller::ControllerCalibState);
    void speedChangedSignal(uint8_t speed);
    void positionChangedSignal(std::vector<double> position);

private slots:

    void onControllerCallbackStateChangedSlot(const bool status);
    void onWorkerCmdFinishedCallbackStateChangedSlot(Controller::Controller::ControllerCmdResponse response);

private:

    void setConnectionState(Controller::Controller::ControllerState connectionState)
    {
           _connectionState = connectionState;
           emit connectionStateChangedSignal(connectionState);
    }

    void setCalibState(Controller::Controller::ControllerCalibState calibState)
    {
           _calibState = calibState;
           emit calibStateChangedSignal(calibState);
    }

    void setSpeed(uint8_t speed)
    {
           _speed = speed;
           emit speedChangedSignal(_speed);
    }

    void setPosition(std::vector<double> position)
    {
           _position = position;
           emit positionChangedSignal(_position);
    }

    Controller::Controller::ControllerState _connectionState;
    Controller::Controller::ControllerCalibState _calibState;
    uint8_t _speed;
    std::vector<double> _position;

    Controller::Controller *_controller;

    StandartdWorker *_stdWorker;
    JogWorker       *_jogWorker;
    TeachWorker     *_teachWorker;
    FileWorker      *_fileWorker;
};

#endif // ARS_H
