#ifndef ARSCOREJOYSTICK_GLOBAL_H
#define ARSCOREJOYSTICK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ARSCOREJOYSTICK_LIBRARY)
#  define ARSCOREJOYSTICK_EXPORT Q_DECL_EXPORT
#else
#  define ARSCOREJOYSTICK_EXPORT Q_DECL_IMPORT
#endif

#endif // ARSCOREJOYSTICK_GLOBAL_H
