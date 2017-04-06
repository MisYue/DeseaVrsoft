#ifndef MATERIALLIB_GLOBAL_H
#define MATERIALLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MATERIALLIB_LIB
# define MATERIALLIB_EXPORT Q_DECL_EXPORT
#else
# define MATERIALLIB_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "materiallib.lib")
#endif

#endif // MATERIALLIB_GLOBAL_H
