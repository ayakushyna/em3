#ifndef OPERATION_H
#define OPERATION_H

#include <QString>


struct Operation{
    QString name;
    void (*func) ();
};


#endif // OPERATION_H
