#include "memory.h"

Memory::Memory(): memoryCells()
{
    memoryCells.resize(size);
    memoryCells.fill(QString(Parser::length, '0'));
}

Memory::Memory(const QVector<QString>& cells): memoryCells()
{
    memoryCells.resize(size);
    setMemoryCells(cells);
}

void Memory::setMemoryCells(const QVector<QString>& cells)
{
    if(cells.size() <= memoryCells.size())
        this->memoryCells = cells;
    else throw;
}

const QVector<QString>& Memory::getMemoryCells() const
{
    return this->memoryCells;
}

QString& Memory::operator[](int index)
{
    return memoryCells[index % size];
}

const QString& Memory::operator[](int index) const
{
    return memoryCells[index % size];
}

int Memory::getSize() const
{
    return memoryCells.size();
}

Memory::~Memory(){}
