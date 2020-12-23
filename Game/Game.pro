TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    ../Course/Course/CourseLib/actors/nysse.cc \
    ../Course/Course/CourseLib/actors/passenger.cc \
    ../Course/Course/CourseLib/actors/stop.cc \
    ../Course/Course/CourseLib/core/location.cc \
    ../Course/Course/CourseLib/errors/gameerror.cc \
    ../Course/Course/CourseLib/offlinereader.cc \
    core/city.cc \
    core/gamelogic.cc \
    core/statistic.cc \
    creategame.cc \
    graphics/digitalclock.cc \
    graphics/gameoverdialog.cc \
    graphics/gamemainwindow.cc \
    graphics/gamedialog.cc \
    main.cc \
    graphics/treasureItem.cc \
    graphics/bus_actoritem.cc \
    graphics/player_actoritem.cc

INCLUDEPATH += \
    $$PWD/../Course/Course/CourseLib/

DEPENDPATH += \
    $$PWD/../Course/Course/CourseLib/

RESOURCES += \
    $$PWD/offlinedata.qrc

HEADERS += \
    ../Course/Course/CourseLib/actors/nysse.hh \
    ../Course/Course/CourseLib/actors/passenger.hh \
    ../Course/Course/CourseLib/actors/stop.hh \
    ../Course/Course/CourseLib/core/location.hh \
    ../Course/Course/CourseLib/errors/gameerror.hh \
    ../Course/Course/CourseLib/interfaces/iactor.hh \
    ../Course/Course/CourseLib/interfaces/ipassenger.hh \
    ../Course/Course/CourseLib/interfaces/istop.hh \
    ../Course/Course/CourseLib/interfaces/ivehicle.hh \
    ../Course/Course/CourseLib/offlinereader.hh \
    core/city.hh \
    core/statistic.hh \
    creategame.hh \
    graphics/digitalclock.hh \
    graphics/gameoverdialog.hh \
    graphics/gamedialog.hh \
    core/gamelogic.hh \
    graphics/gamemainwindow.hh \
    graphics/treasureItem.hh \
    graphics/bus_actoritem.hh \
    graphics/player_actoritem.hh

FORMS += \
    graphics/gameoverdialog.ui \
    graphics/gamedialog.ui \
    graphics/gamemainwindow.ui
