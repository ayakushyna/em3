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
    void setProgramTableWidget(QTableWidget* table);
    void setRow(QTableWidget* table, const QString& str, int i);
    void initRegistersListWidget(QListWidget* list);

private slots:
    void on_startButton_clicked();
    void on_enterButton_clicked();
    void on_showButton_clicked();
    void on_storeButton_clicked();
    void on_clearButton_clicked();
    void on_digitsRadioButton_clicked(bool checked);

    void saveApp();
    void loadApp();
    void infoDialog();
};

#endif // MAINWINDOW_H
