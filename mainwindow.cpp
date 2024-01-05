#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"

/**
 * @brief The Logger class stream the messages in the console
 */
class Log : public Logger {
public:

    void logMessage(std::string&& msg, Level lvl, std::string domain)
    {
        QString message = QString::fromUtf8(msg.c_str());
        QString dom = QString::fromUtf8(domain.c_str());

        if (lvl == CRITICAL)
            qDebug() << "[" << dom << "- CRITICAL" <<"]:"<< message;
        else if (lvl == WARNING)
            qDebug() << "[" << dom << "- WARNING" <<"]:"<< message;
        else if (lvl == INFO)
            qDebug() << "[" << dom << "- INFO" <<"]:"<< message;
        else
            qDebug() << "[" << dom << "- DEBUG" <<"]:"<< message;
    }

    ~Log() {}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Logger::CreateLogger([]() {
        std::shared_ptr<Logger> lg = std::make_shared<Logger>();
        return lg;
    });

    ui->setupUi(this);

    _robotStateIndicationLed = new LedIndicator();
    _robotStateIndicationLed->setOnColor(Qt::green);
    _robotStateIndicationLed->setOffColor(Qt::red);
    _robotStateIndicationLed->setState(false);
    ui->robotStatusIndicationLedLay->addWidget(_robotStateIndicationLed, 1, 0);

    _robotCalibrationStateIndicationLed = new LedIndicator();
    _robotCalibrationStateIndicationLed->setOnColor(Qt::green);
    _robotCalibrationStateIndicationLed->setOffColor(Qt::red);
    _robotCalibrationStateIndicationLed->setState(false);
    ui->robotCalibrationStatusIndicationLedLay->addWidget(_robotCalibrationStateIndicationLed, 1, 0);

    QObject::connect(ui->robotStartBtn, &QPushButton::clicked, this, &MainWindow::onStartRobotButtonClickedSlot);
    QObject::connect(ui->robotStopBtn, &QPushButton::clicked, this, &MainWindow::onStopRobotButtonClickedSlot);
    QObject::connect(ui->arsCalibStartBtn, &QPushButton::clicked, this, &MainWindow::onCalibStartButtonClickedSlot);
    QObject::connect(ui->arsHomeStartBtn, &QPushButton::clicked, this, &MainWindow::onHomeStartButtonClickedSlot);

    QObject::connect(ui->arsJogModeStartBtn, &QPushButton::clicked, this, &MainWindow::onJogModeStartButtonClickedSlot);
    QObject::connect(ui->arsJogModeStopBtn, &QPushButton::clicked, this, &MainWindow::onJogModeStopButtonClickedSlot);

    QObject::connect(ui->arsTeachModeStartBtn, &QPushButton::clicked, this, &MainWindow::onTeachModeStartButtonClickedSlot);
    QObject::connect(ui->arsTeachModeStopBtn, &QPushButton::clicked, this, &MainWindow::onTeachModeStopButtonClickedSlot);

    QObject::connect(ui->arsFileModeStartBtn, &QPushButton::clicked, this, &MainWindow::onFileModeStartButtonClickedSlot);
    QObject::connect(ui->arsFileModeStopBtn, &QPushButton::clicked, this, &MainWindow::onFileModeStopButtonClickedSlot);

    // Create autonoumus robot system
    _ars = new Ars();
    QObject::connect(_ars, &Ars::connectionStateChangedSignal, this, &MainWindow::onRobotCallbackStateChangedSlot);
    QObject::connect(_ars, &Ars::calibStateChangedSignal, this, &MainWindow::onRobotCallbackCalibStateChangedSlot);
    QObject::connect(_ars, &Ars::speedChangedSignal, this, &MainWindow::onRobotCallbackSpeedChangedSlot);
    QObject::connect(_ars, &Ars::positionChangedSignal, this, &MainWindow::onRobotCallbackPositionChangedSlot);
}

MainWindow::~MainWindow()
{
    delete _ars;
    delete ui;
}

void MainWindow::onStartRobotButtonClickedSlot()
{
    _ars->start();
}

void MainWindow::onStopRobotButtonClickedSlot()
{
    _ars->stop();
}

void MainWindow::onRobotCallbackStateChangedSlot(Controller::Controller::ControllerState state)
{
    if (state == Controller::Controller::eControllerConnected) {
        _robotStateIndicationLed->setState(true);
    }
    else {
        _robotStateIndicationLed->setState(false);
        _robotCalibrationStateIndicationLed->setOffColor(Qt::red);
    }
}

void MainWindow::onCalibStartButtonClickedSlot()
{
    _ars->calibrate();
}

void MainWindow::onRobotCallbackCalibStateChangedSlot(Controller::Controller::ControllerCalibState status)
{
    if (status == Controller::Controller::ControllerCalibState::eControllerCalibrated) {
        _robotCalibrationStateIndicationLed->setOffColor(Qt::green);
    }
    else if (status == Controller::Controller::ControllerCalibState::eControllerCalibrationIntialized) {
        _robotCalibrationStateIndicationLed->setOffColor(Qt::blue);
    }
    else {
        _robotCalibrationStateIndicationLed->setOffColor(Qt::red);
    }
}

void MainWindow::onRobotCallbackSpeedChangedSlot(uint8_t speed)
{
    ui->robotSpeedText->setText(QString::number(speed));
}

void MainWindow::onRobotCallbackPositionChangedSlot(std::vector<double> position)
{
    ui->robotPosX->setText(QString::number(position[0]));
    ui->robotPosY->setText(QString::number(position[1]));
    ui->robotPosZ->setText(QString::number(position[2]));
    ui->robotAngleA->setText(QString::number(position[3]));
    ui->robotAngleB->setText(QString::number(position[4]));
}

void MainWindow::onHomeStartButtonClickedSlot()
{
    _ars->home();
}

void MainWindow::onJogModeStartButtonClickedSlot()
{
    _ars->jogModeStart();
}

void MainWindow::onJogModeStopButtonClickedSlot()
{
    _ars->jogModeStop();
}

void MainWindow::onTeachModeStartButtonClickedSlot()
{
    _ars->teachModeStart();
}

void MainWindow::onTeachModeStopButtonClickedSlot()
{
    _ars->teachModeStop();
}

void MainWindow::onFileModeStartButtonClickedSlot()
{
    _ars->fileModeStart();
}

void MainWindow::onFileModeStopButtonClickedSlot()
{
    _ars->fileModeStop();
}
