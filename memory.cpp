#include "memory.h"

Memory::Memory(uint8_t length): memoryCells()
{
    memoryCells.resize(size);
    memoryCells.fill(QString(length, '0'));
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

QString& Memory::operator[](uint index)
{
    return memoryCells[index % size];
}

const QString& Memory::operator[](uint index) const
{
    return memoryCells[index % size];
}

int Memory::getSize() const
{
    return memoryCells.size();
}

Memory::~Memory(){}
