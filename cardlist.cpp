#include "cardlist.h"
#include "listwidgetitem.h"
#include "cardwidget.h"
#include "widgettype.h"
#include "usermodelrole.h"

CardList::CardList()
{

}

QWidget* CardList::createWidgetForModelRow(QAbstractItemModel *model, int row, QWidget *parent) const
{
    WType type = model->data(model->index(row,0), Qt::UserRole).value<WType>();
    switch(type){
    case WType::NameCard:{
        auto *item = new CardWidget(parent);
        return item;
    }
    case WType::Message:{
        auto *item = new ListWidgetItem(parent);
        return item;
    }
    default:{
        return new QWidget();
    }
    }
}

void CardList::setDataToWidget(QWidget *item, QAbstractItemModel *model, int row)
{
    WType type = model->data(model->index(row,0), (int)MRole::type).value<WType>();
    switch(type){
    case WType::NameCard:{
        auto *data_widget = qobject_cast<CardWidget*>(item);
        data_widget->setName(model->data(model->index(row,0), (int)MRole::name).toString());
        data_widget->setFName(model->data(model->index(row,0), (int)MRole::fname).toString());
        data_widget->setAge(model->data(model->index(row,0), (int)MRole::age).toInt());
        return;
    }
    case WType::Message:{
        auto *data_widget = qobject_cast<ListWidgetItem*>(item);
        data_widget->setSender(model->data(model->index(row,0), (int)MRole::sender).toString());
        data_widget->setMessage(model->data(model->index(row,0), (int)MRole::message).toString());
        return;
    }
    default:{
        return;
    }
    }
}
