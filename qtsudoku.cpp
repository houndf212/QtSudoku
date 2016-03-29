#include "qtsudoku.h"
#include <QPainter>
#include <QLine>
#include <QRect>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

QtSudoku::QtSudoku(QWidget* parent) :
    QWidget(parent),
    curpos(0, 0)
{
    int arr[9][9] =
    {
        {8, 0, 0,  0, 0, 0,  0, 0, 0}, //1
        {0, 0, 3,  6, 0, 0,  0, 0, 0}, //2
        {0, 7, 0,  0, 9, 0,  2, 0, 0}, //3

        {0, 5, 0,  0, 0, 7,  0, 0, 0}, //4
        {0, 0, 0,  0, 4, 5,  7, 0, 0}, //5
        {0, 0, 0,  1, 0, 0,  0, 3, 0}, //6

        {0, 0, 1,  0, 0, 0,  0, 6, 8}, //7
        {0, 0, 8,  5, 0, 0,  0, 1, 0}, //8
        {0, 9, 0,  0, 0, 0,  4, 0, 0}  //9
    };
    sudoku.GetFromArr(arr);
    cur_color = Qt::blue;
    rect_color = Qt::green;
    gridcolor = Qt::black;
    fontcolor_set = Qt::red;
    fontcolor_unset = Qt::black;
    backcolor_set = backcolor_unset = Qt::cyan;
    //setMouseTracking(true); //cause cpu up!
    setMinimumSize(viewsize, viewsize);
    fontfamily = "Arial";
}
void QtSudoku::Solve()
{
    bool b = sudoku.Solve();

    if (b)
    { update(); }
    else
    {
        QMessageBox::warning(this, "Sudoku", "It seems no answer, please check sudoku!");
    }
}

void QtSudoku::Reset()
{
    sudoku.Clear();
    update();
}
void QtSudoku::paintEvent(QPaintEvent* )
{
    QPainter painter(this);

    painter.setRenderHints(QPainter::TextAntialiasing|QPainter::Antialiasing, true);
    painter.setWorldMatrixEnabled(false);
    painter.setViewport(0, 0, this->width(), this->height());
    painter.setWindow(0, 0, viewsize, viewsize);

    for (int r = 0; r < 9; ++r)
        for (int c = 0; c < 9; ++c)
        { draw_oneblock(&painter, r, c); }

    draw_curpos(&painter);
    draw_grid(&painter);
    //curtransform = painter.worldTransform(); //same as transform()
    //curtransform = painter.transform(); //不行
    assert(painter.worldTransform() == painter.transform());
    //curtransform = painter.combinedTransform().inverted(); //very nice
    curtrans_r = painter.combinedTransform();
    curtransform = curtrans_r.inverted();
    //curtransform = painter.deviceTransform().inverted(); //不准
}


Pos QtSudoku::trans_point(const QPoint& p) const
{
    QPointF ff(p.x(), p.y());
    QPointF t = curtransform.map(ff);
    Pos pp(t.x() / blocksize, t.y() / blocksize);
    return pp;
}

QRect QtSudoku::get_real_rect_by_pos(const Pos& p) const
{
    const QRect rect1(p.x*blocksize, p.y*blocksize, blocksize, blocksize);
    const QRect rect2 = curtrans_r.mapRect(rect1);
    return rect2;
}

void QtSudoku::mouseMoveEvent(QMouseEvent* e)
{
    QPoint clickpos = e->pos();
    const Pos p = trans_point(clickpos);
    changepos(p);
}

void QtSudoku::mouseReleaseEvent(QMouseEvent* e)
{
    if (!(e->button() & Qt::LeftButton))
        return;
    QPoint clickpos = e->pos();
    const Pos p = trans_point(clickpos);
    changepos(p);
}

void QtSudoku::changepos(const Pos& p)
{
    if (curpos.x == p.x && curpos.y == p.y)
    { return; }

    //由于变换可能超出边界，所以加上保护
    if (!(0 <= p.x && p.x < 9 && 0 <= p.y && p.y < 9))
    { return; }

    Pos old = curpos;
    curpos.x = p.x;
    curpos.y = p.y;
    //update old curpos
    if (old.x!=curpos.x || old.y!=curpos.y)
        update(get_real_rect_by_pos(old));

    update(get_real_rect_by_pos(curpos));
}

void QtSudoku::draw_grid(QPainter* painter)
{
//    QRect rect1(0, 0, viewsize, viewsize * 2 / 3);
//    QRect rect2(0, viewsize / 3, viewsize, viewsize * 2 / 3);
//    QRect rect3(viewsize / 3, 0, viewsize / 3, viewsize);
    painter->setPen(QPen(gridcolor, 0.8));

    QRect rect1(0, 0, viewsize, viewsize);
    QRect rect2(0, viewsize/3, viewsize, viewsize/3);
    QRect rect3(viewsize/3, 0, viewsize/3, viewsize);
    painter->drawRect(rect1);
    painter->drawRect(rect2);
    painter->drawRect(rect3);
}

void QtSudoku::draw_oneblock(QPainter* painter, int row, int col)
{
    QRect rect1(col * blocksize, row * blocksize, blocksize, blocksize);

    QColor backcolor = get_back_color(row, col);

    painter->fillRect(rect1, backcolor);
    painter->setPen(rect_color);
    painter->drawRect(rect1);


    int val = sudoku.GetPos(row, col);

    if (val == 0)
    { return; }

    QColor fontcolor = get_font_color(row, col);
    painter->setPen(fontcolor);

    QFont font;
    font.setPixelSize(rect1.width() * 4 / 5);
    font.setFamily(fontfamily);
    painter->setFont(font);
    painter->drawText(rect1, Qt::AlignCenter, QString("%1").arg(val));
}

void QtSudoku::draw_curpos(QPainter* painter)
{

    int col = curpos.x;
    int row = curpos.y;
    QRect rect1(col * blocksize, row * blocksize, blocksize, blocksize);

    painter->fillRect(rect1, cur_color);
    painter->setPen(rect_color);
    painter->drawRect(rect1);

    int val = sudoku.GetPos(row, col);

    if (val == 0)
    { return; }

    QColor fontcolor = get_font_color(row, col);
    painter->setPen(fontcolor);

    QFont font;
    font.setPixelSize(rect1.width() * 4 / 5);
    font.setFamily(fontfamily);
    painter->setFont(font);

    painter->drawText(rect1, Qt::AlignCenter, QString("%1").arg(val));
}

void QtSudoku::MoveCurPos(MoveDirect d)
{
    int dx = 0,  dy = 0;

    switch(d)
    {
    case Up:
        dy = -1;
        break;

    case Down:
        dy = 1;
        break;

    case Left:
        dx = -1;
        break;

    case Right:
        dx = 1;
        break;
    }

    changepos(Pos(curpos.x+dx, curpos.y+dy));
}

void QtSudoku::SetVal(int val)
{
    assert(0 <= val && val <= 9);
    sudoku.SetPos(curpos.y, curpos.x, val);
    update(get_real_rect_by_pos(curpos));
}
