#ifndef FILEWORKER_H
#define FILEWORKER_H

#include "controller.h"
#include <QObject>
#include <QThread>
#include <QDir>

/**
 * @brief The FileWorkerThread class
 */
class FileWorkerThread: public QObject {
    Q_OBJECT

public:

    /**
     * @brief FileWorkerThread
     */
    explicit FileWorkerThread(Controller::Controller *controller);

    /**
     * @brief Dtor
     */
    ~FileWorkerThread();

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

    QFile file;
    QTextStream stream;
};

/**
 * @brief The FileWorker class
 */
class FileWorker : public QObject {
    Q_OBJECT

public:

    /**
     * @brief FileWorker
     * @param controller
     * @param parent
     */
    explicit FileWorker(Controller::Controller *controller, QString &hmi, QObject *parent = nullptr);

    /**
     * Dtor.
     */
    ~FileWorker();

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

    // File worker thread
    FileWorkerThread * _fileWorkerThread;
};

#endif // FILEWORKER_H
