#ifndef OSGTOOL_GLOBAL_H
#define OSGTOOL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef OSGTOOL_LIB
# define OSGTOOL_EXPORT Q_DECL_EXPORT
#else
# define OSGTOOL_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "osgtool.lib")
#endif

#endif // OSGTOOL_GLOBAL_H
