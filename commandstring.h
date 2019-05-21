#ifndef COMMANDSTRING_H
#define COMMANDSTRING_H

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
    CommandString(const QString &str, uint16_t address);

    void setArgs(const QString &str);
    //void setArgs(QVector<uint16_t> args);
    const QVector<uint16_t>& getArgs()const;

    void setAddressing(const QString &str);
    //void setAddressing(QVector<SA> sa);
    const QVector<SA>& getAddressing()const;

    void setKey(const QString &str);
    //void setKey(uint16_t key);
    uint16_t getKey();

    void setAddress(uint16_t address);
    uint16_t getAddress();

    ~CommandString();
};

#endif // COMMANDSTRING_H
