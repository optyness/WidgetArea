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
    case MRole::type:
        return QVariant::fromValue(model_data[index.row()].type);
    case MRole::name:
        return QVariant::fromValue(model_data[index.row()].name);
    case MRole::fname:
        return QVariant::fromValue(model_data[index.row()].fname);
    case MRole::age:
        return QVariant::fromValue(model_data[index.row()].age);
    default:
        return QVariant();
    }
}

bool WidgetModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role){
    case MRole::type:
        model_data[model_data.size() - 1].type = value.value<WType>();
        return true;
    case MRole::name:
        model_data[model_data.size() - 1].name = value.toString();
        return true;
    case MRole::fname:
        model_data[model_data.size() - 1].fname = value.toString();
        return true;
    case MRole::age:
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
