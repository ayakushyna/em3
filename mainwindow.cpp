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

    setProgramTableWidget(ui->programTableWidget);
    setRegistersListWidget(ui->registersListWidget);

    ui->inputTextEdit->setEnabled(false);
    ui->outputTextEdit->setEnabled(false);
}

void MainWindow::setProgramTableWidget(QTableWidget* table)
{
    Memory memory = em3.getMemory();
    int count = memory.getSize();
    table->setRowCount(count);

    for(int i = 0; i < count; i++)
    {
        TableItem* item = new TableItem(memory[i]);
        table->setCellWidget(i, 0, item);
    }

}

void MainWindow::setRegistersListWidget(QListWidget* list){}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    QTableWidget* table = ui->programTableWidget;
    QVector<QString> cells;

    for(int i = 0; i < table->rowCount(); i++)
    {
        QString str = dynamic_cast<QLineEdit*>(table->cellWidget(i,0))->text();
        str = Parser::parseToMemory(str);
        cells.append(str);
    }
    //QString text = ui->programTextEdit->toPlainText();
    //str = Parser::parseToMemory(str);
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

