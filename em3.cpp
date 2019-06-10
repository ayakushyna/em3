#include "em3.h"

EM3::EM3(const Settings &settings):
            length(settings.length), commands(),
            settings(settings),
            memory(length), registers(settings.regSize),
            RA(0), RC(settings, memory[0]),
            Z(0), S(0),
            Stop(false), Input(false), Output(false)
{
    commands.insert(0,&EM3::cop00);
    commands.insert(1,&EM3::cop01);
    commands.insert(2,&EM3::cop02);

    commands.insert(1000,&EM3::cop1000);
    commands.insert(1001,&EM3::cop1001);
    commands.insert(1002,&EM3::cop1002);

    commands.insert(1100,&EM3::cop1100);
    commands.insert(1101,&EM3::cop1101);
    commands.insert(1102,&EM3::cop1102);

    commands.insert(1200,&EM3::cop1200);
    commands.insert(1201,&EM3::cop1201);
    commands.insert(1202,&EM3::cop1202);

    commands.insert(1300,&EM3::cop1300);
    commands.insert(1301,&EM3::cop1301);
    commands.insert(1302,&EM3::cop1302);

    commands.insert(1400,&EM3::cop1400);
    commands.insert(1401,&EM3::cop1401);
    commands.insert(1410,&EM3::cop1410);
    commands.insert(1411,&EM3::cop1411);
    commands.insert(1402,&EM3::cop1402);

    commands.insert(1500,&EM3::cop1500);
    commands.insert(1501,&EM3::cop1501);
    commands.insert(1502,&EM3::cop1502);

    commands.insert(1600,&EM3::cop1600);
    commands.insert(1601,&EM3::cop1601);
    commands.insert(1602,&EM3::cop1602);

    commands.insert(1701,&EM3::cop1701);
    commands.insert(1702,&EM3::cop1702);
    commands.insert(1710,&EM3::cop1710);
    commands.insert(1712,&EM3::cop1712);
    commands.insert(1720,&EM3::cop1720);
    commands.insert(1721,&EM3::cop1721);

    commands.insert(1801,&EM3::cop1801);
    commands.insert(1802,&EM3::cop1802);

    commands.insert(1900,&EM3::cop1900);
    commands.insert(1901,&EM3::cop1901);
    commands.insert(1902,&EM3::cop1902);

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

const QVector<uint64_t>& EM3::getRegisters() const
{
    return this->registers;
}

bool EM3::isStopped() const
{
    return Stop;
}

bool EM3::isZero() const
{
    return Z;
}

bool EM3::isSigned() const
{
    return S;
}


uint64_t EM3::getRA() const
{
    return RA;
}

void EM3::setRA(uint64_t i)
{
    RA = i;
}


bool EM3::getInput()const
{
    return Input;
}
void EM3::setInput(bool input)
{
    Input = input;
}

bool EM3::getOutput()const
{
    return Output;
}
void EM3::setOutput(bool output)
{
    Output = output;
}

void EM3::setStrList(const QStringList& list)
{
    InOutStringList = list;
}
const QStringList& EM3::getStrList() const
{
    return InOutStringList;
}
void EM3::resizeStrList(uint64_t newSize)
{
    uint64_t size = InOutStringList.size();
    while(size < newSize)
    {
        InOutStringList << "0";
        size++;
    }
    while(size > newSize)
    {
        InOutStringList.pop_back();
        size--;
    }
}

void EM3::exec(uint64_t index)
{
    RA = index;
    RC = CommandString(settings, memory[RA]);
    (this->*commands.value(RC.getCommCode()))();
}
void EM3::init()
{
    RA = 0;
    RC = CommandString(settings, memory[0]);
    registers = QVector<uint64_t>(settings.regSize);

    Z = false;
    S = false;

    Stop = false;
    Input = false;
    Output = false;
}

void EM3::cop1099()
{
    Stop = true;
}

//беззнаковое число
void EM3::cop00(){}

//знаковое число
void EM3::cop01(){}

//вещественное число
void EM3::cop02(){}

QVector<uint64_t> EM3::getOperands() const
{
    QVector<uint64_t> operands (3);

    for(int i = 0; i < 3; i++)
    {
        QString str = RC.getOperand(memory, registers, i);
        operands[i] = str.mid(settings.numCodeLength).toULongLong();
    }

    return operands;
}

void EM3::saveIntegerU(uint64_t result, uint64_t address)
{
    Z = (result == 0);
    S = false;

    if(RC.getMA(0) == MA::RA)
    {
        address = address % registers.size();
        registers[address] = result;
    }
    else
    {
        memory[address] = memory[address]
                              .setNum(result)
                              .rightJustified(length-2, '0');

        memory[address].prepend("00");
    }
}

void EM3::saveIntegerS(int64_t result, uint64_t address)
{
    Z = (result == 0);
    S = (result < 0);

    num.i = result;

    if(RC.getMA(0) == MA::RA)
    {
        address = address % registers.size();
        registers[address] = num.ui;
    }
    else
    {
        memory[address] = memory[address]
                              .setNum(num.ui)
                              .rightJustified(length-2, '0');

        memory[address].prepend("01");
    }

}

void EM3::saveDouble(double result, uint64_t address)
{
    Z = (result == 0.);
    S = (result < 0);

    num.d = result;

    if(RC.getMA(0) == MA::RA)
    {
        address = address % registers.size();
        registers[address] = num.ui;
    }
    else
    {
        memory[address] = memory[address]
                              .setNum(num.ui)
                              .rightJustified(length-2, '0');

        memory[address].prepend("02");
    }
}

//присваивание беззнакового целого
void EM3::cop1000()
{
    QVector<uint64_t> operands = getOperands();
    saveIntegerU(operands[2], operands[0]);
}

//присваивание знакового целого
void EM3::cop1001()
{
    QVector<uint64_t> operands = getOperands();
    num.ui = operands[2];
    int64_t result = num.i;
    saveIntegerS(result, operands[0]);
}

//присваивание вещественного числа
void EM3::cop1002()
{
    QVector<uint64_t> operands = getOperands();
    num.ui = operands[2];
    double result = num.d;
    saveDouble(result, operands[0]);
}

//сложение беззнаковых целых
void EM3::cop1100()
{
    QVector<uint64_t> operands = getOperands();
    uint64_t result = operands[1] + operands[2];
    saveIntegerU(result, operands[0]);
}

//сложение знаковых целых
void EM3::cop1101()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    int64_t first = num.i;
    num.ui = operands[2];
    int64_t second = num.i;

    int64_t result = first + second;
    saveIntegerS(result, operands[0]);
}

