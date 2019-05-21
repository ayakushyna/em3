#include "memory.h"

Memory::Memory(): memoryCells()
{
    memoryCells.resize(size);
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

QString& Memory::operator[](uint16_t index)
{
    return memoryCells[index % size];
}

const QString& Memory::operator[](uint16_t index) const
{
    return memoryCells[index % size];
}

Memory::~Memory(){}
