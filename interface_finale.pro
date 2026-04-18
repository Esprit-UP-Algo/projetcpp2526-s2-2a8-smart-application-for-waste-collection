QT += core gui widgets sql printsupport charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    client.cpp \
    collecte.cpp \
    connection.cpp \
    conteneur.cpp \
    employe.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mdp_oublier.cpp \
    parametres_employe.cpp \
    recyclage.cpp \
    smsclient.cpp

HEADERS += \
    client.h \
    collecte.h \
    connection.h \
    conteneur.h \
    employe.h \
    login.h \
    mainwindow.h \
    map.h \
    mdp_oublier.h \
    parametres_employe.h \
    recyclage.h \
    smsclient.h

FORMS += \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    RS7.qrc