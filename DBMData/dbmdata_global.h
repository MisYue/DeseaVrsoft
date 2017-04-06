#ifndef DBMDATA_GLOBAL_H
#define DBMDATA_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DBMDATA_LIB
# define DBMDATA_EXPORT Q_DECL_EXPORT
#else
# define DBMDATA_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "dbmdata.lib")

#endif


#endif // DBMDATA_GLOBAL_H
