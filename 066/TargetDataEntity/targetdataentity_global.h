#ifndef TARGETDATAENTITY_GLOBAL_H
#define TARGETDATAENTITY_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef TARGETDATAENTITY_LIB
# define TARGETDATAENTITY_EXPORT Q_DECL_EXPORT
#else
# define TARGETDATAENTITY_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "targetdataentity.lib")
#endif

#endif // TARGETDATAENTITY_GLOBAL_H
