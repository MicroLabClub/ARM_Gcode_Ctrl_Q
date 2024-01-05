#include "teachworker.h"
#include "logger.h"

TeachWorkerThread::TeachWorkerThread(Controller::Controller *controller)
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

TeachWorkerThread::~TeachWorkerThread()
{
    if (file.isOpen())
        file.close();

    // Disconnect to controller command response
    _controller->connectToCommandResponseSignal(this, SLOT(onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse)), false);

    // Disconnect joystick
    QObject::disconnect(_joystick, &QJoysticks::axisChanged, this, &TeachWorkerThread::onJoystickAxisChngedSlot);
    QObject::disconnect(_joystick, &QJoysticks::povChanged, this, &TeachWorkerThread::onJoystickPowChangedSlot);
    QObject::disconnect(_joystick, &QJoysticks::buttonChanged, this, &TeachWorkerThread::onJoystickButtonsChangedSlot);

    _controller = nullptr;
    _joystick = nullptr;
}

void TeachWorkerThread::run()
{
    Logger::GetLogger()->logMessage("JogWorkerThread is running...", Logger::Level::DEBUG, "JogWorkerThread");

    _joystick = QJoysticks::getInstance();

    QString dirName("/TeachFiles");
    QDir dir;

    // We create the directory if needed
    if (!dir.exists(QDir::currentPath()+ dirName))
        dir.mkpath(QDir::currentPath() + dirName);

    QString fileName = QDir::currentPath() + dirName + "/teach_file.txt";

    file.setFileName(fileName);

    if (file.exists()) {
        file.remove();
    }

    file.open(QIODevice::WriteOnly);

    // Connect joystick signals
    QObject::connect(_joystick, &QJoysticks::axisChanged, this, &TeachWorkerThread::onJoystickAxisChngedSlot);
    QObject::connect(_joystick, &QJoysticks::povChanged, this, &TeachWorkerThread::onJoystickPowChangedSlot);
    QObject::connect(_joystick, &QJoysticks::buttonChanged, this, &TeachWorkerThread::onJoystickButtonsChangedSlot);

    // Connect to controller command response
    _controller->connectToCommandResponseSignal(this, SLOT(onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse)), true);
}

void TeachWorkerThread::onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);

    if (response == Controller::Controller::eControllerSetSpeedCmdResp) {
        if (file.isOpen()) {
            QString str = "G07 VP=" +
                QString::number(_controller->getSpeed()) +
                "\r\n";
            QTextStream stream(&file);
            stream << str;
        }

        return;
    }

    if (response != Controller::Controller::eControllerSetPosCmdResp) {
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

void TeachWorkerThread::onJoystickAxisChngedSlot(const int js, const int axis, const qreal value)
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

void TeachWorkerThread::onJoystickPowChangedSlot(const int js, const int pov, const int angle)
{
    (void)js;
    (void)pov;
    (void)angle;
}

void TeachWorkerThread::onJoystickButtonsChangedSlot(const int js, const int button, const bool pressed)
{
    (void)js;

    if (button == 0) {
        if (!pressed)
            return;

        if (file.isOpen()) {
            QString str = "G06 T=1000\r\n";
            QTextStream stream(&file);
            stream << str;
            str = "G06 O=P1.1\r\n";
            stream << str;
            str = "G06 T=1000\r\n";
            stream << str;
        }

        _controller->pumpOn();
        return;
    }

    if (button == 1) {
        if (!pressed)
            return;

        if (file.isOpen()) {
            QString str = "G06 T=1000\r\n";
            QTextStream stream(&file);
            stream << str;
            str = "G06 O=P1.0\r\n";
            stream << str;
            str = "G06 T=1000\r\n";
            stream << str;
        }

        _controller->pumpOff();
        return;
    }

    if (button == 2) {
        if (!pressed)
            return;

        if (file.isOpen()) {
            QString str = "G06 T=1000\r\n";
            QTextStream stream(&file);
            stream << str;
            str = "G06 O=P0.0\r\n";;
            stream << str;
            str = "G06 T=1000\r\n";
            stream << str;
        }

        _controller->catchStart();
        return;
    }

    if (button == 3) {
        if (!pressed)
            return;

        if (file.isOpen()) {
            QString str = "G06 T=1000\r\n";
            QTextStream stream(&file);
            stream << str;
            str = "G06 O=P0.1\r\n";
            stream << str;
            str = "G06 T=1000\r\n";
            stream << str;
        }

        _controller->releaseStart();
        return;
    }

    if (button == 8) {
        if (!pressed)
            return;

        if (file.isOpen()) {
            double x;
            double y;
            double z;
            double a;
            double b;

            _controller->getPosition(&x, &y, &z, &a, &b);

            QString str = "G21 X=" + QString::number(x) +
                             " Y=" + QString::number(y) +
                             " Z=" + QString::number(z) +
                             " A=" + QString::number(a) +
                             " B=" + QString::number(b) +
                             " C=" + QString::number(0) +
                             " D=" + QString::number(0) +
                             "\r\n";

            QTextStream stream(&file);
            stream << str;
        }

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

TeachWorker::TeachWorker(Controller::Controller *controller, QString &hmi, QObject *parent)
    : QObject{parent}
    , _isRunning{false}
    , _controller{controller}
    , _teachWorkerThread{nullptr}
{
    Q_UNUSED(hmi);
}

TeachWorker::~TeachWorker()
{
    if (_workerThread.isRunning()) {
        _workerThread.quit();
        _workerThread.wait();
        _isRunning = false;
    }
}

void TeachWorker::workerCallbackCmdFinishedSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);
}

bool TeachWorker::startWorker(const uint8_t type)
{
    Q_UNUSED(type);

    if (_workerThread.isRunning()) {
        return false;
    }

    if (_controller->getCalibState() != Controller::Controller::ControllerCalibState::eControllerCalibrated)
        return false;

    if (_controller->getState() != Controller::Controller::ControllerJobState::eControllerJobStopped)
        return false;

    _teachWorkerThread = new TeachWorkerThread(_controller);
    _teachWorkerThread->moveToThread(&_workerThread);
    QObject::connect(&_workerThread, &QThread::finished, _teachWorkerThread, &QObject::deleteLater);
    QObject::connect(&_workerThread, &QThread::started, _teachWorkerThread, &TeachWorkerThread::run);
    QObject::connect(_teachWorkerThread, &TeachWorkerThread::workerCmdFinishedSignal, this, &TeachWorker::workerCallbackCmdFinishedSlot);

    _isRunning = true;
    _workerThread.start();

    return _isRunning;
}

bool TeachWorker::stopWorker()
{
    if (_workerThread.isRunning()) {
        _workerThread.quit();
        _workerThread.wait();
        _isRunning = false;
    }

    return _isRunning;
}
