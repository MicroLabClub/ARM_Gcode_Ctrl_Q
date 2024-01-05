#ifndef _QJOYSTICKS_SDL_JOYSTICK_H
#define _QJOYSTICKS_SDL_JOYSTICK_H

#include <SDL.h>
#include <QObject>
#include <QMap>
#include <JoysticksCommon.h>

/**
 * \brief Translates SDL events into \c QJoysticks events
 *
 * This class is in charge of managing and operating real joysticks through the
 * SDL API. The implementation procedure is the same for every operating system.
 *
 * The only thing that differs from each operating system is the backup mapping
 * applied in the case that we do not know what mapping to apply to a joystick.
 *
 * \note The joystick values are refreshed every 20 milliseconds through a
 *       simple event loop.
 */
class SDL_Joysticks : public QObject
{
    Q_OBJECT

signals:
    void countChanged();
    void POVEvent(const QJoystickPOVEvent &event);
    void axisEvent(const QJoystickAxisEvent &event);
    void buttonEvent(const QJoystickButtonEvent &event);

public:
    SDL_Joysticks(QObject *parent = Q_NULLPTR);
    ~SDL_Joysticks();

    QMap<int, QJoystickDevice *> joysticks();

public slots:
    void rumble(const QJoystickRumble &request);

private slots:
    void update();
    void configureJoystick(const SDL_Event *event);

private:
    QJoystickDevice *getJoystick(int id);
    QJoystickPOVEvent getPOVEvent(const SDL_Event *sdl_event);
    QJoystickAxisEvent getAxisEvent(const SDL_Event *sdl_event);
    QJoystickButtonEvent getButtonEvent(const SDL_Event *sdl_event);

    QMap<int, QJoystickDevice *> m_joysticks;
};

#endif
