#include "matrix.h"
#include "checker.h"
using namespace std;

Matrix::Matrix()
{

}

bool Matrix::check_row(int row, int val) const
{
    assert (0<=row && row<DF::kLen);
    assert (0<val && val <9);

    for (int c = 0; c < DF::kLen; ++c)
    {
        if (m[row][c] == val)
        { return false; }
    }

    return true;
}

bool Matrix::check_col(int col, int val) const
{
    assert (0<=col && row<DF::kLen);
    assert (0<val && val <9);

    for (int r = 0; r < DF::kLen; ++r)
    {
        if (m[r][col] == val)
        { return false; }
    }

    return true;
}

bool Matrix::check_group(int row, int col, int val) const
{
    int rowindex, colindex;
    get_group_topleft(&rowindex, &colindex, row, col);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if(m[rowindex + i][colindex + j] == val)
            { return false; }

    return true;
}

bool Matrix::check_is_right() const
{
    for(int i = 0; i < 9; ++i)
    {
        if (!check_row_right(i)
                || !check_col_right(i)
                || !check_group_right(i))
        { return false; }
    }

    return true;
}

bool Matrix::check_row_right(int row) const
{
    assert(0<=row && row <DF::kLen);
    Checker ck;
    for (int c=0; c<DF::kLen; ++c)
    {
        if (!ck.set(m[row][c]))
            return false;
    }
    return true;
}

bool Matrix::check_col_right(int col) const
{
    assert(0<=col && col <DF::kLen);
    Checker ck;
    for (int r=0; r<DF::kLen; ++r)
    {
        if (!ck.set(m[r][col]))
            return false;
    }
    return true;
}

bool Matrix::check_group_right(int groupindex) const
{
    Checker ck;

    int rowindex;
    int colindex;
    get_index_from_groupnum(&rowindex, &colindex, groupindex);

    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            int cur_row = rowindex + r;
            int cur_col = colindex + c;

            if (!ck.set(cur_row, cur_col))
                return false;
        }
    }
    return true;
}
