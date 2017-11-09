#include "widgetmodel.h"

WidgetModel::WidgetModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

int WidgetModel::rowCount(const QModelIndex &parent) const
{
    int count = qMax(names.size(),f_names.size());
    return count;
}

QVariant WidgetModel::data(const QModelIndex &index, int role) const
{
    //qDebug() << index.row();
    switch(role){
    case Qt::UserRole:
        return QVariant::fromValue(widget_type[index.row()]);
    case Qt::UserRole+1:
        return QVariant::fromValue(names[index.row()]);
    case Qt::UserRole+2:
        return QVariant::fromValue(f_names[index.row()]);
    default:
        return QVariant();
    }
}

bool WidgetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role){
    case (Qt::UserRole):
        widget_type.append(value.value<WType>());
        return true;
    case Qt::UserRole+1:
        names.append(value.toString());
        return true;
    case Qt::UserRole+2:
        f_names.append(value.toString());
        return true;
    default:
        return false;
    }
}
