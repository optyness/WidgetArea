#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "listwidgetitem.h"
#include <QtWidgets>

class ListWidget : public QScrollArea
{
    Q_OBJECT

public:
    ListWidget(QWidget *parent = 0);
    ~ListWidget();

    void setModel(QAbstractItemModel *model);

protected:
    void resizeEvent(QResizeEvent* event) override;

public slots:
    void scrollMoved(int value);

private:
    int nextIndex(int index);
    int prevIndex(int index);

    QAbstractItemModel *model_ptr;
    QFrame *layout_w;
    QVector <QWidget*> items;
    int margin_w;
    int page_size;
    int index_first, index_last;
    int model_first, model_last;
};

#endif // LISTWIDGET_H
