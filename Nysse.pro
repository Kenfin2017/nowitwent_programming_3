TEMPLATE = subdirs

SUBDIRS += \
	CourseLib \
	Game

CourseLib.subdir = course/CourseLib
Game.depends = CourseLib