//сложение вещественных
void EM3::cop1102()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    double first = num.d;
    num.ui = operands[2];
    double second = num.d;

    double result = first + second;
    saveDouble(result, operands[0]);
}

//вычитание беззнаковых целых
void EM3::cop1200()
{
    QVector<uint64_t> operands = getOperands();


    uint64_t result = operands[1] - operands[2];
    saveIntegerU(result, operands[0]);
}

//вычитание знаковых целых
void EM3::cop1201()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    int64_t first = num.i;
    num.ui = operands[2];
    int64_t second = num.i;

    int64_t result = first - second;
    saveIntegerS(result, operands[0]);
}

//вычитание вещественных
void EM3::cop1202()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    double first = num.d;
    num.ui = operands[2];
    double second = num.d;

    double result = first - second;
    saveDouble(result, operands[0]);
}


//умножение беззнаковых целых
void EM3::cop1300()
{
    QVector<uint64_t> operands = getOperands();

    uint64_t result = operands[1] * operands[2];
    saveIntegerU(result, operands[0]);
}

//умножение знаковых целых
void EM3::cop1301()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    int64_t first = num.i;
    num.ui = operands[2];
    int64_t second = num.i;

    int64_t result = first * second;
    saveIntegerS(result, operands[0]);
}


//умножение вещественных
void EM3::cop1302()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    double first = num.d;
    num.ui = operands[2];
    double second = num.d;

    double result = first * second;
    saveDouble(result, operands[0]);
}

//деление беззнаковых целых
void EM3::cop1400()
{
    QVector<uint64_t> operands = getOperands();


    uint64_t result = operands[1] / operands[2];
    saveIntegerU(result, operands[0]);
}

//деление знаковых целых
void EM3::cop1401()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    int64_t first = num.i;
    num.ui = operands[2];
    int64_t second = num.i;

    int64_t result = first / second;
    saveIntegerS(result, operands[0]);
}


//деление по модулю беззнаковых целых
void EM3::cop1410()
{
    QVector<uint64_t> operands = getOperands();
    uint64_t result = operands[1] % operands[2];
    saveIntegerU(result, operands[0]);
}

//деление по модулю знаковых целых
void EM3::cop1411()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    int64_t first = num.i;
    num.ui = operands[2];
    int64_t second = num.i;

    int64_t result = first % second;
    saveIntegerS(result, operands[0]);
}


//деление вещественных
void EM3::cop1402()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    double first = num.d;
    num.ui = operands[2];
    double second = num.d;

    double result = first / second;
    saveDouble(result, operands[0]);
}


//ввод беззнаковых целых
void EM3::cop1500()
{
    if(InOutStringList.empty())
    {
        Input = true;
    }
    else
    {
        QVector<uint64_t> operands = getOperands();
        uint64_t size = operands[1];
        resizeStrList(size);

        for (uint64_t i = 0; i < size; i++)
        {
            uint64_t result = InOutStringList[i].toULongLong();
            saveIntegerU(result, operands[0]+i);
        }

        InOutStringList.clear();
    }
}

//ввод знаковых целых
void EM3::cop1501()
{
    if(InOutStringList.empty())
    {
        Input = true;
    }
    else
    {
        QVector<uint64_t> operands = getOperands();
        uint64_t size = operands[1];
        resizeStrList(size);

        for (uint64_t i = 0; i < size; i++)
        {
            int64_t result = InOutStringList[i].toLongLong();
            saveIntegerS(result, operands[0]+i);
        }

        InOutStringList.clear();
    }
}

