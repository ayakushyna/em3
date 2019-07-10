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

QString& Memory::operator[](uint64_t index)
{
    return memoryCells[index % size];
}

const QString& Memory::operator[](uint64_t index) const
{
    return memoryCells[index % size];
}

uint64_t Memory::getSize() const
{
    return memoryCells.size();
}

void Memory::write(QJsonObject &json) const {
    for(int i = 0; i < memoryCells.size(); i++)
    {
        json[(i < 10? "00": i <100? "0":"")+QString::number(i)] = memoryCells[i];
    }

}

void Memory::read(const QJsonObject &json){
    for(int i = 0; i < memoryCells.size(); i++)
    {
        if (json.contains((i < 10? "00": i <100? "0":"")+QString::number(i)))
            memoryCells[i] = json[(i < 10? "00": i <100? "0":"")+QString::number(i)].toString();
        else {
            throw std::logic_error("Invalid data");
        }
    }
}

Memory::~Memory(){}
