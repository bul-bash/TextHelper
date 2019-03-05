#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDirModel>
#include<QFileSystemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
//    QDirModel *model = new QDirModel();

    QFileSystemModel *fileModel = new QFileSystemModel();
    fileModel->setRootPath(QDir::currentPath());
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Dirs);
    ui->treeView->setModel(fileModel);

    ui->treeView->setRootIndex(fileModel->index("/home"));
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

//    ui->treeView->setRootIndex(model->index("/"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
