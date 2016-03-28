#include "checker.h"

Checker::Checker()
{
    s.reset();
}

bool Checker::set(int i)
{
    assert(0<=i && i<=DF::kLen);

    if (i!=DF::kNone)
    {
        if (s.test(i))
        { return false; }
        else
        {
            s.set(i);
            return true;
        }
    }
    else
    { return true; }
}

