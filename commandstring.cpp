#include "commandstring.h"

CommandString::CommandString():address(0), key(0), args(){}

CommandString::CommandString(QString str, uint16_t address){
    setAddress(address);
    setKey(str);
    setAddressing(str);
    setArgs(str);
}

void CommandString::setAddress(uint16_t address)
{
    this->address = address;
}

uint16_t CommandString::getAddress()
{
    return this->address;
}

void CommandString::setKey(QString str)
{
    QString keyStr = str.left(keyLength);

    bool ok = true;
    this->key = keyStr.toUShort(&ok,16);
}

uint16_t CommandString::getKey()
{
    return this->key;
}

void CommandString::setAddressing(QString str)
{
    sa.resize(saNum);
    QString addressingStr = str.mid(keyLength,saNum*saLength);

    for(int i = 0; i < saNum; i++)
    {
        this->sa[i] = static_cast<SA>(addressingStr[i].digitValue());
    }
}

QVector<SA> CommandString::getAddressing()
{
    return this->sa;
}

void CommandString::setArgs(QString str)
{
    int argsNum = saNum*2;
    args.resize(argsNum);

    for(int i = 0; i < argsNum; i++)
    {
        int index = keyLength + saNum*saLength + i*argLength;
        QString argStr = str.mid(index,argLength);

        bool ok = true;
        this->args[i] = argStr.toUShort(&ok,16);
    }
}

QVector<uint16_t> CommandString::getArgs()
{
    return this->args;
}
