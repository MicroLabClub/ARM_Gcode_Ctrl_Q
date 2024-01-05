#ifndef ARSCORE_GLOBAL_H
#define ARSCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ARSCORE_LIBRARY)
#  define ARSCORE_EXPORT Q_DECL_EXPORT
#else
#  define ARSCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // ARSCORE_GLOBAL_H
