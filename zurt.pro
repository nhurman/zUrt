TEMPLATE = app
QT = core network sql
CONFIG += qt release warn_on console
DESTDIR = build/bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui
SOURCES = \
 src/main.cpp \
 src/coeur/Arguments.cpp \
 src/coeur/Log.cpp \
 src/coeur/ParseurLog.cpp \
 src/coeur/Serveur.cpp \
 src/coeur/zUrt.cpp \
 \
 src/modules/Joueur.cpp \
 src/modules/Admin.cpp \
 src/modules/Bonjour.cpp
HEADERS += \
 src/coeur/Arguments.h \
 src/coeur/Log.h \
 src/coeur/Module.h \
 src/coeur/ParseurLog.h \
 src/coeur/Serveur.h \
 src/coeur/Singleton.h \
 src/coeur/Sleep.h \
 src/coeur/zUrt.h \
 \
 src/modules/Joueur.h \
 src/modules/Admin.h \
 src/modules/Bonjour.h
