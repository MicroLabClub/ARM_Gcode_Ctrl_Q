#include "stdworker.h"
#include "logger.h"

CalibWorkerThread::CalibWorkerThread(Controller::Controller *controller)
    : _controller{controller}
{

}

CalibWorkerThread::~CalibWorkerThread()
{
    _controller = nullptr;
}

void CalibWorkerThread::run()
{
    Logger::GetLogger()->logMessage("CalibWorkerThread is running...", Logger::Level::DEBUG, "CalibWorkerThread");

    // Connect to controller command response
    _controller->connectToCommandResponseSignal(this, SLOT(onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse)), true);

    if(!_controller->calibrate())
        QThread::currentThread()->quit();
}

void CalibWorkerThread::onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);
}

HomeWorkerThread::HomeWorkerThread(Controller::Controller *controller)
    : _controller{controller}
{

}

HomeWorkerThread::~HomeWorkerThread()
{
    _controller = nullptr;
}

void HomeWorkerThread::run()
{
    Logger::GetLogger()->logMessage("HomeWorkerThread is running...", Logger::Level::DEBUG, "HomeWorkerThread");

    _controller->connectToCommandResponseSignal(this, SLOT(onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse)), true);

    if (!_controller->goHome())
        QThread::currentThread()->quit();
}

void HomeWorkerThread::onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);
}

StandartdWorker::StandartdWorker(Controller::Controller *controller, QObject *parent)
    : QObject{parent}
    , _isRunning{false}
    , _controller{controller}
    , _calibWorkerThread{nullptr}
{

}

StandartdWorker::~StandartdWorker()
{
    if (_workerThread.isRunning()) {
        _workerThread.quit();
        _workerThread.wait();
        _isRunning = false;
    }
}

void StandartdWorker::workerCallbackCmdFinishedSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);
}

bool StandartdWorker::startWorker(const uint8_t type)
{
    if (_workerThread.isRunning()) {
        return false;
    }

    if (type == 0) {
        _calibWorkerThread = new CalibWorkerThread(_controller);
        _calibWorkerThread->moveToThread(&_workerThread);
        QObject::connect(&_workerThread, &QThread::finished, _calibWorkerThread, &QObject::deleteLater);
        QObject::connect(&_workerThread, &QThread::started, _calibWorkerThread, &CalibWorkerThread::run);
        QObject::connect(_calibWorkerThread, &CalibWorkerThread::workerCmdFinishedSignal, this, &StandartdWorker::workerCallbackCmdFinishedSlot);
    }
    else if (type == 1) {
        _homeWorkerThread = new HomeWorkerThread(_controller);
        _homeWorkerThread->moveToThread(&_workerThread);
        QObject::connect(&_workerThread, &QThread::finished, _homeWorkerThread, &QObject::deleteLater);
        QObject::connect(&_workerThread, &QThread::started, _homeWorkerThread, &HomeWorkerThread::run);
        QObject::connect(_homeWorkerThread, &HomeWorkerThread::workerCmdFinishedSignal, this, &StandartdWorker::workerCallbackCmdFinishedSlot);
    }
    else {
        Logger::GetLogger()->logMessage("StandartdWorker invalid type", Logger::Level::WARNING, "StandartdWorker");
        return false;
    }

    _isRunning = true;
    _workerThread.start();

    return _isRunning;
}

bool StandartdWorker::stopWorker()
{
    if (_workerThread.isRunning()) {
        _workerThread.quit();
        _workerThread.wait();
        _isRunning = false;
    }

    return _isRunning;
}
