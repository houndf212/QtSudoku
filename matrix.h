#ifndef MATRIX_H
#define MATRIX_H
#include <array>
#include "defines.h"


// some help func
inline void get_group_topleft(int* rowindex, int* colindex, int row, int col)
{
    *rowindex = row / 3 * 3;
    *colindex = col / 3 * 3;
}

inline void get_index_from_groupnum(int* rowindex, int* colindex, int groupnum)
{
    assert(0 <= groupnum && groupnum < DF::kLen);

    *rowindex = groupnum / 3 * 3;
    *colindex = groupnum % 3 * 3;
}

class Matrix
{
public:
    Matrix();
    bool Solve();
    //use 0 for unset
    void GetFromArr(int arr[9][9]);
    void SetPos(int row, int col, int val);
    int GetPos(int row, int col) const;
    bool IsSet(int row, int col) const;
    void Print() const;
private:
    //also is the rule of sudoku
    bool check_val(int row, int col, int val) const;
    bool check_row(int row, int val) const;
    bool check_col(int col, int val) const;
    bool check_group(int row, int col, int val) const;

    //the _right for make sure sudoku is right.
    bool check_is_right() const;
    bool check_row_right(int row) const;
    bool check_col_right(int col) const;
    bool check_group_right(int groupindex) const;
private:
    std::array<std::array<int, DF::kLen>, DF::kLen> m;
};

#endif // MATRIX_H
