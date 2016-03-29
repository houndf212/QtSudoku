#ifndef CHECKER_H
#define CHECKER_H
#include <bitset>
#include "defines.h"

class Checker
{
public:
    Checker();
    bool set(int i);
private:
    std::bitset<DF::kLen+1> s;
};

#endif // CHECKER_H
