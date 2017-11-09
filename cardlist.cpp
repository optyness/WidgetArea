#include "cardlist.h"

CardList::CardList()
{

}

QWidget* CardList::getDataWidgetType(QAbstractItemModel *model, int row, QWidget *parent)
{
    WType type = model->data(model->index(row,0),Qt::UserRole).value<WType>();
    switch(type){
    case WType::NameCard:{
        CardWidget *item = new CardWidget(parent);
        return item;
    }
    case WType::Message:{
        ListWidgetItem *item = new ListWidgetItem(parent);
        return item;
    }
    default:{
        return new QWidget();
    }
    }
}

void CardList::setDataToWidget(QWidget *item, QAbstractItemModel *model, int row)
{
    qDebug() << "1";
    WType type = model->data(model->index(row,0),Qt::UserRole).value<WType>();
    switch(type){
    case WType::NameCard:{
        qDebug() << "2";
        CardWidget *data_widget = qobject_cast<CardWidget*>(item);
        data_widget->setName(model->data(model->index(row,0),Qt::UserRole+1));
        data_widget->setFName(model->data(model->index(row,0),Qt::UserRole+2));
        data_widget->setAge(model->data(model->index(row,0),Qt::UserRole+3));
        qDebug() << "3";
        return;
    }
    case WType::Message:{
        qDebug() << "4";
        ListWidgetItem *data_widget = qobject_cast<ListWidgetItem*>(item);
        data_widget->setSender(model->data(model->index(row,0),Qt::UserRole+1));
        data_widget->setMessage(model->data(model->index(row,0),Qt::UserRole+2));
        return;
    }
    default:{
        return;
    }
    }
}
