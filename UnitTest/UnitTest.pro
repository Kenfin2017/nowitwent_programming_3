TARGET = tst_statistic
TEMPLATE = app

QT += testlib
QT += gui core widgets multimedia

CONFIG += qt warn_on depend_includepath testcase

INCLUDEPATH += \
    $$PWD/../Course/Course/CourseLib/ \
    $$PWD/../Game/

DEPENDPATH += \
    $$PWD/../Course/Course/CourseLib/ \
    $$PWD/../Game/
HEADERS += \
            ../Course/Course/CourseLib/actors/nysse.hh \
            ../Course/Course/CourseLib/actors/passenger.hh \
            ../Course/Course/CourseLib/actors/stop.hh \
            ../Course/Course/CourseLib/core/location.hh \
            ../Course/Course/CourseLib/errors/gameerror.hh \
            ../Course/Course/CourseLib/errors/initerror.hh \
            ../Course/Course/CourseLib/interfaces/icity.hh \
            ../Course/Course/CourseLib/interfaces/ipassenger.hh \
            ../Course/Course/CourseLib/interfaces/istatistics.hh \
            ../Course/Course/CourseLib/interfaces/istop.hh \
            ../Course/Course/CourseLib/offlinereader.hh \
            ../Game/core/city.hh \
            ../Game/core/gamelogic.hh \
            ../Game/core/statistic.hh \
            ../Game/graphics/bus_actoritem.hh \
            ../Game/graphics/player_actoritem.hh \
            ../Game/graphics/treasureItem.hh \
            tst_statistic.hh

SOURCES +=  \
            ../Course/Course/CourseLib/actors/nysse.cc \
            ../Course/Course/CourseLib/actors/passenger.cc \
            ../Course/Course/CourseLib/actors/stop.cc \
            ../Course/Course/CourseLib/core/location.cc \
            ../Course/Course/CourseLib/errors/gameerror.cc \
            ../Course/Course/CourseLib/errors/initerror.cc \
            ../Course/Course/CourseLib/offlinereader.cc \
            ../Game/core/city.cc \
            ../Game/core/gamelogic.cc \
            ../Game/graphics/bus_actoritem.cc \
            ../Game/graphics/player_actoritem.cc \
            ../Game/graphics/treasureItem.cc \
            tst_statistic.cpp \
            ../Game/core/statistic.cc

RESOURCES += \
    ../Game/offlinedata.qrc

DISTFILES +=
