#ifndef DBACCESS_GLOBAL_H
#define DBACCESS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DBACCESS_LIB
# define DBACCESS_EXPORT Q_DECL_EXPORT
#else
# define DBACCESS_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "dbaccess.lib")

#endif


#endif // DBACCESS_GLOBAL_H
