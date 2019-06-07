#include "em3.h"

EM3::EM3(const Settings &settings): length(settings.length), commands(),
            memory(length), settings(settings),
            RA(0), RC(settings, memory[0], 0),
            Z(0), C(0), S(0), O(0), Stop(false)
{
    commands.insert(0,&EM3::cop00);
    commands.insert(1,&EM3::cop01);
    commands.insert(2,&EM3::cop02);

    commands.insert(1010,&EM3::cop1010);
    commands.insert(1011,&EM3::cop1011);
//    commands.insert(1012,&EM3::cop1012);

//    commands.insert(1020,&EM3::cop1020);
//    commands.insert(1021,&EM3::cop1021);
//    commands.insert(1022,&EM3::cop1022);

//    commands.insert(1030,&EM3::cop1030);
//    commands.insert(1031,&EM3::cop1031);
//    commands.insert(1032,&EM3::cop1032);

//    commands.insert(1040,&EM3::cop1040);
//    commands.insert(1041,&EM3::cop1041);
//    commands.insert(1042,&EM3::cop1042);

    commands.insert(1099,&EM3::cop1099);
}

const Memory& EM3::getMemory() const
{
    return this->memory;
}

void EM3::setMemory( Memory& memory)
{
    this->memory = memory;
}

void EM3::exec(){
    int size = memory.getSize();
    for(int i = 0; i < size && !Stop; i++)
    {
        RA = i;
        RC = CommandString(settings, memory[i], i);
        (this->*commands.value(RC.getCommCode()))();
    }

}

void EM3::cop00()
{

}

void EM3::cop1099()
{
    Stop = true;
}



void EM3::cop01()
{

}

void EM3::cop02()
{

}

void EM3::cop1010()
{
    QVector<uint64_t> operands (3);

    for(int i = 0; i < 3; i++)
    {
        QString str = RC.getOperand(memory, registers, i);
        operands[i] = str.mid(2).toULongLong();
    }

    num.ui = operands[0];
    int64_t first = num.i;
    num.ui = operands[1];
    int64_t second = num.i;

    int64_t result = first + second;

    if((first > 0  && second > 0 && result < 0)
      || (first < 0  && second < 0 && result > 0))
        O = true;

    C = false;
    Z = result == 0? true : false;
    S = result < 0? true : false;


    num.i = result;

    memory[operands[2]] = memory[operands[2]]
                          .setNum(num.ui)
                          .rightJustified(length-2, '0');

    memory[operands[2]].prepend("00");
}

void EM3::cop1011()//вычитание беззнаковых целых
{
    QVector<uint64_t> operands (3);

    for(int i = 0; i < 3; i++)
    {
        QString str = RC.getOperand(memory, registers, i);
        operands[i] = str.mid(2).toULongLong();
    }


    uint64_t result = operands[0] + operands[1];

    if(result < operands[0] || result < operands[1])
         C = true;

    O = false;
    Z = result == 0? true : false;
    S = result < 0? true : false;


    memory[operands[2]] = memory[operands[2]]
                          .setNum(result)
                          .rightJustified(length-2, '0');

    memory[operands[2]].prepend("01");
}

void EM3::cop1012()
{
    QVector<uint64_t> operands (3);

    for(int i = 0; i < 3; i++)
    {
        QString str = RC.getOperand(memory, registers, i);
        operands[i] = str.mid(2).toULongLong();
    }

    num.ui = operands[0];
    double first = num.d;
    num.ui = operands[1];
    double second = num.d;

    double result = first + second;

    if((first > 0  && second > 0 && result < 0)
      || (first < 0  && second < 0 && result > 0))
        O = true;

    C = false;
    Z = result == 0? true : false;
    S = result < 0? true : false;


    num.d = result;

    memory[operands[2]] = memory[operands[2]]
                          .setNum(num.ui)
                          .rightJustified(length-2, '0');

    memory[operands[2]].prepend("03");
}

void EM3::cop1020()
{
    QVector<uint64_t> operands (3);

    for(int i = 0; i < 3; i++)
    {
        QString str = RC.getOperand(memory, registers, i);
        operands[i] = str.mid(2).toULongLong();
    }

    num.ui = operands[0];
    int64_t first = num.i;
    num.ui = operands[1];
    int64_t second = num.i;

    int64_t result = first - second;

    if((operands[0] < 0  && operands[1] > 0 && result < 0)
      || (operands[0] > 0  && operands[1] < 0 && result > 0))
        O = true;

    C = false;
    Z = result == 0? true : false;
    S = result < 0? true : false;


    num.i = result;

    memory[operands[2]] = memory[operands[2]]
                          .setNum(num.ui)
                          .rightJustified(length-2, '0');

    memory[operands[2]].prepend("00");
}

void EM3::cop1021()//вычитание беззнаковых целых
{
    QVector<uint64_t> operands (3);

    for(int i = 0; i < 3; i++)
    {
        QString str = RC.getOperand(memory, registers, i);
        operands[i] = str.mid(2).toULongLong();
    }


    uint64_t result = operands[0] - operands[1];

    if(result > operands[0] || result > operands[1])
         C = true;

    O = false;
    Z = result == 0? true : false;
    S = result < 0? true : false;


    memory[operands[2]] = memory[operands[2]]
                          .setNum(result)
                          .rightJustified(length-2, '0');

    memory[operands[2]].prepend("01");
}

void EM3::cop1022()
{
    QVector<uint64_t> operands (3);

    for(int i = 0; i < 3; i++)
    {
        QString str = RC.getOperand(memory, registers, i);
        operands[i] = str.mid(2).toULongLong();
    }

    num.ui = operands[0];
    double first = num.d;
    num.ui = operands[1];
    double second = num.d;

    double result = first - second;

    if((first > 0  && second > 0 && result < 0)
      || (first < 0  && second < 0 && result > 0))
        O = true;

    C = false;
    Z = result == 0? true : false;
    S = result < 0? true : false;


    num.d = result;

    memory[operands[2]] = memory[operands[2]]
                          .setNum(num.ui)
                          .rightJustified(length-2, '0');

    memory[operands[2]].prepend("03");
}

EM3::~EM3(){}
