#include "codetab.h"
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
CodeTab::CodeTab(QWidget* parent)
    :QTabWidget(parent)
{
    newFile();
}
CodeEditor* CodeTab::currentEditor(){
    CodeWidget* tab=(CodeWidget*)this->currentWidget();
    return tab->codeEditor;
}
//fileEditing 改变情形：
//打开文件、保存文件并改变名称时，另新建时要设为空("")
QString& CodeTab::currentFile(){
    CodeWidget* tab=(CodeWidget*)this->currentWidget();
    return tab->fileEditing;
}
//新建一个空文件，加入标签并切换至该标签
CodeWidget* CodeTab::newFile(){
    CodeWidget* w=new CodeWidget(this);
    w->fileEditing="";
    addTab(w,"Untitled");
    //切换页面至新标签
    this->setCurrentWidget(w);
    return w;
}
//打开文件，如果已开直接切换标签，否则新建对应标签并切换
bool CodeTab::openFile(QString& fileName){
    //如果该文件已经打开，则直接切换到对应tab
    for(int i=0;i<this->count();i++){
        CodeWidget* tab=(CodeWidget*)this->widget(i);
        if(tab->fileEditing==fileName){
            this->setCurrentIndex(i);
            return true;
        }
    }

    //如果该文件未打开，则打开
    //打开失败返回 false
    QFile file(fileName); // 新建QFile对象
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("多文档编辑器"),
                              tr("无法读取文件 %1:\n%2.")
                              .arg(fileName).arg(file.errorString()));
        return false; // 只读方式打开文件，出错则提示，并返回false
    }

    //打开文件成功后，将文件内容输送到文本框界面
    QTextStream in(&file); // 新建文本流对象


    // 读取文件的全部文本内容，并添加到编辑器中
    //如果当前tab对应页面为新建页面且未修改，则直接刷新内容到该页面上
    //否则新建文件，刷新到此页面上
    CodeWidget* ctab=(CodeWidget*)this->currentWidget();
    bool currentPageNew=ctab->fileEditing==""&&ctab->codeEditor->toPlainText().length()==0;
    if(!currentPageNew)
        ctab=newFile();
    //刷新时更新2个内容：文本框显示内容，对应文件名
    ctab->codeEditor->setPlainText(in.readAll());
    ctab->fileEditing=fileName;
    ctab->beTitled();
    this->setCurrentWidget(ctab);

    QString name=QFileInfo(fileName).fileName();
    this->setTabText(this->currentIndex(),name);


    return true;
}
CodeWidget* CodeTab::currentTab(){
    return (CodeWidget*)this->currentWidget();
}
bool CodeTab::isCurTabUntitled(){
    CodeWidget* curTab=(CodeWidget*)this->currentWidget();
    return curTab->isUntitled();
}
bool CodeTab::save(){
    if(isCurTabUntitled()){
        return saveAs();
    }else{
        return saveFile(currentFile());
    }
}


bool CodeTab::saveAs(){
    QString filename=QFileDialog::getSaveFileName(this,tr("另存为"),currentFile());
    if(filename.isEmpty()) return false;
    return saveFile(filename);
}

bool CodeTab::saveFile(const QString &fileName){
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,tr("多文档编辑器"),tr("无法写入文件 %1: /n %2").arg(fileName).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);

    out<<currentEditor()->toPlainText();

    //设置已命名状况
    currentTab()->beTitled();

//    loadtree(fileName);//保存之后加载目录树
    QString name=QFileInfo(fileName).fileName();
    this->setTabText(this->currentIndex(),name);

    return true;
}

bool CodeTab::maybeSave(){
    //如果文件被修改过
    if(currentEditor()->document()->isModified()){
       //警告框
       QMessageBox box;
       box.setWindowTitle(tr("警告"));
       box.setIcon(QMessageBox::Warning);
       box.setText(currentFile()+tr("尚未保存，是否保存？"));

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

