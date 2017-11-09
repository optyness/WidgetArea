#include "listwidget.h"

ListWidget::ListWidget(QWidget *parent)
    : QScrollArea(parent), index_first(0), index_last(0), model_first(0), model_last(0),
      old_scroll(0)
{
    layout_w = new QFrame(this);
    layout_w->setFrameStyle(QFrame::Panel | QFrame::Raised);
    layout_w->setLineWidth(2);
    //layout_w->resize(150,1000);
    setWidget(layout_w);
    connect(verticalScrollBar(), &QScrollBar::valueChanged,
            this, &ListWidget::scrollMoved);
}

ListWidget::~ListWidget()
{

}

void ListWidget::setModel(QAbstractItemModel *model)
{
    //загрузка первого элемента, для установки размеров
    int  average_height = 0;
    model_ptr = model;
    items.append(getDataWidgetType(model_ptr,0,layout_w));
    setDataToWidget(items[index_first],model_ptr,model_first);
    items[0]->show();
    average_height += items[0]->height();

    //загрузка первого листа элементов
    while(items[index_last]->y() + items[index_last]->height() < height() &&
          model_last < model_ptr->rowCount() - 1){
        ++index_last;
        ++model_last;
        items.append(getDataWidgetType(model_ptr,model_last,layout_w));
        setDataToWidget(items[index_last],model_ptr,model_last);
        average_height += items[index_last]->height();
        items[index_last]->show();
        items[index_last]->move(0,items[index_last-1]->y() + items[index_last-1]->height());
    }
    layout_w->resize(viewport()->width() - 20,
                    average_height / (index_last + 1) * model_ptr->rowCount());
}

void ListWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    if(items.isEmpty())
        return;

    //проверить с разным количеством элементов в окне и разными размерами
    while(items[index_last]->y() + items[index_last]->height() <
            verticalScrollBar()->value() + height()){
        WType type = model_ptr->data(model_ptr->index(++model_last,0)).value<WType>();
        if(!(cache.contains(type))){
            cache.insert(type,QVector<QWidget*>());
        }
        if(index_last != items.size() - 1)
            ++index_first;
        if(cache[type].isEmpty()){
            items.insert(++index_last,getDataWidgetType(model_ptr,model_last,layout_w));
        }else{
            items.insert(++index_last,cache[type].takeLast());
        }
        setDataToWidget(items[index_last],model_ptr,model_last);
        items[index_last]->show();
        items[index_last]->move(0,items[index_last-1]->y() + items[index_last-1]->height());
    }
    while(items[index_last]->y() >
          verticalScrollBar()->value() + height()){
        WType type = model_ptr->data(model_ptr->index(model_last,0)).value<WType>();
        if(!(cache.contains(type))){
            cache.insert(type,QVector<QWidget*>());
        }
        items[index_last]->hide();
        cache[type].append(items[index_last]);
        if(index_last != items.size() - 1)
            index_first = prevIndex(index_first);
        items.remove(index_last);
        index_last = prevIndex(index_last);
        --model_last;
    }
}

void ListWidget::scrollMoved(int value)
{
    //присвоение "уходящим" виджетам нового значения и перемещение на сторону "вхождения"
    if(value > old_scroll)
    while((value > items[index_first]->y() + items[index_first]->height()) ||
          (value + height() > items[index_last]->y() + items[index_last]->height())){
        if(value > items[index_first]->y() + items[index_first]->height()){
            WType type = model_ptr->data(model_ptr->index(model_first,0)).value<WType>();
            //QString type = model_ptr->data(model_ptr->index(model_first,0)).toString();
            if(!(cache.contains(type))){
                cache.insert(type,QVector<QWidget*>());
            }
            items[index_first]->hide();
            cache[type].append(items[index_first]);
            if(index_first == 0)
                index_last = prevIndex(index_last);
            items.remove(index_first);
            ++model_first;
        }
        if(value + height() > items[index_last]->y() + items[index_last]->height()){
            if(model_last + 1 >= model_ptr->rowCount()) break;
            WType type = model_ptr->data(model_ptr->index(++model_last,0)).value<WType>();
            //QString type = model_ptr->data(model_ptr->index(++model_last,0)).toString();
            if(!(cache.contains(type))){
                cache.insert(type,QVector<QWidget*>());
            }
            if(index_last != items.size() - 1)
                ++index_first;
            if(cache[type].isEmpty()){
                items.insert(++index_last,getDataWidgetType(model_ptr,model_last,layout_w));
            }else{
                items.insert(++index_last,cache[type].takeLast());
            }
            setDataToWidget(items[index_last],model_ptr,model_last);
            items[index_last]->show();
            items[index_last]->move(0,items[prevIndex(index_last)]->y()
                    + items[prevIndex(index_last)]->height());
        }
    }
    if(value < old_scroll)
    while((value + height() < items[index_last]->y()) ||
          (value < items[index_first]->y() + items[index_first]->height())){
        if(value + height() < items[index_last]->y()){
            WType type = model_ptr->data(model_ptr->index(model_last,0)).value<WType>();
            //QString type = model_ptr->data(model_ptr->index(model_last,0)).toString();
            if(!(cache.contains(type))){
                cache.insert(type,QVector<QWidget*>());
            }
            items[index_last]->hide();
            cache[type].append(items[index_last]);
            if(index_last != items.size() - 1)
                index_first = prevIndex(index_first);
            items.remove(index_last);
            index_last = prevIndex(index_last);
            --model_last;
        }
        if(value < items[index_first]->y() + items[index_first]->height()){
            if(model_first <= 0) break;
            WType type = model_ptr->data(model_ptr->index(--model_first,0)).value<WType>();
            //QString type = model_ptr->data(model_ptr->index(--model_first,0)).toString();
            if(!(cache.contains(type))){
                cache.insert(type,QVector<QWidget*>());
            }
            if(index_first == 0)
                ++index_last;
            if(cache[type].isEmpty()){
                items.insert(index_first,getDataWidgetType(model_ptr,model_first,layout_w));
            }else{
                items.insert(index_first,cache[type].takeLast());
            }
            setDataToWidget(items[index_first],model_ptr,model_first);
            items[index_first]->show();
            items[index_first]->move(0,items[nextIndex(index_first)]->y()
                    - items[index_first]->height());
        }
    }
    old_scroll = value;
}

int ListWidget::nextIndex(int index)
{
    return (index == items.size() - 1) ? 0 : ++index;
}

int ListWidget::prevIndex(int index)
{
    return (index == 0) ? items.size() - 1 : --index;
}
