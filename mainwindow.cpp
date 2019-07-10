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
    connect(ui->actionAbout,SIGNAL(triggered()),this, SLOT(aboutApp()));
    connect(ui->actionInfo,SIGNAL(triggered()),this, SLOT(infoDialog()));

    ui->digitsOnlyCheckBox->setChecked(true);

    ui->showButton->setEnabled(false);
    ui->enterButton->setEnabled(false);
    ui->stopButton->setEnabled(false);
    ui->stepButton->setEnabled(false);

    initProgramTableWidget(ui->programTableWidget);
    initRegistersListWidget(ui->registersListWidget);

    ui->inputTextEdit->setEnabled(false);
    ui->outputTextEdit->setEnabled(false);

    setAttribute( Qt::WA_DeleteOnClose, true );
    setFixedSize(995,570);
    statusBar()->setSizeGripEnabled(false);
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

}

void MainWindow::setRow(QTableWidget* table, int i, const QString& str, bool checked)
{
    QString cell = parser.parseFromMemory(str);
    bool command = parser.isCommand(cell);

    TableItem* item = new TableItem(cell, settings, parser, digitsOnly, command, table);
    table->setCellWidget(i, 1, item);

    QRadioButton* button = new QRadioButton();
    button->setChecked(checked);
    button->setAutoExclusive(false);
    table->setCellWidget(i,0,button);
}

void MainWindow::initProgramTableWidget(QTableWidget* table)
{
    Memory memory = em3.getMemory();
    int count = memory.getSize();
    table->setRowCount(count);

    QStringList header;
    header << "" << "CODE ARG OP1 ARG OP2 ARG OP3";

    QStringList addresses;
    for(int i = 0; i < count; i++)
    {
        addresses << (i < 10? "00": i <100? "0":"") + QString::number(i);
        setRow(table,i, memory[i]);
    }

    table->setHorizontalHeaderLabels(header);
    table->setVerticalHeaderLabels(addresses);
}



void MainWindow::editMemoryCells(QTableWidget* table)
{
    int count = table->rowCount();

    for(int i = 0; i < count; i++)
    {
        QString str = dynamic_cast<TableItem*>(table->cellWidget(i,1))->text();
        bool checked =  dynamic_cast<QRadioButton*>(table->cellWidget(i,0))->isChecked();
        setRow(table,i,str, checked);
    }

}

void MainWindow::updateMemoryCells(QTableWidget* table)
{
    Memory memory = em3.getMemory();
    int count = table->rowCount();

    QStringList addresses;
    for(int i = 0; i < count; i++)
    {
        addresses << (i < 10? "00": i <100? "0":"") + QString::number(i);
        QString str = memory[i];
        bool checked =  dynamic_cast<QRadioButton*>(table->cellWidget(i,0))->isChecked();
        setRow(table,i,str, checked);
    }

    table->setVerticalHeaderLabels(addresses);
}



