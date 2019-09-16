#ifndef CODETAB_H
#define CODETAB_H

#include<QTabWidget>
#include"codeeditor.h"
#include"codewidget.h"


class CodeTab : public QTabWidget
{
public:
    CodeTab(QWidget* parent=nullptr);

    //实现文件的打开、新建、保存
    bool openFile(QString& path);
    CodeWidget* newFile();
    bool saveFile(const QString& fileName);
    bool saveAs();
    bool save();
    bool isCurTabUntitled();
    bool maybeSave();

    QString& currentFile();
    CodeEditor* currentEditor();
    CodeWidget* currentTab();


};

#endif // CODETAB_H
