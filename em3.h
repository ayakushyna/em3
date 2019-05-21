#ifndef EM3_H
#define EM3_H

#include "memory.h"
#include "operation.h"
#include "commandstring.h"
#include <QMap>


class EM3
{
public:
    EM3();
    const Memory& getMemory() const;
    void setMemory(const Memory& memory);
    ~EM3();

private:
    Memory memory;

    uint16_t RA;
    QString RC;

    bool Z;//признак нулевого результата
    bool C;//признак переноса из старшего разряда
    bool S;//знак результата
    bool O;//признак переполнения результата

    static const QMap<uint16_t,Operation> commands;

    void cop00(const CommandString& str);
    void cop01(const CommandString& str);//хранение знакового байта
    void cop02(const CommandString& str);//хранение беззнакового байта
    void cop03(const CommandString& str);//хранение знакового полуслова
    void cop04(const CommandString& str);//хранение беззнакового полуслова
    void cop05(const CommandString& str);//хранение знакового двойного слова
    void cop06(const CommandString& str);//хранение беззнакового двойного слова
    void cop07(const CommandString& str);//хранение знакового числа с ПТ
    void cop08(const CommandString& str);//хранение беззнакового числа с ПТ
    void cop09(const CommandString& str);//сложение байт
    void cop10(const CommandString& str);//вычитание байт
    void cop11(const CommandString& str);//сложение полуслов
    void cop12(const CommandString& str);//вычитание полуслов
    void cop13(const CommandString& str);//сложение двойных слов
    void cop14(const CommandString& str);//вычитание двойных слов
    void cop15(const CommandString& str);//сложение чисел с ПТ
    void cop16(const CommandString& str);//вычитание чисел с ПТ

};

#endif // EM3_H
