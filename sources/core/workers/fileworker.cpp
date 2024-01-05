#include "fileworker.h"
#include "logger.h"

FileWorkerThread::FileWorkerThread(Controller::Controller *controller)
    : _controller{controller}
{

}

FileWorkerThread::~FileWorkerThread()
{
    if (file.isOpen())
        file.close();

    // Disconnect to controller command response
    _controller->connectToCommandResponseSignal(this, SLOT(onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse)), false);

    _controller = nullptr;
}

void FileWorkerThread::run()
{
    Logger::GetLogger()->logMessage("JogWorkerThread is running...", Logger::Level::DEBUG, "JogWorkerThread");

    QString dirName("/TeachFiles");
    QString fileName = QDir::currentPath() + dirName + "/teach_file.txt";

    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly);

    // Connect to controller command response
    _controller->connectToCommandResponseSignal(this, SLOT(onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse)), true);

    if (file.isOpen()) {
        stream.setDevice(&file);

        if (!stream.atEnd())
        {
            QString line = stream.readLine();
            line += "\r\n";
            _controller->setCommand(line);
        }
        else {
            QThread::currentThread()->quit();
        }
    }
}

void FileWorkerThread::onControllerCommandResponseSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);

    if (file.isOpen()) {
        if (!stream.atEnd())
        {
            QString line = stream.readLine();
            line += "\r\n";
            _controller->setCommand(line);
        }
        else {
            QThread::currentThread()->quit();
        }
    }
}

FileWorker::FileWorker(Controller::Controller *controller, QString &hmi, QObject *parent)
    : QObject{parent}
    , _isRunning{false}
    , _controller{controller}
    , _fileWorkerThread{nullptr}
{
    Q_UNUSED(hmi);
}

FileWorker::~FileWorker()
{
    if (_workerThread.isRunning()) {
        _workerThread.quit();
        _workerThread.wait();
        _isRunning = false;
    }
}

void FileWorker::workerCallbackCmdFinishedSlot(Controller::Controller::ControllerCmdResponse response)
{
    emit workerCmdFinishedSignal(response);
}

bool FileWorker::startWorker(const uint8_t type)
{
    Q_UNUSED(type);

    if (_workerThread.isRunning()) {
        return false;
    }

    if (_controller->getCalibState() != Controller::Controller::ControllerCalibState::eControllerCalibrated)
        return false;

    if (_controller->getState() != Controller::Controller::ControllerJobState::eControllerJobStopped)
        return false;

    _fileWorkerThread = new FileWorkerThread(_controller);
    _fileWorkerThread->moveToThread(&_workerThread);
    QObject::connect(&_workerThread, &QThread::finished, _fileWorkerThread, &QObject::deleteLater);
    QObject::connect(&_workerThread, &QThread::started, _fileWorkerThread, &FileWorkerThread::run);
    QObject::connect(_fileWorkerThread, &FileWorkerThread::workerCmdFinishedSignal, this, &FileWorker::workerCallbackCmdFinishedSlot);

    _isRunning = true;
    _workerThread.start();

    return _isRunning;
}

bool FileWorker::stopWorker()
{
    if (_workerThread.isRunning()) {
        _workerThread.quit();
        _workerThread.wait();
        _isRunning = false;
    }

    return _isRunning;
}
