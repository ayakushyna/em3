#ifndef TABLEITEM_H
#define TABLEITEM_H

#include <QObject>
#include <QtWidgets>
#include <QStyleOption>
#include <QLineEdit>
#include <QKeyEvent>
#include "parser.h"
#include "validator.h"
#include "shared_defs.h"

class TableItem: public QLineEdit
{
    Q_OBJECT
public:
    TableItem(const QString& str,
              const Settings &settings,
              const Parser& parser,
              bool digitsOnly = true,
              bool command = false,
              QWidget* parent = 0);
    ~TableItem();

protected:
    virtual void keyPressEvent(QKeyEvent* pe);

private slots:
    void selectionSlot();

public slots:
    void inputTypeChangedSlot();

private:
    Parser parser;
    bool digitsOnly, command;
    uint8_t commCodeLength;
    uint8_t numCodeLength;

    void setMask();
};

#endif // TABLEITEM_H
