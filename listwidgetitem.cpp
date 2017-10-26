#include "listwidgetitem.h"

ListWidgetItem::ListWidgetItem(QWidget *parent) : QFrame(parent)
{
    resize(120,70);
    text_t = new QLabel("test",this);
    text_b = new QLabel("test2",this);
    text_r = new QLabel("test3",this);

    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(2);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(text_t,0,0);
    layout->addWidget(text_b,3,0);
    layout->addWidget(text_r,2,1);
    setLayout(layout);
//    text_t->move(topPos);
//    text_b->move(botPos);
//    text_r->move(rightPos);
}

void ListWidgetItem::setData(QVariant v)
{
    QString s = v.toString();
    text_t->setText(s);
    text_b->setText(s);
    text_r->setText(s);
}

//enum dataWidgetTypes {IDCard, nonCard};

QWidget* getDataWidgetType(QAbstractItemModel *model, int role, QWidget *parent)
{
    QString type = model->data(model->index(0,0),role).toString();
    if(type == "IDCard"){//создание виджета объекта IDCard
        QWidget* item = new QWidget(parent);
        item->resize(100,100);
        QLabel* l = new QLabel("test",item);
        return item;
    }else{
        ListWidgetItem* item = new ListWidgetItem(parent);
        //QObjectList obj = item->children();
        //qDebug() << obj;
        return item;
    }
}

void setDataToWidget(QWidget *item, QAbstractItemModel *model, int row)
{
    QString type = model->data(model->index(0,0)).toString();
    if(type == "IDCard"){
        return;//изменение виджета объекта IDCard
    }else{
        QObjectList child_list = item->children();
        QLabel *lbl = qobject_cast<QLabel*>(child_list[0]);
        lbl->setText(model->data(model->index(row,0)).toString());
        lbl = qobject_cast<QLabel*>(child_list[1]);
        lbl->setText(model->data(model->index(row,0)).toString());
        lbl = qobject_cast<QLabel*>(child_list[2]);
        lbl->setText(model->data(model->index(row,0)).toString());
    }
}
