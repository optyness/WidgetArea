#include "listwidget.h"
#include "cardlist.h"
#include "widgetmodel.h"
#include "usermodelrole.h"

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
    for(int i = 0; i < 170; ++i){
        model->createData();
        if(i % 3 == 0){
            model->setData(QModelIndex(),QVariant::fromValue(WType::NameCard),(int)MRole::type);
            model->setData(QModelIndex(),
                           QVariant::fromValue(QString("Имя %1").arg(i)),(int)MRole::name);
            model->setData(QModelIndex(),
                           QVariant::fromValue(QString("Фамилия %1").arg(i)),(int)MRole::fname);
            model->setData(QModelIndex(),
                           QVariant::fromValue(i),(int)MRole::age);
        }else{
            model->setData(QModelIndex(),QVariant::fromValue(WType::Message),(int)MRole::type);
            model->setData(QModelIndex(),
                           QVariant::fromValue(QString("ФИО Отправителя %1").arg(i)),(int)MRole::sender);
            model->setData(QModelIndex(),
                           QVariant::fromValue(QString("Сообщение")),(int)MRole::message);
        }
    }
    list->setModel(model);

    return a.exec();
}
