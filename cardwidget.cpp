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

void CardWidget::setName(QString name)
{
    text_name->setText(name);
}

void CardWidget::setFName(QString fname)
{
    text_f->setText(fname);
}

void CardWidget::setAge(unsigned int age)
{
    text_age->setText(QString("Возраст: %1").arg(age));
}
