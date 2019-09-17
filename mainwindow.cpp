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
#include<QLineEdit>
#include<QDialog>
#include<QPushButton>
#include<QtGui>
#include<QCheckBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString curFile=ui->codeTab->currentFile();
    setWindowTitle(curFile);

    this->resize(QSize(800,500));//修改初始化窗口大小

    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSelectedDocument(QTreeWidgetItem*,int)));

<<<<<<< HEAD
<<<<<<< HEAD
    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSelectedDocument(QTreeWidgetItem*,int)));//连接目录树的信号和槽

    QT
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile(){
    if(maybeSave()){
        isUntitled=true;
        curFile=tr("未命名.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->treeWidget->clear();//清空
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave(){
    //如果文件被修改过
    if(ui->textEdit->document()->isModified()){
       //警告框
       QMessageBox box;
       box.setWindowTitle(tr("警告"));
       box.setIcon(QMessageBox::Warning);
       box.setText(curFile+tr("尚未保存，是否保存？"));

       QPushButton* yesbtn=box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
       box.addButton(tr("否(&N)"),QMessageBox::NoRole);
       QPushButton* cancelbtn=box.addButton(tr("取消(&C)"),QMessageBox::RejectRole);

       box.exec();
       if(box.clickedButton()==yesbtn){
           return save();
       }else if (box.clickedButton()==cancelbtn) {
           return false;
       }
    }
    return true;
}


bool MainWindow::save(){
||||||| merged common ancestors
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile(){
    if(maybeSave()){
        isUntitled=true;
        curFile=tr("未命名.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->treeWidget->clear();//清空
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave(){
    //如果文件被修改过
    if(ui->textEdit->document()->isModified()){
       //警告框
       QMessageBox box;
       box.setWindowTitle(tr("警告"));
       box.setIcon(QMessageBox::Warning);
       box.setText(curFile+tr("尚未保存，是否保存？"));

       QPushButton* yesbtn=box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
       box.addButton(tr("否(&N)"),QMessageBox::NoRole);
       QPushButton* cancelbtn=box.addButton(tr("取消(&C)"),QMessageBox::RejectRole);

       box.exec();
       if(box.clickedButton()==yesbtn){
           return save();
       }else if (box.clickedButton()==cancelbtn) {
           return false;
       }
    }
    return true;
}


bool MainWindow::save(){
=======
||||||| merged common ancestors
<<<<<<<<< Temporary merge branch 1
    connect(ui->treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(showSelectedDocument(QTreeWidgetItem*,int)));//连接目录树的信号和槽

    QT
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile(){
    if(maybeSave()){
        isUntitled=true;
        curFile=tr("未命名.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->treeWidget->clear();//清空
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave(){
    //如果文件被修改过
    if(ui->textEdit->document()->isModified()){
       //警告框
       QMessageBox box;
       box.setWindowTitle(tr("警告"));
       box.setIcon(QMessageBox::Warning);
       box.setText(curFile+tr("尚未保存，是否保存？"));

       QPushButton* yesbtn=box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
       box.addButton(tr("否(&N)"),QMessageBox::NoRole);
       QPushButton* cancelbtn=box.addButton(tr("取消(&C)"),QMessageBox::RejectRole);

       box.exec();
       if(box.clickedButton()==yesbtn){
           return save();
       }else if (box.clickedButton()==cancelbtn) {
           return false;
       }
    }
    return true;
}


bool MainWindow::save(){
||||||||| merged common ancestors
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFile(){
    if(maybeSave()){
        isUntitled=true;
        curFile=tr("未命名.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->treeWidget->clear();//清空
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave(){
    //如果文件被修改过
    if(ui->textEdit->document()->isModified()){
       //警告框
       QMessageBox box;
       box.setWindowTitle(tr("警告"));
       box.setIcon(QMessageBox::Warning);
       box.setText(curFile+tr("尚未保存，是否保存？"));

       QPushButton* yesbtn=box.addButton(tr("是(&Y)"),QMessageBox::YesRole);
       box.addButton(tr("否(&N)"),QMessageBox::NoRole);
       QPushButton* cancelbtn=box.addButton(tr("取消(&C)"),QMessageBox::RejectRole);

       box.exec();
       if(box.clickedButton()==yesbtn){
           return save();
       }else if (box.clickedButton()==cancelbtn) {
           return false;
       }
    }
    return true;
}


bool MainWindow::save(){
=========
=======
>>>>>>> 253e1f610b35c168bf1f2edfa4378d4d08385c4c
    //my_tab->setShape(QTabBar::TriangularNorth);//设置显示样式
    //splitter();
    ui->splitter->setStretchFactor(0, 1);//初始左边占1/6
    ui->splitter->setStretchFactor(1, 5);//初始右边占5/6


    //查找功能
    findDlg = new QDialog(this);//创建一个对话框
    findDlg->setWindowTitle(tr("查找"));
    findLineEdit = new QLineEdit(findDlg);
    QPushButton *btn= new QPushButton(tr("查找下一个"), findDlg);

    FindBack_CheckBox=new QCheckBox(tr("从后往前查找"));//从后往前查找
    FindWhole_CheckBox=new QCheckBox(tr("全词匹配"));//全词匹配
    FindCase_CheckBox=new QCheckBox(tr("区分大小写"));//区分大小写
/*
    QHBoxLayout *layout_0= new QHBoxLayout(findDlg);//将check框放在一起，水平排列
    layout_0->addWidget(FindBack_CheckBox);
    layout_0->addWidget(FindWhole_CheckBox);
    layout_0->addWidget(FindCase_CheckBox);
    */
<<<<<<< HEAD
>>>>>>> upstream/master
||||||| merged common ancestors
>>>>>>>>> Temporary merge branch 2
=======
>>>>>>> 253e1f610b35c168bf1f2edfa4378d4d08385c4c

    QVBoxLayout *layout_2= new QVBoxLayout(findDlg);//将一个行编辑器和一个按钮放到上面，并使用布局管理器进行布局。
    layout_2->addWidget(findLineEdit);
    layout_2->addWidget(FindBack_CheckBox);
    layout_2->addWidget(FindWhole_CheckBox);
    layout_2->addWidget(FindCase_CheckBox);
    layout_2->addWidget(btn);
    findDlg->setLayout(layout_2);

    connect(btn, SIGNAL(clicked()), this, SLOT(showFindText()));//将按钮的单击信号关联到自定义的显示查找到的文本槽上

    document=ui->codeTab->currentEditor()->document();//将文本编辑区转为QTextDocument对象
    row_num=document->lineCount();//获取行数
    row=0;
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

        if(parent==NULL) //注意：最顶端项是没有父节点的，双击这些项时注意(陷阱)
            return;
        else {//从叶子倒着获取路径
            QTreeWidgetItem *parent_current=parent;
            QTreeWidgetItem *item_current=item;
            while(parent_current!=NULL){
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
        //int col = parent->indexOfChild(item); //item在父项中的节点行号(从0开始)

        if (ui->codeTab->maybeSave()) {

            QString fileurl = current_url;

            // 如果文件名不为空，则加载文件
            if (!fileurl.isEmpty()) {
                 ui->codeTab->openFile(fileurl);
            }
        }
        current_url=url;
}

void MainWindow::showFindText()//在当前打开文本中查找
{
    QString str = findLineEdit->text();//获取行编辑器中要查找的字符串

    if(FindBack_CheckBox->isChecked()){
        if(FindWhole_CheckBox->isChecked()){
            if(FindCase_CheckBox->isChecked()){
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively|QTextDocument::FindWholeWords))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                   QMessageBox::warning(this, tr("查找"),
                            tr("找不到%1").arg(str));
                }
            }
            else{
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindBackward|QTextDocument::FindWholeWords))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                   QMessageBox::warning(this, tr("查找"),
                            tr("找不到%1").arg(str));
                }
            }
        }
        else if(FindCase_CheckBox->isChecked()){
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindBackward|QTextDocument::FindCaseSensitively))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
            else{
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindBackward))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                   QMessageBox::warning(this, tr("查找"),
                            tr("找不到%1").arg(str));
                }
            }

    }
    else if(FindWhole_CheckBox->isChecked()){
            if(FindCase_CheckBox->isChecked()){
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindCaseSensitively|QTextDocument::FindWholeWords))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
            else{
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindWholeWords))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
        }
        else if(FindCase_CheckBox->isChecked()){
                if (!ui->codeTab->currentEditor()->find(str,QTextDocument::FindCaseSensitively))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
            else{
                if (!ui->codeTab->currentEditor()->find(str))//用来指定查找的方式。可以使用“|”符号来一起使用
                {//如果不指定该参数，默认的是向前查找、不区分大小写、包含该字符串的词也可以查找到。
                    QMessageBox::warning(this, tr("查找"),
                        tr("找不到%1").arg(str));
                }
            }
}

void MainWindow::on_action_Find_triggered()//显示查找框
{
   findDlg->show();
   findDlg->setMinimumSize(320,235);
}

void MainWindow::on_action_visible_triggered()
{
    int j=0;
    for(int i=0;i<row_num;i++){//显示每一行
        //qDebug()<<i;
        QTextBlock oTextBlock = document->findBlockByNumber(i);
        oTextBlock.setVisible(true);
        for(;j<size;){//找到行注释和代码同时存在的一行，将行注释添加回去
            qDebug()<<zhushi_hang[j];
            if(i==zhushi_hang[j]){
                QString str="";
                str=daima[j]+zhushi[j];
                //将光标跳到指定行
                QTextCursor tc = ui->codeTab->currentEditor()->textCursor();
                int toPost =document->findBlockByNumber(i).position();
                tc.setPosition(toPost,QTextCursor::MoveAnchor);
                ui->codeTab->currentEditor()->setTextCursor(tc);
                //删除光标所在行
                tc.select(QTextCursor::BlockUnderCursor);
                tc.removeSelectedText();
                ui->codeTab->currentEditor()->insertPlainText("\n"+str);

                text.append(str);
                j++;
                break;
            }
            else{
                text.append(document->findBlockByLineNumber(i).text());//存到list中,用于之后的重写
                break;
            }
        }
    }

    //重写文件
    QString file= text.join("\n");//将QStringlist转化为QString

<<<<<<< HEAD
<<<<<<< HEAD
//创建新的Tab（用于打开文件）
void MainWindow::newTab(const QString& fileName, QFile& file)
{
    int index = 0;
    NotePad *notePad = findNewFile(index);
    if(notePad == NULL)
    {
        notePad = new NotePad(config);
        index = tabWidget->addTab(notePad, QFileInfo(fileName).fileName());
        addToNotePadMap(index, notePad);
    }
    else
    {
        notePad->SetNewFile(false);
        tabWidget->setTabText(index, QFileInfo(fileName).fileName());
        openedFiles.removeAt(index);
        newNumber--;
    }
    openedFiles << fileName;
    QByteArray data = file.readAll();
    notePad->setPlainText(QString::fromLocal8Bit(data));
    tabWidget->setCurrentIndex(index);
    setWindowTitle(QFileInfo(fileName).fileName());
}

//关闭文件（指定文件）
void MainWindow::fileClose(int index)
{
    if(!shouldCloseFile())
    {
        return;
    }
||||||| merged common ancestors
=======
||||||| merged common ancestors
<<<<<<<<< Temporary merge branch 1
//创建新的Tab（用于打开文件）
void MainWindow::newTab(const QString& fileName, QFile& file)
{
    int index = 0;
    NotePad *notePad = findNewFile(index);
    if(notePad == NULL)
    {
        notePad = new NotePad(config);
        index = tabWidget->addTab(notePad, QFileInfo(fileName).fileName());
        addToNotePadMap(index, notePad);
    }
    else
    {
        notePad->SetNewFile(false);
        tabWidget->setTabText(index, QFileInfo(fileName).fileName());
        openedFiles.removeAt(index);
        newNumber--;
    }
    openedFiles << fileName;
    QByteArray data = file.readAll();
    notePad->setPlainText(QString::fromLocal8Bit(data));
    tabWidget->setCurrentIndex(index);
    setWindowTitle(QFileInfo(fileName).fileName());
}

//关闭文件（指定文件）
void MainWindow::fileClose(int index)
{
    if(!shouldCloseFile())
    {
        return;
    }
||||||||| merged common ancestors
=========
=======
>>>>>>> 253e1f610b35c168bf1f2edfa4378d4d08385c4c
    //清空注释list和对应的int数组
    zhushi.clear();
    size=0;
<<<<<<< HEAD
>>>>>>> upstream/master
||||||| merged common ancestors
>>>>>>>>> Temporary merge branch 2
=======
>>>>>>> 253e1f610b35c168bf1f2edfa4378d4d08385c4c

<<<<<<< HEAD
<<<<<<< HEAD
    if (maybeSave(index))
    {
        if (openedFiles.count() == 1)
        {
            openedFiles.clear();
            QString fileName = "New 1";
            openedFiles << fileName;
            mapNotePads[0]->setPlainText("");
            mapNotePads[0]->SetNewFile(true);
            tabWidget->setTabText(0, fileName);
            setWindowTitle(fileName);
            newNumber = 1;
        }
        else
        {
            openedFiles.removeAt(index);
            tabWidget->removeTab(index);
            removeFromNotePadMap(index);
            newNumber--;
        }
    }
}
||||||| merged common ancestors
=======
||||||| merged common ancestors
<<<<<<<<< Temporary merge branch 1
    if (maybeSave(index))
    {
        if (openedFiles.count() == 1)
        {
            openedFiles.clear();
            QString fileName = "New 1";
            openedFiles << fileName;
            mapNotePads[0]->setPlainText("");
            mapNotePads[0]->SetNewFile(true);
            tabWidget->setTabText(0, fileName);
            setWindowTitle(fileName);
            newNumber = 1;
        }
        else
        {
            openedFiles.removeAt(index);
            tabWidget->removeTab(index);
            removeFromNotePadMap(index);
            newNumber--;
        }
    }
}
||||||||| merged common ancestors
=========
=======
>>>>>>> 253e1f610b35c168bf1f2edfa4378d4d08385c4c
    /*调整与更新！！！！超重要！！！*/
    document->adjustSize();
    ui->codeTab->currentEditor()->update();
}

void MainWindow::on_action_unvisible_triggered()
{
    document = ui->codeTab->currentEditor()->document();//将文本编辑区转为QTextDocument对象
    row_num=document->lineCount();//获取行数
    qDebug()<<row_num;

    for(int i=0;i<row_num;i++){
        QString str = document->findBlockByLineNumber(i).text(); //获取第i行的内容

        if(str.contains("/*")){//如果包含“/*”(段落注释)字符串的话
            int j=i;
            for(;j<row_num;j++){
                QString str_j = document->findBlockByLineNumber(j).text(); //获取第j行的内容
                if(str_j.contains("*/")){
                    break;
                }
            }
            i=j;
            continue;
        }
        QString cur="//";
        if(str.contains(cur)){//如果包含“//”字符串的话
            QString str_2=str.trimmed();//去掉字符串首尾空格
            if(str_2.startsWith(cur)){//整行都是注释,直接隐藏掉这一行
                continue;
            }
            else {//把注释删掉并存起来
                int j=str.indexOf(cur);//返回‘//’在str中的索引下标
                QString ss=str.mid(0,j);//取代码部分
                daima.append(ss);
                QString s=str.mid(j);//取注释
                zhushi.append(s);
                zhushi_hang[size]=i;
                size++;
                //需要再把这一行更改后的结果重新写到textedit吗？？？？!!!!!需要!!!!

                //将光标跳到指定行
                QTextCursor tc = ui->codeTab->currentEditor()->textCursor();
                int toPost =document->findBlockByNumber(i).position();
                tc.setPosition(toPost,QTextCursor::MoveAnchor);
                ui->codeTab->currentEditor()->setTextCursor(tc);
                //删除光标所在行
                tc.select(QTextCursor::BlockUnderCursor);
                tc.removeSelectedText();
                ui->codeTab->currentEditor()->insertPlainText("\n"+ss);
            }
        }
    }
    for(int i=0;i<row_num;i++){
        QString str = document->findBlockByLineNumber(i).text(); //获取第i行的内容
        if(str.contains("/*")){//如果包含“/*”(段落注释)字符串的话
            int j=i;
            for(;j<row_num;j++){
                QString str_j = document->findBlockByLineNumber(j).text(); //获取第i行的内容
                if(str_j.contains("*/")){
                    break;
                }
            }
            for(int m=i;m<=j;m++){//隐掉段落注释
                QTextBlock oTextBlock = document->findBlockByNumber(m);
                oTextBlock.setVisible(false);
            }
            i=j;
            continue;
        }
        if(str.contains("//")){//如果包含“//”字符串的话
            QString str_2=str.trimmed();//去掉字符串首尾空格
            if(str_2.startsWith("//")){//整行都是注释,直接隐藏掉这一行
                QTextBlock oTextBlock = document->findBlockByNumber(i);
                oTextBlock.setVisible(false);
            }
        }
    }
    /*调整与更新！！！！超重要！！！*/
    document->adjustSize();
    ui->codeTab->currentEditor()->update();
}


/*
void MainWindow::splitter(){
    QSplitter * mainSplitter = new QSplitter(Qt::Horizontal,ui->centralWidget);
    mainSplitter->setHandleWidth(3);//设置分割条宽度
    mainSplitter->setStyleSheet("QSplitter::handle { background-color: black }"); //设置分界线的样式

    mainSplitter->addWidget(ui->treeWidget);
    mainSplitter->addWidget(ui->codeTab->currentEditor());
    mainSplitter->setOrientation(Qt::Vertical);//指定子窗件按加载顺序进行指定方向排列
    mainSplitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainSplitter->show();
}
*/
<<<<<<< HEAD
>>>>>>> upstream/master
||||||| merged common ancestors
>>>>>>>>> Temporary merge branch 2
=======
>>>>>>> 253e1f610b35c168bf1f2edfa4378d4d08385c4c
