#include "commandstring.h"


CommandString::CommandString(const Settings &settings, const QString &str)
               :str(str), length(settings.length),
                maNum(settings.maNum),
                maLength(settings.maLength),
                commCodeLength(settings.commCodeLength),
                numCodeLength(settings.numCodeLength),
                argLength(settings.argLength),
                regLength(settings.regLength),
                regSize(settings.regSize)
{
    setCommCode(str);
    setNumCode(str);
    setMAs(str);
    setArgs(str);
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

    for(int i = 0; i < maNum; i++)
    {
        this->ma[i] = static_cast<MA>(str[commCodeLength + i*6].digitValue());
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
    args.resize(maNum*2);

    for(int i = 0; i < maNum; i++)
    {
        int index = commCodeLength + 1 + i*6;

        QString regStr = str.mid(index,regLength);
        this->args[i*2] = regStr.toUShort();

        QString argStr = str.mid(index+regLength,argLength);
        this->args[i*2+1] = argStr.toUShort();
    }
}

const QVector<uint16_t>& CommandString::getArgs() const
{
    return this->args;
}

uint16_t CommandString::getArg(uint8_t index)const
{
    return this->args[2*(index % maNum) + 1];
}

uint16_t CommandString::getReg(uint8_t index)const
{
    return this->args[2*(index % maNum)] % regSize;
}

int64_t CommandString::getISConstant() const
{
    num.ui = str.mid(numCodeLength).toULongLong();
    return num.i;
}

uint64_t CommandString::getIUConstant() const
{
    return str.mid(numCodeLength).toULongLong();
}

double CommandString::getDBConstant() const
{
    num.ui = str.mid(numCodeLength).toULongLong();
    return num.d;
}

QString CommandString::getOperand(const Memory& memory,
                                  const QVector<uint64_t>& registers,
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
