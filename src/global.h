#ifndef MERE_CACHE_GLOBAL_H
#define MERE_CACHE_GLOBAL_H

//#include <QtCore/qglobal.h>
//#include <QDebug>

//#if defined(MERE_CACHE_LIB)
//#  define MERE_CACHE_LIB_SPEC Q_DECL_EXPORT
//#else
//#  define MERE_CACHE_LIB_SPEC Q_DECL_IMPORT
//#endif


#if defined(MERE_CACHE_LIB)
#  define MERE_CACHE_LIB_SPEC
#else
#  define MERE_CACHE_LIB_SPEC
#endif

#endif // MERE_CACHE_GLOBAL_H
