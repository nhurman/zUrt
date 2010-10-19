TEMPLATE = app
QT = core network
CONFIG += qt release warn_on console
TRANSLATIONS = locales/fr_FR.ts
DESTDIR = build/bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui
SOURCES = src/main.cpp \
 src/core/Arguments.cpp \
 src/core/Log.cpp \
 src/core/LogParser.cpp \
 src/core/Server.cpp \
 src/core/ZipFile.cpp \
 src/core/zUrt.cpp \
  \
 src/modules/Player.cpp \
 src/modules/Admin.cpp \
 src/modules/Ban.cpp
HEADERS += src/core/Arguments.h \
 src/core/Log.h \
 src/core/LogParser.h \
 src/core/Module.h \
 src/core/Server.h \
 src/core/Singleton.h \
 src/core/Sleep.h \
 src/core/ZipFile.h \
 src/core/zUrt.h \
  \
 src/modules/Player.h \
 src/modules/Admin.h \
 src/modules/Ban.h
