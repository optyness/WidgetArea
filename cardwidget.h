#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QtWidgets>

class CardWidget : public QFrame
{
    Q_OBJECT
public:
    CardWidget(QWidget *parent = nullptr);

    void setName(QVariant v);
    void setFName(QVariant v);
    void setAge(QVariant v);

private:
    QLabel *text_name;
    QLabel *text_f;
    QLabel *text_age;
};

#endif // CARDWIDGET_H
