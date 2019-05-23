#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QRegExpValidator>

class TableItem: public QLineEdit
{
    Q_OBJECT
public:
    TableItem(const QString& str, QWidget* parent = 0);
    ~TableItem();


protected:
    virtual void keyPressEvent(QKeyEvent* pe);


private slots:
    void selectionSlot();
};

#endif // TABLEITEM_H
