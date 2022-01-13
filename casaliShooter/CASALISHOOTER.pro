TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        check.cpp \
        generate.cpp \
        main.cpp \
        bgtext.cpp \
        menu.cpp \
        move.cpp \
        yaml.cpp

include(MinGL2/mingl.pri)

HEADERS += \
    bgtext.h \
    check.h \
    enemyStruct.h \
    generate.h \
    menu.h \
    move.h \
    mugstruct.h \
    playersStruct.h \
    yaml.h
