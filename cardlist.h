#ifndef CARDLIST_H
#define CARDLIST_H

#include "listwidget.h"

class CardList : public ListWidget
{
public:
    CardList();

protected:
    QWidget* createWidgetForModelRow(QAbstractItemModel *model,
                               int row, QWidget *parent) const override;
    void setDataToWidget(QWidget *item, QAbstractItemModel *model, int row) override;

};

#endif // CARDLIST_H
