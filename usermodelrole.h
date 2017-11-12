#ifndef USERMODELROLE_H
#define USERMODELROLE_H

#include <QAbstractItemModel>

enum class MRole {
    type = Qt::UserRole,
    name,
    fname,
    age
};

#endif // USERMODELROLE_H
