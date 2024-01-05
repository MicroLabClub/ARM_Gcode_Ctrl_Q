#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "joysticks.h"
#include "sources/core/ars.h"

#include "sources/gui_components/LedIndicator/LedIndicator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void onRobotCallbackStateChangedSlot(Controller::Controller::ControllerState state);
    void onStartRobotButtonClickedSlot();
    void onStopRobotButtonClickedSlot();
    void onCalibStartButtonClickedSlot();
    void onRobotCallbackCalibStateChangedSlot(Controller::Controller::ControllerCalibState status);
    void onRobotCallbackSpeedChangedSlot(uint8_t speed);
    void onRobotCallbackPositionChangedSlot(std::vector<double> position);
    void onHomeStartButtonClickedSlot();
    void onJogModeStartButtonClickedSlot();
    void onJogModeStopButtonClickedSlot();
    void onTeachModeStartButtonClickedSlot();
    void onTeachModeStopButtonClickedSlot();
    void onFileModeStartButtonClickedSlot();
    void onFileModeStopButtonClickedSlot();

private:

    Ui::MainWindow *ui;

    // Joystick interface
    QJoysticks *_joystick;

    LedIndicator *_robotStateIndicationLed;
    LedIndicator *_robotCalibrationStateIndicationLed;

    // Autonoumus robot system
    Ars *_ars;
};

#endif // MAINWINDOW_H
