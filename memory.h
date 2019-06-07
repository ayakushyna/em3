#ifndef MEMORY_H
#define MEMORY_H

#include <memory>
#include <QVector>
#include <QString>

class Memory
{
public:
    Memory(uint8_t length);
    Memory(const QVector<QString>& cells);
    void setMemoryCells(const QVector<QString>& cells);
    const QVector<QString>& getMemoryCells() const;
    ~Memory();

    QString& operator[](uint index);
    const QString& operator[](uint index) const;

    int getSize() const;

private:
    static const uint16_t size = 10;
    QVector<QString> memoryCells;
};

#endif // MEMORY_H
