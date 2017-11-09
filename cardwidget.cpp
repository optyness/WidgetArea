#include "cardwidget.h"

CardWidget::CardWidget(QWidget *parent) : QFrame(parent)
{
    resize(150,70);
    text_name = new QLabel(this);
    text_f = new QLabel(this);
    text_age = new QLabel(this);

    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(2);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(text_name,0,0);
    layout->addWidget(text_f,1,0);
    layout->addWidget(text_age,2,0);
    setLayout(layout);
}

void CardWidget::setName(QVariant v)
{
    QString s = v.toString();
    text_name->setText(s);
}

void CardWidget::setFName(QVariant v)
{
    QString s = v.toString();
    text_f->setText(s);
}

void CardWidget::setAge(QVariant v)
{
    int age = v.toInt();
    text_age->setText(QString("Возраст: %1").arg(age));
}
