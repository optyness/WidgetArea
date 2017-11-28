#include "listwidget.h"

ListWidget::ListWidget(QWidget *parent)
    : QScrollArea(parent), index_first(0), index_last(0), model_first(0), model_last(0),
      old_scroll(0), margin(20), margin_b(10)
{
    layout_w = new QWidget(this);
    setWidget(layout_w);
    connect(verticalScrollBar(), &QScrollBar::valueChanged,
            this, &ListWidget::onScrollMoved);
}

void ListWidget::setModel(QAbstractItemModel *model)
{
    //загрузка первого элемента, для установки размеров
    int  average_height = 0;
    model_ptr = model;
    items.append(createWidgetForModelRow(model_ptr, 0, layout_w));
    setDataToWidget(items[index_first], model_ptr, model_first);
    items[0]->show();
    items[0]->move(margin,margin);
    average_height += items[0]->height();

    //загрузка первого листа элементов
    while(items[index_last]->y() + items[index_last]->height() < height() &&
          model_last < model_ptr->rowCount() - 1){
        ++index_last;
        ++model_last;
        items.append(createWidgetForModelRow(model_ptr, model_last, layout_w));
        setDataToWidget(items[index_last], model_ptr, model_last);
        average_height += items[index_last]->height();
        items[index_last]->show();
        items[index_last]->move(margin, items[index_last-1]->y() + items[index_last-1]->height() + margin_b);
    }
    layout_w->resize(viewport()->width() + margin * 2,
                    average_height / (index_last + 1) * model_ptr->rowCount() + margin * 2 +
                     margin_b * (model_ptr->rowCount() - 1));
}

void ListWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    if(items.isEmpty())
        return;

    if(layout_w->height() < height())
        return;

    auto maxSizeHint = 0;
    //ширина внутренних виджетов
    for(int i = 0; i < items.size(); ++i){
        auto viewportWidth = viewport()->width();
        auto itemHight = items[i]->height();

        if(items[i]->sizeHint().isValid()){
            if(viewportWidth > items[i]->sizeHint().width() + margin * 2){
                items[i]->resize(viewportWidth - margin * 2, itemHight);
            }else{
                items[i]->resize(items[i]->sizeHint().width(), itemHight);
            }
            if(items[i]->sizeHint().width() > maxSizeHint)
                maxSizeHint = items[i]->sizeHint().width();
        }else{
            items[i]->resize(viewportWidth - margin * 2, itemHight);
        }
    }
    //ширина внешнего виджета
    if(viewport()->width() < maxSizeHint + margin * 2)
        layout_w->resize(maxSizeHint + margin * 2, layout_w->height());
    else
        layout_w->resize(viewport()->width(), layout_w->height());

    while(items[index_last]->y() + items[index_last]->height() <
            verticalScrollBar()->value() + height()){
        if(model_last + 1 >= model_ptr->rowCount()) break;
        auto type = model_ptr->data(model_ptr->index(++model_last, 0), Qt::UserRole).toInt();
        if(!(cache.contains(type))){
            cache.insert(type, QVector<QWidget*>());
        }
        if(index_last != items.size() - 1)
            ++index_first;
        if(cache[type].isEmpty()){
            items.insert(++index_last, createWidgetForModelRow(model_ptr, model_last, layout_w));
            items[index_last]->resize(layout_w->width(), items[index_last]->height());//-
        }else{
            items.insert(++index_last, cache[type].takeLast());
            items[index_last]->resize(layout_w->width(), items[index_last]->height());//-
        }
        setDataToWidget(items[index_last], model_ptr,model_last);
        items[index_last]->show();
        items[index_last]->move(margin, items[index_last - 1]->y() + items[index_last - 1]->height() + margin_b);

        //размеры виджета-полотна
        if(verticalScrollBar()->value() + verticalScrollBar()->pageStep() >= verticalScrollBar()->maximum() &&
                model_last != model_ptr->rowCount() && items[index_last]->y() + items[index_last]->height() > layout_w->height()){

            layout_w->resize(layout_w->width(),
                             items[index_last]->y() + items[index_last]->height());
            layout_w->show();
        }
    }
    //добавление в начало (растяжение вверх)
    while(items[index_last]->y() >
          verticalScrollBar()->value() + height()){
        auto type = model_ptr->data(model_ptr->index(model_last, 0), Qt::UserRole).toInt();
        if(!(cache.contains(type))){
            cache.insert(type, QVector<QWidget*>());
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

void ListWidget::onScrollMoved(int value)
{
    //присвоение "уходящим" виджетам нового значения и перемещение на сторону "вхождения"
    if(value > old_scroll)
    //скролл вниз
    while((value > items[index_first]->y() + items[index_first]->height()) ||
          (value + height() > items[index_last]->y() + items[index_last]->height())){
        if(value > items[index_first]->y() + items[index_first]->height()){
            auto type = model_ptr->data(model_ptr->index(model_first, 0), Qt::UserRole).toInt();
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
            auto type = model_ptr->data(model_ptr->index(++model_last, 0), Qt::UserRole).toInt();
            if(!(cache.contains(type))){
                cache.insert(type, QVector<QWidget*>());
            }
            if(index_last != items.size() - 1)
                ++index_first;
            if(cache[type].isEmpty()){
                items.insert(++index_last, createWidgetForModelRow(model_ptr, model_last, layout_w));
                items[index_last]->resize(layout_w->width(), items[index_last]->height());//-
            }else{
                items.insert(++index_last,cache[type].takeLast());
                items[index_last]->resize(layout_w->width(), items[index_last]->height());//-
            }
            setDataToWidget(items[index_last], model_ptr, model_last);
            items[index_last]->show();
            items[index_last]->move(margin, items[prevIndex(index_last)]->y()
                    + items[prevIndex(index_last)]->height() + margin_b);
            //--------
            if(value + verticalScrollBar()->pageStep() >= verticalScrollBar()->maximum() &&
                    model_last != model_ptr->rowCount() && items[index_last]->y() + items[index_last]->height() > layout_w->height()){
                layout_w->resize(layout_w->width(),
                                 items[index_last]->y() + items[index_last]->height());
                layout_w->show();
            }
        }
    }
    if(value < old_scroll)
    //скролл вверх
    while((value + height() < items[index_last]->y()) ||
          (value < items[index_first]->y() + items[index_first]->height())){
        if(value + height() < items[index_last]->y()){
            auto type = model_ptr->data(model_ptr->index(model_last, 0), Qt::UserRole).toInt();
            if(!(cache.contains(type))){
                cache.insert(type, QVector<QWidget*>());
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
            auto type = model_ptr->data(model_ptr->index(--model_first, 0), Qt::UserRole).toInt();
            if(!(cache.contains(type))){
                cache.insert(type, QVector<QWidget*>());
            }
            if(index_first == 0)
                ++index_last;
            if(cache[type].isEmpty()){
                items.insert(index_first, createWidgetForModelRow(model_ptr, model_first, layout_w));
                items[index_last]->resize(layout_w->width(), items[index_last]->height());//-
            }else{
                items.insert(index_first, cache[type].takeLast());
                items[index_last]->resize(layout_w->width(), items[index_last]->height());//-
            }
            setDataToWidget(items[index_first], model_ptr, model_first);
            items[index_first]->show();
            items[index_first]->move(margin, items[nextIndex(index_first)]->y()
                    - items[index_first]->height() - margin_b);
        }
    }
    old_scroll = value;
}

void ListWidget::setMargin(unsigned int between, unsigned int edge)
{
    margin = edge;
    margin_b = between;
}

int ListWidget::nextIndex(int index) const
{
    return (index == items.size() - 1) ? 0 : ++index;
}

int ListWidget::prevIndex(int index) const
{
    return (index == 0) ? items.size() - 1 : --index;
}
