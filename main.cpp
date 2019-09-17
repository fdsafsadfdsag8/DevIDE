#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include<QTextCodec>
#include<QTreeWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    MainWindow w;
<<<<<<< HEAD

    w.show();
||||||| merged common ancestors
    w.show();


=======
    w.show();

>>>>>>> upstream/master
    return a.exec();
}
