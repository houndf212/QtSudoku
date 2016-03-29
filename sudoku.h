#ifndef SUDOKU_H
#define SUDOKU_H
#include <array>
#include "defines.h"

class Sudoku
{
public:
    bool Solve();
    //use 0 for unset
    void GetFromArr(const int arr[9][9]);
    void SetPos(int row, int col, int val);
    void ResetPos(int row, int col) { m[row][col]=DF::kNone; }
    int GetPos(int row, int col) const;
    bool IsSet(int row, int col) const;
    void Print() const;
    void Clear();
private:
    static bool solve_r(Sudoku& m, int num);
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

#endif // SUDOKU_H
