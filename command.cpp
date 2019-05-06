#include "command.h"

Command::Command(): Cell(), op(0), operands(0) {}

Command::Command(const QString& commandStr)
{

}
void Command::setCommand(const uint8_t op, const QVector<uint32_t>& operands)
{

}
void Command::setCommand(const QString& commandStr)
{

}
Command Command::getCommand()
{

}

Command::~Command() {}
