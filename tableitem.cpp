#include "tableitem.h"

TableItem::TableItem(const QString& str, QWidget* parent): QLineEdit(str, parent)
{
    setFrame(false);
    setInputMask(QString(">HH H HH HHHH H HH HHHH H HH HHHH"));
    QObject::connect(this , &TableItem::selectionChanged, this, &TableItem::selectionSlot);

}

TableItem::~TableItem(){}

void TableItem::keyPressEvent(QKeyEvent* ke)
{
    if (ke->key()!=Qt::Key_Backspace &&
        ke->key()!=Qt::Key_Delete)
    {
       QLineEdit::keyPressEvent(ke);
    }
    else {
        ke->ignore();
    }
}


void TableItem::selectionSlot()
{
    TableItem* item = dynamic_cast<TableItem*>(sender());
    int pos = item->cursorPosition();
    item->deselect();
    item->setCursorPosition(pos);
}
