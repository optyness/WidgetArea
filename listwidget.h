#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QtWidgets>
#include "widgettype.h"

class ListWidget : public QScrollArea
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = nullptr);
    ~ListWidget() = default;

    void setModel(QAbstractItemModel *model);

protected:
    void resizeEvent(QResizeEvent* event) override;
    virtual QWidget* createWidgetForModelRow(QAbstractItemModel *model,
                                       int row, QWidget *parent) const = 0;
    virtual void setDataToWidget(QWidget *item, QAbstractItemModel *model, int row) = 0;

public slots:
    void onScrollMoved(int value);

private:
    int nextIndex(int index) const;
    int prevIndex(int index) const;

    QAbstractItemModel *model_ptr;
    QWidget *layout_w;
    QVector<QWidget*> items;
    QMap<WType,QVector<QWidget*>> cache;
    int old_scroll;
    int index_first, index_last;
    int model_first, model_last;
};

#endif // LISTWIDGET_H
