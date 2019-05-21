#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    em3()
{
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);
    ui->nextStepButton->setEnabled(false);
    ui->showButton->setEnabled(false);
    ui->enterButton->setEnabled(false);
    ui->registersListWidget->setEnabled(false);
    ui->inputTextEdit->setEnabled(false);
    ui->outputTextEdit->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    QString text = ui->programTextEdit->toPlainText();
    QVector<QString> cells = Parser::parseToMemory(text);
    Memory memory(cells);
    em3.setMemory(memory);

    ui->saveButton->setEnabled(true);
    ui->nextStepButton->setEnabled(true);
    ui->showButton->setEnabled(true);
}

void MainWindow::on_saveButton_clicked()
{

}

void MainWindow::on_loadButton_clicked()
{

}

void MainWindow::on_enterButton_clicked()
{

}

void MainWindow::on_showButton_clicked()
{
    QVector<QString> cells = em3.getMemory()
                             .getMemoryCells();

    MemoryDialog* dialog = new MemoryDialog(cells, this);
    dialog->setModal(true);
    dialog->show();

}
