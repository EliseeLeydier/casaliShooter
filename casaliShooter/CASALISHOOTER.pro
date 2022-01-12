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

include(/Users/elisee/OneDrive - Aix-Marseille Université/SAE/3/R.101/CS/CasaliShooter-main/MinGL2/mingl.pri)

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
