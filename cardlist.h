#ifndef CARDLIST_H
#define CARDLIST_H

#include "listwidget.h"
#include "listwidgetitem.h"
#include "cardwidget.h"

class CardList : public ListWidget
{
public:
    CardList();

protected:
    QWidget* getDataWidgetType(QAbstractItemModel *model,
                               int row, QWidget *parent) override;
    void setDataToWidget(QWidget *item, QAbstractItemModel *model, int row) override;
private:
    enum class WType;

};

#endif // CARDLIST_H
