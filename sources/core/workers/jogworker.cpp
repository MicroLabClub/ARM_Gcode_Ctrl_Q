#include "jogworker.h"
#include "logger.h"
#include <QDebug>

JogWorkerThread::JogWorkerThread(Controller::Controller *controller)
    : _controller{controller}
    , _joystick{nullptr}
    , _moveOnXFwd{false}
    , _moveOnXRev{false}
    , _moveOnYFwd{false}
    , _moveOnYRev{false}
    , _moveOnZFwd{false}
    , _moveOnZRev{false}
    , _moveOnAFwd{false}
    , _moveOnARev{false}
    , _moveOnBFwd{false}
    , _moveOnBRev{false}
    , _moveOnXFwdOld{false}
    , _moveOnXRevOld{false}
    , _moveOnYFwdOld{false}
    , _moveOnYRevOld{false}
    , _moveOnZFwdOld{false}
    , _moveOnZRevOld{false}
    , _moveOnAFwdOld{false}
    , _moveOnARevOld{false}
    , _moveOnBFwdOld{false}
    , _moveOnBRevOld{false}
{

}

JogWorkerThread::~JogWorkerThread()
{
    // Disconnect to controller command response
    _controller->connectToCommandResponseSignal(this, SLOT(onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse)), false);

    // Disconnect joystick
    QObject::disconnect(_joystick, &QJoysticks::axisChanged, this, &JogWorkerThread::onJoystickAxisChngedSlot);
    QObject::disconnect(_joystick, &QJoysticks::povChanged, this, &JogWorkerThread::onJoystickPowChangedSlot);
    QObject::disconnect(_joystick, &QJoysticks::buttonChanged, this, &JogWorkerThread::onJoystickButtonsChangedSlot);

    _controller = nullptr;
}

void JogWorkerThread::run()
{
    Logger::GetLogger()->logMessage("JogWorkerThread is running...", Logger::Level::DEBUG, "JogWorkerThread");

    _joystick = QJoysticks::getInstance();

    // Connect joystick signals
    QObject::connect(_joystick, &QJoysticks::axisChanged, this, &JogWorkerThread::onJoystickAxisChngedSlot);
    QObject::connect(_joystick, &QJoysticks::povChanged, this, &JogWorkerThread::onJoystickPowChangedSlot);
    QObject::connect(_joystick, &QJoysticks::buttonChanged, this, &JogWorkerThread::onJoystickButtonsChangedSlot);

    // Connect to controller command response
    _controller->connectToCommandResponseSignal(this, SLOT(onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse)), true);
}

void JogWorkerThread::onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);

    if (response == Controller::Controller::eControllerSetSpeedCmdResp) {
        return;
    }

    if (response == Controller::Controller::eControllerGripperCmdReps) {
        return;
    }

    double x;
    double y;
    double z;
    double a;
    double b;

    _controller->getPosition(&x, &y, &z, &a, &b);

    if ((_moveOnXFwd) && (!_moveOnXRev)) {
        x += 1;
    }
    else if ((!_moveOnXFwd) && (_moveOnXRev)) {
        x -= 1;
    }

    if ((_moveOnYFwd) && (!_moveOnYRev)) {
        y += 1;
    }
    else if ((!_moveOnYFwd) && (_moveOnYRev)) {
        y -= 1;
    }

    if ((_moveOnZFwd) && (!_moveOnZRev)) {
        z += 1;
    }
    else if ((!_moveOnZFwd) && (_moveOnZRev)) {
        z -= 1;
    }

    if ((_moveOnAFwd) && (!_moveOnARev)) {
        a += 1;
    }
    else if ((!_moveOnAFwd) && (_moveOnARev)) {
        a -= 1;
    }

    if ((_moveOnBFwd) && (!_moveOnBRev)) {
        b += 1;
    }
    else if ((!_moveOnBFwd) && (_moveOnBRev)) {
        b -= 1;
    }

    if ((_moveOnXFwd == false) && (_moveOnXRev == false) &&
        (_moveOnYFwd == false) && (_moveOnYRev == false) &&
        (_moveOnZFwd == false) && (_moveOnZRev == false) &&
        (_moveOnAFwd == false) && (_moveOnARev == false) &&
        (_moveOnBFwd == false) && (_moveOnBRev == false)) {

        return;
    }

    _controller->setPosition(x, y, z, a, b);
}

