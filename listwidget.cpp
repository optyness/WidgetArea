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
    model_ptr = model;
    items.append(getDataWidgetType(model_ptr,0,layout_w));
    setDataToWidget(items[index_first],model_ptr,model_first);
    items[0]->show();

    //загрузка первого листа элементов
    while(items[index_last]->y() + items[index_last]->height() < height()){
        ++index_last;
        ++model_last;
        items.append(getDataWidgetType(model_ptr,model_last,layout_w));
        setDataToWidget(items[index_last],model_ptr,model_last);
        items[index_last]->show();
        items[index_last]->move(0,items[index_last-1]->y() + items[index_last-1]->height());
    }
    layout_w->resize(viewport()->width() - 20,
                    items[0]->height() * model->rowCount());
}

void ListWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    if(items.isEmpty())
        return;

    while(items[index_last]->y() + items[index_last]->height() <
            verticalScrollBar()->value() + height()){
        QString type = model_ptr->data(model_ptr->index(++model_last,0)).toString();
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
        QString type = model_ptr->data(model_ptr->index(model_last,0)).toString();
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
//    int new_page_size = this->height() / items[0]->height() + 2;

//    if(new_page_size == page_size)
//        return;

//    if(new_page_size > model_ptr->rowCount())
//        return;

//    //изменение количества отображаемых элементов (корректировка размера items)
//    if(new_page_size > page_size){ //добавление
//        for(int i = 0; i < new_page_size - page_size; ++i){
//            if(index_last == items.size() - 1){
//                items.append(getDataWidgetType(model_ptr,Qt::DisplayRole,layout_w));
//                ++index_last;
//            }else{
//                items.insert(++index_last,getDataWidgetType(model_ptr,Qt::DisplayRole,layout_w));
//                ++index_first;
//            }
//            items[index_last]->show();

//            //items[index_last]->setData(model_ptr->data(model_ptr->index(++model_last,0)));
//            //setDataToWidget(items[index_last],model_ptr,++model_last);
//            items[index_last]->move(0,items[index_last-1]->y() + items[index_last]->height());
//        }
//        page_size = new_page_size;
//    }else if(new_page_size < page_size){  //удаление
//        for(int i = 0; i < page_size - new_page_size; ++i){
//            if(index_last == items.size() - 1){
//                items[index_last]->deleteLater();
//                items.removeLast();
//                --index_last;
//            }else{
//                items[index_last]->deleteLater();
//                items.removeAt(index_last);
//                index_last = prevIndex(index_last);
//                index_first = prevIndex(index_first);
//            }
//            --model_last;
//        }
//        page_size = new_page_size;
//    }
}

void ListWidget::scrollMoved(int value)
{
    //присвоение "уходящим" виджетам нового значения и перемещение на сторону "вхождения"
    if(value > old_scroll)
    while((value > items[index_first]->y() + items[index_first]->height()) ||
          (value + height() > items[index_last]->y() + items[index_last]->height())){
        if(value > items[index_first]->y() + items[index_first]->height()){
            //WType type = qvariant_cast<WType>(model_ptr->data(model_ptr->index(model_first,0)));
            QString type = model_ptr->data(model_ptr->index(model_first,0)).toString();
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
            //WType type = qvariant_cast<WType>(model_ptr->data(model_ptr->index(++model_last,0)));
            QString type = model_ptr->data(model_ptr->index(++model_last,0)).toString();
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
            //WType type = qvariant_cast<WType>(model_ptr->data(model_ptr->index(model_last,0)));
            QString type = model_ptr->data(model_ptr->index(model_last,0)).toString();
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
            //WType type = qvariant_cast<WType>(model_ptr->data(model_ptr->index(--model_first,0)));
            QString type = model_ptr->data(model_ptr->index(--model_first,0)).toString();
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

//void ListWidget::cacheAction()
//{
//    QString new_type = model_ptr->data(model_ptr->index(++model_last,0)).toString();
//    QString old_type = model_ptr->data(model_ptr->index(model_first,0)).toString();
//    if(!(cache.contains(new_type))){
//        cache.insert(new_type,QVector<QWidget*>());
//    }

//    ++model_first;
//    if(new_type != old_type){
//        items[index_first]->hide();
//        cache[old_type].append(items[index_first]);
//        if(cache[new_type].isEmpty()){
//            items[index_first] = getDataWidgetType(model_ptr,model_last,layout_w);
//        }else{
//            items[index_first] = cache[new_type].takeLast();
//        }
//    }
//    setDataToWidget(items[index_first],model_ptr,model_last);
//    items[index_first]->move(0,items[index_last]->y() + items[index_last]->height());
//    items[index_first]->show();
//    index_last = index_first;
//    index_first = nextIndex(index_first);
//}

//enum class widget_type;
