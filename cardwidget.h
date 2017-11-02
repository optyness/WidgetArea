#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QtWidgets>

class CardWidget : public QFrame
{
    Q_OBJECT
public:
    CardWidget(QWidget *parent = nullptr);

    void setTextLabel(QVariant v);

private:
    QLabel *text_t;
    QLabel *text_b;
    QLabel *text_r;
};

#endif // CARDWIDGET_H
