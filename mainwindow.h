#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QFileInfoList>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QString current_url;//当前打开文件夹路径

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void newFile();				//新建
    bool maybeSave();			//判断是否需要保存
    bool save();				//保存操作
    bool saveAs();				//另存为操作
    bool saveFile(const QString& fileName);//保存文件
    bool loadFile(const QString &fileName); // 加载文件

<<<<<<< HEAD
    QFileInfoList allfile(QTreeWidgetItem *root,QString path);//遍历目录
    void loadtree(const QString &fileName);//显示目录树

signals:
    void itemClicked ( QTreeWidgetItem * item, int column );//发射鼠标点击信号

||||||| merged common ancestors
=======
    QFileInfoList allfile(QTreeWidgetItem *root,QString path);//遍历目录
    void loadtree(const QString &fileName);//显示目录树

>>>>>>> upstream/dev
private slots:
    void on_action_New_triggered();

    void on_action_Save_triggered();

    void on_action_SaveAs_triggered();

    void on_action_Close_triggered();

    void on_action_Run_triggered();

    void on_action_Compile_triggered();

<<<<<<< HEAD
    void on_action_open_file_triggered();//打开单个文件

    void on_action_open_files_triggered();//打开文件夹

    void showSelectedDocument(QTreeWidgetItem * item, int column); //双击目录树中的文件显示文件内容事件


||||||| merged common ancestors
=======
    void on_action_open_file_triggered();//打开单个文件

    void on_action_open_files_triggered();//打开文件夹

    void treewidgetDoubleClick(const QTreeWidgetItem * item,int col);//双击目录树中的文件显示文件内容


>>>>>>> upstream/dev
private:
    Ui::MainWindow *ui;
    //为真：未保存过；为假：保存过
    bool isUntitled;
    //保存当前文件的路径
    QString curFile;
};

#endif // MAINWINDOW_H
