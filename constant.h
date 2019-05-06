#ifndef CONSTANT_H
#define CONSTANT_H

#include <memory.h>

class Constant:public Cell
{
public:
    Constant();
    Constant(const QString& cellStr);
    void setConstant(const QString& cellStr);
    Constant getCommand();
    ~Constant();
};

#endif // CONSTANT_H
