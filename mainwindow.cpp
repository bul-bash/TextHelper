#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDirModel>
#include<QMessageBox>
#include<QFileDialog>

#include<QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();

    ui->textEdit->setFont(*font);

    directoriesModel = new QFileSystemModel(this);
    filesModel = new QFileSystemModel(this);

    directoriesModel->setFilter(QDir::NoDotAndDotDot |QDir::Dirs);
    directoriesModel->setRootPath("/home");
    ui->treeView->setModel(directoriesModel);
    ui->treeView->setRootIndex(directoriesModel->index("/home"));
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    filesModel->setFilter(QDir::Files);
    filesModel->setRootPath("");

    ui->listView->setModel(filesModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
     currentPath = directoriesModel->fileInfo(index).absoluteFilePath();
     ui->listView->setRootIndex(filesModel->setRootPath(currentPath));
     QDir dir;
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QModelIndexList templatelist = ui->listView->selectionModel()->selectedIndexes();

    currentFileName=templatelist[0].data().toString();
    openFile();
}

QString MainWindow::createFullName(){
    return currentPath+"/"+currentFileName;
}

void MainWindow::openFile(QString name){

    ui->textEdit->clear();

    QFile file(name);

    if(file.open(QIODevice::ReadWrite)){
        QTextStream stream(&file);
        stream.setCodec(codec);
        QString str;
        while(!stream.atEnd()){
            str = stream.readLine();
            ui->textEdit->append(str);
        }

        if(stream.status()!=QTextStream::Ok){
            //TODO exception
        }

        file.close();
    }
}
void MainWindow::openFile(){
     openFile(createFullName());
}

void MainWindow::setCodec(QTextCodec *codec){
    this->codec=codec;
}


void MainWindow::on_utf8_toggled(bool checked){
    if(checked){
        setCodec(QTextCodec::codecForName("UTF-8"));
        openFile();
    }
}

void MainWindow::on_cp1251_clicked(bool checked){
    if(checked){
        setCodec(QTextCodec::codecForName("cp1251"));
        openFile();
    }
}

void MainWindow::setFont(){
    font->setBold(ui->bold->isChecked());
    font->setItalic(ui->italic->isChecked());
    font->setUnderline(ui->underline->isChecked());

    QColor color(ui->colorComboBox->currentText());

    ui->textEdit->setTextColor(color);
    ui->textEdit->setFont(*font);

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About TextHelper", "Simple text helper\nDesigned by Roman Frontov");
}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_resetButton_clicked()
{
    ui->bold->setChecked(false);
    ui->italic->setChecked(false);
    ui->underline->setChecked(false);

    ui->utf8->setChecked(true);

    ui->colorComboBox->setCurrentIndex(0);
    setFont();

}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,
            "Select file destination", "", "Text (*.txt);;All Files (*)");

    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        stream.setCodec(codec);

        stream<< (ui->textEdit->toPlainText());
        if(stream.status()!=QTextStream::Ok){
            //TODO exception
        }
        file.close();

    }
}

void MainWindow::on_colorComboBox_currentIndexChanged(const QString &arg1)
{
    setFont();
}

void MainWindow::on_bold_clicked()
{
    setFont();
}

void MainWindow::on_italic_clicked()
{
    setFont();
}

void MainWindow::on_underline_clicked()
{
    setFont();
}
