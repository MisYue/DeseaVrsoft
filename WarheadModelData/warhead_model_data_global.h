#ifndef WARHEADMODELDATA_GLOBAL_H
#define WARHEADMODELDATA_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef WARHEADMODELDATA_LIB
# define WARHEADMODELDATA_EXPORT Q_DECL_EXPORT
#else
# define WARHEADMODELDATA_EXPORT Q_DECL_IMPORT
#pragma comment(lib, "WarheadModelData.lib")
#endif


#ifdef _DEBUG
#pragma comment(lib, "BIT2DCSSupportd.lib")
#pragma comment(lib, "BITPointSupportd.lib")
#pragma comment(lib, "BITUnitsSupportd.lib")
#pragma comment(lib, "BITMathSupportd.lib")
#pragma comment(lib, "BIT2DComputeSupportd.lib")


#else
#pragma comment(lib, "BIT2DCSSupportr.lib")
#pragma comment(lib, "BITPointSupportr.lib")
#pragma comment(lib, "BITUnitsSupportr.lib")
#pragma comment(lib, "BITMathSupportr.lib")
#pragma comment(lib, "BIT2DComputeSupportr.lib")

#endif

#endif // WARHEADMODELDATA_GLOBAL_H
