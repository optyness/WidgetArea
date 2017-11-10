#include "widgetmodel.h"

WidgetModel::WidgetModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

int WidgetModel::rowCount(const QModelIndex &parent) const
{
    int count = model_data.size();
    return count;
}

QVariant WidgetModel::data(const QModelIndex &index, int role) const
{
    switch(role){
    case Qt::UserRole:
        return QVariant::fromValue(model_data[index.row()].type);
    case Qt::UserRole+1:
        return QVariant::fromValue(model_data[index.row()].name);
    case Qt::UserRole+2:
        return QVariant::fromValue(model_data[index.row()].fname);
    case Qt::UserRole+3:
        return QVariant::fromValue(model_data[index.row()].age);
    default:
        return QVariant();
    }
}

bool WidgetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role){
    case (Qt::UserRole):
        model_data[model_data.size() - 1].type = value.value<WType>();
        return true;
    case Qt::UserRole+1:
        model_data[model_data.size() - 1].name = value.toString();
        return true;
    case Qt::UserRole+2:
        model_data[model_data.size() - 1].fname = value.toString();
        return true;
    case Qt::UserRole+3:
        model_data[model_data.size() - 1].age = value.toInt();
        return true;
    default:
        return false;
    }
}

void WidgetModel::createData()
{
    model_data.append(DataStruct());
}
