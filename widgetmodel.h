#ifndef WIDGETMODEL_H
#define WIDGETMODEL_H

#include <QAbstractListModel>
#include <QtWidgets>
#include <widgettype.h>

class WidgetModel : public QAbstractListModel
{
    Q_OBJECT
public:
    WidgetModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

private:
    QVector <QString> names;
    QVector <QString> f_names;
    QVector <WType> widget_type;
};

#endif // WIDGETMODEL_H
