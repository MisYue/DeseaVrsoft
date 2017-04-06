#ifndef DBMINTERFACE_GLOBAL_H
#define DBMINTERFACE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DBMINTERFACE_LIB
# define DBMINTERFACE_EXPORT Q_DECL_EXPORT
#else
# define DBMINTERFACE_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "dbminterface.lib")

#endif


#endif // DBMINTERFACE_GLOBAL_H
