#ifndef UINTVALIDATOR_H
#define UINTVALIDATOR_H

#include <QObject>
#include <QWidget>
#include <QValidator>

class CommValidator: public QValidator
{

public:
    CommValidator(uint8_t commCodeLength);
    ~CommValidator();
private:
    const uint8_t commCodeLength;
    QValidator::State validate(QString &input, int &pos) const;
};

class UIntValidator: public QValidator
{
public:
    UIntValidator(uint8_t numCodeLength);
    ~UIntValidator();
private:
    const uint8_t numCodeLength;
    QValidator::State validate(QString &input, int &pos) const;
};

#endif // UINTVALIDATOR_H
