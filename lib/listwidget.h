#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QtWidgets>

class ListWidget : public QScrollArea
{
public:
    explicit ListWidget(QWidget *parent = nullptr);
    ~ListWidget() = default;

    void setModel(QAbstractItemModel *model);

protected:
    void resizeEvent(QResizeEvent* event) override;
    virtual QWidget* createWidgetForModelRow(QAbstractItemModel *model,
                                       int row, QWidget *parent) const = 0;
    virtual void setDataToWidget(QWidget *item, QAbstractItemModel *model, int row) = 0;
    void setMargin(unsigned int between, unsigned int edge);

public slots:
    void onScrollMoved(int value);

private:
    int nextIndex(int index) const;
    int prevIndex(int index) const;

    QAbstractItemModel *model_ptr;
    QWidget *layout_w;
    QVector<QWidget*> items;
    QMap<int,QVector<QWidget*>> cache;
    int old_scroll;
    int index_first, index_last;
    int model_first, model_last;
    unsigned int margin, margin_b;
};

#endif // LISTWIDGET_H
