#include "qtsudokudialg.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>

QtSudokuDialg::QtSudokuDialg(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Sudoku Solver");
    QVBoxLayout* mainlayout = new QVBoxLayout;
    qsudoku = new QtSudoku(this);

    btnsolve = new QPushButton(this);
    btnclear = new QPushButton(this);

    btnsolve->setFocusPolicy(Qt::NoFocus);
    btnclear->setFocusPolicy(Qt::NoFocus);

    btnsolve->setText("&Solve Sudoku");
    btnclear->setText("&Clear");
    QHBoxLayout* btnlayout = new QHBoxLayout;
    //btnlayout->addStretch();
    btnlayout->addWidget(btnclear);
    btnlayout->addWidget(btnsolve);

    mainlayout->addWidget(qsudoku);
    //mainlayout->addStretch();
    mainlayout->addLayout(btnlayout);

    setLayout(mainlayout);
    connect(btnsolve, SIGNAL(clicked()), qsudoku, SLOT(Solve()));
    connect(btnclear, SIGNAL(clicked()), qsudoku, SLOT(Reset()));
}

void QtSudokuDialg::keyReleaseEvent(QKeyEvent* e)
{
    int key = e->key();
    int val = -1;

    switch(key)
    {
    case Qt::Key_Backspace:
    case Qt::Key_0:
        val = 0;
        break;

    case Qt::Key_1:
        val = 1;
        break;

    case Qt::Key_2:
        val = 2;
        break;

    case Qt::Key_3:
        val = 3;
        break;

    case Qt::Key_4:
        val = 4;
        break;

    case Qt::Key_5:
        val = 5;
        break;

    case Qt::Key_6:
        val = 6;
        break;

    case Qt::Key_7:
        val = 7;
        break;

    case Qt::Key_8:
        val = 8;
        break;

    case Qt::Key_9:
        val = 9;
        break;

    case Qt::Key_Right:
        qsudoku->MoveCurPos(QtSudoku::Right);
        break;

    case Qt::Key_Left:
        qsudoku->MoveCurPos(QtSudoku::Left);
        break;

    case Qt::Key_Up:
        qsudoku->MoveCurPos(QtSudoku::Up);
        break;

    case Qt::Key_Down:
        qsudoku->MoveCurPos(QtSudoku::Down);
        break;

    default:
        return;
    }

    if(0 <= val && val <= 9)
    { qsudoku->SetVal(val); }
}
