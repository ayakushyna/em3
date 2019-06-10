#ifndef EM3_H
#define EM3_H

#include <QMap>
#include <QVector>
#include "memory.h"
#include "operation.h"
#include "commandstring.h"

class EM3
{
public:
    EM3(const Settings &settings);
    ~EM3();

    const Memory& getMemory() const;
    void setMemory(Memory& memory);

    const QVector<uint64_t>& getRegisters() const;

    void exec(uint64_t index);
    void init();

    bool isStopped() const;
    bool isZero() const;
    bool isSigned() const;

    uint64_t getRA() const;
    void setRA(uint64_t i);

    bool getInput() const;
    void setInput(bool);
    void setStrList(const QStringList& list);

    bool getOutput() const;
    void setOutput(bool);
    const QStringList& getStrList() const;

    void read(const QJsonObject&);
    void write(QJsonObject&) const;

private:
    uint8_t length;

    QMap<uint16_t,void (EM3::*)()> commands;
    Settings settings;

    Memory memory;
    QVector<uint64_t> registers;

    uint64_t RA;
    CommandString RC;

    bool Z;//признак нулевого результата
    bool S;//знак результата

    bool Stop;

    bool Input;
    bool Output;
    QStringList InOutStringList;
    void resizeStrList(uint64_t size);

    QVector<uint64_t> getOperands() const;
    void saveIntegerS(int64_t result, uint64_t address);
    void saveIntegerU(uint64_t result, uint64_t address);
    void saveDouble(double result, uint64_t address);

    void cop00();
    void cop01();
    void cop02();

    void cop1000();
    void cop1001();
    void cop1002();

    void cop1100();
    void cop1101();
    void cop1102();

    void cop1200();
    void cop1201();
    void cop1202();

    void cop1300();
    void cop1301();
    void cop1302();

    void cop1400();
    void cop1401();
    void cop1410();
    void cop1411();
    void cop1402();

    void cop1500();
    void cop1501();
    void cop1502();

    void cop1600();
    void cop1601();
    void cop1602();

    void cop1701();
    void cop1702();
    void cop1710();
    void cop1712();
    void cop1720();
    void cop1721();

    void cop1801();
    void cop1802();

    void cop1900();
    void cop1901();
    void cop1902();

    void cop1099();
};

#endif // EM3_H
