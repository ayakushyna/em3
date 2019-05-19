#ifndef COMMANDSTRING_H
#define COMMANDSTRING_H

#include <string>
#include <QVector>
#include <QString>
enum SA { NA, PA, KPA, BRA, IA};

class CommandString
{
private:
    uint16_t address;
    uint16_t key;
    QVector<SA> sa;
    QVector<uint16_t> args;

    static const int saNum = 3;
    static const int saLength = 1;
    static const int keyLength = 2;
    static const int argLength = 4;

public:
    CommandString();
    CommandString(QString str, uint16_t address);

    void setArgs(QString str);
    //void setArgs(QVector<uint16_t> args);
    QVector<uint16_t> getArgs();

    void setAddressing(QString str);
    //void setAddressing(QVector<SA> sa);
    QVector<SA> getAddressing();

    void setKey(QString str);
    //void setKey(uint16_t key);
    uint16_t getKey();

    void setAddress(uint16_t address);
    uint16_t getAddress();

    ~CommandString();
};

#endif // COMMANDSTRING_H
