#ifndef DEFINES_H
#define DEFINES_H
#include <cassert>

namespace DF{
const int kNone = 0;
const int kLen = 9;
}

inline bool checkBound(int n)
{
    return 0<=n && n<DF::kLen;
}

inline bool checkBound(int r, int c)
{
    return checkBound(r) && checkBound(c);
}

inline bool checkNum(int v)
{
    return 0<=v && v<=9;
}
#endif // DEFINES_H
