#ifndef LIBDIALOG_GLOBAL_H
#define LIBDIALOG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBDIALOG_LIBRARY)
#define LIBDIALOG_EXPORT Q_DECL_EXPORT
#else
#define LIBDIALOG_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBDIALOG_GLOBAL_H
