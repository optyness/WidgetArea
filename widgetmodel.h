#ifndef WIDGETMODEL_H
#define WIDGETMODEL_H

#include <QAbstractListModel>
#include "widgettype.h"

class WidgetModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WidgetModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    void createData();

private:
    struct DataStruct
    {
        WType type;
        QString name;
        QString fname;
        unsigned int age;
        QString sender;
        QString message;
    };
    QVector<DataStruct> model_data;
};

#endif // WIDGETMODEL_H
