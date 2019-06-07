#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    digitsOnly(true), settings(), parser(settings, digitsOnly), em3(settings)
{
    ui->setupUi(this);

    ui->digitsRadioButton->setChecked(true);

    ui->saveButton->setEnabled(false);
    ui->showButton->setEnabled(false);
    ui->enterButton->setEnabled(false);

    initProgramTableWidget(ui->programTableWidget);
    setRegistersListWidget(ui->registersListWidget);

    ui->inputTextEdit->setEnabled(false);
    ui->outputTextEdit->setEnabled(false);
}

void MainWindow::setRow(QTableWidget* table, const QString& str, int i)
{
    QString cell = parser.parseFromMemory(str);
    bool command = parser.getCurrCommand(cell);
    TableItem* item = new TableItem(cell, settings, parser, digitsOnly, command, table);
    table->setCellWidget(i, 0, item);
}

void MainWindow::initProgramTableWidget(QTableWidget* table)
{
    Memory memory = em3.getMemory();
    int count = memory.getSize();
    table->setRowCount(count);

    for(int i = 0; i < count; i++)
        setRow(table,memory[i],i);
}

void MainWindow::setProgramTableWidget(QTableWidget* table)
{
    int count = table->rowCount();

    for(int i = 0; i < table->rowCount(); i++)
    {
        QString str = dynamic_cast<QLineEdit*>(table->cellWidget(i,0))->text();
        str.replace(" ", "");
        setRow(table,str,i);
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
        str = parser.parseToMemory(str);
        cells.append(str);
    }

    Memory memory(cells);
    em3.setMemory(memory);
    em3.exec();

    initProgramTableWidget(ui->programTableWidget);
    ui->saveButton->setEnabled(true);
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


void MainWindow::on_digitsRadioButton_clicked(bool checked)
{
    digitsOnly = checked;
    parser.setDigitsOnly(digitsOnly);
    setProgramTableWidget(ui->programTableWidget);
}
