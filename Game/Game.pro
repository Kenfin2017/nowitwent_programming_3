TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    city.cc \
    creategame.cc \
    gamedialog.cc \
    gamelogic.cc \
    gamemainwindow.cc \
    main.cc \
    treasure.cc

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../course/CourseLib/

DEPENDPATH += \
    $$PWD/../course/CourseLib/

RESOURCES += \
    $$PWD/../course/CourseLib/offlinedata.qrc

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../course/CourseLib/libCourseLib.a

HEADERS += \
    city.hh \
    creategame.hh \
    gamedialog.hh \
    gamelogic.hh \
    gamemainwindow.hh \
    treasure.hh

FORMS += \
    gamedialog.ui \
    gamemainwindow.ui
