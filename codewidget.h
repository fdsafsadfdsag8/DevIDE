#ifndef CODEWIDGET_H
#define CODEWIDGET_H

#include <QWidget>
#include"codeeditor.h"
#include<QVBoxLayout>

class CodeWidget: public QWidget
{
    Q_OBJECT
public:
    explicit CodeWidget(QWidget* parent=nullptr);

    CodeEditor* codeEditor;
    QVBoxLayout* vLayout;
    QString fileEditing;
    bool isUntitled();
    //从未命名到命名了的是一个单向过程
    void beTitled();
private:
    bool titled;
};

#endif // CODEWIDGET_H
