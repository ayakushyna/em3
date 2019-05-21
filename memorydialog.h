#ifndef MEMORYDIALOG_H
#define MEMORYDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>

class MemoryDialog: public QDialog {
    Q_OBJECT

public:
    MemoryDialog(QVector<QString> cells, QWidget* parent = 0);
    void setList(QVector<QString> cells,  QListWidget* listWidget);
    ~MemoryDialog();

private:
    QListWidget* list;
};

#endif // MEMORYDIALOG_H
