#ifndef TASKDBACCESS_GLOBAL_H
#define TASKDBACCESS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef TASKDBACCESS_LIB
# define TASKDBACCESS_EXPORT Q_DECL_EXPORT
#else
# define TASKDBACCESS_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "taskdbaccess.lib")
#endif

#endif // TASKDBACCESS_GLOBAL_H
