#include "sudoku.h"
#include <stdlib.h>
#include "qtsudoku.h"
#include <QApplication>
#include <QTextCodec>
#include "qtsudokudialg.h"
#include "matrix.h"
int main(int argc, char* argv[])
{
//    QApplication app( argc, argv);

//    QTextCodec *utf8 = QTextCodec::codecForName("utf-8");
//    QTextCodec::setCodecForLocale(utf8);

//    QtSudokuDialg qtsudoku;
//    qtsudoku.show();

//    return app.exec();
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

    Sudoku sd;
    sd.GetFromArr(arr);
    sd.Solve();
    sd.Print();
    Matrix m;
}
