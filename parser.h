#ifndef PARSER_H
#define PARSER_H

#include <QMap>
#include <QString>
#include <QVector>
#include "exception"
#include "shared_defs.h"



class Parser
{
public:
    Parser(const Settings &settings, bool digitsOnly);
    QString parseToMemory(const QString& str);
    QString parseFromMemory(const QString& cell);

    bool getCurrCommand(const QString &str);

    void setDigitsOnly( bool digitsOnly);
    bool  getDigitsOnly() const;
    ~Parser();


private:
    uint8_t length;
    uint8_t numCodeLength;
    uint8_t commCodeLength;
    bool digitsOnly;
    QMap<QString,QString> codes;//key = word, value = code

};

#endif // PARSER_H