void MainWindow::initRegistersListWidget(QListWidget* list)
{
    list->clear();
    QVector<uint64_t> registers = em3.getRegisters();
    int count = registers.size();

    list->addItem("Z   :"+ QString::number(em3.isZero()));
    list->addItem("S   :"+ QString::number(em3.isSigned()));
    list->addItem("RA  :"+QString::number(em3.getRA())
                  .rightJustified(settings.length-2, '0'));

    for (int i = 0; i < count; i++)
    {
        list->addItem("RG"+(i < 10? "0"+QString::number(i): QString::number(i))+":"
                      +QString::number(registers[i])
                      .rightJustified(settings.length-2, '0'));
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::step()
{
    try
    {
        bool command = parser.isCommand(em3.getMemory()[em3.getRA()]);
        if(command)
        {
            em3.exec(em3.getRA());

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
                em3.exec(em3.getRA());

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
        em3.setRA(em3.getRA()+ 1);

    }
    catch (std::exception& e)
    {
        ui->outputTextEdit->setPlainText(e.what());
    }
}

void MainWindow::on_stepButton_clicked()
{
    step();

    updateMemoryCells(ui->programTableWidget);
    initRegistersListWidget(ui->registersListWidget);

    if(!em3.isStopped())
    {
        dynamic_cast<QRadioButton*>(ui->programTableWidget->cellWidget(em3.getRA(),0))->setFocus();
        ui->programTableWidget->setVerticalHeaderItem(em3.getRA(), new QTableWidgetItem("->"));
    }
    else
    {
        ui->stepButton->setEnabled(false);
        ui->stopButton->setEnabled(false);
    }
}

void MainWindow::on_startButton_clicked()
{
    on_storeButton_clicked();
    ui->outputTextEdit->clear();
    ui->stepButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    em3.init();
    uint64_t size = em3.getMemory().getSize();
    initRegistersListWidget(ui->registersListWidget);

    while(em3.isStopped() != true && em3.getRA() < size)
    {
        bool checked = dynamic_cast<QRadioButton*>(ui->programTableWidget->cellWidget(em3.getRA(),0))->isChecked();

        if(checked)
        {
            ui->stepButton->setEnabled(true);
            ui->stopButton->setEnabled(true);
            break;
        }
        else
            step();
    }

    updateMemoryCells(ui->programTableWidget);
    initRegistersListWidget(ui->registersListWidget);
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
    QJsonObject em3Object;
    em3.write(em3Object);
    json["em3"] = em3Object;
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

    try {
        read(loadDoc.object());
    }
    catch (std::exception& e)
    {
        ui->outputTextEdit->setPlainText(e.what());
    }

}

void MainWindow::read(const QJsonObject &json){

    on_clearButton_clicked();

    if (json.contains("em3"))
    {
            QJsonObject em3Object = json["em3"].toObject();
            em3.read(em3Object);
    }
    else {
        throw std::logic_error("Invalid data");
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
    QVector<QString> cells = em3.getMemory().getMemoryCells();

    MemoryDialog* dialog = new MemoryDialog(cells, this);
    dialog->setModal(true);
    dialog->show();

}


void MainWindow::infoDialog()
{
    QDialog* dialog = new QDialog(this);
    QHBoxLayout *layout = new QHBoxLayout(dialog);
    QTextBrowser *textBrowser = new QTextBrowser(dialog);
    textBrowser->setSource(QUrl("qrc:/commands.html"));
    layout->addWidget(textBrowser);
    dialog->setLayout(layout);
    dialog->setModal(false);
    dialog->setWindowTitle("Commands");
    dialog->setFixedSize(QSize(800,800));
    dialog->show();
}

void MainWindow::aboutApp(){
    QMessageBox::about(this, "About", "Это приложение создано студенткой 2 курса КИ Якушиной Анастасией");
}


void MainWindow::on_storeButton_clicked()
{
    try
    {
        QTableWidget* table = ui->programTableWidget;
        QVector<QString> cells;

        for(int i = 0; i < table->rowCount(); i++)
        {
            QString str = dynamic_cast<TableItem*>(table->cellWidget(i,1))->text();
            str = parser.parseToMemory(str);
            cells.append(str);
        }

        Memory memory(cells);
        em3.setMemory(memory);
    }
    catch (std::exception& e)
    {
        ui->outputTextEdit->setPlainText(e.what());
    }
}

void MainWindow::on_clearButton_clicked()
{
    em3 = EM3(settings);
    initProgramTableWidget(ui->programTableWidget);
    initRegistersListWidget(ui->registersListWidget);
    ui->outputTextEdit->clear();
    ui->stepButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
}


void MainWindow::on_stopButton_clicked()
{
    em3.init();
    initProgramTableWidget(ui->programTableWidget);
    initRegistersListWidget(ui->registersListWidget);
    ui->stopButton->setEnabled(false);
    ui->stepButton->setEnabled(false);
}


void MainWindow::on_digitsOnlyCheckBox_clicked(bool checked)
{
    digitsOnly = checked;
    parser.setDigitsOnly(digitsOnly);
    editMemoryCells(ui->programTableWidget);
}
