#ifndef JOGWORKER_H
#define JOGWORKER_H

#include "controller.h"
#include "joysticks.h"
#include <QObject>
#include <QThread>

/**
 * @brief The JogWorkerThread class
 */
class JogWorkerThread: public QObject {
    Q_OBJECT

public:

    /**
     * @brief CalibWorkerThread
     */
    explicit JogWorkerThread(Controller::Controller *controller);

    /**
     * @brief Dtor
     */
    ~JogWorkerThread();

    /**
     * @brief run
     */
    void run();

signals:

    void workerCmdFinishedSignal(Controller::Controller::ControllerCmdResponse response);

private slots:

    void onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse response);

    void onJoystickAxisChngedSlot(const int js, const int axis, const qreal value);
    void onJoystickPowChangedSlot(const int js, const int pov, const int angle);
    void onJoystickButtonsChangedSlot(const int js, const int button, const bool pressed);

private:

    // Controller
    Controller::Controller *_controller;

    // Joystick interface
    QJoysticks *_joystick;

    // Movements indication
    std::atomic<bool> _moveOnXFwd;
    std::atomic<bool> _moveOnXRev;
    std::atomic<bool> _moveOnYFwd;
    std::atomic<bool> _moveOnYRev;
    std::atomic<bool> _moveOnZFwd;
    std::atomic<bool> _moveOnZRev;
    std::atomic<bool> _moveOnAFwd;
    std::atomic<bool> _moveOnARev;
    std::atomic<bool> _moveOnBFwd;
    std::atomic<bool> _moveOnBRev;

    std::atomic<bool> _moveOnXFwdOld;
    std::atomic<bool> _moveOnXRevOld;
    std::atomic<bool> _moveOnYFwdOld;
    std::atomic<bool> _moveOnYRevOld;
    std::atomic<bool> _moveOnZFwdOld;
    std::atomic<bool> _moveOnZRevOld;
    std::atomic<bool> _moveOnAFwdOld;
    std::atomic<bool> _moveOnARevOld;
    std::atomic<bool> _moveOnBFwdOld;
    std::atomic<bool> _moveOnBRevOld;
};

/**
 * @brief The JogWorker class
 */
class JogWorker : public QObject {
    Q_OBJECT

public:

    /**
     * @brief JogWorker
     * @param controller
     * @param parent
     */
    explicit JogWorker(Controller::Controller *controller, QString &hmi, QObject *parent = nullptr);

    /**
     * Dtor.
     */
    ~JogWorker();

    /**
     * @brief startWorker
     * @return
     */
    bool startWorker(const uint8_t type);

    /**
     * @brief stopWorker
     * @return
     */
    bool stopWorker();

signals:

    void workerCmdFinishedSignal(Controller::Controller::ControllerCmdResponse response);

private slots:

    void workerCallbackCmdFinishedSlot(Controller::Controller::ControllerCmdResponse response);

private:

    // State indication
    std::atomic<bool> _isRunning;

    Controller::Controller *_controller;

    // Worker thread
    QThread _workerThread;

    // Jog worker thread
    JogWorkerThread * _jogWorkerThread;
};

#endif // JOGWORKER_H
