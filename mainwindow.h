#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QtWidgets>
#include "em3.h"
#include "memory.h"
#include "parser.h"
#include "memorydialog.h"
#include "tableitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EM3 em3;

    void setProgramTableWidget(QTableWidget* table);
    void setRegistersListWidget(QListWidget* list);

private slots:
    void on_startButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_enterButton_clicked();
    void on_showButton_clicked();
};

#endif // MAINWINDOW_H
