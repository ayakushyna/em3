#include "em3.h"

EM3::EM3(): memory(), RA(0), RC(memory[0]),
            Z(0), C(0), S(0), O(0)
{

}

const Memory& EM3::getMemory() const
{
    return this->memory;
}

void EM3::setMemory(const Memory& memory)
{
    this->memory = memory;
}

EM3::~EM3(){}
