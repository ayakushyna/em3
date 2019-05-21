#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <QVector>
#include "exception"

class Parser
{
private:

public:
    Parser();
    static QVector<QString> parseToMemory(const QString& lines);
    ~Parser();
};

#endif // PARSER_H
