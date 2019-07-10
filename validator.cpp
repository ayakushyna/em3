#include "validator.h"

CommValidator::CommValidator(uint8_t commCodeLength)
    :commCodeLength(commCodeLength)
{
}

CommValidator::~CommValidator(){}

QValidator::State CommValidator::validate(QString &input, int &pos) const
{
    QString maLimit = "5";
    QString memoryLimit = "511";
    QString regLimit = "31";

    int i = commCodeLength + 1;
    for(int j = 0; j < 3; j++)
    {
        if(input.mid(i,1) > maLimit)
            input.replace(i, 1, maLimit);
        i++;

        if(input.mid(i, 2) > regLimit)
             input.replace(i, 2, regLimit);
        i+=3;

        if(input.mid(i, 3) > memoryLimit)
            input.replace(i, 3, memoryLimit);
        i+=4;
    }
    return QValidator::Acceptable;
}


UIntValidator::UIntValidator(uint8_t numCodeLength)
    :numCodeLength(numCodeLength)
{

}

UIntValidator::~UIntValidator(){}

QValidator::State UIntValidator::validate(QString &input, int &pos) const
{
    QString limit = "18 446 744 073 709 551 615";
    if(input.mid(numCodeLength) > limit)
    {
        input.replace(numCodeLength, limit.length(), limit);
    }
    return QValidator::Acceptable;
}
