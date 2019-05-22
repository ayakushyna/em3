#ifndef COMMANDSTRING_H
#define COMMANDSTRING_H

#include <QVector>
#include <QString>

//Methods of Addressing
enum MA { ImA, DA, IRA, BRA, IA};
//Immediate Addressing
//Direct Addressing
//Indirect Register Addressing
//Basic Register Addressing
//Index Addressing

class CommandString
{
private:
    uint16_t address;
    uint16_t key;
    QVector<MA> ma;
    QVector<uint16_t> args;

    static const uint8_t maNum = 3;
    static const uint8_t maLength = 1;
    static const uint8_t keyLength = 2;
    static const uint8_t argLength = 4;

public:
    CommandString();
    CommandString(const QString &str, uint16_t address);

    void setArgs(const QString &str);
    //void setArgs(QVector<uint16_t> args);
    const QVector<uint16_t>& getArgs()const;
    uint16_t getArg1(uint8_t index)const;
    uint16_t getArg2(uint8_t index)const;

    void setMAs(const QString &str);
    //void setAddressing(QVector<SA> sa);
    const QVector<MA>& getMAs()const;
    const MA& getMA(uint8_t index)const;

    void setKey(const QString &str);
    //void setKey(uint16_t key);
    uint16_t getKey();

    void setAddress(uint16_t address);
    uint16_t getAddress();

    ~CommandString();
};

#endif // COMMANDSTRING_H
