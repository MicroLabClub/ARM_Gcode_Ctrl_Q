#ifndef TEACHWORKER_H
#define TEACHWORKER_H

#include "controller.h"
#include "joysticks.h"
#include <QObject>
#include <QThread>
#include <QDir>

/**
 * @brief The TeachWorkerThread class
 */
class TeachWorkerThread: public QObject {
    Q_OBJECT

public:

    /**
     * @brief CalibWorkerThread
     */
    explicit TeachWorkerThread(Controller::Controller *controller);

    /**
     * @brief Dtor
     */
    ~TeachWorkerThread();

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

    QFile file;
};

/**
 * @brief The TeachWorker class
 */
class TeachWorker : public QObject {
    Q_OBJECT

public:

    /**
     * @brief TeachWorker
     * @param controller
     * @param parent
     */
    explicit TeachWorker(Controller::Controller *controller, QString &hmi, QObject *parent = nullptr);

    /**
     * Dtor.
     */
    ~TeachWorker();

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

    // Theach worker thread
    TeachWorkerThread * _teachWorkerThread;
};

#endif // TEACHWORKER_H
