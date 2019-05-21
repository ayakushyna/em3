#ifndef MEMORY_H
#define MEMORY_H

#include <memory>
#include <QVector>
#include <QString>


class Memory
{
public:
    Memory();
    Memory(const QVector<QString>& cells);
    void setMemoryCells(const QVector<QString>& cells);
    const QVector<QString>& getMemoryCells() const;
    ~Memory();

    QString& operator[](uint16_t index);
    const QString& operator[](uint16_t index) const;

private:
    static const uint16_t size = 65535;
    QVector<QString> memoryCells;
};

#endif // MEMORY_H
