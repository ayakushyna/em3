#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include "exception"
#include "em3.h"

class Parser
{
public:
    Parser();
    QVector<QString> parseToMemory(const QString& lines);
};

#endif // PARSER_H
