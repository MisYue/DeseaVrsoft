#ifndef WARHEADREADWRITE_GLOBAL_H
#define WARHEADREADWRITE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef WARHEADREADWRITE_LIB
# define WARHEADREADWRITE_EXPORT Q_DECL_EXPORT
#else
# define WARHEADREADWRITE_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "WarheadReadWrite.lib")
#endif

#endif // WARHEADREADWRITE_GLOBAL_H