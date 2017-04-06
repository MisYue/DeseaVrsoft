#ifndef BASICTOOL_GLOBAL_H
#define BASICTOOL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef BASICTOOL_LIB
# define BASICTOOL_EXPORT Q_DECL_EXPORT
#else
# define BASICTOOL_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "basictool.lib")
#endif

#endif // BASICTOOL_GLOBAL_H
