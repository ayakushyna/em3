#include "parser.h"

Parser::Parser()
{

}


QString& Parser::parseToMemory(QString &str)
{
    if(str.isEmpty())
        throw ;

     str.replace(" ", "");

     if(str.contains(QRegExp("[^A-Fa-f0-9]+")))
         throw ;

     if(str.length() > length)
         throw ;

    return str;

}

Parser::~Parser()
{

}
