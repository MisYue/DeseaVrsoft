#ifndef COORDSYSTEM_GLOBAL_H
#define COORDSYSTEM_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef COORDSYSTEM_LIB
# define COORDSYSTEM_EXPORT Q_DECL_EXPORT
#else
# define COORDSYSTEM_EXPORT Q_DECL_IMPORT
#endif

#endif // COORDSYSTEM_GLOBAL_H
