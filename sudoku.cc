#include "sudoku.h"
#include <iostream>

namespace
{
int rowcol2num(int row, int col)
{
    assert(0 <= row && row < 9);
    assert(0 <= col && col < 9);

    return row * 9 + col;
}

void num2rowcol(int* row, int* col, int numval)
{
    assert(0 <= numval && numval <= 80);
    assert(row != 0 && col != 0);

    *row = numval / 9;
    *col = numval % 9;
}
}

void Sudoku::clear()
{
    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            matrix[r][c] = kNone;
            flags[r][c] = kUnset;
        }
    }
}

Sudoku::Sudoku()
{
    clear();
}

void Sudoku::GetFromArr(int arr[9][9])
{
    for(int r = 0; r < 9; ++r)
    {
        for (int c = 0; c != 9; ++c)
        {
            assert(0 <= arr[r][c] && arr[r][c] <= 9);
            matrix[r][c] = arr[r][c];

            if (matrix[r][c] == 0)
            { flags[r][c] = kUnset; }
            else
            { flags[r][c] = kSet; }
        }
    }
}

void Sudoku::Print() const
{
    for(int r = 0; r < 9; ++r)
    {
        for (int c = 0; c != 9; ++c)
        {
            std::cout << matrix[r][c] << ' ';
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void Sudoku::SetPos(int row, int col, int val)
{
    assert(assert_bound(row, col));
    assert(0 <= val && val <= 9);
    matrix[row][col] = val;

    if (val != 0)
    { flags[row][col] = kSet; }
    else
    { flags[row][col] = kUnset; }

}

bool Sudoku::Solve()
{
#ifndef NDEBUG

    //make sure matrix unset is 0, and set is 1~9, so sudoku is in good status
    for (int r = 0; r < 0; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            const int val = matrix[r][c];
            const SetFlag flag = flags[r][c];

            if (flag != kUnset)
            { assert(1 <= val && val <= 9); }
            else
            { assert(val == 0); }
        }
    }

    bool check = check_is_right();

    if (!check)
    { return false; }

    bool s = mysolve(0);

    if (!s)
    { return false; }

    return true;
#else
    return check_is_right() && mysolve(0);
#endif
}

void Sudoku::clear_try(int numval)
{
    assert(0 <= numval && numval < 81);

    for (int num = numval; num != 9 * 9; ++num)
    {
        int row, col;
        num2rowcol(&row, &col, num);

        if (!IsSet(row, col))
        { matrix[row][col] = kNone; }
    }
}

bool Sudoku::mysolve(int numval)
{
    assert(0 <= numval && numval <= 81);
#ifndef NDEBUG
    static int count = 0;
    count++;
    std::cout<<count<<std::endl;
#endif

    if (numval == 81)
    { return true; }

    int row, col;
    num2rowcol(&row, &col, numval);

    if (IsSet(row, col))
    { return mysolve(numval + 1); }

    //first must set val to 0, so check_val can check 1~9
    matrix[row][col] = kNone;

    for (int trynum = 1; trynum <= 9; ++trynum)
    {
        if (!check_val(row, col, trynum))
        { continue; }

        matrix[row][col] = trynum;
        flags[row][col] = kTryset;
        const bool b = mysolve(numval + 1);

        if (b == true)
        { return true; }
    }

    //ensure check_val wroks right;
    clear_try(numval);
    return false;

}
bool Sudoku::check_val(int row, int col, int val) const
{
    return check_row(row, val)
           && check_col(col, val)
           && check_group(row, col, val);
}

bool Sudoku::check_row(int row, int val) const
{
    for (int c = 0; c < 9; ++c)
    {
        if (matrix[row][c] == val)
        { return false; }
    }

    return true;
}

bool Sudoku::check_col(int col, int val) const
{
    for (int r = 0; r < 9; ++r)
    {
        if (matrix[r][col] == val)
        { return false; }
    }

    return true;
}

namespace
{
inline void get_group_topleft(int* rowindex, int* colindex, int row, int col)
{
    *rowindex = row / 3 * 3;
    *colindex = col / 3 * 3;
}
}

bool Sudoku::check_group(int row, int col, int val) const
{
    int rowindex, colindex;
    get_group_topleft(&rowindex, &colindex, row, col);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if(matrix[rowindex + i][colindex + j] == val)
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

namespace
{
void arr_init(bool* arr, int size)
{
    for(int i = 0; i < size; ++i)
    {
        arr[i] = false;
    }
}
}

bool Sudoku::check_row_right(int row) const
{
    bool arr[10];
    arr_init(arr, sizeof(arr) / sizeof(arr[0]));

    for(int col = 0; col < 9; ++col)
    {
        if (!IsSet(row, col))
        { continue; }

        const int num = matrix[row][col];

        if (arr[num] == true)
        { return false; }
        else
        { arr[num] = true; }
    }

    return true;
}

bool Sudoku::check_col_right(int col) const
{
    bool arr[10];
    arr_init(arr, 10);

    for(int row = 0; row < 9; ++row)
    {
        if (!IsSet(row, col))
        { continue; }

        const int num = matrix[row][col];

        if (arr[num] == true)
        { return false; }
        else
        { arr[num] = true; }
    }

    return true;
}
namespace
{
inline void get_index_from_groupnum(int* rowindex, int* colindex, int groupnum)
{
    assert(rowindex != 0);
    assert(colindex != 0);
    assert(0 <= groupnum && groupnum < 9);

    *rowindex = groupnum / 3 * 3;
    *colindex = groupnum % 3 * 3;
}
}
bool Sudoku::check_group_right(int groupnum) const
{
    bool arr[10];
    arr_init(arr, 10);

    int rowindex;
    int colindex;
    get_index_from_groupnum(&rowindex, &colindex, groupnum);

    for (int r = 0; r < 3; ++r)
    {
        for (int c = 0; c < 3; ++c)
        {
            const int cur_row = rowindex + r;
            const int cur_col = colindex + c;

            if (!IsSet(cur_row, cur_col))
            { continue; }

            const int num = matrix[cur_row][cur_col];

            if (arr[num] == true)
            { return false; }
            else
            { arr[num] = true; }
        }
    }

    return true;
}
