#ifndef QTSUDOKU_H
#define QTSUDOKU_H

#include <QWidget>
#include "sudoku.h"
#include <QColor>
struct Pos
{
    int x;
    int y;
    Pos(int x, int y);
};
inline Pos::Pos(int m, int n)
    : x(m), y(n)
{}

class QPainter;
class QMouseEvent;
class QKeyEvent;

class QtSudoku : public QWidget
{
    Q_OBJECT
public:
    explicit QtSudoku(QWidget* parent = 0);
    void SetVal(int val);
    enum MoveDirect {Up, Down, Left, Right};
    void MoveCurPos(MoveDirect d);

protected:
    virtual void paintEvent ( QPaintEvent* event );
    virtual void mouseMoveEvent ( QMouseEvent* event );
    virtual void mouseReleaseEvent ( QMouseEvent* event );

signals:

public slots:
    void Solve();
    void Reset();
private:

    static const int blocksize = 40;
    static const int viewsize = blocksize * 9;
    Sudoku sudoku;
    Pos curpos;

    void draw_grid(QPainter* painter);
    void draw_oneblock(QPainter* painter, int row, int col);
    void draw_curpos(QPainter* painter);

    QTransform curtransform;
    QTransform curtrans_r;
    Pos trans_point(const QPoint& p) const;
    QRect get_real_rect_by_pos(const Pos& p) const;
    void changepos(const Pos& p);

    QColor cur_color;
    QColor rect_color;
    QColor gridcolor;
    QColor backcolor_set;
    QColor fontcolor_set;
    QColor backcolor_unset;
    QColor fontcolor_unset;
    QColor get_font_color(int row, int col) const;
    QColor get_back_color(int row, int col) const;
    QString fontfamily;

};

inline QColor QtSudoku::get_font_color(int row, int col) const
{
    return sudoku.IsSet(row, col) ? fontcolor_set : fontcolor_unset;
}

inline QColor QtSudoku::get_back_color(int row, int col) const
{
    return sudoku.IsSet(row, col) ? backcolor_set : backcolor_unset;
}



#endif // QTSUDOKU_H
