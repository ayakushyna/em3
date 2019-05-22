#include "commandstring.h"

CommandString::CommandString():address(0), key(0), args(){}

CommandString::CommandString(const QString &str, uint16_t address){
    setAddress(address);
    setKey(str);
    setMAs(str);
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

void CommandString::setKey(const QString &str)
{
    QString keyStr = str.left(keyLength);

    bool ok = true;
    this->key = keyStr.toUShort(&ok,16);
}

uint16_t CommandString::getKey()
{
    return this->key;
}

void CommandString::setMAs(const QString &str)
{
    ma.resize(maNum);
    QString addressingStr = str.mid(keyLength,maNum*maLength);

    for(int i = 0; i < maNum; i++)
    {
        this->ma[i] = static_cast<MA>(addressingStr[i].digitValue());
    }
}

const QVector<MA>& CommandString::getMAs()const
{
    return this->ma;
}

const MA& CommandString::getMA(uint8_t index)const
{
    return this->ma[index % maNum];
}

void CommandString::setArgs(const QString &str)
{
    int argsNum = maNum*2;
    args.resize(argsNum);

    for(int i = 0; i < argsNum; i++)
    {
        int index = keyLength + maNum*maLength + i*argLength;
        QString argStr = str.mid(index,argLength);

        bool ok = true;
        this->args[i] = argStr.toUShort(&ok,16);
    }
}

const QVector<uint16_t>& CommandString::getArgs() const
{
    return this->args;
}

uint16_t CommandString::getArg1(uint8_t index)const
{
    return this->args[2*(index % maNum)];
}

uint16_t CommandString::getArg2(uint8_t index)const
{
    return this->args[2*(index % maNum) + 1];
}
