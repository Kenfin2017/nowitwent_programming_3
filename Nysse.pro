TEMPLATE = subdirs

SUBDIRS += \
	CourseLib \
        Game \
        UnitTest
CourseLib.subdir = Course/Course/CourseLib
Game.depends = CourseLib
UnitTest.depends = Game