void JogWorkerThread::onJoystickAxisChngedSlot(const int js, const int axis, const qreal value)
{
    (void)js;

    if (axis == 0) {
        if (value > 0.2) {
            // Up
            _moveOnYFwd = true;
            // Down
            _moveOnYRev = false;
        }
        else if (value < -0.2) {
            // Up
            _moveOnYFwd = false;
            // Down
            _moveOnYRev = true;
        }
        else {
            // Up
            _moveOnYFwd = false;
            // Down
            _moveOnYRev = false;
        }
    }

    if (axis == 1) {
        if (value > 0.2) {
            // Left
            _moveOnXFwd = false;
            // Right
            _moveOnXRev = true;
        }
        else if (value < -0.2) {
            // Left
            _moveOnXFwd = true;
            // Right
            _moveOnXRev = false;
        }
        else {
            // Left
            _moveOnXFwd = false;
            // Right
            _moveOnXRev = false;
        }
    }

    if (axis == 2) {
        if (value > 0.8) {
            // Left
            _moveOnZFwd = false;
            // Right
            _moveOnZRev = true;
        }
        else if (value < -0.8) {
            // Left
            _moveOnZFwd = true;
            // Right
            _moveOnZRev = false;
        }
        else {
            // Left
            _moveOnZFwd = false;
            // Right
            _moveOnZRev = false;
        }
    }

    if ((_moveOnXFwdOld == false) && (_moveOnXRevOld == false) &&
        (_moveOnYFwdOld == false) && (_moveOnYRevOld == false) &&
        (_moveOnZFwdOld == false) && (_moveOnZRevOld == false) &&
        (_moveOnAFwdOld == false) && (_moveOnARevOld == false) &&
        (_moveOnBFwdOld == false) && (_moveOnBRevOld == false)) {

        onControllerCommandResponseSlot(Controller::Controller::eControllerSetPosCmdResp);
    }

    _moveOnXFwdOld.store(_moveOnXFwd);
    _moveOnXRevOld.store(_moveOnXRev);
    _moveOnYFwdOld.store(_moveOnYFwd);
    _moveOnYRevOld.store(_moveOnYRev);
    _moveOnZFwdOld.store(_moveOnZFwd);
    _moveOnZRevOld.store(_moveOnZRev);
}

void JogWorkerThread::onJoystickPowChangedSlot(const int js, const int pov, const int angle)
{
    (void)js;
    qDebug() << pov << angle;
}

void JogWorkerThread::onJoystickButtonsChangedSlot(const int js, const int button, const bool pressed)
{
    (void)js;

    if (button == 0) {
        if (!pressed)
            return;

        _controller->pumpOn();
        return;
    }

    if (button == 1) {
        if (!pressed)
            return;

        _controller->pumpOff();
        return;
    }

    if (button == 2) {
        if (!pressed)
            return;

        _controller->catchStart();
        return;
    }

    if (button == 3) {
        if (!pressed)
            return;

        _controller->releaseStart();
        return;
    }

    if (button == 6) {// B
        _moveOnBFwd = false;
        _moveOnBRev = pressed;
    }

    if (button == 4) {// B
        _moveOnBFwd = pressed;
        _moveOnBRev = false;
    }

    if (button == 7) {// A
        _moveOnAFwd = false;
        _moveOnARev = pressed;
    }

    if (button == 5) {// A
        _moveOnAFwd = pressed;
        _moveOnARev = false;
    }

    if ((_moveOnXFwdOld == false) && (_moveOnXRevOld == false) &&
        (_moveOnYFwdOld == false) && (_moveOnYRevOld == false) &&
        (_moveOnZFwdOld == false) && (_moveOnZRevOld == false) &&
        (_moveOnAFwdOld == false) && (_moveOnARevOld == false) &&
        (_moveOnBFwdOld == false) && (_moveOnBRevOld == false)) {

        onControllerCommandResponseSlot(Controller::Controller::eControllerSetPosCmdResp);
    }

    _moveOnAFwdOld.store(_moveOnAFwd);
    _moveOnARevOld.store(_moveOnARev);
    _moveOnBFwdOld.store(_moveOnBFwd);
    _moveOnBRevOld.store(_moveOnBRev);
}

JogWorker::JogWorker(Controller::Controller *controller, QString &hmi, QObject *parent)
    : QObject{parent}
    , _isRunning{false}
    , _controller{controller}
    , _jogWorkerThread{nullptr}
{
    Q_UNUSED(hmi);
}

JogWorker::~JogWorker()
{
    if (_workerThread.isRunning()) {
        _workerThread.quit();
        _workerThread.wait();
        _isRunning = false;
    }
}

void JogWorker::workerCallbackCmdFinishedSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);
}

bool JogWorker::startWorker(const uint8_t type)
{
    Q_UNUSED(type);

    if (_workerThread.isRunning()) {
        return false;
    }

    if (_controller->getCalibState() != Controller::Controller::ControllerCalibState::eControllerCalibrated)
        return false;

    if (_controller->getState() != Controller::Controller::ControllerJobState::eControllerJobStopped)
        return false;

    _jogWorkerThread = new JogWorkerThread(_controller);
    _jogWorkerThread->moveToThread(&_workerThread);
    QObject::connect(&_workerThread, &QThread::finished, _jogWorkerThread, &QObject::deleteLater);
    QObject::connect(&_workerThread, &QThread::started, _jogWorkerThread, &JogWorkerThread::run);
    QObject::connect(_jogWorkerThread, &JogWorkerThread::workerCmdFinishedSignal, this, &JogWorker::workerCallbackCmdFinishedSlot);

    _isRunning = true;
    _workerThread.start();

    return _isRunning;
}

bool JogWorker::stopWorker()
{
    if (_workerThread.isRunning()) {
        _controller->pumpOff();
        _workerThread.quit();
        _workerThread.wait();
        _isRunning = false;
    }

    return _isRunning;
}
