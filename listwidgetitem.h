#ifndef LISTWIDGETITEM_H
#define LISTWIDGETITEM_H

#include <QtWidgets>

class ListWidgetItem : public QFrame
{
    Q_OBJECT
public:
    explicit ListWidgetItem(QWidget *parent = nullptr);

    void setSender(QVariant v);
    void setMessage(QVariant v);

private:
    QLabel *text_sender;
    QLabel *text_message;
};

#endif // LISTWIDGETITEM_H
