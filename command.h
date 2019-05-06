#ifndef COMMAND_H
#define COMMAND_H

#include <memory.h>
#include <QString>
#include <QVector>

class Command: public Cell
{

public:
    Command();
    Command(const QString& commandStr);
    void setCommand(const uint8_t op,const QVector<uint32_t>& operands);
    void setCommand(const QString& commandStr);
    Command getCommand();
    ~Command();

private:
    uint8_t op;
    QVector<uint32_t> operands;
};

#endif // COMMAND_H
