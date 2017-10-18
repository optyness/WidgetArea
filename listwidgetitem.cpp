#include "listwidgetitem.h"

static const QPoint topPos(10,10);
static const QPoint botPos(10,30);
static const QPoint rightPos(90,20);

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
