#ifndef COMMANDSTRING_H
#define COMMANDSTRING_H

#include <QVector>
#include <QString>
#include "memory.h"
#include "shared_defs.h"


class CommandString
{
private:
    uint index;

    uint16_t commCode;
    uint16_t numCode;
    QVector<MA> ma;
    QVector<uint16_t> args;

    QString str;
    uint8_t length;
    uint8_t maNum;
    uint8_t maLength;
    uint8_t commCodeLength;
    uint8_t numCodeLength;
    uint8_t argLength;

public:
    CommandString(const Settings &settings, const QString &str, uint index);

    void setArgs(const QString &str);
    //void setArgs(QVector<uint16_t> args);
    const QVector<uint16_t>& getArgs()const;
    uint16_t getArg(uint8_t index)const;
    uint16_t getReg(uint8_t index)const;

    void setMAs(const QString &str);
    //void setAddressing(QVector<SA> sa);
    const QVector<MA>& getMAs()const;
    const MA& getMA(uint8_t index)const;

    void setCommCode(const QString &str);
    uint16_t getCommCode()const;

    void setNumCode(const QString &str);
    uint16_t getNumCode()const;

    void setIndex(uint index);
    uint getIndex()const;

    int64_t getISConstant() const;
    uint64_t getIUConstant() const;
    double getDBConstant() const;

    QString getOperand(const Memory& memory,
                       const QVector<int>& registers,
                       uint8_t index) const;

    ~CommandString();
};

#endif // COMMANDSTRING_H
