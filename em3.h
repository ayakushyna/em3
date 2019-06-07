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
    const Memory& getMemory() const;
    void setMemory(Memory& memory);
    void exec();
    ~EM3();

private:
    uint8_t length;

    QMap<uint16_t,void (EM3::*)()> commands;
    Memory memory;
    Settings settings;
    QVector<int> registers;

    uint16_t RA;
    CommandString RC;

    bool Z;//признак нулевого результата
    bool C;//признак переноса из старшего разряда
    bool S;//знак результата
    bool O;//признак переполнения результата

    bool Stop;

    void cop00();
    void cop01();
    void cop02();

    void cop1010();
    void cop1011();
    void cop1012();

    void cop1020();
    void cop1021();
    void cop1022();


    void cop1030();
    void cop1031();
    void cop1032();


    void cop1040();
    void cop1041();
    void cop1042();

    void cop1099();
};

#endif // EM3_H
