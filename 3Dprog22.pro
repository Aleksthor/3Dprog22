QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    Structures.cpp \
    basicmesh.cpp \
    camera.cpp \
    collider.cpp \
    component.cpp \
    cube.cpp \
    curveo1.cpp \
    disc.cpp \
    door.cpp \
    gameobject.cpp \
    house.cpp \
    interpo2.cpp \
    landscape.cpp \
    line.cpp \
    logger.cpp \
    mainwindow.cpp \
    movers.cpp \
    neuralnetwork.cpp \
    npco2.cpp \
    octahedron.cpp \
    parabel.cpp \
    perlinnoise.cpp \
    physicscomponent.cpp \
    physicsspherecollider.cpp \
    pickups.cpp \
    player.cpp \
    pointso2.cpp \
    ppm.cpp \
    quadtree.cpp \
    renderwindow.cpp \
    scene.cpp \
    shader.cpp \
    spherecollider.cpp \
    surfaceo1.cpp \
    tetraeder.cpp \
    texture.cpp \
    transform.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp \
    visualobjectcomponent.cpp \
    writefile.cpp \
    xyz.cpp

HEADERS += \
    Structures.h \
    basicmesh.h \
    camera.h \
    collider.h \
    component.h \
    cube.h \
    curveo1.h \
    disc.h \
    door.h \
    gameobject.h \
    house.h \
    interpo2.h \
    landscape.h \
    line.h \
    logger.h \
    mainwindow.h \
    movers.h \
    neuralnetwork.h \
    neuron.h \
    npco2.h \
    octahedron.h \
    parabel.h \
    perlinnoise.h \
    physicscomponent.h \
    physicsspherecollider.h \
    pickups.h \
    player.h \
    pointso2.h \
    ppm.h \
    quadtree.h \
    renderwindow.h \
    scene.h \
    shader.h \
    spherecollider.h \
    stb_image.h \
    surfaceo1.h \
    tetraeder.h \
    texture.h \
    transform.h \
    trianglesurface.h \
    uniforms.h \
    vertex.h \
    visualobject.h \
    visualobjectcomponent.h \
    writefile.h \
    xyz.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    plainshader.frag \
    plainshader.vert \
    textureshader.frag \
    textureshader.vert
