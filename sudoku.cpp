#include "sudoku.h"
#include "checker.h"
#include <iostream>
using namespace std;
namespace{
// some help func
inline void get_group_topleft(int* rowindex, int* colindex, int row, int col)
{
    assert(checkBound(row, col));
    *rowindex = row / 3 * 3;
    *colindex = col / 3 * 3;
}

inline void get_index_from_groupnum(int* rowindex, int* colindex, int groupnum)
{
    assert(0<=groupnum && groupnum<DF::kLen);

    *rowindex = groupnum / 3 * 3;
    *colindex = groupnum % 3 * 3;
}

inline int rowcol2num(int row, int col)
{
    assert(checkBound(row, col));
    return row * DF::kLen + col;
}

inline void num2rowcol(int* row, int* col, int numval)
{
    assert(0<=numval && numval<DF::kLen*DF::kLen);

    *row = numval / DF::kLen;
    *col = numval % DF::kLen;
}
} //end namespace

bool Sudoku::Solve()
{
    if (!check_is_right())
    { return false; }
    else
    { return solve_r(*this, 0); }
}

void Sudoku::GetFromArr(const int arr[][9])
{
    for(int r = 0; r<DF::kLen; ++r)
    {
        for (int c = 0; c<DF::kLen; ++c)
        {
            assert(checkNum(arr[r][c]));
            m[r][c] = arr[r][c];
        }
    }
}

void Sudoku::SetPos(int row, int col, int val)
{
    assert(checkBound(row, col));
    assert(checkNum(val));
    m[row][col] = val;
}

int Sudoku::GetPos(int row, int col) const
{
    assert(checkBound(row, col));
    return m[row][col];
}

bool Sudoku::IsSet(int row, int col) const
{
    assert(checkBound(row, col));
    return m[row][col] != DF::kNone;
}

void Sudoku::Print() const
{
    for(int r = 0; r < DF::kLen; ++r)
    {
        for (int c = 0; c < DF::kLen; ++c)
        {
            std::cout << m[r][c] << ' ';
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void Sudoku::Clear()
{
    for (int i=0; i<DF::kLen; ++i)
        m[i].fill(DF::kNone);
}

bool Sudoku::solve_r(Sudoku &m, int num)
{
    if (num == DF::kLen*DF::kLen)
        return true;

    int row, col;
    num2rowcol(&row, &col, num);

    if (m.GetPos(row, col) != DF::kNone)
    { return solve_r(m, ++num); }

    for (int n=1; n<=9; ++n)
    {
        if (m.check_val(row, col, n))
        {
            m.SetPos(row, col, n);
            int lnum = num + 1;
            if (!solve_r(m, lnum))
            { m.ResetPos(row, col); }
            else
            { return true; }
        }
    }
    return false;
}

bool Sudoku::check_val(int row, int col, int val) const
{
    assert (0<=row && row<DF::kLen);
    assert (0<val && val<=9);

    return check_row(row, val)
            && check_col(col, val)
            && check_group(row, col, val);
}

bool Sudoku::check_row(int row, int val) const
{
    for (int c = 0; c < DF::kLen; ++c)
    {
        if (m[row][c] == val)
        { return false; }
    }

    return true;
}

bool Sudoku::check_col(int col, int val) const
{
    for (int r = 0; r < DF::kLen; ++r)
    {
        if (m[r][col] == val)
        { return false; }
    }

    return true;
}

bool Sudoku::check_group(int row, int col, int val) const
{
    int rowindex, colindex;
    get_group_topleft(&rowindex, &colindex, row, col);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if(m[rowindex + i][colindex + j] == val)
            { return false; }

    return true;
}

bool Sudoku::check_is_right() const
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

bool Sudoku::check_row_right(int row) const
{
    Checker ck;
    for (int c=0; c<DF::kLen; ++c)
    {
        if (!ck.set(m[row][c]))
            return false;
    }
    return true;
}

bool Sudoku::check_col_right(int col) const
{
    Checker ck;
    for (int r=0; r<DF::kLen; ++r)
    {
        if (!ck.set(m[r][col]))
            return false;
    }
    return true;
}

bool Sudoku::check_group_right(int groupindex) const
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

            if (!ck.set(m[cur_row][cur_col]))
                return false;
        }
    }
    return true;
}
