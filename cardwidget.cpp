#include "cardwidget.h"

CardWidget::CardWidget(QWidget *parent) : QFrame(parent)
{
    setFixedSize(150,70);
    text_name = new QLabel(this);
    text_f = new QLabel(this);
    text_age = new QLabel(this);

    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(2);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(text_name);
    layout->addWidget(text_f);
    layout->addWidget(text_age);
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
