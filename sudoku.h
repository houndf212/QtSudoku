#ifndef SUDOKU_H
#define SUDOKU_H
#include <assert.h>
class Sudoku
{
public:
    static const int kNone = 0;
public:
    Sudoku();
    bool Solve();
    //use 0 for unset
    void GetFromArr(int arr[9][9]);
    void SetPos(int row, int col, int val);
    int GetPos(int row, int col) const;
    bool IsSet(int row, int col) const;
    void Print() const;
    void Clear() { clear(); }
private:
    Sudoku& operator=(const Sudoku&);
    Sudoku(const Sudoku&);
    void clear();
    void clear_try(int numval);
    bool check_is_right() const;
    bool mysolve(int numval);

    //also is the rule of sudoku
    bool check_val(int row, int col, int val) const;
    bool check_row(int row, int val) const;
    bool check_col(int col, int val) const;
    bool check_group(int row, int col, int val) const;

    //the _right for make sure sudoku is right.
    bool check_row_right(int row) const;
    bool check_col_right(int col) const;
    bool check_group_right(int groupindex) const;

    enum SetFlag {kUnset, kSet, kTryset};
    SetFlag flags[9][9];
    int matrix[9][9];

};

inline bool assert_bound(int row, int col)
{
    assert(0 <= row && row < 9);
    assert(0 <= col && col < 9);
    return true;
}

inline bool assert_val(int val)
{
    assert(1 <= val && val <= 9);
    return true;
}

inline bool Sudoku::IsSet(int row, int col) const
{
    assert(assert_bound(row, col));
    return flags[row][col] == kSet ? true : false;
}

inline int Sudoku::GetPos(int row, int col) const
{
    assert(assert_bound(row, col));
    return flags[row][col] != kUnset ? matrix[row][col] : 0;
}

#endif // SUDOKU_H
