#include "listwidget.h"
#include "listwidgetitem.h"

ListWidget::ListWidget(QWidget *parent)
    : QScrollArea(parent)
{
    layout_w = new QFrame(this);
    layout_w->setFrameStyle(QFrame::Panel | QFrame::Raised);
    layout_w->setLineWidth(2);
    margin_w += 10;
    setViewportMargins(10,0,10,0);
    setWidget(layout_w);
    connect(verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(scrollMoved(int)));
}

ListWidget::~ListWidget()
{

}

void ListWidget::setModel(QAbstractItemModel *model)
{
    //загрузка первого элемента, для установки размеров
    model_ptr = model;
    items.append(new ListWidgetItem(layout_w));
    items[0]->show();
    items[0]->setData(model_ptr->data(model_ptr->index(0,0)));
    index_first = 0;
    model_first = 0;

    //загрузка первого листа элементов
    page_size = this->height() / items[0]->height() + 2;
    index_last = page_size - 1;
    for(int i = 1; i < page_size; ++i){
        items.append(new ListWidgetItem(layout_w));
        items[i]->show();
        items[i]->setData(model_ptr->data(model_ptr->index(i,0)));
        items[i]->move(0,items[i-1]->y() + items[i]->height());
    }
    model_last = page_size - 1;
    layout_w->resize(items[0]->width(),
                    items[0]->height() * model->rowCount());
}

void ListWidget::resizeEvent(QResizeEvent *event)
{
    QScrollArea::resizeEvent(event);

    if(items.isEmpty())
        return;

    int new_page_size = this->height() / items[0]->height() + 2;

    if(new_page_size == page_size)
        return;

    if(new_page_size > model_ptr->rowCount())
        return;

    //изменение количества отображаемых элементов (корректировка размера items)
    if(new_page_size > page_size){ //добавление
        for(int i = 0; i < new_page_size - page_size; ++i){
            if(index_last == items.size() - 1){
                items.append(new ListWidgetItem(layout_w));
                ++index_last;
            }else{
                items.insert(++index_last,new ListWidgetItem(layout_w));
                ++index_first;
            }
            items[index_last]->show();
            items[index_last]->setData(model_ptr->data(model_ptr->index(++model_last,0)));
            items[index_last]->move(0,items[index_last-1]->y() + items[index_last]->height());
        }
        page_size = new_page_size;
    }else if(new_page_size < page_size){  //удаление
        for(int i = 0; i < page_size - new_page_size; ++i){
            if(index_last == items.size() - 1){
                items[index_last]->deleteLater();
                items.removeLast();
                --index_last;
            }else{
                items[index_last]->deleteLater();
                items.removeAt(index_last);
                index_last = prevIndex(index_last);
                index_first = prevIndex(index_first);
            }
            --model_last;
        }
        page_size = new_page_size;
    }
}

void ListWidget::scrollMoved(int value)
{
    //присвоение "уходящим" виджетам нового значения и перемещение на сторону "вхождения"
    if(value + height() > items[index_last]->y() + items[index_last]->height()){
        int diff_num = ((value + height()) - (items[index_last]->y() + items[index_last]->height())) / items[0]->height();
        for(int i = 0; i <= diff_num; ++i){
            ++model_first;
            items[index_first]->setData(model_ptr->data(model_ptr->index(++model_last,0)));
            items[index_first]->move(0,items[index_last]->y() + items[index_last]->height());
            index_last = index_first;
            index_first = nextIndex(index_first);
        }

    }else if (value < items[index_first]->y()){
        int diff_num = (items[index_first]->y() - value) / items[0]->height();
        for(int i = 0; i <= diff_num; ++i){
            --model_last;
            items[index_last]->setData(model_ptr->data(model_ptr->index(--model_first,0)));
            items[index_last]->move(0,items[index_first]->y() - items[index_first]->height());
            index_first = index_last;
            index_last = prevIndex(index_last);
        }
    }

}

int ListWidget::nextIndex(int index)
{
    return (index == items.size() - 1) ? 0 : ++index;
}

int ListWidget::prevIndex(int index)
{
    return (index == 0) ? items.size() - 1 : --index;
}
