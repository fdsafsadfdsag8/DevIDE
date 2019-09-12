#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QPushButton>
#include<QFileDialog>
#include<QTextStream>
#include<QDebug>
#include<QTreeWidget>
#include<QTabBar>
#include<QCompleter>
#include<QFile>
#include<QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString curFile=ui->codeTab->currentFile();
    setWindowTitle(curFile);

    this->resize(QSize(800,500));//修改初始化窗口大小

    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSelectedDocument(QTreeWidgetItem*,int)));

    //my_tab->setShape(QTabBar::TriangularNorth);//设置显示样式
    //splitter();
    ui->splitter->setStretchFactor(0, 1);//初始左边占1/6
    ui->splitter->setStretchFactor(1, 5);//初始右边占5/6

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    ui->codeTab->newFile();
}


void MainWindow::on_action_Save_triggered()
{
    ui->codeTab->save();
}

void MainWindow::on_action_SaveAs_triggered()
{
    ui->codeTab->saveAs();
}

void MainWindow::on_action_open_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    // 如果文件名不为空，则加载文件
    if (!fileName.isEmpty()) {
        ui->codeTab->openFile(fileName);
        loadtree(fileName);
    }
}

void MainWindow::on_action_open_files_triggered()
{
    QString directoryName = QFileDialog::getExistingDirectory(this,tr("选择文件夹"),".");

    if (!directoryName.isEmpty()){
        loadtree(directoryName);
    }
}

void MainWindow::on_action_Close_triggered()
{
    if (ui->codeTab->maybeSave()) {
        ui->codeTab->removeTab(ui->codeTab->currentIndex());
    }
}

void MainWindow::on_action_Run_triggered()
{
    QString curFile=ui->codeTab->currentFile();

    QString dirName=QFileInfo(curFile).path();
    QString baseName=QFileInfo(curFile).baseName();
    QString suffix=QFileInfo(curFile).completeSuffix();
    QString fullName=QFileInfo(curFile).fileName();
    QString prefix;
    if(QString::compare(suffix,"cpp")==0)
        prefix="g++";
    else if(QString::compare(suffix,"c")==0)
        prefix="gcc";
    else {
        throw "FILE_SUFFIX_ERROR";
    }

    QString enterCmd="cd /d "+dirName;
    QString compileCmd=prefix+" -g "+fullName+" -o "+baseName+".exe";
    QString runCmd=baseName+".exe";

    QString cmd=enterCmd+" && "+compileCmd+" && "+runCmd;

    system(cmd.toStdString().c_str());
}

void MainWindow::on_action_Compile_triggered()
{
    QString curFile=ui->codeTab->currentFile();

    QString dirName=QFileInfo(curFile).path();
    QString baseName=QFileInfo(curFile).baseName();
    QString suffix=QFileInfo(curFile).completeSuffix();
    QString fullName=QFileInfo(curFile).fileName();
    QString prefix;
    if(QString::compare(suffix,"cpp")==0)
        prefix="g++";
    else if(QString::compare(suffix,"c")==0)
        prefix="gcc";
    else {
        throw "FILE_SUFFIX_ERROR";
    }

    QString enterCmd="cd /d "+dirName;
    QString compileCmd=prefix+" -g "+fullName+" -o "+baseName+".exe";
    QString cmd=enterCmd+" && "+compileCmd;
//    save();
    system(cmd.toStdString().c_str());
}


void MainWindow::loadtree(const QString &fileName){//加载当前文件的目录树

    ui->treeWidget->clear();//先清空之前的内容
    //创建目录根项
    //QString rootpath=QFileInfo(fileName).path();//获取绝对路径如"F:/qt/homework"    调用这个函数会让文件夹向上一级
    QString rootpath=fileName;
    current_url=rootpath;//获取当前的url
    qDebug() << rootpath;
    /*获取文件名以及路径
    QString file_full, file_name, file_path;
    QFileInfo fi;
    file_full = QFileDialog::getOpenFileName(this);
    fi = QFileInfo(file_full);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    */
    QTreeWidgetItem* root = new QTreeWidgetItem(QStringList()<<rootpath);
    //root->setIcon(0, QIcon(":/file/image/link.ico"));
    root->setCheckState(1, Qt::Checked);
    allfile(root,rootpath);//遍历添加home目录下所有文件
}

