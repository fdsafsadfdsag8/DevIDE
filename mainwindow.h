#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void newFile();				//新建
    bool maybeSave();			//判断是否需要保存
    bool save();				//保存操作
    bool saveAs();				//另存为操作
    bool saveFile(const QString& fileName);//保存文件
    bool loadFile(const QString &fileName); // 加载文件

private slots:
    void on_action_New_triggered();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Close_triggered();

    void on_action_Run_triggered();

    void on_action_Compile_triggered();

private:
    Ui::MainWindow *ui;
    //为真：未保存过；为假：保存过
    bool isUntitled;
    //保存当前文件的路径
    QString curFile;
};

#endif // MAINWINDOW_H
