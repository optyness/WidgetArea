#include "cardwidget.h"

CardWidget::CardWidget(QWidget *parent) : QFrame(parent)
{
    resize(70,120);
    text_t = new QLabel("test",this);
    text_b = new QLabel("test2",this);
    text_r = new QLabel("test3",this);

    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setLineWidth(2);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(text_t,0,1);
    layout->addWidget(text_b,1,0);
    layout->addWidget(text_r,2,1);
    setLayout(layout);
}

void CardWidget::setTextLabel(QVariant v)
{
    QString s = v.toString();
    text_t->setText(s);
    text_b->setText(s);
    text_r->setText(s);
}