QFileInfoList MainWindow::allfile(QTreeWidgetItem *root,QString path)//参数为主函数中添加的item和路径名
{
    ui->treeWidget->addTopLevelItem(root);

    /*添加path路径文件*/
    QDir dir(path);//遍历各级子目录
    QDir dir_file(path);//遍历子目录中所有文件
    dir_file.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);//获取当前所有文件
    dir_file.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list_file = dir_file.entryInfoList();
    for (int i = 0; i < list_file.size(); ++i) {//将当前目录中所有文件添加到treewidget中
        QFileInfo fileInfo = list_file.at(i);
        QString name2=fileInfo.fileName();
        QTreeWidgetItem* child = new QTreeWidgetItem(QStringList()<<name2);
        //child->setIcon(0, QIcon(":/file/image/link.ico"));
        child->setCheckState(1, Qt::Checked);
        root->addChild(child);
    }

    QFileInfoList file_list=dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);//获取当前所有目录

    for(int i = 0; i != folder_list.size(); i++)//自动递归添加各目录到上一级目录
    {
             QString namepath = folder_list.at(i).absoluteFilePath();//获取路径
             QFileInfo folderinfo= folder_list.at(i);
             QString name=folderinfo.fileName();//获取目录名
             QTreeWidgetItem* childroot = new QTreeWidgetItem(QStringList()<<name);
             //childroot->setIcon(0, QIcon(":/file/image/link.ico"));
             childroot->setCheckState(1, Qt::Checked);
             root->addChild(childroot);//将当前目录添加成path的子项
             QFileInfoList child_file_list = allfile(childroot,namepath);//进行递归
             file_list.append(child_file_list);
             file_list.append(name);
     }
    return file_list;
}

void MainWindow::showSelectedDocument(QTreeWidgetItem * item,int column){

    QString url = current_url;//保存最初始的url
    QTreeWidgetItem *parent = item->parent();

    int count=0;//以'/'分开的路径个数;
    QStringList name_list;

    //QTreeWidgetItem *item_current = ui->treeWidget->currentItem();//获取当前item

        if(NULL==parent) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
            return;
        else {//从叶子倒着获取路径
            QTreeWidgetItem *parent_current=parent;
            QTreeWidgetItem *item_current=item;
            while(NULL!=parent_current){
                name_list.append(item_current->text(0));
                //name_list[count]=item_current->text(0);//这样会报错
                count++;
                parent_current = item_current->parent();
                item_current=parent_current;
                qDebug()<< name_list[count-1];
            }
        }
        for(int i=count-2;i>=0;i--){//倒着得到正确的路径
            current_url+='/';
            current_url+=name_list[i];
        }
        int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)

        if (ui->codeTab->maybeSave()) {

            QString fileurl = current_url;
            //qDebug()<< fileName;
            //qDebug()<< col;
            //qDebug()<< (item->text(0));//只有item->text(0)才能获取当前item的文件名

            // 如果文件名不为空，则加载文件
            if (!fileurl.isEmpty()) {
                 ui->codeTab->openFile(fileurl);
            }
        }
        current_url=url;
}

/*
void MainWindow::splitter(){
    QSplitter * mainSplitter = new QSplitter(Qt::Horizontal,ui->centralWidget);
    mainSplitter->setHandleWidth(3);//设置分割条宽度
    mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式

    mainSplitter->addWidget(ui->treeWidget);
    mainSplitter->addWidget(ui->textEdit);
    mainSplitter->setOrientation(Qt::Vertical);//指定子窗件按加载顺序进行指定方向排列
    mainSplitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainSplitter->show();
}
*/



