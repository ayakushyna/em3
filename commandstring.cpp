#include "commandstring.h"


CommandString::CommandString(const Settings &settings, const QString &str, uint index)
               :str(str), length(settings.length),
                maNum(settings.maNum),
                maLength(settings.maLength),
                commCodeLength(settings.commCodeLength),
                numCodeLength(settings.numCodeLength),
                argLength(settings.argLength)
{
    setIndex(index);
    setCommCode(str);
    setNumCode(str);
    setMAs(str);
    setArgs(str);
}

void CommandString::setIndex(uint index)
{
    this->index = index;
}

uint CommandString::getIndex()const
{
    return this->index;
}

void CommandString::setCommCode(const QString &str)
{
    QString code = str.left(commCodeLength);
    this->commCode = code.toUShort();
}

uint16_t CommandString::getCommCode()const
{
    return this->commCode;
}

void CommandString::setNumCode(const QString &str)
{
    QString code = str.left(numCodeLength);
    this->numCode = code.toUShort();
}

uint16_t CommandString::getNumCode()const
{
    return this->numCode;
}

void CommandString::setMAs(const QString &str)
{
    ma.resize(maNum);
    QString addressingStr = str.mid(commCodeLength,maNum*maLength);

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
        int index = commCodeLength + maNum*maLength + i*argLength;
        QString argStr = str.mid(index,argLength);
        this->args[i] = argStr.toUShort();
    }
}

const QVector<uint16_t>& CommandString::getArgs() const
{
    return this->args;
}

uint16_t CommandString::getArg(uint8_t index)const
{
    return this->args[2*(index % maNum)];
}

uint16_t CommandString::getReg(uint8_t index)const
{
    return this->args[2*(index % maNum) + 1];
}

int64_t CommandString::getISConstant() const
{
    num.ui = str.mid(2).toUInt();
    return num.i;
}

uint64_t CommandString::getIUConstant() const
{
    return str.mid(2).toUInt();
}

double CommandString::getDBConstant() const
{
    num.ui = str.mid(2).toUInt();
    return num.d;
}

QString CommandString::getOperand(const Memory& memory,
                                  const QVector<int>& registers,
                                  uint8_t index) const
{

    MA ma = getMA(index);
    QString operand(length, '0');
    switch (ma) {
        case ImA:
            operand = operand.setNum(getArg(index)).rightJustified(length,'0');
            break;
        case DA:
            operand = memory[getArg(index)];
            break;
        case RA:
            operand = operand.setNum(registers[getReg(index)]).rightJustified(length,'0');;
            break;
        case IRA:
            operand = memory[registers[getReg(index)]];
            break;
        case BRA:
            operand = memory[getArg(index) + registers[getReg(index)]];
            break;
        case IA:
            operand = memory[getArg(index) + registers[getReg(index)]];
            break;
    }
    return operand;
}

CommandString::~CommandString(){}
