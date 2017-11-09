#include "listwidget.h"
//#include "listwidgetitem.h"
#include "cardlist.h"
#include "widgetmodel.h"
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

//    QStringListModel *model = new QStringListModel();
//    QStringList lines;
//    for(int i = 0; i < 1000; ++i)
//        if(i % 5 == 0){
//            lines << QString("IDCard");
//        }else{
//            lines << QString("List");
//        }
//    model->setStringList(lines);

    WidgetModel *model = new WidgetModel();
    for(int i = 0; i < 17; ++i){
//        if(i % 3 == 0){
            model->setData(QModelIndex(),QVariant::fromValue(WType::NameCard),Qt::UserRole);
            model->setData(QModelIndex(),
                           QVariant::fromValue(QString("Имя %1").arg(i)),Qt::UserRole+1);
            model->setData(QModelIndex(),
                           QVariant::fromValue(QString("Фамилия %1").arg(i)),Qt::UserRole+2);
            model->setData(QModelIndex(),
                           QVariant::fromValue(i),Qt::UserRole+3);
//        }else{
//            model->setData(QModelIndex(),QVariant::fromValue(WType::Message),Qt::UserRole);
//            model->setData(QModelIndex(),
//                           QVariant::fromValue(QString("ФИО Отправителя %1").arg(i)),Qt::UserRole+1);
//            model->setData(QModelIndex(),
//                           QVariant::fromValue(QString("Сообщение")),Qt::UserRole+2);
//        }
    }
    list->setModel(model);

    return a.exec();
}
