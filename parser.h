#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QVector>
#include "exception"

class Parser
{
public:
    Parser();
    static const uint8_t length = 23;
    static QString&  parseToMemory( QString& lines);
    ~Parser();
};

#endif // PARSER_H
