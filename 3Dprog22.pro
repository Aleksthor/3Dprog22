QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    Structures.cpp \
    camera.cpp \
    cube.cpp \
    curveo1.cpp \
    logger.cpp \
    mainwindow.cpp \
    octahedron.cpp \
    renderwindow.cpp \
    shader.cpp \
    surfaceo1.cpp \
    tetraeder.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp \
    writefile.cpp \
    xyz.cpp

HEADERS += \
    Structures.h \
    camera.h \
    cube.h \
    curveo1.h \
    logger.h \
    mainwindow.h \
    octahedron.h \
    renderwindow.h \
    shader.h \
    surfaceo1.h \
    tetraeder.h \
    trianglesurface.h \
    vertex.h \
    visualobject.h \
    writefile.h \
    xyz.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    plainshader.frag \
    plainshader.vert
