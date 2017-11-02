#include "cardlist.h"

CardList::CardList()
{

}

QWidget* CardList::getDataWidgetType(QAbstractItemModel *model, int row, QWidget *parent)
{
    QString type = model->data(model->index(row,0),Qt::DisplayRole).toString();
    if(type == "IDCard"){//создание виджета объекта IDCard
        CardWidget *item = new CardWidget(parent);
        return item;
    }else{
        ListWidgetItem *item = new ListWidgetItem(parent);
        return item;
    }
}

void CardList::setDataToWidget(QWidget *item, QAbstractItemModel *model, int row)
{
    QString type = model->data(model->index(row,0)).toString();
    if(type == "IDCard"){
        CardWidget *data_widget = qobject_cast<CardWidget*>(item);
        data_widget->setTextLabel(model->data(model->index(row,0)));
    }else{
        ListWidgetItem *data_widget = qobject_cast<ListWidgetItem*>(item);
        data_widget->setTextLabel(model->data(model->index(row,0)));
    }
}
