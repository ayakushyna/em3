#include "memorydialog.h"

MemoryDialog::MemoryDialog(QVector<QString> cells, QWidget* parent):
              QDialog(parent)
{
    list = new QListWidget(this);
    setList(cells, list);
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(list);
    this->setLayout(layout);
}

void MemoryDialog::setList(QVector<QString> cells, QListWidget *listWidget)
{
    foreach(QString str, cells)
    {
         new QListWidgetItem(str, listWidget);
    }
}

MemoryDialog::~MemoryDialog(){}
