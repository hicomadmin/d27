#ifndef HSPLUGINBASECONTROLLER_GLOBAL_H
#define HSPLUGINBASECONTROLLER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HSPLUGINBASECONTROLLER_LIBRARY)
#  define HSPLUGINBASECONTROLLERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HSPLUGINBASECONTROLLERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HSSHAREHMIDATACENTER_GLOBAL_H
