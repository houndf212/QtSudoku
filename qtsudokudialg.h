#ifndef QTSUDOKUDIALG_H
#define QTSUDOKUDIALG_H

#include <QDialog>
#include <QPushButton>
#include "qtsudoku.h"

class QtSudokuDialg : public QDialog
{
public:
    QtSudokuDialg(QWidget* parent = 0);
    virtual void keyReleaseEvent ( QKeyEvent* event );
private:
    QtSudoku* qsudoku;
    QPushButton* btnsolve;
    QPushButton* btnclear;

};

#endif // QTSUDOKUDIALG_H
