#include "parser.h"

Parser::Parser(const Settings &settings, bool digitsOnly)
                : length(settings.length),
                  numCodeLength(settings.numCodeLength),
                  commCodeLength(settings.commCodeLength)
{
    this->digitsOnly=digitsOnly;

    codes.insert("IU", "00");
    codes.insert("IS", "01");
    codes.insert("DB", "02");

    codes.insert("ASIU", "1000");
    codes.insert("ASIS", "1001");
    codes.insert("ASDB", "1002");

    codes.insert("ADIU", "1100");
    codes.insert("ADIS", "1101");
    codes.insert("ADDB", "1102");

    codes.insert("SBIU", "1200");
    codes.insert("SBIS", "1201");
    codes.insert("SBDB", "1202");

    codes.insert("MLIU", "1300");
    codes.insert("MLIS", "1301");
    codes.insert("MLDB", "1302");

    codes.insert("DVIU", "1400");
    codes.insert("DVIS", "1401");
    codes.insert("DMIU", "1410");
    codes.insert("DMIS", "1411");
    codes.insert("DVDB", "1402");

    codes.insert("INIU", "1500");
    codes.insert("INIS", "1501");
    codes.insert("INDB", "1502");

    codes.insert("OUIU", "1600");
    codes.insert("OUIS", "1601");
    codes.insert("OUDB", "1602");

    codes.insert("UTOS", "1701");
    codes.insert("UTOD", "1702");
    codes.insert("STOU", "1710");
    codes.insert("STOD", "1712");
    codes.insert("DTOU", "1720");
    codes.insert("DTOS", "1721");

    codes.insert("GOTO", "1801");
    codes.insert("GOIF", "1802");

    codes.insert("CMIU", "1900");
    codes.insert("CMIS", "1901");
    codes.insert("CMDB", "1902");

    codes.insert("STOP", "1099");
}

void Parser::toDigits(QString &str)
{
    bool command = isCommand(str);
    if(command)
    {
        if(codes.keys().contains(str.left(commCodeLength)))
        {
            str.replace(0,commCodeLength,
                        codes.value(str.left(commCodeLength)));

        }
        else
            str.replace(0,commCodeLength,QString(commCodeLength, '0'));

    }
    else {

        if(codes.keys().contains(str.left(numCodeLength)))
        {
            str.replace(0,numCodeLength,
                        codes.value(str.left(numCodeLength)));
        }
        else
            str.replace(0,numCodeLength,QString(numCodeLength, '0'));

    }
}

void Parser::toLetters(QString &str)
{
    bool command = isCommand(str);
    if (command){
        if(codes.values().contains(str.left(commCodeLength)))
        {
            str.replace(0,commCodeLength,
                        codes.key(str.left(commCodeLength)));
        }
        else
            str.replace(0,commCodeLength,"IU00");

    }
    else {
        if(codes.values().contains(str.left(numCodeLength)))
        {
            str.replace(0,numCodeLength,
                        codes.key(str.left(numCodeLength)));
        }
        else
            str.replace(0,numCodeLength,"IU");
    }
}


QString Parser::parseToMemory(const QString &str)
{
    QString cell = str;
    if(cell.isEmpty())
        throw ;

     cell.replace(" ", "");

     if(!digitsOnly)
        toDigits(cell);

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
        currCommand =  (  str.left(2) != "IU"
                       && str.left(2) != "IS"
                       && str.left(2) != "DB");
    return currCommand;
}



QString Parser::parseFromMemory(const QString &cell)
{
    QString str = cell;

    bool currDigitsOnly  = (str[0].isDigit());

    if(currDigitsOnly != digitsOnly && !digitsOnly)
    {
        toLetters(str);
    }
    else if (currDigitsOnly != digitsOnly && digitsOnly)
    {
        toDigits(str);
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
