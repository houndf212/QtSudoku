#include <QApplication>
#include <QTextCodec>
#include "qtsudokudialg.h"
#include "qtsudoku.h"

int main(int argc, char* argv[])
{
    QApplication app( argc, argv);

    QTextCodec *utf8 = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(utf8);

    QtSudokuDialg qtsudoku;
    qtsudoku.show();

    return app.exec();
}
