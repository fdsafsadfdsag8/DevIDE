#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QPushButton>
#include<QFileDialog>
#include<QTextStream>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isUntitled=true;
    curFile=tr("未命名.txt");
    setWindowTitle(curFile);
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

    if(isUntitled){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}


bool MainWindow::saveAs(){
    QString filename=QFileDialog::getSaveFileName(this,tr("另存为"),curFile);
    if(filename.isEmpty()) return false;
    return saveFile(filename);
}

bool MainWindow::saveFile(const QString &fileName){
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,tr("多文档编辑器"),tr("无法写入文件 %1: /n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<ui->textEdit->toPlainText();

    QApplication::restoreOverrideCursor();
    isUntitled=false;

    curFile=QFileInfo(fileName).canonicalFilePath();
    setWindowTitle(curFile);
    return true;
}

void MainWindow::on_action_New_triggered()
{
    newFile();
}


void MainWindow::on_action_Save_triggered()
{
    save();
}

void MainWindow::on_action_SaveAs_triggered()
{
    saveAs();
}

bool MainWindow::loadFile(const QString &fileName)
{
   QFile file(fileName); // 新建QFile对象
   if (!file.open(QFile::ReadOnly | QFile::Text)) {
       QMessageBox::warning(this, tr("多文档编辑器"),
                             tr("无法读取文件 %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
       return false; // 只读方式打开文件，出错则提示，并返回false
   }
   QTextStream in(&file); // 新建文本流对象
   QApplication::setOverrideCursor(Qt::WaitCursor);
   // 读取文件的全部文本内容，并添加到编辑器中
   ui->textEdit->setPlainText(in.readAll());
   QApplication::restoreOverrideCursor();

   // 设置当前文件
   curFile = QFileInfo(fileName).canonicalFilePath();
   setWindowTitle(curFile);
   qDebug()<<"The file name is: "<<curFile<<endl;
   return true;
}


void MainWindow::on_action_Open_triggered()
{
    if (maybeSave()) {

        QString fileName = QFileDialog::getOpenFileName(this);

        // 如果文件名不为空，则加载文件
        if (!fileName.isEmpty()) {
             loadFile(fileName);
             ui->textEdit->setVisible(true);
        }
    }
}

void MainWindow::on_action_Close_triggered()
{
    if (maybeSave()) {
        ui->textEdit->setVisible(false);
    }
}

void MainWindow::on_action_Run_triggered()
{
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

    qDebug()<<"the run command is: "<<cmd<<endl;

//    system("cd C:/Users/wuyan/Desktop && g++ -g first.cpp -o first.exe && first.exe");
    system(cmd.toStdString().c_str());
    qDebug()<<"The end of run command"<<endl;
}

void MainWindow::on_action_Compile_triggered()
{
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
        throw("FILE_SUFFIX_ERROR");
    }

    QString enterCmd="cd /d "+dirName;
    QString compileCmd=prefix+" -g "+fullName+" -o "+baseName+".exe";
    QString cmd=enterCmd+" && "+compileCmd;
    qDebug()<<"the compiling command is: "<<cmd<<endl;

    system(cmd.toStdString().c_str());
    qDebug()<<"The end"<<endl;
}
