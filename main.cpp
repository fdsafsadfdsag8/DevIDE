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
<<<<<<< HEAD

    w.show();
||||||| merged common ancestors
    w.show();


=======
||||||| merged common ancestors
<<<<<<<<< Temporary merge branch 1

    w.show();
||||||||| merged common ancestors
    w.show();


=========
=======
>>>>>>> 253e1f610b35c168bf1f2edfa4378d4d08385c4c
    w.show();

<<<<<<< HEAD
>>>>>>> upstream/master
||||||| merged common ancestors
>>>>>>>>> Temporary merge branch 2
=======
>>>>>>> 253e1f610b35c168bf1f2edfa4378d4d08385c4c
    return a.exec();
}
