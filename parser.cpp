#include "parser.h"

Parser::Parser(const Settings &settings, bool digitsOnly)
                : length(settings.length),
                  numCodeLength(settings.numCodeLength),
                  commCodeLength(settings.commCodeLength)
{
    this->digitsOnly=digitsOnly;

    codes.insert("IS", "00");
    codes.insert("IU", "01");
    codes.insert("DB", "02");

    codes.insert("ADIS", "1010");
    codes.insert("ADIU", "1011");
    codes.insert("ADDB", "1012");

    codes.insert("SBIS", "1020");
    codes.insert("SBIU", "1021");
    codes.insert("SBDB", "1022");

    codes.insert("MLIS", "1030");
    codes.insert("MLIU", "1031");
    codes.insert("MLDB", "1032");

    codes.insert("DVIS", "1040");
    codes.insert("DVIU", "1041");
    codes.insert("DVDB", "1042");
}


QString Parser::parseToMemory(const QString &str)
{
    QString cell = str;
    if(cell.isEmpty())
        throw ;

     cell.replace(" ", "");
     bool command = isCommand(str);

     if(command)
     {
         if(!this->digitsOnly)
            cell.replace(0,commCodeLength,
                         codes.value(cell.mid(0,commCodeLength)));
     }
     else {

         if(!this->digitsOnly)
            cell.replace(0,numCodeLength,
                        codes.value(cell.mid(0,numCodeLength)));
     }

    if(cell.contains(QRegExp("\\D")))
        throw ;

    if(cell.length() > length)
        throw ;

    return cell;
}

bool Parser::isCommand(const QString &str)
{
    bool currCommand = false;
    bool currDigitsOnly  = (str[0].isDigit());

    if(currDigitsOnly)
        currCommand = (str[0] != '0');
    else
        currCommand =  (str.left(2) != "IS"
           && str.left(2) != "IU"
           && str.left(2) != "DB");
    return currCommand;
}

QString Parser::parseFromMemory(const QString &cell)
{
    QString str = cell;

    bool currDigitsOnly  = (str[0].isDigit());
    bool command = isCommand(str);

    if(currDigitsOnly != digitsOnly && !digitsOnly)
    {
        if (command){
            str.replace(0,commCodeLength,
                        codes.key(str.mid(0,commCodeLength)));
        }
        else {
            str.replace(0,numCodeLength,
                        codes.key(str.mid(0,numCodeLength)));
        }
    }
    else if (currDigitsOnly != digitsOnly && digitsOnly)
    {
        if (command){
            str.replace(0,commCodeLength,
                        codes.value(str.mid(0,commCodeLength)));
        }
        else {
            str.replace(0,numCodeLength,
                        codes.value(str.mid(0,numCodeLength)));
        }
    }
    return str;
}


void Parser::setDigitsOnly(bool digitsOnly)
{
    this->digitsOnly = digitsOnly;
}

bool  Parser::getDigitsOnly() const
{
    return this->digitsOnly;
}

Parser::~Parser()
{

}
