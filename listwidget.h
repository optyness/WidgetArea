#ifndef LISTWIDGET_H
#define LISTWIDGET_H

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
    virtual QWidget* getDataWidgetType(QAbstractItemModel *model,
                                       int row, QWidget *parent) = 0;
    virtual void setDataToWidget(QWidget *item, QAbstractItemModel *model, int row) = 0;
    //void cacheAction();
public slots:
    void scrollMoved(int value);

private:
    int nextIndex(int index);
    int prevIndex(int index);

    enum class WType;
    QAbstractItemModel *model_ptr;
    QFrame *layout_w;
    QVector<QWidget*> items;
    QMap<QString,QVector<QWidget*>> cache;
    int old_scroll;
    int index_first, index_last;
    int model_first, model_last;
};

#endif // LISTWIDGET_H
