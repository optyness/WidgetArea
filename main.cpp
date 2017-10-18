#include "listwidget.h"
#include "listwidgetitem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    ListWidget *list = new ListWidget;
    QHBoxLayout *layout = new QHBoxLayout(&w);
    layout->addWidget(list);
    w.setLayout(layout);
    w.show();

    w.resize(200,600);
    QStringListModel *model = new QStringListModel();
    QStringList lines;
    for(int i = 0; i < 1000; ++i)
        lines << QString("%1").arg(i);
    model->setStringList(lines);
    list->setModel(model);

    return a.exec();
}
