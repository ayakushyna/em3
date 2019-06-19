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
#include "shared_defs.h"
#include <exception>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    Ui::MainWindow *ui;
    bool digitsOnly;
    Settings settings;
    Parser parser;
    EM3 em3;

    void initProgramTableWidget(QTableWidget* table);
    void editMemoryCells(QTableWidget* table);
    void updateMemoryCells(QTableWidget* table);
    void setRow(QTableWidget* table, int i , const QString& str, bool checked = false);
    void initRegistersListWidget(QListWidget* list);
    void step();

private slots:
    void on_startButton_clicked();
    void on_enterButton_clicked();
    void on_showButton_clicked();
    void on_storeButton_clicked();
    void on_clearButton_clicked();
    void on_stepButton_clicked();
    void on_stopButton_clicked();
    void on_digitsOnlyCheckBox_clicked(bool checked);

    void saveApp();
    void loadApp();
    void aboutApp();
    void infoDialog();

};

#endif // MAINWINDOW_H
