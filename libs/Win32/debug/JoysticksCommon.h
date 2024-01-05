#ifndef _QJOYSTICKS_COMMON_H
#define _QJOYSTICKS_COMMON_H

#include <QString>
#include <QList>

/**
 * @brief Represents a joystick and its properties
 *
 * This structure contains:
 *     - The numerical ID of the joystick
 *     - The sdl instance id of the joystick
 *     - The joystick display name
 *     - The number of axes operated by the joystick
 *     - The number of buttons operated by the joystick
 *     - The number of POVs operated by the joystick
 *     - A boolean value blacklisting or whitelisting the joystick
 */
struct QJoystickDevice
{
    int id; /**< Holds the ID of the joystick */
    int instanceID; /**< Holds the sdl instance id of the joystick */
    QString name; /**< Holds the name/title of the joystick */
    QList<int> povs; /**< Holds the values for each POV */
    QList<double> axes; /**< Holds the values for each axis */
    QList<bool> buttons; /**< Holds the values for each button */
    bool blacklisted; /**< Holds \c true if the joystick is disabled */
};

/**
 * @brief Represents a joystick rumble request
 *
 * This structure contains:
 *    - A pointer to the joystick that should be rumbled
 *    - The length (in milliseconds) of the rumble effect.
 *    - The strength of the effect (from 0 to 1)
 */
struct QJoystickRumble
{
    uint length; /**< The duration of the effect */
    qreal strength; /**< Strength of the effect (0 to 1) */
    QJoystickDevice *joystick; /**< The pointer to the target joystick */
};

/**
 * @brief Represents an POV event that can be triggered by a joystick
 *
 * This structure contains:
 *    - A pointer to the joystick that triggered the event
 *    - The POV number/ID
 *    - The current POV angle
 */
struct QJoystickPOVEvent
{
    int pov; /**< The numerical ID of the POV */
    int angle; /**< The current angle of the POV */
    QJoystickDevice *joystick; /**< Pointer to the device that caused the event */
};

/**
 * @brief Represents an axis event that can be triggered by a joystick
 *
 * This structure contains:
 *    - A pointer to the joystick that caused the event
 *    - The axis number/ID
 *    - The current axis value
 */
struct QJoystickAxisEvent
{
    int axis; /**< The numerical ID of the axis */
    qreal value; /**< The value (from -1 to 1) of the axis */
    QJoystickDevice *joystick; /**< Pointer to the device that caused the event */
};

/**
 * @brief Represents a button event that can be triggered by a joystick
 *
 * This structure contains:
 *   - A pointer to the joystick that caused the event
 *   - The button number/ID
 *   - The current button state (pressed or not pressed)
 */
struct QJoystickButtonEvent
{
    int button; /**< The numerical ID of the button */
    bool pressed; /**< Set to \c true if the button is pressed */
    QJoystickDevice *joystick; /**< Pointer to the device that caused the event */
};

#endif
