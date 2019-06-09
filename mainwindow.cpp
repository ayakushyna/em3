#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    digitsOnly(true),
    settings(),
    parser(settings, digitsOnly),
    em3(settings)
{
    ui->setupUi(this);

    connect(ui->actionOpen,SIGNAL(triggered()),this, SLOT(loadApp()));
    connect(ui->actionSave,SIGNAL(triggered()),this, SLOT(saveApp()));

    ui->digitsRadioButton->setChecked(true);

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
    bool command = parser.isCommand(cell);
    TableItem* item = new TableItem(cell, settings, parser, digitsOnly, command, table);
    table->setCellWidget(i, 0, item);
}

void MainWindow::initProgramTableWidget(QTableWidget* table)
{
    Memory memory = em3.getMemory();
    int count = memory.getSize();
    table->setRowCount(count);

    QStringList addresses;

    for(int i = 0; i < count; i++)
    {
        addresses << QString::number(i);;
        setRow(table,memory[i],i);
    }

    table->setVerticalHeaderLabels(addresses);
}

void MainWindow::setProgramTableWidget(QTableWidget* table)
{
    int count = table->rowCount();

    for(int i = 0; i < count; i++)
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
    uint64_t size = memory.getSize();

    em3.init();
    for(em3.RA = 0; em3.isStopped() != true && em3.RA < size; em3.RA++)
    {
        bool command = parser.isCommand(em3.getMemory()[em3.RA]);
        if(command)
        {
            em3.exec(em3.RA);

            if(em3.getInput())
            {
                ui->inputTextEdit->setEnabled(true);
                ui->enterButton->setEnabled(true);

                QEventLoop loop;
                connect(ui->enterButton, &QPushButton::clicked,
                        [&]()
                {
                    loop.quit();
                    on_enterButton_clicked();
                });
                loop.exec();
                em3.exec(em3.RA);

                ui->inputTextEdit->clear();
                ui->inputTextEdit->setEnabled(false);
                ui->enterButton->setEnabled(false);
            }

            else if(em3.getOutput())
            {
                ui->outputTextEdit->setPlainText(em3.getStrList().join('\n'));
                em3.setOutput(false);
                em3.setStrList(QStringList());
            }
        }
    }

    initProgramTableWidget(ui->programTableWidget);
    ui->showButton->setEnabled(true);
}

void MainWindow::saveApp()
{
    const QString ext = ".json" ;
    QString file = QFileDialog::getSaveFileName(this, "Save memory into file", ".//", "*"+ext).trimmed();
    if (file.right(ext.length()).toLower() != ext)
    {
        file += ext;
    }

    QFile saveFile(file);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }

    QJsonObject appObject;
    write(appObject);
    QJsonDocument saveDoc(appObject);
    saveFile.write(saveDoc.toJson(QJsonDocument::Indented));

}

void MainWindow::write(QJsonObject &json) const{
    QJsonObject memoryObject;
    em3.write(memoryObject);
    json["memory"] = memoryObject;
}

void MainWindow::loadApp()
{
    QString file = QFileDialog::getOpenFileName(this, "Open json files", ".//", "*.json");
    QFile loadFile(file);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    read(loadDoc.object());
}

void MainWindow::read(const QJsonObject &json){

    if (json.contains("memory"))
    {
            QJsonObject memoryObject = json["memory"].toObject();
            em3.read(memoryObject);
    }

    initProgramTableWidget(ui->programTableWidget);
}

void MainWindow::on_enterButton_clicked()
{
    em3.setStrList(ui->inputTextEdit->toPlainText()
                    .split(QRegExp("\\s+"), QString::SkipEmptyParts));
    em3.setInput(false);
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
