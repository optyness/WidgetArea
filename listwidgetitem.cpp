#include "listwidgetitem.h"

ListWidgetItem::ListWidgetItem(QWidget *parent) : QFrame(parent)
{
    resize(150,100);
    text_sender = new QLabel(this);
    text_message = new QLabel(this);

    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(2);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(text_sender,0,0);
    layout->addWidget(text_message,1,0);
    setLayout(layout);
}

void ListWidgetItem::setSender(QVariant v)
{
    QString s = v.toString();
    text_sender->setText(s);
}

void ListWidgetItem::setMessage(QVariant v)
{
    QString s = v.toString();
    text_message->setText(s);
}
