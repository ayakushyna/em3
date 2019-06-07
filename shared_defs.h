#ifndef NUMBER_H
#define NUMBER_H

#include <Qt>

//Methods of Addressing
enum MA { ImA, DA, RA, IRA, BRA, IA};
//Immediate Addressing
//Direct Addressing
//Indirect Register Addressing
//Basic Register Addressing
//Index Addressing

struct Settings
{
    const uint8_t maNum = 3;
    const uint8_t maLength = 1;
    const uint8_t commCodeLength = 4;
    const uint8_t numCodeLength = 2;
    const uint8_t argLength = 3;
    const uint8_t length = 22;
};

enum Number {Integer, UInteger, Double};

union{
    double d;
    uint64_t ui;
    int64_t i;
} num;

#endif // NUMBER_H
