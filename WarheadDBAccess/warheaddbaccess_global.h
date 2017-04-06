#ifndef WARHEADDBACCESS_GLOBAL_H
#define WARHEADDBACCESS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef WARHEADDBACCESS_LIB
# define WARHEADDBACCESS_EXPORT Q_DECL_EXPORT
#else
# define WARHEADDBACCESS_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "warheaddbaccess.lib")
#endif

#endif // WARHEADDBACCESS_GLOBAL_H
