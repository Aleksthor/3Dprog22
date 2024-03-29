QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering


SOURCES += main.cpp \
    Structures.cpp \
    basicmesh.cpp \
    bspline.cpp \
    camera.cpp \
    collider.cpp \
    component.cpp \
    cube.cpp \
    cubemap.cpp \
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
    material.cpp \
    movers.cpp \
    mymath.cpp \
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
    staticmesh.cpp \
    surfaceo1.cpp \
    tetraeder.cpp \
    texture.cpp \
    texture2d.cpp \
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
    bspline.h \
    camera.h \
    collider.h \
    component.h \
    cube.h \
    cubemap.h \
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
    material.h \
    movers.h \
    mymath.h \
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
    staticmesh.h \
    stb_image.h \
    surfaceo1.h \
    tetraeder.h \
    texture.h \
    texture2d.h \
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
    cubemap.frag \
    cubemap.vert \
    lightShader.frag \
    lightShader.vert \
    plainshader.frag \
    plainshader.vert \
    textureshader.frag \
    textureshader.vert
