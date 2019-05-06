#ifndef MEMORY_H
#define MEMORY_H

#include <QVector>
#include <memory>

class Cell
{
public:
    Cell();
    virtual ~Cell();
};

class Memory
{
public:
    Memory();
    ~Memory();

private:
    uint16_t size = 512;
    QVector<std::shared_ptr<Cell>> memoryCells;
};

#endif // MEMORY_H