//ввод вещественных
void EM3::cop1502()
{
    if(InOutStringList.empty())
    {
        Input = true;
    }
    else
    {
        QVector<uint64_t> operands = getOperands();
        uint64_t size = operands[1];
        resizeStrList(size);

        for (uint64_t i = 0; i < size; i++)
        {
            double result = InOutStringList[i].toDouble();
            saveDouble(result, operands[0]+i);
        }

        InOutStringList.clear();
    }
}

//вывод беззнаковых целых
void EM3::cop1600()
{
    if(InOutStringList.empty())
    {
        QVector<uint64_t> operands = getOperands();
        uint64_t size = operands[1];

        for (uint64_t i = 0; i < size; i++)
        {
            uint64_t result = CommandString(settings,
                                           memory[operands[0]+i])
                             .getIUConstant();
            InOutStringList << QString::number(result);
        }

        Output = true;
    }
}

//вывод знаковых целых
void EM3::cop1601()
{
    if(InOutStringList.empty())
    {
        QVector<uint64_t> operands = getOperands();
        uint64_t size = operands[1];

        for (uint64_t i = 0; i < size; i++)
        {
            int64_t result = CommandString(settings,
                                           memory[operands[0]+i])
                             .getISConstant();
            InOutStringList << QString::number(result);
        }

        Output = true;
    }
}

//вывод вещественных
void EM3::cop1602()
{
    if(InOutStringList.empty())
    {
        QVector<uint64_t> operands = getOperands();
        uint64_t size = operands[1];

        for (uint64_t i = 0; i < size; i++)
        {
            double result = CommandString(settings,
                                           memory[operands[0]+i])
                             .getDBConstant();
            InOutStringList << QString::number(result);
        }

        Output = true;
    }
}

//из беззнаковых целых в знаковые
void EM3::cop1701()
{
    QVector<uint64_t> operands = getOperands();
    int64_t result = CommandString(settings,
                                   memory[operands[2]])
                                  .getIUConstant();
    saveIntegerS(result, operands[0]);
}

//из беззнаковых целых в вещественные
void EM3::cop1702()
{
    QVector<uint64_t> operands = getOperands();
    double result = CommandString(settings,
                                   memory[operands[2]])
                                  .getIUConstant();
    saveDouble(result, operands[0]);
}


//из знаковых целых в беззнаковые
void EM3::cop1710()
{
    QVector<uint64_t> operands = getOperands();
    uint64_t result = CommandString(settings,
                                    memory[operands[2]])
                                    .getISConstant();

    saveIntegerU(result, operands[0]);
}

//из знаковых целых в вещественные
void EM3::cop1712()
{
    QVector<uint64_t> operands = getOperands();
    double result = CommandString(settings,
                                  memory[operands[2]])
                                  .getISConstant();
    saveDouble(result, operands[0]);
}

//из вещественных в беззнаковые
void EM3::cop1720()
{
    QVector<uint64_t> operands = getOperands();
    uint64_t result = CommandString(settings,
                                    memory[operands[2]])
                                    .getDBConstant();
    saveIntegerU(result, operands[0]);
}

//из вещественных  в знаковые
void EM3::cop1721()
{
    QVector<uint64_t> operands = getOperands();
    int64_t result = CommandString(settings,
                                   memory[operands[2]])
                                   .getDBConstant();
    saveIntegerS(result, operands[0]);
}


//безусловный переход
void EM3::cop1801()
{
     QVector<uint64_t> operands = getOperands();
     RA = operands[1] - 1;
}

//условный переход
void EM3::cop1802()
{
    QVector<uint64_t> operands = getOperands();
    if(Z == true)
        RA = operands[0] - 1;
    else if(S == true)
        RA = operands[1] - 1;
    else
        RA = operands[2] - 1;
}

//сравнение беззнаковых целых
void EM3::cop1900()
{
    QVector<uint64_t> operands = getOperands();
    Z = (operands[1] == operands[2]);
    S = (operands[1] < operands[2]);
}

//сравнение знаковых целых
void EM3::cop1901()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    int64_t first = num.i;
    num.ui = operands[2];
    int64_t second = num.i;

    Z = (first == second);
    S = (first < second);
}

//сравнение вещественных
void EM3::cop1902()
{
    QVector<uint64_t> operands = getOperands();

    num.ui = operands[1];
    double first = num.d;
    num.ui = operands[2];
    double second = num.d;

    Z = (first == second);
    S = (first < second);
}


void EM3::write(QJsonObject &json) const{
    QJsonObject memoryObject;
    memory.write(memoryObject);
    json["memory"] = memoryObject;
}

void EM3::read(const QJsonObject &json){

    if (json.contains("memory"))
    {
        QJsonObject memoryObject = json["memory"].toObject();
        memory.read(memoryObject);

    }
}

EM3::~EM3(){}
