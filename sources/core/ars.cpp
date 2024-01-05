#include "ars.h"
#include "sources/core/workers/fileworker.h"
#include <QDebug>

#define CALIB_WORKER    0
#define GO_HOME_WORKER  1

Ars::Ars(QObject *parent)
    : QObject{parent}
    , _connectionState{Controller::Controller::eControllerDisconnected}
    , _calibState{Controller::Controller::eControllerNotCalibrated}
{
    // Create controller
    _controller = Controller::Controller::GetController("G-Code");

    // Create calibration worker and inject controller
    _stdWorker = new StandartdWorker(_controller);

    // Create jog worker and inject controller
    QString hmiType = "Joytick";
    _jogWorker = new JogWorker(_controller, hmiType);

    // Create teach worker and inject controller
    _teachWorker = new TeachWorker(_controller, hmiType);

    // Create teach worker and inject controller
    _fileWorker = new FileWorker(_controller, hmiType);
}

Ars::~Ars()
{
    _stdWorker->stopWorker();
    _jogWorker->stopWorker();
    _teachWorker->stopWorker();
    _fileWorker->stopWorker();

    delete _stdWorker;
    delete _jogWorker;
    delete _teachWorker;
    delete _fileWorker;
    delete _controller;
}

void Ars::onControllerCallbackStateChangedSlot(bool status)
{
    if (status) {
        setConnectionState(Controller::Controller::eControllerConnected);

        setSpeed(_controller->getSpeed());

        double x = 0;
        double y = 0;
        double z = 0;
        double a = 0;
        double b = 0;

        _controller->getPosition(&x, &y, &z, &a, &b);
        std::vector<double> position;
        position.push_back(x);
        position.push_back(y);
        position.push_back(z);
        position.push_back(a);
        position.push_back(b);
        setPosition(position);
    }
    else {
        setConnectionState(Controller::Controller::eControllerDisconnected);
    }
}

void Ars::onWorkerCmdFinishedCallbackStateChangedSlot(Controller::Controller::ControllerCmdResponse response)
{
    if (response == Controller::Controller::ControllerCmdResponse::eControllerIntializedCmdResp) {
        setCalibState(Controller::Controller::ControllerCalibState::eControllerCalibrationIntialized);
        return;
    }

    if (response == Controller::Controller::ControllerCmdResponse::eControllerCalibratedCmdResp) {
        setCalibState(Controller::Controller::ControllerCalibState::eControllerCalibrated);

        double x = 0;
        double y = 0;
        double z = 0;
        double a = 0;
        double b = 0;

        _controller->getPosition(&x, &y, &z, &a, &b);
        std::vector<double> position;
        position.push_back(x);
        position.push_back(y);
        position.push_back(z);
        position.push_back(a);
        position.push_back(b);
        setPosition(position);
        _controller->setSpeed(50);
        return;
    }


    if (response == Controller::Controller::ControllerCmdResponse::eControllerHomeCmdResp) {

            double x = 0;
            double y = 0;
            double z = 0;
            double a = 0;
            double b = 0;

            _controller->getPosition(&x, &y, &z, &a, &b);
            std::vector<double> position;
            position.push_back(x);
            position.push_back(y);
            position.push_back(z);
            position.push_back(a);
            position.push_back(b);
            setPosition(position);
    }

    if (response == Controller::Controller::ControllerCmdResponse::eControllerSetPosCmdResp) {
        double x = 0;
        double y = 0;
        double z = 0;
        double a = 0;
        double b = 0;

        _controller->getPosition(&x, &y, &z, &a, &b);
        std::vector<double> position;
        position.push_back(x);
        position.push_back(y);
        position.push_back(z);
        position.push_back(a);
        position.push_back(b);
        setPosition(position);
    }

    if (response == Controller::Controller::ControllerCmdResponse::eControllerSetSpeedCmdResp) {
        setSpeed(_controller->getSpeed());
        _stdWorker->stopWorker();
    }
}

void Ars::start()
{
    if (!_controller->connectToConnectionStatusSignal(this, SLOT(onControllerCallbackStateChangedSlot(bool)), true)) {
        return;
    }

    QString comPortName = "COM1";
    QString baudRate = "115200";

    // Connect controller
    _controller->connect(comPortName, baudRate);
}

void Ars::stop()
{
    QObject::disconnect(_stdWorker, &StandartdWorker::workerCmdFinishedSignal, this, &Ars::onWorkerCmdFinishedCallbackStateChangedSlot);

    _stdWorker->stopWorker();
    _jogWorker->stopWorker();
    _teachWorker->stopWorker();
    _controller->disconnect();
}

bool Ars::calibrate()
{
    QObject::connect(_stdWorker, &StandartdWorker::workerCmdFinishedSignal, this, &Ars::onWorkerCmdFinishedCallbackStateChangedSlot);

    return _stdWorker->startWorker(CALIB_WORKER);
}

bool Ars::home()
{
    _jogWorker->stopWorker();
    _teachWorker->stopWorker();
    _fileWorker->stopWorker();
    QObject::connect(_stdWorker, &StandartdWorker::workerCmdFinishedSignal, this, &Ars::onWorkerCmdFinishedCallbackStateChangedSlot);
    return _stdWorker->startWorker(GO_HOME_WORKER);
}

void Ars::jogModeStart()
{
    _stdWorker->stopWorker();
    _teachWorker->stopWorker();
    _fileWorker->stopWorker();
    _jogWorker->stopWorker();
    QObject::connect(_jogWorker, &JogWorker::workerCmdFinishedSignal, this, &Ars::onWorkerCmdFinishedCallbackStateChangedSlot);
    _jogWorker->startWorker(0);
}

void Ars::jogModeStop()
{
    _jogWorker->stopWorker();
}

void Ars::teachModeStart()
{
    _stdWorker->stopWorker();
    _jogWorker->stopWorker();
    _fileWorker->stopWorker();
    QObject::connect(_teachWorker, &TeachWorker::workerCmdFinishedSignal, this, &Ars::onWorkerCmdFinishedCallbackStateChangedSlot);
    _teachWorker->startWorker(0);
}

void Ars::teachModeStop()
{
    _teachWorker->stopWorker();
}

void Ars::fileModeStart()
{
    _stdWorker->stopWorker();
    _jogWorker->stopWorker();
    _teachWorker->stopWorker();
    QObject::connect(_fileWorker, &FileWorker::workerCmdFinishedSignal, this, &Ars::onWorkerCmdFinishedCallbackStateChangedSlot);
    _fileWorker->startWorker(0);
}

void Ars::fileModeStop()
{
    _fileWorker->stopWorker();
}

void Ars::pumpOff()
{
    _controller->pumpOff();
}

void Ars::pumpOn()
{
    _controller->pumpOn();
}

void Ars::releaseStart()
{
    _controller->releaseStart();
}

void Ars::catchStart()
{
    _controller->catchStart();
}
