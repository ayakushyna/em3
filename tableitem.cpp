#include "tableitem.h"

TableItem::TableItem(const QString& str,
                     const Settings &settings,
                     const Parser& parser,
                     bool digitsOnly,
                     bool command,
                     QWidget* parent): QLineEdit(str, parent), parser(parser),
                     digitsOnly(digitsOnly), command(command),
                     commCodeLength(settings.commCodeLength),
                     numCodeLength(settings.numCodeLength)
{
    setFrame(false);
    setMask();

    if(command)
        setValidator(new CommValidator(settings.commCodeLength));
    else
        setValidator(new UIntValidator(settings.numCodeLength));

    QObject::connect(this , &TableItem::selectionChanged, this, &TableItem::selectionSlot);
    QObject::connect(this , &TableItem::textChanged, this, &TableItem::inputTypeChangedSlot);
}


TableItem::~TableItem(){}

void TableItem::keyPressEvent(QKeyEvent* ke)
{
    if(command && (ke->key()==Qt::Key_Backspace || ke->key()==Qt::Key_Delete))
    {
           ke->ignore();
    }
    else
         QLineEdit::keyPressEvent(ke);
}

void TableItem::setMask()
{
    if(digitsOnly)
        setInputMask(QString(">9999 999 999 999 999 999 999"));
    else {
        if(command)
            setInputMask(QString(">AANN 999 999 999 999 999 999"));
        else
            setInputMask(QString(">AA99 999 999 999 999 999 999"));
    }
}

void TableItem::inputTypeChangedSlot()
{
    int pos = cursorPosition();
    QString currStr = this->text();
    bool i = parser.getCurrCommand(currStr);

    if(i && i != command)
    {
        command = i;
        setMask();
        setValidator(new CommValidator(commCodeLength));
        setCursorPosition(pos);
    }
    else if( !i && i != command)
    {
        command = i;
        setMask();
        setValidator(new UIntValidator(numCodeLength));
        setCursorPosition(pos);
    }
}

void TableItem::selectionSlot()
{
    TableItem* item = dynamic_cast<TableItem*>(sender());
    int pos = item->cursorPosition();
    item->deselect();
    item->setCursorPosition(pos);
}
