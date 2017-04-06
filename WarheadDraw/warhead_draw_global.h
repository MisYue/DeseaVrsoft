#ifndef WARHEADDRAW_GLOBAL_H
#define WARHEADDRAW_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef WARHEADDRAW_LIB
# define WARHEADDRAW_EXPORT Q_DECL_EXPORT
#else
# define WARHEADDRAW_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "warheaddraw.lib")

#endif

#endif // WARHEADDRAW_GLOBAL_H
