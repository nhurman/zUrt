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
    src/Log.cpp
HEADERS += src/Log.h
