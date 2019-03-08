#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QFileSystemModel>

#include<QTextCodec>
#include<QFont>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

    void on_utf8_toggled(bool checked);

    void on_cp1251_clicked(bool checked);

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

    void on_resetButton_clicked();

    void on_actionSave_As_triggered();

    void on_colorComboBox_currentIndexChanged(const QString &arg1);

    void on_bold_clicked();

    void on_italic_clicked();

    void on_underline_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel * directoriesModel;
    QFileSystemModel * filesModel;

    QString currentPath;
    QString currentFileName;

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QFont * font = new QFont("Times New Roman", 12);

    void setCodec(QTextCodec * codec);

    void setFont();

    QString createFullName();

    void openFile(QString name);
    void openFile();
};

#endif // MAINWINDOW_H
