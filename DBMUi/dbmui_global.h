#ifndef DBMUI_GLOBAL_H
#define DBMUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DBMUI_LIB
# define DBMUI_EXPORT Q_DECL_EXPORT
#else
# define DBMUI_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "dbmui.lib")

#endif


#endif // DBMUI_GLOBAL_H
