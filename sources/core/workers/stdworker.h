#ifndef STDWORKER_H
#define STDWORKER_H


#include "controller.h"
#include <QObject>
#include <QThread>

/**
 * @brief The CalibWorkerThread class
 */
class CalibWorkerThread: public QObject {
    Q_OBJECT

public:

    /**
     * @brief CalibWorkerThread
     */
    explicit CalibWorkerThread(Controller::Controller *controller);

    /**
     * @brief Dtor
     */
    ~CalibWorkerThread();

    /**
     * @brief run
     */
    void run();

signals:

    void workerCmdFinishedSignal(Controller::Controller::ControllerCmdResponse response);

private slots:

    void onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse response);

private:

    // Controller
    Controller::Controller *_controller;
};


/**
 * @brief The HomeWorkerThread class
 */
class HomeWorkerThread: public QObject {
    Q_OBJECT

public:

    /**
     * @brief CalibWorkerThread
     */
    explicit HomeWorkerThread(Controller::Controller *controller);

    /**
     * @brief Dtor
     */
    ~HomeWorkerThread();

    /**
     * @brief run
     */
    void run();

signals:

    void workerCmdFinishedSignal(Controller::Controller::ControllerCmdResponse response);

private slots:

    void onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse response);

private:

    // Controller
    Controller::Controller *_controller;
};

/**
 * @brief The StandartdWorker class
 */
class StandartdWorker : public QObject {
    Q_OBJECT

public:

    /**
     * @brief StandartdWorker
     * @param controller
     * @param parent
     */
    explicit StandartdWorker(Controller::Controller *controller, QObject *parent = nullptr);

    /**
     * Dtor.
     */
    ~StandartdWorker();

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

    // Calibration and home worker thread
    CalibWorkerThread * _calibWorkerThread;
    HomeWorkerThread  * _homeWorkerThread;
};

#endif // STDWORKER_H
