#ifndef _QJOYSTICKS_MAIN_H
#define _QJOYSTICKS_MAIN_H

#include <QObject>
#include <QStringList>
#include "arscorejoystick_global.h"
#include "JoysticksCommon.h"

#ifdef Q_OS_WIN
#   ifdef main
#      undef main
#   endif
#endif

class QSettings;
class SDL_Joysticks;

/**
 * \brief Manages the input systems and communicates them with the application
 *
 * The \c QJoysticks class is the "god-object" of this system. It manages every
 * input system used by the application (e.g. SDL for real joysticks and
 * keyboard for virtual joystick) and communicates every module/input system
 * with the rest of the application through standarized types.
 *
 * The joysticks are assigned a numerical ID, which the \c QJoysticks can use to
 * identify them. The ID's start with \c 0 (as with a QList). The ID's are
 * refreshed when a joystick is attached or removed. The first joystick that
 * has been connected to the computer will have \c 0 as an ID, the second
 * joystick will have \c 1 as an ID, and so on...
 *
 * \note the virtual joystick will ALWAYS be the last joystick to be registered,
 *       even if it has been enabled before any SDL joystick has been attached.
 */
class ARSCOREJOYSTICK_EXPORT QJoysticks : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int nonBlacklistedCount READ nonBlacklistedCount NOTIFY countChanged)
    Q_PROPERTY(QStringList deviceNames READ deviceNames NOTIFY countChanged)

    friend class Test_QJoysticks;

signals:
    void countChanged();
    void enabledChanged(const bool enabled);
    void POVEvent(const QJoystickPOVEvent &event);
    void axisEvent(const QJoystickAxisEvent &event);
    void buttonEvent(const QJoystickButtonEvent &event);
    void povChanged(const int js, const int pov, const int angle);
    void axisChanged(const int js, const int axis, const qreal value);
    void buttonChanged(const int js, const int button, const bool pressed);

public:
    static QJoysticks *getInstance();

    int count() const;
    int nonBlacklistedCount();
    QStringList deviceNames() const;

    Q_INVOKABLE int getPOV(const int index, const int pov);
    Q_INVOKABLE double getAxis(const int index, const int axis);
    Q_INVOKABLE bool getButton(const int index, const int button);

    Q_INVOKABLE int getNumAxes(const int index);
    Q_INVOKABLE int getNumPOVs(const int index);
    Q_INVOKABLE int getNumButtons(const int index);
    Q_INVOKABLE bool isBlacklisted(const int index);
    Q_INVOKABLE bool joystickExists(const int index);
    Q_INVOKABLE QString getName(const int index);

    SDL_Joysticks *sdlJoysticks() const;
    QJoystickDevice *getInputDevice(const int index);
    QList<QJoystickDevice *> inputDevices() const;

public slots:
    void updateInterfaces();
    void setSortJoysticksByBlacklistState(bool sort);
    void setBlacklisted(int index, bool blacklisted);

protected:
    explicit QJoysticks();
    ~QJoysticks();

private slots:
    void resetJoysticks();
    void addInputDevice(QJoystickDevice *device);
    void onPOVEvent(const QJoystickPOVEvent &e);
    void onAxisEvent(const QJoystickAxisEvent &e);
    void onButtonEvent(const QJoystickButtonEvent &e);

private:
    bool m_sortJoyticks;

    QSettings *m_settings;
    SDL_Joysticks *m_sdlJoysticks;

    QList<QJoystickDevice *> m_devices;
};

#endif
