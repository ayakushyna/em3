#ifndef MEMORY_H
#define MEMORY_H

#include <memory>
#include <QVector>
#include <QString>
#include <QtWidgets>

class Memory
{
public:
    Memory(uint8_t length);
    Memory(const QVector<QString>& cells);
    void setMemoryCells(const QVector<QString>& cells);
    const QVector<QString>& getMemoryCells() const;
    ~Memory();

    QString& operator[](uint64_t index);
    const QString& operator[](uint64_t index) const;

    uint64_t getSize() const;

    void read(const QJsonObject&);
    void write(QJsonObject&) const;

private:
    static const uint64_t size = 512;
    QVector<QString> memoryCells;
};

#endif // MEMORY_H
