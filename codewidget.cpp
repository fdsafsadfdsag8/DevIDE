#include "codewidget.h"

CodeWidget::CodeWidget(QWidget* parent)
    :QWidget (parent)
{
    //创建布局 vLayout
    vLayout=new QVBoxLayout(this);
    vLayout->setContentsMargins(9,9,9,9);
    vLayout->setSpacing(5);

    //创建对应编辑器 codeEditor
    codeEditor=new CodeEditor(this);

    //设置布局
    vLayout->addWidget(codeEditor);
    //初始未命名
    titled=false;

    //设置自动补全模板
    // 初始化智能提示
    completer = new QCompleter(this);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    codeEditor->setCompleter(completer);
}

bool CodeWidget::isUntitled(){
    return !titled;
}

void CodeWidget::beTitled(){
    titled=true;
}
