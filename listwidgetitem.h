#ifndef LISTWIDGETITEM_H
#define LISTWIDGETITEM_H

#include <QtWidgets>

class ListWidgetItem : public QFrame
{
    Q_OBJECT
public:
    explicit ListWidgetItem(QWidget *parent = nullptr);

    void setData(QVariant v);

signals:

public slots:

private:
    QLabel *text_t;
    QLabel *text_b;
    QLabel *text_r;
};

#endif // LISTWIDGETITEM_H

QWidget* getDataWidgetType(QAbstractItemModel* model, int role, QWidget* parent);

void setDataToWidget(QWidget *item, QAbstractItemModel *model, int row);
