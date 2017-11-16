#include "listwidgetitem.h"

ListWidgetItem::ListWidgetItem(QWidget *parent) : QFrame(parent)
{
    resize(150,100);
    text_sender = new QLabel(this);
    text_message = new QLabel(this);

    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(2);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(text_sender);
    layout->addWidget(text_message);
    setLayout(layout);
}

void ListWidgetItem::setSender(QString sender)
{
    text_sender->setText(sender);
}

void ListWidgetItem::setMessage(QString message)
{
    text_message->setText(message);
}
