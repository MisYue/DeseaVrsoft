#ifndef POWERANALYSIS_GLOBAL_H
#define POWERANALYSIS_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef POWERANALYSIS_LIB
# define POWERANALYSIS_EXPORT Q_DECL_EXPORT
#else
# define POWERANALYSIS_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "poweranalysis.lib")
#endif

#endif // POWERANALYSIS_GLOBAL_H
