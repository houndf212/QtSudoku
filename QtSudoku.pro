QT += widgets
CONFIG += c++11

TEMPLATE      = app
HEADERS += \
    sudoku.h \
    qtsudoku.h \
    qtsudokudialg.h \
    matrix.h \
    defines.h \
    checker.h
SOURCES += \
    sudoku.cc \
    main.cpp \
    qtsudoku.cpp \
    qtsudokudialg.cpp \
    matrix.cpp \
    defines.cpp \
    checker.cpp
