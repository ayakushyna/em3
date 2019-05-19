#include "parser.h"

Parser::Parser()
{

}


QVector<QString> Parser::parseToMemory(const QString &lines)
{
    if(lines.isEmpty())
        throw ;

    QStringList list = lines.split('\n', QString::SkipEmptyParts);

    for(int i = 0; i < list.size(); i++)
    {
        QString str = list[i];
        str.replace(" ", "");

        if(str.contains(QRegExp("[^A-F0-9]+")))
            throw ;


        if(str.length() > 30)
            throw ;
    }

    return list.toVector();

}
