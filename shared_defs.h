#ifndef NUMBER_H
#define NUMBER_H

#include <Qt>
//Methods of Addressing
enum MA { ImA, DA, RA, IRA, BRA, IA};
//Immediate Addressing
//Direct Addressing
//Register Addressing
//Indirect Register Addressing
//Basic Register Addressing
//Index Addressing

struct Settings
{
    static const uint64_t regSize = 32;
    static const uint64_t memSize = 512;

    static const uint8_t maNum = 3;
    static const uint8_t maLength = 1;
    static const uint8_t argLength = 3;
    static const uint8_t regLength = 2;

    static const uint8_t commCodeLength = 4;
    static const uint8_t numCodeLength = 2;

    static const uint8_t length = 22;
};

union {
    double d;
    uint64_t ui;
    int64_t i;
} num;

#endif // NUMBER_H
