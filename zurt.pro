TEMPLATE = app
QT = core \
    network \
    sql
CONFIG += qt \
    release \
    warn_on \
    console
DESTDIR = build/bin
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
UI_DIR = build/ui
SOURCES = src/main.cpp \
    src/coeur/Serveur.cpp \
    src/coeur/Log.cpp \
    src/coeur/zUrt.cpp \
    src/coeur/ParseurLog.cpp \
    src/modules/Admin.cpp
HEADERS += src/coeur/Serveur.h \
    src/coeur/Log.h \
    src/coeur/Singleton.h \
    src/coeur/zUrt.h \
    src/coeur/Module.h \
    src/coeur/ParseurLog.h \
    src/modules/Admin.h
