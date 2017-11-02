#include "listwidget.h"
//#include "listwidgetitem.h"
#include "cardlist.h"
//#include "cardwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    CardList *list = new CardList;
    QHBoxLayout *layout = new QHBoxLayout(&w);
    layout->addWidget(list);
    w.setLayout(layout);
    w.show();

    w.resize(200,600);
    QStringListModel *model = new QStringListModel();
    QStringList lines;
    for(int i = 0; i < 1000; ++i)
        if(i % 5 == 0){
            lines << QString("IDCard");
        }else{
            lines << QString("List");
        }
    model->setStringList(lines);
    list->setModel(model);

    return a.exec();
}
